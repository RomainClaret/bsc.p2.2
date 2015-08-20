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

#include "b_water_v1.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

B_Water_v1::B_Water_v1(int xpos, int ypos, QGraphicsItem *parent) : G_Surface_v1(xpos, ypos, parent)
{
    setDesign();
}
B_Water_v1::B_Water_v1(QGraphicsItem *parent) : G_Surface_v1(0, 0, parent) //Pas le choix, obligé de donner un position fictive
{
    setDesign();
}
void B_Water_v1::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::blue);

//    setBrush(brush);
}
