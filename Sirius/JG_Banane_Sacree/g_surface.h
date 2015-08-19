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

#ifndef G_SURFACE_H
#define G_SURFACE_H

#include <QGraphicsRectItem>
class QPoint;

/**
 * @brief Walking blocks.
 * @details Surfaces are blocks that allows the player to move on.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class G_Surface : public QGraphicsRectItem
{
public:
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem to depend on
     */
    G_Surface(int xpos, int ypos, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor with setup position and size.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param width set the size of self
     * @param height set the size of self
     * @param parent QGraphicsItem to depend on
     */
    G_Surface(int xpos, int ypos, int width, int height, QGraphicsItem *parent = 0);

    //Destructor
    ~G_Surface();

    /**
     * @brief Set the position of self related to gamesquare.
     * @param x set the postion on the x-axis
     * @param y set the postion on the y-axis
     */
    void setPos(int x, int y);

    /**
     * @brief Set the position of self with pixels.
     * @param x set the postion on the x-axis
     * @param y set the postion on the y-axis
     */
    void setPosPixel(int x, int y);

    /**
     * @brief Get the position of self.
     * @return points of the position of self
     */
    QPoint getPos();

    /**
     * @brief Set color the brush on self.
     * @param brushColor color name
     */
    void setColor(QString brushColor);
};

#endif // G_SURFACE_H
