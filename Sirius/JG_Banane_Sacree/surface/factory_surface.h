#ifndef FACTORY_SURFACE_H
#define FACTORY_SURFACE_H

#include "../surface/g_surface.h"

#include "../surface/s_dialog.h"
#include "../surface/s_ice.h"
#include "../surface/s_snow.h"
#include "../surface/s_viewblocknpc.h"
#include "../surface/s_door.h"
#include "../surface/s_fire.h"
#include "../surface/s_stone.h"

#include "../surface/b_movable.h"
#include "../surface/b_movable_simple.h"
#include "../surface/b_movable_throw.h"
#include "../surface/b_wall.h"
#include "../surface/b_water.h"
#include "../surface/b_wall_alone.h"
#include "../surface/b_wall_group.h"

#include "g_gameboard.h"

class QGraphicsScene;

/**
 * @brief Factory for surfaces
 * @details Design pattern Factory for surfaces. Using a methode to create a specific surface and add it to the given scene.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.6
 * @date 31 August 2015
 */
class Factory_Surface
{
public:

    static QString SURFACE_ICE;
    static QString SURFACE_SNOW;
    static QString SURFACE_DIALOG;
    static QString SURFACE_DOOR;
    static QString BLOC_MOVABLE;
    static QString BLOC_WALL_ALONE;
    static QString BLOC_WALL_GROUP;
    static QString BLOC_WATER;
    static QString BLOC_FIRE;
    static QString BLOC_STONE;

    /**
     * @brief Creates, returns and add given item to scene.
     * @param type type of the item to add
     * @param xpos x-axis position of the item to add
     * @param ypos y-axis position of the item to add
     * @param scene scene to add the surface to
     * @return G_Surface* of created item
     */
    static G_Surface* createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Ice Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return S_Ice* of created item
     */
    static S_Ice* createSurfaceIce(int xpos, int ypos, QGraphicsScene *scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Snow Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return S_Snow* of created item
     */
    static S_Snow* createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Dialog Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @param text text to display
     * @param image image to display
     * @return S_Dialog* of created item
     */
    static S_Dialog* createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game, QString text = "", QString image="");

    /**
     * @brief Creates, returns and add a Door Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return S_Door* of created item
     */
    static S_Door* createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Door Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param item name of the item required
     * @param quantity number of items required
     * @param scene scene to add the surface to
     * @return S_Door* of created item
     */
    static S_Door* createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Door Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param nextLevel level to move the player to
     * @param scene scene to add the surface to
     * @return S_Door* of created item
     */
    static S_Door* createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Movable Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return B_Movable* of created item
     */
    static B_MovableSimple* createBlocMovable(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Movable Throw Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return B_Movable* of created item
     */
    static B_MovableThrow* createBlocMovableThrow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard* game);

    /**
     * @brief Creates, returns and add a Wall Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return B_Wall_Alone* of created item
     */
    static B_Wall_Alone* createBlocWallAlone(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Wall Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return B_Wall_Group* of created item
     */
    static B_Wall_Group* createBlocWallGroup(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);


    /**
     * @brief Creates, returns and add a Water Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return B_Water* of created item
     */
    static B_Water* createBlocWater(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Fire Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return S_Fire* of created item
     */
    static S_Fire* createBlocFire(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);

    /**
     * @brief Creates, returns and add a Stone Surface to scene.
     * @param xpos x-axis position of the item
     * @param ypos y-axis position of the item
     * @param scene scene to add the surface to
     * @return S_Stone* of created item
     */
    static S_Stone* createBlocStone(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game);
};

#endif // FACTORY_SURFACE_H
