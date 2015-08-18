#ifndef SURFACEFACTORY_H
#define SURFACEFACTORY_H

#include "surface.h"

#include "s_dialog.h"
#include "s_ice.h"
#include "s_snow.h"
#include "s_viewblockenemy.h"
#include "s_viewtransition.h"

#include "b_movable.h"
#include "b_wall.h"
#include "b_water.h"

class QGraphicsScene;

class SurfaceFactory
{
public:

    static QString SURFACE_ICE;
    static QString SURFACE_SNOW;
    static QString SURFACE_DIALOG;
    static QString SURFACE_DOOR;
    static QString BLOC_MOVABLE;
    static QString BLOC_WALL;
    static QString BLOC_WATER;

    static Surface* createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene);
    static S_Ice* createSurfaceIce(int xpos, int ypos, QGraphicsScene *scene);
    static S_Snow* createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene);
    static S_Dialog* createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, QString text = "");
    static S_ViewTransition* createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene);
    static S_ViewTransition* createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene);
    static S_ViewTransition* createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene);
    static B_Movable* createBlocMovable(int xpos, int ypos, QGraphicsScene* scene);
    static B_Wall* createBlocWall(int xpos, int ypos, QGraphicsScene* scene);
    static B_Water* createBlocWater(int xpos, int ypos, QGraphicsScene* scene);
};

#endif // SURFACEFACTORY_H
