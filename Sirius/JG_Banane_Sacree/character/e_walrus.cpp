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

#include "../character/e_walrus.h"
#include "../g_gameboard.h"
#include "../surface/s_viewblocknpc.h"
#include "../surface/factory_surface.h"

#include "../state/state_enemywalrus.h"

#include <QDebug>

/**
 * @details Set the skin, speed at 10, Z value at 2 and default orientation to top.
 * Vision of the enemy is created here.
 */
E_Walrus::E_Walrus(QString position, QList<QPoint> path, G_Gameboard *g) : C_Enemy(position, path, g)
{
    this->gameBoard = g;
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 7;

    leftSkin = ":/characters/characters/walrus_front.png";
    rightSkin = ":/characters/characters/walrus_front.png";
    upSkin = ":/characters/characters/walrus_front.png";
    downSkin = ":/characters/characters/walrus_front.png";

    //Création du champs de vue
    S_ViewBlockNPC* vb = new S_ViewBlockNPC(0, 1, this, game);
    vb->setStyleNone();
    viewField.append(vb);

    resetDefaultOrientation();

    state = new State_EnemyWalrus();
}

E_Walrus::~E_Walrus()
{
}

void E_Walrus::action()
{
    int val = rand() % 2;
    if(val == 1)
    {
        Factory_Surface::createBlocMovableThrow(pos().x()/32, pos().y()/32+1, gameBoard->getGraphicsScene(), gameBoard);
    }
}


void E_Walrus::setSpecialTexture(bool value)
{
    if(value)
    {
        leftSkin = ":/characters/characters/walrus_special.png";
        rightSkin = ":/characters/characters/walrus_special.png";
        upSkin = ":/characters/characters/walrus_special.png";
        downSkin = ":/characters/characters/walrus_special.png";
    }
    else
    {
        leftSkin = ":/characters/characters/walrus_front.png";
        rightSkin = ":/characters/characters/walrus_front.png";
        upSkin = ":/characters/characters/walrus_front.png";
        downSkin = ":/characters/characters/walrus_front.png";
    }
}
