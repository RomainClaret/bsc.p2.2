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
class B_MovableSimple;
class S_Footstep;
class QGraphicsScene;
class G_Gameboard;

#include <QList>

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
    S_Snow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup.
     * @param parent QGraphicsItem to depend on
     */
    S_Snow(QGraphicsScene* scene,G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief setMovableSunk show the snow like a sunk movable
     * @param b
     */
    void setMovableSunk(B_MovableSimple *b);

    /**
     * @brief showFootPrint display the foot step on the snow
     * @param sens direction of the character
     */
    S_Footstep* showFootPrint(char sens);


protected:
    void advance(int step);

private:
    /**
     * @brief Set the design of self and the pictures for the annimation
     */
    void setDesign();

    QGraphicsScene* scene;
    int iTime;
    int speed;

    bool movableSunk;
};

#endif // S_SNOW_H
