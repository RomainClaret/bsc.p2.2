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

#ifndef B_WATER_H
#define B_WATER_H
#include "s_surfaceautotexture.h"

class QGraphicsRectItem;
#include <QVector>
class G_Gameboard;

/**
 * @brief Water block
 * @details This block make the character fall in the water.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
class B_Water : public S_SurfaceAutoTexture
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem to depend on
     */
    B_Water(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent = 0);

    void calculateTextures(int** mapSurfaces, int width, int height);
//    bool isCollidingWithWater(QGraphicsRectItem* bloc);

    /**
     * @brief Constructor without position setup
     * @param parent QGraphicsItem parent
     */
    B_Water(G_Gameboard* game, QGraphicsItem *parent = 0);

private:
    /**
     * @brief Set the skin of the block.
     */
    void setDesign();
};

#endif // B_WATER_H
