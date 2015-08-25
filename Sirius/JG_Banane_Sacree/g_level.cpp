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

#include "observer_npc.h"
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

#include <QPoint>
#include <QDebug>
#include <QList>

#include <QDomNodeList>
#include <QDomElement>
#include <QDomDocument>

int G_Level::S_SNOW = 1;

/**
 * @details Create Level according to levelNumber and read the basics XML level informations
 */
G_Level::G_Level(int levelNumber, Observer_NPC* observer, G_Gameboard *game)
{
    this->game = game;
    this->levelNumber = levelNumber;
    this->observerEnemy = observer;

    maxBlocksHeight = 2*G_Gameboard::sizeY;
    maxBlocksWidth = 3*G_Gameboard::sizeX;

    startingPoint = new QPoint(0,0);
    viewStart = new QPoint(0,0);
    unlockEnd = new QPoint(0,0);

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

    mapSurfaces = (int**)calloc(maxBlocksWidth, sizeof(int*));
    for(int i=0; i<maxBlocksWidth; i++)
    {
        mapSurfaces[i] = (int*)calloc(maxBlocksHeight, sizeof(int));
    }
}

QPoint* G_Level::getStartingPoint()
{
    return this->startingPoint;
}

/**
 * @details Populate the scene that will be returned by using addLevelItem method.
 */
QGraphicsScene* G_Level::populateScene()
{
    QGraphicsScene* scene = new QGraphicsScene();

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
        surfaceAuto->calculateTextures(mapSurfaces, maxBlocksWidth, maxBlocksHeight);
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
        G_Surface* surface = Factory_Surface::createSurface(elem.attribute("type"), x, y, scene);

        if(elem.attribute("type") == Factory_Surface::BLOC_WATER)
        {
            S_SurfaceAutoTexture *autoSurface = dynamic_cast<S_SurfaceAutoTexture*>(surface);
            listAutoTextures.append(autoSurface);
        }

        if(elem.attribute("type") == Factory_Surface::SURFACE_SNOW)
        {
            //(mapSurfaces.at(x)).at(y) = G_Level::S_SNOW;
            mapSurfaces[x][y] = G_Level::S_SNOW;
        }
    }
    else if(tagName == "ITEM")
    {
        scene->addItem(new G_Object(elem.attribute("type"),x,y));
    }
    else if(tagName == "DOOR")
    {
        Factory_Surface::createSurfaceDoor(x,y,elem.attribute("item"),elem.attribute("nbItem").toInt(),scene);
    }
    else if(tagName == "END")
    {
        Factory_Surface::createSurfaceLastDoor(x,y,elem.attribute("nextLevel").toInt(),scene);
    }
    else if(tagName == "ENEMY")
    {
        QString ennemiType = elem.attribute("type");
        QList<QPoint> move;
        for(QDomElement moveElement = elem.firstChildElement(); !moveElement.isNull(); moveElement = moveElement.nextSiblingElement())
        {
           move.append(QPoint(moveElement.attribute("x").toInt(),moveElement.attribute("y").toInt()));
        }

        Factory_Character::createEnemy(ennemiType, move, game, observerEnemy, scene);
    }
    else if(tagName == "DIALOG")
    {
        Factory_Surface::createSurfaceDialog(x, y, scene, elem.attribute("text"), elem.attribute("image"));
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
