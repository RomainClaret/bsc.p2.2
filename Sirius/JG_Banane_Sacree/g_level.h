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
class Observer_Enemy;
class S_SurfaceAutoTexture;
class B_Wall_Group;

#include <QList>
#include <QVector>

#include "widget/dialog/w_dialog.h"
#include <QDomElement>
#include <QList>
#include <QDomDocument>

#include "character/p_penguin.h"
#include "character/c_player.h"

class S_Door;

/**
 * @brief Where the level informations are read (from XML) and stored.
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
    G_Level(int levelNumber, Observer_Enemy* observer, G_Gameboard *game);

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

    void unlock();

    static int S_SNOW;
    static int B_WALL_GROUP;

    /**
     * @brief loadInformation
     */
    void loadInformation();

    void clearScene();

    void loadLevel(int levelNumber);

private:
    // Level Playing Informations
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;
    QPoint* unlockEnd;

    // Game
    G_Gameboard *game;
    Observer_Enemy *observerEnemy;

    // Level Size
    int maxBlocksHeight;
    int maxBlocksWidth;

    // XML Informations Files
    QString fileName;
    QDomDocument* doc;

    QList<S_SurfaceAutoTexture* > listAutoTextures;
    QList<B_Wall_Group* > listWallGroup;
    int** mapSurfacesSnow;
    int** mapSurfacesWallGroup;

    QList<S_Door*> doorList;

    QGraphicsScene* scene;

};

#endif // G_LEVEL_H
