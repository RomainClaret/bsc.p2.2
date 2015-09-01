#ifndef MEMENTO_H
#define MEMENTO_H

#include <QHash>
#include "surface/g_surface.h"
#include "character/c_enemy.h"
#include <QGraphicsScene>
#include <QPoint>
#include <QList>
#include "surface/b_movable.h"
#include "surface/b_movable_throw.h"

class Memento
{
public:
    static Memento* getInstance();

    void setPosSurface(G_Surface* item, QPoint* position);
    void removePosSurface(G_Surface* item);
    QPoint* getPosSurface(G_Surface* item);
    void setPosCharacter(C_Enemy* item, QPoint* position);
    QPoint* getPosCharacter(C_Enemy* item);
    void clear();
    void saveCheckpoint();
    void restartLevel(QGraphicsScene* mainScene);
    void addSpecialEventSurface(G_Surface*element);
    void removeSpecialEventSurface(QGraphicsScene *scene, G_Surface *movable);
    void addRemovedSurface(G_Surface *element);

private:
    Memento();
    static Memento* instance;
    QHash<G_Surface*,QPoint*> hashMapSurface;
    QHash<C_Enemy*,QPoint*> hashMapCharacter;
    QList<G_Surface*> specialEventSurface;
    QList<G_Surface*>removedSurface;
};

#endif // MEMENTO_H
