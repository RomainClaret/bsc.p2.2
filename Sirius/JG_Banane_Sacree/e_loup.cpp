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

#include "e_wolf.h"
#include "gameboard.h"
#include "s_viewblockenemy.h"

/**
 * @details Set the skin, speed at 8, Z value at 2 and default orientation to top.
 * Vision of the enemy is created here.
 */
E_Wolf::E_Wolf(QList<QPoint> path, Gameboard *g) : Enemy(path, g)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 8; //vitesse par défaut

    leftSkin = ":/characters/characters/loup_left.png";
    rightSkin = ":/characters/characters/loup_right.png";
    upSkin = ":/characters/characters/loup_back.png";
    downSkin = ":/characters/characters/loup_front.png";

        setZValue(2);

    //Création du champs de vue
    for(int i=1; i<=5; i++)
    {
        S_ViewBlockEnemy* vb = new S_ViewBlockEnemy(0, i, this);
        viewField.append(vb);
    }

    //il lui faut une orientation de base
    setOrientation_top();

}
