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

#include "../character/e_otter.h"
#include "../g_gameboard.h"
#include "../surface/s_viewblocknpc.h"
#include "../state/state_enemyfriendly.h"
#include "../surface/b_wall.h"
#include "../surface/b_water.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

/**
 * @details Set the skin, speed at 10, Z value at 2 and default orientation to top.
 * Vision of the enemy is created here.
 */
E_Otter::E_Otter(QList<QPoint> path, G_Gameboard *g) : C_Enemy(path, g)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 10; //vitesse par défaut

    leftSkin = ":/characters/characters/loutre.png";
    rightSkin = ":/characters/characters/loutre.png";
    upSkin = ":/characters/characters/loutre.png";
    downSkin = ":/characters/characters/loutre.png";

    setZValue(3);

    S_ViewBlockNPC* vb1 = new S_ViewBlockNPC(0, 1, this);
    S_ViewBlockNPC* vb2 = new S_ViewBlockNPC(0, -1, this);
    S_ViewBlockNPC* vb3 = new S_ViewBlockNPC(1, -1, this);
    S_ViewBlockNPC* vb4 = new S_ViewBlockNPC(1, 0, this);
    S_ViewBlockNPC* vb5 = new S_ViewBlockNPC(1, 1, this);
    S_ViewBlockNPC* vb6 = new S_ViewBlockNPC(-1, -1, this);
    S_ViewBlockNPC* vb7 = new S_ViewBlockNPC(-1, 0, this);
    S_ViewBlockNPC* vb8 = new S_ViewBlockNPC(-1, 1, this);

    //vb->setStyleNone();

    viewField.append(vb1);
    viewField.append(vb2);
    viewField.append(vb3);
    viewField.append(vb4);
    viewField.append(vb5);
    viewField.append(vb6);
    viewField.append(vb7);
    viewField.append(vb8);

    foreach(S_ViewBlockNPC* vb, viewField)
    {
        setActive(false);
    }

    //il lui faut une orientation de base
    setOrientation_top();
}

void E_Otter::playableCharacterDetection()
{
    detectPlayableCharacter = false;
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        if(vb->isActive())
        {
            QList<QGraphicsItem *> CollidingItems = vb->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(P_Penguin).name())
                {
                    detectPlayableCharacter = true;
                    QString text = tr("N'oubliez pas mes poissons");
                    game->showDialog(text,"");
                }
            }
        }
    }
}

void E_Otter::checkPenguin()
{
    detectPlayableCharacter = false;
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        if(vb->isActive())
        {
            QList<QGraphicsItem *> CollidingItems = vb->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(P_Penguin).name())
                {
                    detectPlayableCharacter = true;
                }
            }
        }
    }
}

void E_Otter::changeState(State_Enemy* newState)
{
    delete newState;
    delete state;
    this->state = new State_EnemyFriendly();
}

bool E_Otter::collide()
{
    S_ViewBlockNPC *collideRect;
    foreach (S_ViewBlockNPC* vb, viewField) {
        if(vb->getColonne()==1 && vb->getLine()==0){
            collideRect = vb;
        }
    }

    QList<QGraphicsItem *> CollidingItems = collideRect->collidingItems();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_MovableSimple).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(C_Enemy).name())
        {
            return true;
        }
    }
    return false;
}


