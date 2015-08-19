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

#include "b_wall.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

B_Wall::B_Wall(int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    setDesign();
}
/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
B_Wall::B_Wall(QGraphicsItem *parent) : G_Surface(0, 0, parent)
{
    setDesign();
}

void B_Wall::setDesign()
{
    //QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    //brush.setColor(Qt::red);

//    setBrush(brush);
}
