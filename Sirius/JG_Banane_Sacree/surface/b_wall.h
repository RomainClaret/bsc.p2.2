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

#ifndef B_WALL_H
#define B_WALL_H
#include "../surface/g_surface.h"

class QGraphicsRectItem;

/**
 * @brief Wall block
 * @details This block can not be moved with characters.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
class B_Wall : public G_Surface
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem to depend on
     */
    B_Wall(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup
     * @param parent QGraphicsItem parent
     */
    B_Wall(QGraphicsItem *parent = 0);

private:
    /**
     * @brief Set the skin of the block.
     */
    void setDesign();
};

#endif // B_WALL_H
