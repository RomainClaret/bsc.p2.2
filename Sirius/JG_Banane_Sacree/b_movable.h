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

#ifndef B_MOVABLE_H
#define B_MOVABLE_H
#include "surface.h"
#include <QList>

class QGraphicsRectItem;
class QGraphicsScene;

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
class B_Movable : public Surface
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    B_Movable(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup
     * @param parent QGraphicsItem to depend on
     */
    B_Movable(QGraphicsItem *parent = 0);

    //Methods related to the Scene
    /**
     * @brief Add self to scene.
     * @param Scene scene to add self to
     */
    void addToScene(QGraphicsScene* Scene);
    /**
     * @brief Remove self to scene.
     * @param Scene scene to remove self from
     */
    void removeFromScene(QGraphicsScene* Scene);

    /**
     * @brief Move self by x and y values.
     * @param x move this amount on the x-axis
     * @param y move this amount on the y-axis
     */
    void moveBy(int x, int y);

    /**
     * @brief Set the position of self with the x and y values.
     * @param x set the postion on the x-axis
     * @param y set the postion on the y-axis
     */
    void setPos(int x, int y);

    //Methods related to the displacement of the block
    /**
     * @brief Check if self can move to the left.
     * @return true if can move to left
     */
    bool IsMovableToLeft();

    /**
     * @brief Check if self can move to the right.
     * @return true if can move to right
     */
    bool IsMovableToRight();

    /**
     * @brief Check if self can move to the bottom.
     * @return true if can move to bottom
     */
    bool IsMovableToBottom();

    /**
     * @brief Check if self can move to the top.
     * @return true if can move to top
     */
    bool IsMovableToTop();

    /**
     * @brief Check if self should slide
     * @return true if self collides with a specific block.
     */
    bool isSlide();

    /**
     * @brief Get all colliding blocks.
     * @return colliding QGraphicsItem
     */
    QList<QGraphicsItem *> CollidesCenter();

    /**
     * @brief Get the colliding block from a direction.
     * @param sens the side to check for a collision
     * @return QGraphicsRectItem in collision with the parameter
     */
    QGraphicsRectItem* getCollideBlocPosition(char sens);

    /**
     * @brief Box on the left side of the b_movable.
     */
    QGraphicsRectItem *leftCollideBox;

    /**
     * @brief Box on the right side of the b_movable.
     */
    QGraphicsRectItem *rightCollideBox;

    /**
     * @brief Box on the bottom side of the b_movable.
     */
    QGraphicsRectItem *bottomCollideBox;

    /**
     * @brief Box on the top side of the b_movable.
     */
    QGraphicsRectItem *topCollideBox;

private:

    /**
     * @brief Check if self is movable.
     * @param l QList of QGraphicsItem
     * @return true if self can move
     */
    bool IsMovable(QList<QGraphicsItem *> l);

    /**
     * @brief Create the cross of items around self.
     * @param xpos position of the item on the x-axis
     * @param ypos position of the item on the y-axis
     */
    void setDesign(int xpos, int ypos);


};

#endif // B_MOVABLE_H
