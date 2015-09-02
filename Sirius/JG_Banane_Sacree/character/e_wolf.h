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

#ifndef E_WOLF_H
#define E_WOLF_H
#include "../character/c_enemy.h"

class G_Gameboard;

/**
 * @brief Enemy Character: Wolf
 * @details This is a character with its own characteristics.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
class E_Wolf : public C_Enemy
{
public:
    //Constructors
    /**
     * @brief Constructor with path setup.
     * @param path QList of QPoint for the path
     * @param g Gameboard to depend on
     */
    E_Wolf(QString position, QList<QPoint> path, G_Gameboard *g);

    void setSpecialTexture(bool value);
};

#endif // E_WOLF_H
