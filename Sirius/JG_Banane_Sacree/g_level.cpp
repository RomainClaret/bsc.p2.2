/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#include "g_level.h"
#include "g_gameboard.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <QList>

#include "observer_enemy.h"
#include "character/factory_character.h"

#include "surface/g_surface.h"
#include "surface/factory_surface.h"
#include "surface/b_wall.h"
#include "surface/b_water.h"
#include "surface/b_movable.h"
#include "surface/s_snow.h"
#include "surface/s_ice.h"
#include "surface/s_door.h"
#include "surface/s_dialog.h"
#include "surface/s_surfaceautotexture.h"
#include "g_object.h"

#include "character/e_wolf.h"
#include "character/e_fox.h"
#include "character/e_walrus.h"

#include "memento.h"

#include <QPoint>
#include <QDebug>
#include <QList>
#include <QStringList>

#include <QDomNodeList>
#include <QDomElement>
#include <QDomDocument>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

int G_Level::S_SNOW = 1;
int G_Level::B_WALL_GROUP = 2;

/**
 * @details Create Level according to levelNumber and read the basics XML level informations
 */
G_Level::G_Level(int levelNumber, Observer_Enemy* observer, G_Gameboard *game)
{
    this->game = game;
    this->levelNumber = levelNumber;
    this->observerEnemy = observer;

    maxBlocksHeight = 2*G_Gameboard::sizeY;
    maxBlocksWidth = 3*G_Gameboard::sizeX;

    startingPoint = new QPoint(0,0);
    viewStart = new QPoint(0,0);
    unlockEnd = new QPoint(0,0);

    scene = new QGraphicsScene();

    loadLevel(levelNumber);
    qDebug() << "NEW!";}

QPoint* G_Level::getStartingPoint()
{
    return this->startingPoint;
}

/**
 * @details Populate the scene that will be returned by using addLevelItem method.
 */
QGraphicsScene* G_Level::populateScene()
{
    clearScene();

    QString background = ":/maps/maps/";
    background.append(QString("%1").arg(levelNumber));
    background.append(".png");
    QPixmap pixmapBackground(background);
    scene->setBackgroundBrush(pixmapBackground);

    QDomNode level = doc->firstChildElement().firstChild();
    QDomNode levelItem = level.nextSibling();

    //LIGNE
    for(QDomElement elemLine = levelItem.firstChildElement(); !elemLine.isNull(); elemLine = elemLine.nextSiblingElement())
    {
        //COLONNE
        for(QDomElement elemColonne = elemLine.firstChildElement(); !elemColonne.isNull(); elemColonne = elemColonne.nextSiblingElement())
        {
            //ITEM
            for(QDomElement elemItem = elemColonne.firstChildElement(); !elemItem.isNull(); elemItem = elemItem.nextSiblingElement())
            {
               addLevelItem(scene, elemItem, elemLine.attribute("position").toInt(), elemColonne.attribute("position").toInt());
            }
        }
    }

    //Calculate the autoTextures
    qDebug() << "nombre de texture automatiques : " << listAutoTextures.size();
    foreach (S_SurfaceAutoTexture* surfaceAuto, listAutoTextures)
    {
        surfaceAuto->calculateTextures(mapSurfacesSnow, maxBlocksWidth, maxBlocksHeight);
    }

     qDebug() << "nombre de wallGroup : " << listWallGroup.size();
    foreach (B_Wall_Group* surfaceAuto, listWallGroup)
    {
        surfaceAuto->calculateTextures(mapSurfacesWallGroup, maxBlocksWidth, maxBlocksHeight);
    }
    return scene;
}

/**
 * @details Put informations into class's attribute according to QDomElement type.
 */
void G_Level::addLevelInformation(QDomElement elem)
{
    QString tagName = elem.tagName();
    if(tagName == "SIZE")
    {
        maxBlocksWidth = elem.attribute("width").toInt();
        maxBlocksHeight = elem.attribute("height").toInt();
    }
    else if(tagName == "POSITION")
    {
        viewStart->setX(elem.attribute("x").toInt());
        viewStart->setY(elem.attribute("y").toInt());
    }
    else if(tagName == "START")
    {
        startingPoint->setX(elem.attribute("x").toInt());
        startingPoint->setY(elem.attribute("y").toInt());
    }
    else if(tagName == "END")
    {
        unlockEnd->setX(elem.attribute("x").toInt()*G_Gameboard::getGameSquares());
        unlockEnd->setY(elem.attribute("y").toInt()*G_Gameboard::getGameSquares());
    }
}

/**
 * @details Add into the Scene an Item on (x;y) position according to QDomElement data
 */
