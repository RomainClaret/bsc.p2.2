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

#include "character/c_player.h"
#include "g_gameboard.h"

#include <QPainter>
#include <QDebug>
#include <QRectF>


C_Player::C_Player(G_Gameboard* game)
{
    leftSkin = ":/characters/characters/player_left.png";
    rightSkin = ":/characters/characters/player_right.png";
    upSkin = ":/characters/characters/player_back.png";
    downSkin = ":/characters/characters/player_front.png";
    orientation = 'b'; //Orientation de depart du joueur

    setZValue(10);

    this->game = game;
}

void C_Player::setPlayerOrientation(char orientation)
{
    this->orientation = orientation;
}

char C_Player::getPlayerOrientation()
{
    return orientation;
}

QPoint* C_Player::getPos()
{
    return new QPoint(xPos, yPos);
}
QPoint C_Player::getPosOnGame()
{
    int x = (this->pos().x()-1) /G_Gameboard::getGameSquares();
    int y = (this->pos().y()-1) /G_Gameboard::getGameSquares();
    return QPoint(x, y);
}
