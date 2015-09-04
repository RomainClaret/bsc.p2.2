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

#include "../surface/b_movable_throw.h"

#include "../surface/b_wall.h"
#include "../surface/b_movable.h"
#include "../surface/b_wall_alone.h"
#include "../surface/b_wall_group.h"
#include "../surface/b_water.h"
#include "../character/c_enemy.h"
#include "../character/e_fox.h"
#include "../character/e_wolf.h"
#include "../g_gameboard.h"
#include "../surface/s_ice.h"
#include "../memento.h"

#include "g_gameboard.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

/**
 * @details Uses setDesign(xpos, ypos) to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */

B_MovableThrow::B_MovableThrow(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : B_Movable(xpos, ypos, game->getGraphicsScene(), game, parent)
{

    int val = rand() % 10+3;
    speed = val;
    time = 0;

    setTexture(QPixmap(":/items/items/tonneau.png"));
}

/**
 * @details The use FICTIVE positions x and y to create the cross of box around self to check collisions.
 * Sets the position on the Z-axis to 1 to be on top of the scene which is at 0.
 */

B_MovableThrow::B_MovableThrow(G_Gameboard* game, QGraphicsItem *parent) : B_Movable(0, 0, NULL, game, parent) //obligé de donner une position fictive
{
    speed = 7;
    time = 0;
}

void B_MovableThrow::advance(int step)
{
    if(step == 0 && !game->getPauseState())
    {
        time ++;
        if(time % speed == 0)
        {
            moveBy(0,1);
        }

        checkPosition();
    }
}

void B_MovableThrow::checkPosition()
{
    QList<QGraphicsItem *> l = this->collidingItems();
    for(int i=0; i<l.length(); i++)
    {

        if(typeid(*l.at(i)).name() == typeid(B_Wall_Alone).name() ||
           typeid(*l.at(i)).name() == typeid(B_Wall_Group).name() ||
           typeid(*l.at(i)).name() == typeid(B_Water).name() ||
           typeid(*l.at(i)).name() == typeid(B_MovableSimple).name())
        {
            Memento::getInstance()->removeSpecialEventSurface(game->getGraphicsScene(), this);
            delete this;
        }
        if(typeid(*l.at(i)).name() == typeid(P_Penguin).name())
        {
            P_Penguin* penguin = (P_Penguin*)l.at(i);
            penguin->endMove();
            penguin->disconnectTimer();
            game->disconnectTimer();
            game->restartEnigma();
        }
    }
}

