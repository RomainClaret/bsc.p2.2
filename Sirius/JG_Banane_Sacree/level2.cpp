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

#include "level.h"
#include "gameboard.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>

#include "surface.h"
#include "surfacefactory.h"
#include "b_wall.h"
#include "b_water.h"
#include "b_movable.h"
#include "s_snow.h"
#include "s_ice.h"
#include "s_viewtransition.h"
#include "s_dialog.h"
#include "object.h"

#include "e_loup.h"
#include "e_renard.h"

#include <QPoint>
#include <QDebug>
#include <QList>

#include <QDomNodeList>
#include <QDomElement>
#include <QDomDocument>

Level2::Level2(int levelNumber, Gameboard *game)
{
    this->game = game;
    this->levelNumber = levelNumber;

    maxBlocksHeight = 2*Gameboard::sizeY;
    maxBlocksWidth = 3*Gameboard::sizeX;

    startingPoint = new QPoint(0,0);
    viewStart = new QPoint(0,0);
    unlockEnd = new QPoint(0,0);

    QString fileName = ":/maps/maps/L";
    fileName.append(QString("%1").arg(levelNumber));
    fileName.append(".xml");
    qDebug() << fileName;

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
}

QPoint* Level2::getStartingPoint()
{
    return this->startingPoint;
}

QGraphicsScene* Level2::populateScene()
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
    return scene;
}

void Level2::addLevelInformation(QDomElement elem)
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
        unlockEnd->setX(elem.attribute("x").toInt()*Gameboard::getGameSquares());
        unlockEnd->setY(elem.attribute("y").toInt()*Gameboard::getGameSquares());
    }
}

void Level2::addLevelItem(QGraphicsScene* scene, QDomElement elem, int x, int y)
{
    QString tagName = elem.tagName();
    if(tagName == "BLOC")
    {       
        SurfaceFactory::createSurface(elem.attribute("type"),x,y,scene);
    }
    else if(tagName == "ITEM")
    {
        scene->addItem(new Object(elem.attribute("type"),x,y));
    }
    else if(tagName == "DOOR")
    {
        SurfaceFactory::createSurfaceDoor(x,y,elem.attribute("item"),elem.attribute("nbItem").toInt(),scene);
    }
    else if(tagName == "END")
    {
        SurfaceFactory::createSurfaceLastDoor(x,y,elem.attribute("nextLevel").toInt(),scene);
    }
    else if(tagName == "ENEMY")
    {
        QString ennemiType = elem.attribute("type");
        QList<QPoint> move;
        for(QDomElement moveElement = elem.firstChildElement(); !moveElement.isNull(); moveElement = moveElement.nextSiblingElement())
        {
           move.append(QPoint(moveElement.attribute("x").toInt(),moveElement.attribute("y").toInt()));
        }
        if(ennemiType == "FOX")
        {
            E_Renard *item2 = new E_Renard(move, game);
            item2->addToScene(scene);
        }
        else if(ennemiType == "WOLF")
        {
            E_Loup *item2 = new E_Loup(move, game);
            item2->addToScene(scene);
        }
    }
    else if(tagName == "DIALOG")
    {
        SurfaceFactory::createSurfaceDialog(x, y, scene, elem.attribute("text"));
    }
}

QPoint Level2::getViewStart()
{
    return *(this->viewStart);
}

QPoint Level2::getUnlockEndPoint()
{
    return *(this->unlockEnd);
}

int Level2::getLevelNumber()
{
    return this->levelNumber;
}
