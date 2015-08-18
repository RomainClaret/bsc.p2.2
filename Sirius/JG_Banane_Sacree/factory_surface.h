#ifndef FACTORY_SURFACE_H
#define FACTORY_SURFACE_H

#include "g_surface.h"

#include "s_dialog.h"
#include "s_ice.h"
#include "s_snow.h"
#include "s_viewblocknpc.h"
#include "s_door.h"

#include "b_movable.h"
#include "b_wall.h"
#include "b_water.h"

class QGraphicsScene;

class Factory_Surface
{
public:

    static QString SURFACE_ICE;
    static QString SURFACE_SNOW;
    static QString SURFACE_DIALOG;
    static QString SURFACE_DOOR;
    static QString BLOC_MOVABLE;
    static QString BLOC_WALL;
    static QString BLOC_WATER;

    static G_Surface* createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene);
    static S_Ice* createSurfaceIce(int xpos, int ypos, QGraphicsScene *scene);
    static S_Snow* createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene);
    static S_Dialog* createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, QString text = "");
    static S_Door* createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene);
    static S_Door* createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene);
    static S_Door* createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene);
    static B_Movable* createBlocMovable(int xpos, int ypos, QGraphicsScene* scene);
    static B_Wall* createBlocWall(int xpos, int ypos, QGraphicsScene* scene);
    static B_Water* createBlocWater(int xpos, int ypos, QGraphicsScene* scene);
};

#endif // FACTORY_SURFACE_H
