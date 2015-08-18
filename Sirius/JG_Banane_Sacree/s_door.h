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

#ifndef S_DOOR_H
#define S_DOOR_H

#include "g_surface.h"

class QGraphicsItem;

/**
 * @brief View Transition Surface.
 * @details This surface can move player's view on the scene.
 * It checks if the level is completed.
 * Moves the player and changes the view to the next level is it's complited.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 18 August 2015
 */
class S_Door : public G_Surface
{
public:
    S_Door(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Door(QGraphicsItem *parent = 0);

    bool isEndLevel();
    void setLevelEnd(bool value);
    void setNeededItem(QString value);

    QString getNeededItem();
    bool isNeedingItem();

    void setNbItem(int nb);
    int getNbItem();

    void setNextLevel(int nb);
    int getNextLevel();

private:
    void setDesign();
    bool levelEnd;
    int nextLevel;

    bool needItem;
    int nbItem;
    QString* neededItem;
};

#endif // S_DOOR_H
