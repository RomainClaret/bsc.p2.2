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

#include "../surface/g_surface.h"
#include "../g_gameboard.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QPen>

#include <QDebug>

G_Surface::G_Surface(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, G_Gameboard::getGameSquares(), G_Gameboard::getGameSquares(), parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
G_Surface::G_Surface(int xpos, int ypos, int width, int height, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, width, height, parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
G_Surface::~G_Surface(){}

void G_Surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*G_Gameboard::getGameSquares(), y*G_Gameboard::getGameSquares());
}
void G_Surface::setPosPixel(int x, int y)
{
    QGraphicsRectItem::setPos(x, y);
}
QPoint G_Surface::getPos()
{
    return QPoint(this->pos().x()/G_Gameboard::getGameSquares(), this->pos().y()/G_Gameboard::getGameSquares());
}

void G_Surface::setColor(QString brushColor)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(brushColor);
    setBrush(brush);
}

void G_Surface::advance(int step)
{
    //qDebug() << "advance call";
}
