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

#include "../surface/g_surface.h"

class QGraphicsItem;
class G_Gameboard;

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
    //Constructors
    /**
     * @brief Constructor with position setup.
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    S_Door(int xpos, int ypos, G_Gameboard* game,  QGraphicsItem *parent = 0);

//    /**
//     * @brief Constructor without position setup.
//     * @param parent QGraphicsItem to depend on
//     */
//    S_Door(QGraphicsItem *parent = 0);

    void setDirection(QChar direction);

    /**
     * @brief Toggle to know if it's the end of the current level.
     * @return true if it is the end of the level
     */
    bool isEndLevel();

    /**
     * @brief Set the level to go to after the end of current level.
     * @param value
     */
    void setLevelEnd(bool value);

    /**
     * @brief Set the item required to pass the door.
     * @param value name of the item
     */
    void setNeededItem(QString value);

    /**
     * @brief Get the item required to pass the door.
     * @return name of the item
     */
    QString getNeededItem();

    /**
     * @brief Toggle to know if the door need an item to unlock.
     * @return true if an item is required
     */
    bool isNeedingItem();

    /**
     * @brief Set the number of item required to pass the door.
     * @param nb
     */
    void setNbItem(int nb);

    /**
     * @brief Get the number of item required to pass the door.
     * @return nb
     */
    int getNbItem();

    /**
     * @brief Set the next level.
     * @param nb level number
     */
    void setNextLevel(int nb);

    /**
     * @brief Get the next level number.
     * @return nb next level level
     */
    int getNextLevel();

    void setBackground(bool state);

private:
    /**
     * @brief Set the design of self.
     */
    void setDesign(QChar direction);
    bool levelEnd;
    int nextLevel;

    bool needItem;
    int nbItem;
    QString* neededItem;
};

#endif // S_DOOR_H
