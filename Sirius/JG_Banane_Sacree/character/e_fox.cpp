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

#include "../character/e_fox.h"
#include "../g_gameboard.h"
#include "../surface/s_viewblocknpc.h"

/**
 * @details Set the skin, speed at 10, Z value at 2 and default orientation to top.
 * Vision of the enemy is created here.
 */
E_Fox::E_Fox(QList<QPoint> path, G_Gameboard *g) : C_Enemy(path, g)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 10; //vitesse par défaut

    leftSkin = ":/characters/characters/renard_left.png";
    rightSkin = ":/characters/characters/renard_right.png";
    upSkin = ":/characters/characters/renard_back.png";
    downSkin = ":/characters/characters/renard_front.png";


    //Création du champs de vue
    for(int i=1; i<=2; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            S_ViewBlockNPC* vb = new S_ViewBlockNPC(j, i, this);
            viewField.append(vb);
        }
    }

    //il lui faut une orientation de base
    setOrientation_top();
}
