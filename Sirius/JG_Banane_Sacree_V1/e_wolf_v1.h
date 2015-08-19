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

#ifndef E_LOUP_V1_H
#define E_LOUP_V1_H

#include "c_enemy_v1.h"
class G_Gameboard_v1;

class E_Wolf_v1 : public C_Enemy_v1
{
public:
    E_Wolf_v1(QList<QPoint> path, G_Gameboard_v1 *g);
};

#endif // E_LOUP_V1_H
