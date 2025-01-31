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

#ifndef E_WALRUS_H
#define E_WALRUS_H
#include "../character/c_enemy.h"

class G_Gameboard;

/**
 * @brief Enemy Character: Walrus
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 21 August 2015
 */
class E_Walrus : public C_Enemy
{
public:
    //Constructors
    /**
     * @brief Constructor with path setup.
     * @param path QList of QPoint for the path
     * @param g Gameboard to depend on
     */
    E_Walrus(QString position, QList<QPoint> path, G_Gameboard *g);

    ~E_Walrus();

    void action();

    void setSpecialTexture(bool value);

private:
    G_Gameboard* gameBoard;
};

#endif // E_WALRUS_H
