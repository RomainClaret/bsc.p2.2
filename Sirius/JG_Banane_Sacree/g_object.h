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


#include "g_surface.h"

class QGraphicsItem;
class QPixmap;
class QGraphicsPixmapItem;
class QBrush;

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
    G_Object(int xpos, int ypos, QGraphicsItem *parent = 0);
    G_Object(QString name, QGraphicsItem *parent = 0);
    G_Object(QString name, int xpos, int ypos, QGraphicsItem *parent = 0);

    void setDesign();
    QString getName();
    QPixmap getTexture();

    static QString OBJECT_EGG;
    static QString OBJECT_SHOES;
    static QString OBJECT_FISH;

private:
    QBrush* objectSkin;
    QString* nom;

};

#endif // G_OBJECT_H
