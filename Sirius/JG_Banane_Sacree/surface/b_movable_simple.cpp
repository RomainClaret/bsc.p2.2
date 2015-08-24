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

#include <QBrush>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "../surface/b_wall.h"
#include "../surface/b_movable.h"
#include "../surface/b_water.h"
#include "../character/c_enemy.h"
#include "../character/e_fox.h"
#include "../character/e_walrus.h"
#include "../character/e_wolf.h"
#include "../g_gameboard.h"
#include "../surface/s_ice.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

/**
 * @details Uses setDesign(xpos, ypos) to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */
B_MovableSimple::B_MovableSimple(int xpos, int ypos, QGraphicsItem *parent) : B_Movable(xpos, ypos, parent)
{
}

/**
 * @details The use FICTIVE positions x and y to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */
B_MovableSimple::B_MovableSimple(QGraphicsItem *parent) : B_Movable(0, 0, parent)
{
}

/**
 * @details Check if the cross of detection collides with S_Ice.
 */
bool B_MovableSimple::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->collidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
        {
            return true;
        }
    }
    return false;
}
