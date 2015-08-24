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

#ifndef S_SNOW_H
#define S_SNOW_H
#include "../surface/g_surface.h"

class QGraphicsItem;

/**
 * @brief Snow Surface.
 * @details Specific design.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class S_Snow : public G_Surface
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    S_Snow(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup.
     * @param parent QGraphicsItem to depend on
     */
    S_Snow(QGraphicsItem *parent = 0);

private:
    /**
     * @brief Set the design of self and the pictures for the annimation
     */
    void setDesign();
};

#endif // S_SNOW_H
