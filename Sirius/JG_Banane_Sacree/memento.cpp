#include "memento.h"
#include "g_gameboard.h"
#include "surface/b_movable_throw.h"
#include <QDebug>

#include "character/e_fox.h"
#include "character/e_wolf.h"
#include "character/e_otter.h"
#include "character/e_walrus.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

Memento::Memento()
{
}

Memento* Memento::getInstance()
{
    if(instance == NULL)
    {
        instance = new Memento();
    }
    return instance;
}

void Memento::setPosSurface(G_Surface* item, QPoint* position)
{
    hashMapSurface[item] = position;
}

QPoint* Memento::getPosSurface(G_Surface* item)
{
    return hashMapSurface[item];
}

void Memento::setPosCharacter(C_Enemy* item, QPoint* position)
{
    hashMapCharacter[item] = position;
}

QPoint* Memento::getPosCharacter(C_Enemy* item)
{
    return hashMapCharacter[item];
}

void Memento::saveCheckpoint()
{
    QHashIterator<G_Surface*, QPoint*> i(hashMapSurface);
    while (i.hasNext()) {
        i.next();
        hashMapSurface[i.key()] = new QPoint(i.key()->pos().x(),i.key()->pos().y());
    }
}

void Memento::restartLevel(QGraphicsScene* mainScene)
{
    qDebug() << "MEMENTO >> RESTART LEVEL";
    QHashIterator<G_Surface*, QPoint*> i(hashMapSurface);
    while (i.hasNext())
    {
        i.next();
        QList<QGraphicsItem *> list = mainScene->items(QPointF(i.key()->pos().x(),i.key()->pos().y()));
        i.key()->setPosition(i.value()->x()/32,i.value()->y()/32);

        if(list.indexOf(i.key()) == -1)
        {
            mainScene->addItem(i.key());
        }
    }

    QHashIterator<C_Enemy*, QPoint*> j(hashMapCharacter);
    while (j.hasNext()) {
        j.next();
        j.key()->setPos(j.value()->x(),j.value()->y());
    }

    for(int k = 0; k < specialEventSurface.size(); ++k)
    {
        specialEventSurface.at(k)->removeFromScene(mainScene);
    }

    for(int l = 0; l < removedSurface.size(); ++l)
    {
        removedSurface.at(l)->addToScene(mainScene);
        hashMapSurface[removedSurface.at(l)] = new QPoint(removedSurface.at(l)->x(), removedSurface.at(l)->y());
    }

    specialEventSurface.clear();
    removedSurface.clear();
}

void Memento::clear()
{
    specialEventSurface.clear();
    removedSurface.clear();
    hashMapSurface.clear();
    hashMapCharacter.clear();
    eggList.clear();
}

void Memento::addSpecialEventSurface(G_Surface* element)
{
    specialEventSurface.append(element);
}

void Memento::addRemovedSurface(G_Surface* element)
{
    if(hashMapSurface.contains(element))
    {
        int size = G_Gameboard::getGameSquares();
        element->setPosition(hashMapSurface[element]->x()/size,hashMapSurface[element]->y()/size);
    }
    removedSurface.append(element);
}

void Memento::removePosSurface(G_Surface* item)
{
    hashMapSurface.remove(item);
}

Memento* Memento::instance = NULL;

void Memento::removeSpecialEventSurface(QGraphicsScene* scene, G_Surface* movable)
{
    for(int i = 0; i < specialEventSurface.size(); ++i)
    {
        if(specialEventSurface.at(i) == movable)
        {
            specialEventSurface.at(i)->removeFromScene(scene);
            specialEventSurface.removeAt(i);
        }
    }
}

void Memento::setSpecialTextureEnemy(bool value)
{
    QHashIterator<C_Enemy*, QPoint*> j(hashMapCharacter);
    while (j.hasNext()) {
        j.next();
        j.key()->setSpecialTexture(value);
    }
}

void Memento::addSpecialItemEgg(G_Object *item)
{
    eggList.append(item);
}

void Memento::setSpecialTextureEgg(bool value)
{
    for(int i = 0; i < eggList.size(); ++i)
    {
        eggList.at(i)->setSpecialTexture(value);
    }
}
