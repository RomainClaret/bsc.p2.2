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

#ifndef S_FIRE_H
#define S_FIRE_H
#include "../surface/g_surface.h"
#include "../surface/s_surfaceautotexture.h"

class QGraphicsRectItem;
class G_Gameboard;

/**
 * @brief Fire Surface
 * @details Only the throw movable blocks can traverse this surface.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 02 September 2015
 */
class S_Fire : public S_SurfaceAutoTexture
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem to depend on
     */
    S_Fire(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup
     * @param parent QGraphicsItem parent
     */
    S_Fire(G_Gameboard* game, QGraphicsItem *parent = 0);

    void calculateTextures(int** mapSurfaces, int width, int height);

private:
    /**
     * @brief Set the skin of the block.
     */
    void setDesign();
};

#endif // S_FIRE_H
