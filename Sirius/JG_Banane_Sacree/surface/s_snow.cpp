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

#include "../surface/s_snow.h"
#include "../surface/b_movable_simple.h"

#include <QBrush>
#include <QGraphicsItem>

S_Snow::S_Snow(int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    setDesign();
    this->setZValue(2);
}
S_Snow::S_Snow(QGraphicsItem *parent) : G_Surface(0, 0, parent)
{
    setDesign();
    this->setZValue(2);
}

void S_Snow::setMovableSunk(B_MovableSimple *b)
{
    this->setBrush(Qt::NoBrush);

    QPixmap pixmap = QPixmap(":/surfaces/surfaces/movable_snow.png");

    int rotation = b->getRotationTexture();
    QTransform transform;
    QTransform trans = transform.rotate(rotation);

    QBrush brush;
    brush.setTexture(QPixmap(pixmap.transformed(trans)));
    setBrush(brush);

    this->setZValue(1);
}

void S_Snow::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}

void S_Snow::showFootPrint(char sens)
{

}
