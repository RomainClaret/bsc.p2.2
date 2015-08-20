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

#include "c_player_v1.h"
#include "g_gameboard_v1.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

#include <QRectF>
#include <QGraphicsItem>


C_Player_v1::C_Player_v1()
{
    leftSkin = ":/characters/characters/player_left.png";
    rightSkin = ":/characters/characters/player_right.png";
    upSkin = ":/characters/characters/player_back.png";
    downSkin = ":/characters/characters/player_front.png";
    playerOrientation = "down"; //Orientation de depart du joueur

    setZValue(2);
}

QRectF C_Player_v1::boundingRect() const
{
    return QRectF(1,1,G_Gameboard_v1::getGameSquares()-2,G_Gameboard_v1::getGameSquares()-2);
}

void C_Player_v1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    playerSkin = new QBrush();

    //Set playerSkin texture depending on player's orientation
    if (playerOrientation == "left"){
        playerSkin->setTexture(QPixmap(leftSkin));
    }
    if (playerOrientation == "right"){
        playerSkin->setTexture(QPixmap(rightSkin));
    }
    if (playerOrientation == "up"){
        playerSkin->setTexture(QPixmap(upSkin));
    }
    if (playerOrientation == "down"){
        playerSkin->setTexture(QPixmap(downSkin));
    }

    QRectF playerBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(playerBox,*playerSkin);   //charger la couleur
    painter->drawRect(playerBox);   //dessiner le joueur
}

void C_Player_v1::setPlayerOrientation(QString orientation)
{
    playerOrientation = orientation;
}

QString C_Player_v1::getPlayerOrientation()
{
    return playerOrientation;
}

QPoint* C_Player_v1::getPos()
{
    return new QPoint(xPos, yPos);
}
