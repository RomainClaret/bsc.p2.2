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

#include "ennemi.h"

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

#include "gameboard.h"
#include "b_wall.h"
#include "b_water.h"
#include "b_movable.h"
#include "player.h"
#include "p_penguin.h"
#include "s_viewblocennemi.h"

#include "stateennemi_patrol.h"
#include "stateennemi_sleep.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

Ennemi::Ennemi(QList<QPoint> path, Gameboard *g)
{
    game = g;

    sens = true;
    detectPinguin = false;

    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 100; //vitesse par défaut
    time = rand() % speed;

    setPath(path);
    setZValue(2);


    //default state
    state = new StateEnnemi_Patrol();
}

Ennemi::~Ennemi()
{
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        delete vb;
    }

    delete state;
}

/**
 * @detail replace the state of the enemy with newState
 */
void Ennemi::changeState(StateEnnemi* newState)
{
    delete state;
    this->state = newState;
}
/**
 * @detail getEnemyPos return the position with the correct coords on the map
 */
QPoint Ennemi::getEnemyPos()
{
    return convertPosPoint(this->pos());
}

void Ennemi::setPath(QList<QPoint> path)
{
    iDestPoint = 0;
    this->path = path;
    setPos(path.at(0).x(), path.at(0).y());
}

void Ennemi::viewBlocActif()
{
    QList<QPoint> toDesactivate;
    bool allunactived = false;

    QList<S_ViewBlocEnnemi* >::iterator it;
    for (it = champVue.begin(); it != champVue.end(); ++it)
    {
        //On les active tous !
        (*it)->setActif(true);

        //lesquels on va désactiver ?
        QList<QGraphicsItem *> CollidingItems = (*it)->collidingItems();
        bool bUnactivate = false;

        foreach (QGraphicsItem *item, CollidingItems) {
            if(typeid(*item).name() == typeid(B_Movable).name()
            || typeid(*item).name() == typeid(B_Wall).name()
            || typeid(*item).name() == typeid(Ennemi).name())
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
        QList<S_ViewBlocEnnemi*>::iterator it;
        for (it = champVue.begin(); it != champVue.end(); ++it)
        {
            //on désactive la ligne
            if(((*it)->getColonne() >= toDes.y() && (*it)->getLine() == toDes.x()) || allunactived)
            {
                (*it)->setActif(false);
            }
        }
    }

}

void Ennemi::pinguinDetection()
{
    detectPinguin = false;
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        if(vb->isActif())
        {
            QList<QGraphicsItem *> CollidingItems = vb->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(Pingouin).name())
                {
                    vb->setStylePinguinOn();
                    pinguinOnViewBloc();
                }
            }
        }
    }
}

//appelé par les s_viewblocennemi si le pingouin marche (se déplace) dessus
//ou par ennemi si un pingouin est detecté
void Ennemi::pinguinOnViewBloc()
{
    this->detectPinguin = true;
    game->restartEnigma();
}

QPoint Ennemi::convertPosPoint(QPointF psrc)
{
    int x = (psrc.x()-1) /Gameboard::getGameSquares();
    int y = (psrc.y()-1) /Gameboard::getGameSquares();
    return QPoint(x, y);
}

bool Ennemi::collide()
{
    S_ViewBlocEnnemi *collideRect;
    foreach (S_ViewBlocEnnemi* vb, champVue) {
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
        else if(typeid(*CollidingItems.at(i)).name() == typeid(Ennemi).name())
        {
            return true;
        }
    }
    return false;
}

//renvoi l'id du point suivant dans la liste de point
//prend en compte le sens de déplacement de l'ennemi
int Ennemi::nextPoint()
{
    if(sens)
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

//Exécuté à chaque appel du slot "advance()" de la scene
//Cerveau de l'ennemi
void Ennemi::advance(int step)
{
    if(step == 1) //répond au second appel
    {
        state->step(this);
    }
}
void Ennemi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Draw the ennemi
    painter->setPen(Qt::transparent);

    ennemiSkin = new QBrush();

    //Set ennemiSkin texture depending on ennemi's orientation
    switch (orientation) {
    case 'l':
        ennemiSkin->setTexture(QPixmap(leftSkin));
        break;
    case 'r':
        ennemiSkin->setTexture(QPixmap(rightSkin));
        break;
    case 't':
        ennemiSkin->setTexture(QPixmap(upSkin));
        break;
    case 'b':
        ennemiSkin->setTexture(QPixmap(downSkin));
        break;
    default:
        break;
    }

    QRectF ennemiBox = boundingRect();  //Setting ennemi's box

    painter->fillRect(ennemiBox,*ennemiSkin);   //charger la couleur
    painter->drawRect(ennemiBox);
}
QRectF Ennemi::boundingRect() const
{
    return QRectF(0,0,Gameboard::getGameSquares()-2,Gameboard::getGameSquares()-2);
}

void Ennemi::setOrientation_top()
{
    orientation = 't';
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), -vb->getColonne()));
    }
    update();
}
void Ennemi::setOrientation_bottom()
{
    orientation = 'b';
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        setPosViewBloc(vb, QPoint(-vb->getLine(), vb->getColonne()));
    }
    update();
}
void Ennemi::setOrientation_left()
{
    orientation = 'l';
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        setPosViewBloc(vb, QPoint(-vb->getColonne(), -vb->getLine()));
    }
    update();
}
void Ennemi::setOrientation_right()
{
    orientation = 'r';
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        setPosViewBloc(vb, QPoint(vb->getColonne(), vb->getLine()));
    }
    update();
}

//Défini la position d'un bloc "viewBloc" en fonction de sa ligne et sa colonne
void Ennemi::setPosViewBloc(S_ViewBlocEnnemi* bloc, QPoint p)
{
    int gs = Gameboard::getGameSquares();
    QPoint posEnnemi = convertPosPoint(this->pos());

    bloc->setPosPixel(posEnnemi.x()*gs + p.x()*gs+1, posEnnemi.y()*gs + p.y()*gs+1);
}

void Ennemi::setPos(int x, int y)
{
    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        setPosViewBloc(vb, QPoint(vb->getLine(), vb->getColonne()));
    }

    QGraphicsItem::setPos(x*Gameboard::getGameSquares()+1, y*Gameboard::getGameSquares()+1);
}
void Ennemi::moveBy(int x, int y)
{
    int gameSquare = Gameboard::getGameSquares();

    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        vb->moveBy(x*gameSquare,y*gameSquare);
    }

    QGraphicsItem::moveBy(x*gameSquare,y*gameSquare);
}

void Ennemi::addToScene(QGraphicsScene* scene)
{
    scene->addItem(this);

    foreach (S_ViewBlocEnnemi* vb, champVue)
    {
        scene->addItem(vb);
    }
}
