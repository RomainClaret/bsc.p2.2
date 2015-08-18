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

#include "g_npc.h"

#include <QGraphicsItem>
#include <QPoint>
#include <QList>

#include <QBrush>
#include <QPen>
#include <QGraphicsRectItem>

#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

#include "g_gameboard.h"
#include "b_wall.h"
#include "b_water.h"
#include "b_movable.h"
#include "g_player.h"
#include "c_penguin.h"
#include "s_viewblocknpc.h"

#include "state_npcpatrol.h"
#include "state_npcsleep.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

/**
 * @details Set the speed at 100, Z value at 2, detectPinguin to false, sens to true and the path given.
 * For the speed: 1 is really fast, 100 is really slow.
 */
G_NPC::G_NPC(QList<QPoint> path, G_Gameboard *g)
{
    game = g;

    direction = true;
    detectPlayableCharacter = false;

    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 100; //vitesse par défaut
    time = rand() % speed;

    setPath(path);
    setZValue(2);


    //default state
    state = new State_NPCPatrol();
}

G_NPC::~G_NPC()
{
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        delete vb;
    }

    delete state;
}

/**
 * @detail replace the state of the enemy with newState
 */
void G_NPC::changeState(State_NPC* newState)
{
    delete state;
    this->state = newState;
}
/**
 * @detail getEnemyPos return the position with the correct coords on the map
 */
QPoint G_NPC::getNPCPos()
{
    return convertPosPoint(this->pos());
}

void G_NPC::setPath(QList<QPoint> path)
{
    iDestPoint = 0;
    this->path = path;
    setPos(path.at(0).x(), path.at(0).y());
}

void G_NPC::viewBlockActive()
{
    QList<QPoint> toDesactivate;
    bool allunactived = false;

    QList<S_ViewBlockNPC* >::iterator it;
    for (it = viewField.begin(); it != viewField.end(); ++it)
    {
        //On les active tous !
        (*it)->setActive(true);

        //lesquels on va désactiver ?
        QList<QGraphicsItem *> CollidingItems = (*it)->collidingItems();
        bool bUnactivate = false;

        foreach (QGraphicsItem *item, CollidingItems) {
            if(typeid(*item).name() == typeid(B_Movable).name()
            || typeid(*item).name() == typeid(B_Wall).name()
            || typeid(*item).name() == typeid(G_NPC).name())
            {
                bUnactivate = true;
            }
        }

        if(bUnactivate)
        {
            if((*it)->getLine()==0 && (*it)->getColonne() ==1) //si c'est le bloc 1
            {
                allunactived = true;
            }
            toDesactivate.append(QPoint((*it)->getLine(), (*it)->getColonne()));
        }
    }

    //on déactive ce qu'il faut
    foreach (QPoint toDes, toDesactivate)
    {
        QList<S_ViewBlockNPC*>::iterator it;
        for (it = viewField.begin(); it != viewField.end(); ++it)
        {
            //on désactive la ligne
            if(((*it)->getColonne() >= toDes.y() && (*it)->getLine() == toDes.x()) || allunactived)
            {
                (*it)->setActive(false);
            }
        }
    }

}

void G_NPC::playableCharacterDetection()
{
    detectPlayableCharacter = false;
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        if(vb->isActive())
        {
            QList<QGraphicsItem *> CollidingItems = vb->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(C_Penguin).name())
                {
                    vb->setStylePlayableCharacterOn();
                    playableCharacterOnViewBlock();
                }
            }
        }
    }
}

/**
  * @details Called by the s_viewblocennemi if the playable character collides with it,
  * Or by the enemy if the playable character is detected.
  */
void G_NPC::playableCharacterOnViewBlock()
{
    this->detectPlayableCharacter = true;
    game->restartEnigma();
}

QPoint G_NPC::convertPosPoint(QPointF psrc)
{
    int x = (psrc.x()-1) /G_Gameboard::getGameSquares();
    int y = (psrc.y()-1) /G_Gameboard::getGameSquares();
    return QPoint(x, y);
}

