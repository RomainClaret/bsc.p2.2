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

#ifndef S_ICE_H
#define S_ICE_H
#include "g_surface.h"

class QGraphicsItem;

/**
 * @brief Ice Surface.
 * @details Specific design.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class S_Ice : public G_Surface
{
public:
    S_Ice(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Ice(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // S_ICE_H
