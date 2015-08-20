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

#include "g_surface_v1.h"
#include "g_gameboard_v1.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QPen>

#include <QDebug>

G_Surface_v1::G_Surface_v1(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, G_Gameboard_v1::getGameSquares(), G_Gameboard_v1::getGameSquares(), parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
G_Surface_v1::G_Surface_v1(int xpos, int ypos, int width, int height, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, width, height, parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
G_Surface_v1::~G_Surface_v1(){}

void G_Surface_v1::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*G_Gameboard_v1::getGameSquares(), y*G_Gameboard_v1::getGameSquares());
}
QPoint G_Surface_v1::getPos()
{
    return QPoint(this->pos().x()/G_Gameboard_v1::getGameSquares(), this->pos().y()/G_Gameboard_v1::getGameSquares());
}

void G_Surface_v1::setColor(QString brushColor)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(brushColor);
    setBrush(brush);
}
