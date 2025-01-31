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

#ifndef B_WATER_V1_H
#define B_WATER_V1_H

#include "g_surface_v1.h"
class QGraphicsRectItem;

class B_Water_v1 : public G_Surface_v1
{
public:
    B_Water_v1(int xpos, int ypos, QGraphicsItem *parent = 0);
    B_Water_v1(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // B_WATER_V1_H
