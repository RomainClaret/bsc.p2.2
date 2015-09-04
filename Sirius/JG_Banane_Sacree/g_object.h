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

#ifndef G_OBJECT_H
#define G_OBJECT_H


#include "surface/g_surface.h"

class QGraphicsItem;
class QPixmap;
class QGraphicsPixmapItem;
class QBrush;
class QPaintEvent;
class G_Gameboard;

/**
 * @brief Object from the game
 * @details Set the object's info and its skin.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */

class G_Object : public G_Surface
{
public:
    //Constructors
    /**
     * @brief Constructor for an object
     * @param xpos x-axis position of the item to add
     * @param ypos y-axis position of the item to add
     * @param parent QGraphicsItem* of the created item
     */
    G_Object(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor for an object
     * @param name name of the object
     * @param parent QGraphicsItem* of the created item
     */
    G_Object(QString name, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Constructor for an object
     * @param name name of the object
     * @param xpos x-axis position of the item to add
     * @param ypos y-axis position of the item to add
     * @param parent QGraphicsItem* of the created item
     */
    G_Object(QString name, int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent = 0);

    /**
     * @brief Set the skin of self.
     */
    void setDesign();

    /**
     * @brief Get the name of self.
     * @return name of self
     */
    QString getName();

    /**
     * @brief Get the texture of self.
     * @return texture of self
     */
    QPixmap getTexture();

    void setSpecialTexture(bool value);

    static QString OBJECT_EGG;
    static QString OBJECT_SHOES;
    static QString OBJECT_FISH;
    static QString OBJECT_BANANA;

private:
    QBrush* objectSkin;
    QString* nom;

};

#endif // G_OBJECT_H
