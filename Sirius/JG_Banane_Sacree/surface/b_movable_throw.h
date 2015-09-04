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

#ifndef B_MOVABLE_THROW_H
#define B_MOVABLE_THROW_H
#include "b_movable.h"
#include <QList>

class QGraphicsRectItem;
class QGraphicsScene;
class G_Gameboard;

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
class B_MovableThrow : public B_Movable
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    B_MovableThrow(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup.
     * @param parent QGraphicsItem to depend on
     */
    B_MovableThrow(G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Check the position of the movable block after moving
     */
    void checkPosition();

protected:
    void advance(int step);

private:
    int speed;
    int time;

};

#endif // B_MOVABLE_THROW_H
