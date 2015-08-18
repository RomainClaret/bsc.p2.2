#include "surfacefactory.h"

#include <QGraphicsScene>

QString SurfaceFactory::SURFACE_ICE = "ICE";
QString SurfaceFactory::SURFACE_SNOW = "SNOW";
QString SurfaceFactory::SURFACE_DIALOG = "DIALOG";
QString SurfaceFactory::SURFACE_DOOR = "DOOR";
QString SurfaceFactory::BLOC_MOVABLE = "MOVABLE";
QString SurfaceFactory::BLOC_WALL = "WALL";
QString SurfaceFactory::BLOC_WATER = "WATER";

Surface* SurfaceFactory::createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene)
{
    if(type == SURFACE_ICE)
    {
        return createSurfaceIce(xpos, ypos, scene);
    }
    else if(type == SURFACE_SNOW)
    {
        return createSurfaceSnow(xpos, ypos, scene);
    }
    else if(type == SURFACE_DIALOG)
    {
        return createSurfaceDialog(xpos, ypos, scene);
    }
    else if(type == SURFACE_DOOR)
    {
        return createSurfaceDoor(xpos, ypos, scene);
    }
    else if(type == BLOC_MOVABLE)
    {
        return createBlocMovable(xpos, ypos, scene);
    }
    else if(type == BLOC_WALL)
    {
        return createBlocWall(xpos, ypos, scene);
    }
    else if(type == BLOC_WATER)
    {
        return createBlocWater(xpos, ypos, scene);
    }
    return NULL;
}

S_Ice* SurfaceFactory::createSurfaceIce(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Ice* i = new S_Ice(xpos, ypos);
    scene->addItem(i);
    return i;
}

S_Snow* SurfaceFactory::createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Snow* s = new S_Snow(xpos, ypos);
    scene->addItem(s);
    return s;
}

S_Dialog* SurfaceFactory::createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, QString text)
{
    S_Dialog *d = new S_Dialog(xpos, ypos);
    d->addDialogText(text);
    scene->addItem(d);
    return d;
}

S_ViewTransition* SurfaceFactory::createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene)
{
    S_ViewTransition* d = new S_ViewTransition(xpos,ypos);
    d->setLevelEnd(false);
    scene->addItem(d);
    return d;
}

S_ViewTransition* SurfaceFactory::createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene)
{
    S_ViewTransition* d = new S_ViewTransition(xpos,ypos);
    d->setLevelEnd(false);
    d->setNeededItem(item);
    d->setNbItem(quantity);
    scene->addItem(d);
    return d;
}

S_ViewTransition* SurfaceFactory::createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene)
{
    S_ViewTransition *d = new S_ViewTransition(xpos,ypos);
    d->setLevelEnd(true);
    d->setNextLevel(nextLevel);
    scene->addItem(d);
    return d;
}

B_Movable* SurfaceFactory::createBlocMovable(int xpos, int ypos, QGraphicsScene* scene)
{
    B_Movable* m = new B_Movable(xpos,ypos);
    m->addToScene(scene);
    return m;
}

B_Wall* SurfaceFactory::createBlocWall(int xpos, int ypos, QGraphicsScene* scene)
{
    B_Wall* w = new B_Wall(xpos, ypos);
    scene->addItem(w);
    return w;
}

B_Water* SurfaceFactory::createBlocWater(int xpos, int ypos, QGraphicsScene* scene)
{
    B_Water *w = new B_Water(xpos, ypos);
    scene->addItem(w);
    return w;
}
