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

#ifndef G_LEVEL_H
#define G_LEVEL_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;
class G_Gameboard;
class QStringList;

#include <QList>

#include "w_dialog.h"
#include <QDomElement>
#include <QDomDocument>

/**
 * @brief Level. Where the level informations are read (from XML) and stored.
 * @details This is the level which will contain the level information and generate the Scene with all items.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 19 August 2015
 */
class G_Level
{
public:
    /**
     * @brief Level's Constructor
     * @param levelNumber int containing the Level Number
     * @param game Gameboard*
     */
    G_Level(int levelNumber, G_Gameboard *game);

    /**
     * @brief Populate the QGraphicsScene according to XML Level File
     * @return QGraphicsScene* containing all items
     */
    QGraphicsScene* populateScene();

    /**
     * @brief Get the starting position of the Penguin
     * @return Starting QPoint*
     */
    QPoint* getStartingPoint();

    /**
     * @brief Get the starting x/y view position
     * @return Starting View QPoint*
     */
    QPoint getViewStart();

    /**
     * @brief Get the current Level Number
     * @return int Level Number
     */
    int getLevelNumber();

    /**
     * @brief Return the unlocking position
     * @return QPoint containing the unlocking position
     */
    QPoint getUnlockEndPoint();

    /**
     * @brief Add the informations from param into the class
     * @param elem QDomElement containing the informations
     */
    void addLevelInformation(QDomElement elem);

    /**
     * @brief Add the item from param into the scene
     * @param scene QGraphicsScene* from the level
     * @param elem QDomElement containing the informations
     * @param x xPosition
     * @param y yPosition
     */
    void addLevelItem(QGraphicsScene* scene, QDomElement elem, int x, int y);

private:
    // Level Playing Informations
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;
    QPoint* unlockEnd;

    // Game
    G_Gameboard *game;

    // Level Size
    int maxBlocksHeight;
    int maxBlocksWidth;

    // XML Informations Files
    QString fileName;
    QDomDocument* doc;
};

#endif // G_LEVEL_H
