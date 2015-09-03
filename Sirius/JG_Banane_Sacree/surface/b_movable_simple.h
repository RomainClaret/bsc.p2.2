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

#ifndef B_MOVABLE_SIMPLE_H
#define B_MOVABLE_SIMPLE_H
#include "b_movable.h"
#include <QList>

class QGraphicsRectItem;
class QGraphicsScene;
class Singleton_Audio;

/**
 * @brief Movable block
 * @details This block can be moved with characters.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
//@bug no bugs
//@warning no warnings
class B_MovableSimple : public B_Movable
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    B_MovableSimple(int xpos, int ypos, QGraphicsScene* scene, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup.
     * @param parent QGraphicsItem to depend on
     */
    B_MovableSimple(QGraphicsItem *parent = 0);

    /**
     * @brief Check if self should slide
     * @return true if self collides with a specific block.
     */
    bool isSlide();

    /**
     * @brief getRotated get the rotation of the texture
     * @return
     */
    int getRotationTexture();

private:
    int rotationTexture;
    Singleton_Audio *audioSingleton;

};

#endif // B_MOVABLE_SIMPLE_H
