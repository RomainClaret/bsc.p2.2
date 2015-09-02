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

#include "character/c_enemy.h"

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

#include "surface/b_wall_alone.h"
#include "surface/b_wall_group.h"
#include "surface/b_water.h"
#include "surface/b_movable.h"
#include "surface/s_viewblocknpc.h"

#include "character/c_player.h"
#include "character/p_penguin.h"

#include "state/state_enemypatrol.h"
#include "state/state_enemysleep.h"
#include "state/state_enemypause.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

/**
 * @details Set the speed at 100, Z value at 2, detectPinguin to false, sens to true and the path given.
 * For the speed: 1 is really fast, 100 is really slow.
 */
C_Enemy::C_Enemy(QString orientation, QList<QPoint> path, G_Gameboard *g) : G_Character(g){
this->defaultOrientation = orientation;
    brain = new C_AI();

    direction = true;
    detectPlayableCharacter = false;

    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 100; //vitesse par défaut
    time = rand() % speed;

    setPath(path);
    setZValue(11);

    //default state
    state = new State_EnemyPause();
}

C_Enemy::~C_Enemy()
{
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        game->getGraphicsScene()->removeItem(vb);
        delete vb;
    }
    delete state;
}

/**
 * @detail replace the state of the enemy with newState
 */
void C_Enemy::changeState(State_Enemy* newState)
{
    delete state;
    this->state = newState;
}
/**
 * @detail getEnemyPos return the position with the correct coords on the map
 */
QPoint C_Enemy::getNPCPos()
{
    return convertPosPoint(this->pos());
}

void C_Enemy::moveByPixel(int x, int y)
{
    //todo
}

void C_Enemy::setPath(QList<QPoint> path)
{
    iDestPoint = 0;
    this->path = path;
    setPos(path.at(0).x(), path.at(0).y());
}

void C_Enemy::viewBlockActive()
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
            if(typeid(*item).name() == typeid(B_MovableSimple).name()
            || typeid(*item).name() == typeid(B_Wall_Alone).name()
            || typeid(*item).name() == typeid(B_Wall_Group).name()
            || typeid(*item).name() == typeid(C_Enemy).name())
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

void C_Enemy::playableCharacterDetection()
{
    detectPlayableCharacter = false;
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        if(vb->isActive())
        {
            QList<QGraphicsItem *> CollidingItems = vb->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(P_Penguin).name())
                {
                    vb->setStylePlayableCharacterOn();
                    P_Penguin* penguin = (P_Penguin*)CollidingItems.at(i);
                    penguin->endMove();
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
void C_Enemy::playableCharacterOnViewBlock()
{
    this->detectPlayableCharacter = true;
    game->disconnectTimer();
    game->restartEnigma();
    this->detectPlayableCharacter = false;

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        vb->setStyleActivated();
    }
}

QPoint C_Enemy::convertPosPoint(QPointF psrc)
{
    int x = (psrc.x()-1) /G_Gameboard::getGameSquares();
    int y = (psrc.y()-1) /G_Gameboard::getGameSquares();
    return QPoint(x, y);
}

/**
 * @details Check for each S_ViewBlocEnnemi of champVue if collides with B_Water, B_Movable, B_Wall, or Ennemi.
 */
bool C_Enemy::collide()
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
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_MovableSimple).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall_Alone).name() || typeid(*CollidingItems.at(i)).name() == typeid(B_Wall_Group).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(C_Enemy).name())
        {
            return true;
        }
    }
    return false;
}

/**
 * @details  Taking in account the direction of the enemy.
 */
int C_Enemy::nextPoint()
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
void C_Enemy::advance(int step)
{
    if(step == 1) //répond au second appel
    {
        state->step(this);

    }
}

void C_Enemy::setOrientation_top()
{
    orientation = 't';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), -vb->getColonne()));
    }
    update();
}
void C_Enemy::setOrientation_bottom()
{
    orientation = 'b';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(-vb->getLine(), vb->getColonne()));
    }
    update();
}
void C_Enemy::setOrientation_left()
{
    orientation = 'l';
    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(-vb->getColonne(), -vb->getLine()));
    }
    update();
}
void C_Enemy::setOrientation_right()
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
 * @details Define the position of the block S_ViewBlocEnnemi in function of its line and column.
 */
void C_Enemy::setPosViewBloc(S_ViewBlockNPC* bloc, QPoint p)
{
    int gs = G_Gameboard::getGameSquares();
    QPoint posEnnemi = convertPosPoint(this->pos());

    bloc->setPosPixel(posEnnemi.x()*gs + p.x()*gs+1, posEnnemi.y()*gs + p.y()*gs+1);
}

void C_Enemy::setPos(int x, int y)
{
    QGraphicsItem::setPos(x*G_Gameboard::getGameSquares()+1, y*G_Gameboard::getGameSquares()+1);

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), vb->getColonne()));
    }

    resetDefaultOrientation();
}

void C_Enemy::moveBy(int x, int y)
{
    int gameSquare = G_Gameboard::getGameSquares();

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        vb->moveBy(x*gameSquare,y*gameSquare);
    }

    QGraphicsItem::moveBy(x*gameSquare,y*gameSquare);
}

void C_Enemy::addToScene(QGraphicsScene* scene)
{
    scene->addItem(this);

    foreach (S_ViewBlockNPC* vb, viewField)
    {
        scene->addItem(vb);
    }
}

void C_Enemy::checkPenguin()
{

}

void C_Enemy::addDialog(QString text)
{
    dialogList.append(text);
}

void C_Enemy::resetDefaultOrientation()
{
    if(this->defaultOrientation == "TOP")
    {
        setOrientation_top();
    }
    else if(this->defaultOrientation == "BOTTOM")
    {
        setOrientation_bottom();
    }
    else if(this->defaultOrientation == "LEFT")
    {
        setOrientation_left();
    }
    else if(this->defaultOrientation == "RIGHT")
    {
        setOrientation_right();
    }
}

void C_Enemy::setDetectPlayableCharacter(bool value)
{
    detectPlayableCharacter = value;

    if(!value)
    {
        foreach (S_ViewBlockNPC* vb, viewField)
        {
            vb->setStyleActivated();
        }
    }
}