void G_Level::addLevelItem(QGraphicsScene* scene, QDomElement elem, int x, int y)
{
    QString tagName = elem.tagName();
    if(tagName == "BLOC")
    {
        G_Surface* surface = Factory_Surface::createSurface(elem.attribute("type"), x, y, scene, game);


        if(elem.attribute("type") == Factory_Surface::BLOC_WATER
                || elem.attribute("type") == Factory_Surface::SURFACE_ICE)
        {
            S_SurfaceAutoTexture *autoSurface = dynamic_cast<S_SurfaceAutoTexture*>(surface);
            listAutoTextures.append(autoSurface);
        }
        else if(elem.attribute("type") == Factory_Surface::BLOC_WALL_GROUP)
        {
            B_Wall_Group *autoSurface = dynamic_cast<B_Wall_Group*>(surface);
            listWallGroup.append(autoSurface);
        }

        //wall is like snow for the water
        if(elem.attribute("type") == Factory_Surface::SURFACE_SNOW
                || elem.attribute("type") == Factory_Surface::BLOC_WALL_ALONE
                || elem.attribute("type") == Factory_Surface::BLOC_WALL_GROUP)
        {
            mapSurfacesSnow[x][y] = G_Level::S_SNOW;
        }

        if(elem.attribute("type") == Factory_Surface::BLOC_WALL_GROUP)
        {
            mapSurfacesWallGroup[x][y] = G_Level::B_WALL_GROUP;
        }
    }
    else if(tagName == "ITEM")
    {
        scene->addItem(new G_Object(elem.attribute("type"),x,y,game));
    }
    else if(tagName == "DOOR")
    {
       S_Door* door = Factory_Surface::createSurfaceDoor(x,y,elem.attribute("item"),elem.attribute("nbItem").toInt(),scene,game);
       if(!elem.attribute("direction").isEmpty())
       {
           qDebug() << "BOUH";
           door->setDirection(elem.attribute("direction").at(0));
       }
    }
    else if(tagName == "END")
    {
        S_Door* door = Factory_Surface::createSurfaceLastDoor(x,y,elem.attribute("nextLevel").toInt(),scene,game);
        if(!elem.attribute("direction").isEmpty())
        {
            door->setDirection(elem.attribute("direction").at(0));
        }
        doorList.append(door);
    }
    else if(tagName == "ENEMY")
    {
        QStringList list;
        QString orientation = "TOP";
        QString ennemiType = elem.attribute("type");
        QList<QPoint> move;
        for(QDomElement child = elem.firstChildElement(); !child.isNull(); child = child.nextSiblingElement())
        {
           if(child.tagName() == "DIALOG")
           {
                list.append(child.attribute("text"));
           }
           else if(child.tagName() == "MOVE")
           {
                move.append(QPoint(child.attribute("x").toInt(),child.attribute("y").toInt()));
           }
           else if(child.tagName() == "ORIENTATION")
           {
               orientation = child.attribute("value");
           }
        }

        C_Enemy* enemy = Factory_Character::createEnemy(ennemiType, orientation, new QPoint(x,y),move, game, observerEnemy, scene);

        for(int i=0; i<list.count(); ++i )
        {
            enemy->addDialog(list.at(i));
        }
    }
    else if(tagName == "DIALOG")
    {
        Factory_Surface::createSurfaceDialog(x, y, scene, game, elem.attribute("text"), elem.attribute("image"));
    }

}

QPoint G_Level::getViewStart()
{
    return *(this->viewStart);
}

QPoint G_Level::getUnlockEndPoint()
{
    return *(this->unlockEnd);
}

int G_Level::getLevelNumber()
{
    return this->levelNumber;
}

void G_Level::unlock()
{
    for(int i=0; i<doorList.count(); ++i)
    {
        doorList[i]->setBackground(true);
    }
    doorList.clear();
}

void G_Level::clearScene()
{
    observerEnemy->clear();
    listAutoTextures.clear();
    listWallGroup.clear();
    Memento::getInstance()->clear();
    //scene->clear();

    QList<QGraphicsItem*> itemsList = scene->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    {
        QGraphicsItem* item = (*iter);
        scene->removeItem(item);
        iter++;
    }
}

void G_Level::loadLevel(int levelNumber)
{
    this->levelNumber = levelNumber;

    QString fileName = ":/maps/maps/L";
    fileName.append(QString("%1").arg(levelNumber));
    fileName.append(".xml");

    QString errorMsg;
    int errorLine, errorColumn;
    doc = new QDomDocument(fileName);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc->setContent(&file, &errorMsg, &errorLine, &errorColumn))
    {
        file.close();
        qDebug() << "ERROR";
        qDebug() << "Parsing error, line " << errorLine
                << " column " << errorColumn
                << ": " << qPrintable(errorMsg) << endl;
        return;
    }
    file.close();

    QDomElement levelInformation = doc->firstChildElement().firstChildElement();
    for(QDomElement elem = levelInformation.firstChildElement(); !elem.isNull(); elem = elem.nextSiblingElement())
    {
        addLevelInformation(elem);
    }

    //allocating the matrixes
    mapSurfacesSnow = (int**)calloc(maxBlocksWidth, sizeof(int*));
    mapSurfacesWallGroup = (int**)calloc(maxBlocksWidth, sizeof(int*));
    for(int i=0; i<maxBlocksWidth; i++)
    {
        mapSurfacesSnow[i] = (int*)calloc(maxBlocksHeight, sizeof(int));
        mapSurfacesWallGroup[i] = (int*)calloc(maxBlocksHeight, sizeof(int));
    }
}
