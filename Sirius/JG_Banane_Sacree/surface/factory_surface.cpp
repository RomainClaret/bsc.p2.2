#include "../surface/factory_surface.h"
#include "t_movesurface.h"
#include <QGraphicsScene>

#include <QDebug>

QString Factory_Surface::SURFACE_ICE = "ICE";
QString Factory_Surface::SURFACE_SNOW = "SNOW";
QString Factory_Surface::SURFACE_DIALOG = "DIALOG";
QString Factory_Surface::SURFACE_DOOR = "DOOR";
QString Factory_Surface::BLOC_MOVABLE = "MOVABLE";
QString Factory_Surface::BLOC_WALL = "WALL";
QString Factory_Surface::BLOC_WATER = "WATER";
QString Factory_Surface::BLOC_FIRE = "FIRE";
QString Factory_Surface::BLOC_STONE = "STONE";

/**
 * @details Returns NULL if the given type is not found.
 */
G_Surface* Factory_Surface::createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene)
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
    else if(type == BLOC_FIRE)
    {
        return createBlocFire(xpos, ypos, scene);
    }
    else if(type == BLOC_STONE)
    {
        return createBlocStone(xpos, ypos, scene);
    }
    return NULL;
}

S_Ice* Factory_Surface::createSurfaceIce(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Ice* i = new S_Ice(xpos, ypos);
    i->addToScene(scene);
    return i;
}

S_Snow* Factory_Surface::createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Snow* s = new S_Snow(xpos, ypos);
    scene->addItem(s);
    return s;
}

S_Dialog* Factory_Surface::createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, QString text, QString image)
{
    S_Dialog *d = new S_Dialog(xpos, ypos);
    d->addDialogText(text);
    d->setImage(image);
    scene->addItem(d);
    return d;
}

S_Door* Factory_Surface::createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Door* d = new S_Door(xpos,ypos);
    d->setLevelEnd(false);
    scene->addItem(d);
    return d;
}

S_Door* Factory_Surface::createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene)
{
    S_Door* d = new S_Door(xpos,ypos);
    d->setLevelEnd(false);
    d->setNeededItem(item);
    d->setNbItem(quantity);
    scene->addItem(d);
    return d;
}

S_Door* Factory_Surface::createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene)
{
    S_Door *d = new S_Door(xpos,ypos);
    d->setLevelEnd(true);
    d->setNextLevel(nextLevel);
    scene->addItem(d);
    return d;
}

B_MovableSimple *Factory_Surface::createBlocMovable(int xpos, int ypos, QGraphicsScene* scene)
{
    B_MovableSimple* m = new B_MovableSimple(xpos,ypos);
    m->addToScene(scene);
    return m;
}

B_MovableThrow *Factory_Surface::createBlocMovableThrow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard* game)
{
    B_MovableThrow* m = new B_MovableThrow(xpos,ypos, game);
    m->addToScene(scene);
    T_MoveSurface timer(m,scene);
    return m;
}

B_Wall* Factory_Surface::createBlocWall(int xpos, int ypos, QGraphicsScene* scene)
{
    B_Wall* w = new B_Wall(xpos, ypos);
    scene->addItem(w);
    return w;
}

B_Water* Factory_Surface::createBlocWater(int xpos, int ypos, QGraphicsScene* scene)
{
    B_Water *w = new B_Water(xpos, ypos);
    w->addToScene(scene);
    return w;
}

S_Fire* Factory_Surface::createBlocFire(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Fire *f = new S_Fire(xpos, ypos);
    scene->addItem(f);
    return f;
}

S_Stone* Factory_Surface::createBlocStone(int xpos, int ypos, QGraphicsScene* scene)
{
    S_Stone *s = new S_Stone(xpos, ypos);
    scene->addItem(s);
    return s;
}
