#include "../surface/factory_surface.h"
#include "t_movesurface.h"
#include <QGraphicsScene>
#include "memento.h"
#include <QDebug>

QString Factory_Surface::SURFACE_ICE = "ICE";
QString Factory_Surface::SURFACE_SNOW = "SNOW";
QString Factory_Surface::SURFACE_DIALOG = "DIALOG";
QString Factory_Surface::SURFACE_DOOR = "DOOR";
QString Factory_Surface::BLOC_MOVABLE = "MOVABLE";
QString Factory_Surface::BLOC_WALL_ALONE = "WALL";
QString Factory_Surface::BLOC_WALL_GROUP = "WALLGROUP";
QString Factory_Surface::BLOC_WATER = "WATER";
QString Factory_Surface::BLOC_FIRE = "FIRE";
QString Factory_Surface::BLOC_STONE = "STONE";

/**
 * @details Returns NULL if the given type is not found.
 */
G_Surface* Factory_Surface::createSurface(QString type, int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    if(type == SURFACE_ICE)
    {
        return createSurfaceIce(xpos, ypos, scene, game);
    }
    else if(type == SURFACE_SNOW)
    {
        return createSurfaceSnow(xpos, ypos, scene, game);
    }
    else if(type == SURFACE_DIALOG)
    {
        return createSurfaceDialog(xpos, ypos, scene, game);
    }
    else if(type == SURFACE_DOOR)
    {
        return createSurfaceDoor(xpos, ypos, scene, game);
    }
    else if(type == BLOC_MOVABLE)
    {
        return createBlocMovable(xpos, ypos, scene, game);
    }
    else if(type == BLOC_WALL_ALONE)
    {
        return createBlocWallAlone(xpos, ypos, scene, game);
    }
    else if(type == BLOC_WALL_GROUP)
    {
        return createBlocWallGroup(xpos, ypos, scene, game);
    }
    else if(type == BLOC_WATER)
    {
        return createBlocWater(xpos, ypos, scene, game);
    }
    else if(type == BLOC_FIRE)
    {
        return createBlocFire(xpos, ypos, scene, game);
    }
    else if(type == BLOC_STONE)
    {
        return createBlocStone(xpos, ypos, scene, game);
    }
    return NULL;
}

S_Ice* Factory_Surface::createSurfaceIce(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Ice* i = new S_Ice(xpos, ypos,game);
    i->addToScene(scene);
    return i;
}

S_Snow* Factory_Surface::createSurfaceSnow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Snow* s = new S_Snow(xpos, ypos, scene,game);
    scene->addItem(s);
    return s;
}

S_Dialog* Factory_Surface::createSurfaceDialog(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game, QString text, QString image)
{
    S_Dialog *d = new S_Dialog(xpos, ypos,game);
    d->addDialogText(text);
    d->setImage(image);
    scene->addItem(d);

    Memento::getInstance()->setPosSurface(d,new QPoint(xpos, ypos));
    return d;
}

S_Door* Factory_Surface::createSurfaceDoor(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Door* d = new S_Door(xpos,ypos,game);
    d->setLevelEnd(false);
    scene->addItem(d);

    Memento::getInstance()->setPosSurface(d,new QPoint(xpos, ypos));
    return d;
}

S_Door* Factory_Surface::createSurfaceDoor(int xpos, int ypos, QString item, int quantity, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Door* d = new S_Door(xpos,ypos,game);
    d->setLevelEnd(false);
    d->setNeededItem(item);
    d->setNbItem(quantity);
    scene->addItem(d);

    Memento::getInstance()->setPosSurface(d,new QPoint(xpos, ypos));

    return d;
}

S_Door* Factory_Surface::createSurfaceLastDoor(int xpos, int ypos, int nextLevel, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Door *d = new S_Door(xpos,ypos,game);
    d->setLevelEnd(true);
    d->setNextLevel(nextLevel);
    scene->addItem(d);

    Memento::getInstance()->setPosSurface(d,new QPoint(xpos, ypos));

    return d;
}

B_MovableSimple *Factory_Surface::createBlocMovable(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    B_MovableSimple* m = new B_MovableSimple(xpos, ypos, game, scene);
    m->addToScene(scene);
    Memento::getInstance()->setPosSurface(m,new QPoint(xpos, ypos));
    return m;
}

B_MovableThrow *Factory_Surface::createBlocMovableThrow(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard* game)
{
    B_MovableThrow* m = new B_MovableThrow(xpos,ypos, game);
    m->addToScene(scene);
    Memento::getInstance()->addSpecialEventSurface(m);
    return m;
}

B_Wall_Alone* Factory_Surface::createBlocWallAlone(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    B_Wall_Alone* w = new B_Wall_Alone(xpos, ypos, game);
    scene->addItem(w);
    return w;
}

B_Wall_Group* Factory_Surface::createBlocWallGroup(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    B_Wall_Group* w = new B_Wall_Group(xpos, ypos, game);
    w->addToScene(scene);
    return w;
}

B_Water* Factory_Surface::createBlocWater(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    B_Water *w = new B_Water(xpos, ypos, game);
    w->addToScene(scene);
    return w;
}

S_Fire* Factory_Surface::createBlocFire(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Fire *f = new S_Fire(xpos, ypos, game);
    scene->addItem(f);
    return f;
}

S_Stone* Factory_Surface::createBlocStone(int xpos, int ypos, QGraphicsScene* scene, G_Gameboard *game)
{
    S_Stone *s = new S_Stone(xpos, ypos, game);
    scene->addItem(s);
    return s;
}
