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

#ifndef W_LIFE_H
#define W_LIFE_H

#include <QWidget>

/**
 * @brief Diplay player's life on the game.
 * @details Widget that shows on top of the game the amount of life left of the player.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 02 Septembre 2015
 */
class W_Life : public QWidget
{
    Q_OBJECT
public:

    static W_Life* getInstance(QWidget* parent = 0);

    static W_Life* resetInstance(QWidget* parent = 0);

    void setSpecialTexture(bool value);

    /**
     * @brief Listen to the paint event
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Update the life amount to given.
     * @param value the amount to change to
     */
    void updateHearts(int value);

signals:

public slots:

private:
    static W_Life* instance;
    QString img;

    int totalLife;

    //Constructor
    /**
     * @brief Overlay widget to display lifes of the player.
     * @param parent if need
     */
    W_Life(QWidget *parent = 0);

};

#endif // W_LIFE_H
