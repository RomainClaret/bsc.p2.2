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

#ifndef W_OBJECT_H
#define W_OBJECT_H

#include <QWidget>
#include "g_object.h"
#include <QList>
#include <QMap>

/**
 * @brief Diplay player's bag on the game.
 * @details Widget that shows on top of the game the objects owned by the player.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class W_Object : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Overlay widget to display objects of the player.
     * @param parent if need
     */
    W_Object(QWidget *parent = 0);

    /**
     * @brief Listen to the paint event
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Update the object list to given.
     * @param objectList list of objects
     */
    void reloadObjectList(QList<G_Object*> objectList);

signals:

public slots:

private:
    QList<G_Object* > sacoche;
    QMap<QString, int> map;

};

#endif // W_OBJECT_H
