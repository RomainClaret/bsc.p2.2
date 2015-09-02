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

#include "../surface/s_stone.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

S_Stone::S_Stone(int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    setDesign();
}
/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
S_Stone::S_Stone(QGraphicsItem *parent) : G_Surface(0, 0, parent)
{
    setDesign();
}

void S_Stone::setDesign()
{
    QBrush brush;
    brush.setTexture(QPixmap(":/surfaces/surfaces/stones_init.png"));
    setBrush(brush);
}
