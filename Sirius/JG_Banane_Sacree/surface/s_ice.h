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
#include "../surface/g_surface.h"
#include "../surface/s_surfaceautotexture.h"

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
class S_Ice : public S_SurfaceAutoTexture
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    S_Ice(int xpos, int ypos, QGraphicsItem *parent = 0);

    S_Ice(QGraphicsItem *parent = 0);

    void calculateTextures(int** mapSurfaces, int width, int height);

private:
    /**
     * @brief Set the design of self.
     */
    void setDesign();
};

#endif // S_ICE_H