/**
 * @details Check for each S_ViewBlocEnnemi of champVue if collides with B_Water, B_Movable, B_Wall, or Ennemi.
 */
bool G_NPC::collide()
{
    S_ViewBlockNPC *collideRect;
    foreach (S_ViewBlockNPC* vb, viewField) {
        if(vb->getColonne()==1 && vb->getLine()==0){
            collideRect = vb;
        }
    }

    QList<QGraphicsItem *> CollidingItems = collideRect->collidingItems();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(G_NPC).name())
        {
            return true;
        }
    }
    return false;
}

/**
 * @details  Taking in account the direction of the enemy.
 */
int G_NPC::nextPoint()
{
    if(direction)
    {
        iDestPoint ++;
    }
    else
    {
        iDestPoint --;
    }

    if(iDestPoint>path.size()-1)
    {
        iDestPoint = 0;
    }
    else if(iDestPoint<0)
    {
        iDestPoint = path.size()-1;
    }

    return iDestPoint;
}

/**
 * @details Executed at each call of the slot advance() from the Scene.
 * It is the brain of the enemy.
 */
void G_NPC::advance(int step)
{
    if(step == 1) //répond au second appel
    {
        state->step(this);
    }
}

void G_NPC::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Draw the ennemi
    painter->setPen(Qt::transparent);

    npcSkin = new QBrush();

    //Set ennemiSkin texture depending on ennemi's orientation
    switch (orientation) {
    case 'l':
        npcSkin->setTexture(QPixmap(leftSkin));
        break;
    case 'r':
        npcSkin->setTexture(QPixmap(rightSkin));
        break;
    case 't':
        npcSkin->setTexture(QPixmap(upSkin));
        break;
    case 'b':
        npcSkin->setTexture(QPixmap(downSkin));
        break;
    default:
        break;
    }

    QRectF ennemiBox = boundingRect();  //Setting ennemi's box

    painter->fillRect(ennemiBox,*npcSkin);   //charger la couleur
    painter->drawRect(ennemiBox);
}

QRectF G_NPC::boundingRect() const
{
    return QRectF(0,0,G_Gameboard::getGameSquares()-2,G_Gameboard::getGameSquares()-2);
}

void G_NPC::setOrientation_top()
{
    orientation = 't';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), -vb->getColonne()));
    }
    update();
}
void G_NPC::setOrientation_bottom()
{
    orientation = 'b';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(-vb->getLine(), vb->getColonne()));
    }
    update();
}
void G_NPC::setOrientation_left()
{
    orientation = 'l';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(-vb->getColonne(), -vb->getLine()));
    }
    update();
}
void G_NPC::setOrientation_right()
{
    orientation = 'r';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(vb->getColonne(), vb->getLine()));
    }
    update();
}

//Défini la position d'un bloc "viewBloc" en fonction de sa ligne et sa colonne
/**
 * @details Define the poistion of the block S_ViewBlocEnnemi in function of its line and column.
 */
void G_NPC::setPosViewBloc(S_ViewBlockNPC* bloc, QPoint p)
{
    int gs = G_Gameboard::getGameSquares();
    QPoint posEnnemi = convertPosPoint(this->pos());

    bloc->setPosPixel(posEnnemi.x()*gs + p.x()*gs+1, posEnnemi.y()*gs + p.y()*gs+1);
}

void G_NPC::setPos(int x, int y)
{
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), vb->getColonne()));
    }

    QGraphicsItem::setPos(x*G_Gameboard::getGameSquares()+1, y*G_Gameboard::getGameSquares()+1);
}

void G_NPC::moveBy(int x, int y)
{
    int gameSquare = G_Gameboard::getGameSquares();

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        vb->moveBy(x*gameSquare,y*gameSquare);
    }

    QGraphicsItem::moveBy(x*gameSquare,y*gameSquare);
}

void G_NPC::addToScene(QGraphicsScene* scene)
{
    scene->addItem(this);

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        scene->addItem(vb);
    }
}
