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

#include "e_wolf_v1.h"
#include "g_gameboard_v1.h"

E_Wolf_v1::E_Wolf_v1(QList<QPoint> path, G_Gameboard_v1 *g) : C_Enemy_v1(path, g)
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
    int gs = G_Gameboard_v1::getGameSquares();
    for(int i=1; i<=5; i++)
    {
        ViewBloc vb;
        vb.bloc = new QGraphicsRectItem(0,0, gs-2, gs-2);
        vb.bloc->setZValue(2);
        vb.colonne=i;
        vb.ligne=0;

        champVue.append(vb);
    }

    //il lui faut une orientation de base
    setOrientation_top();

}
