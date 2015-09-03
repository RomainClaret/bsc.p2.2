#ifndef B_WALL_RANDOM_H
#define B_WALL_RANDOM_H

#include "b_wall.h"
class QGraphicsItem;
/**
 * @brief Wall block alone with random apparence
 * @details This block can not be moved with characters.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 31 august 2015
 */
class B_Wall_Alone : public B_Wall
{
public:

    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem to depend on
     */
    B_Wall_Alone(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor without position setup
     * @param parent QGraphicsItem parent
     */
    B_Wall_Alone(QGraphicsItem *parent = 0);

    /**
     * @brief calculateTextures determinate the texture with the collisions
     * @param mapSurfaces
     * @param width
     * @param height
     */
    void calculateTextures(int** mapSurfaces, int width, int height);

private:
    /**
     * @brief Set the skin of the block with random.
     */
    void setDesign();
};


#endif // B_WALL_RANDOM_H
