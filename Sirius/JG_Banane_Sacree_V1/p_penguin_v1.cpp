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

#include "p_penguin_v1.h"
#include "g_gameboard_v1.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "s_ice_v1.h"
#include "g_object_v1.h"

#include <QPropertyAnimation>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

P_Penguin_v1::P_Penguin_v1() : C_Player_v1()
{
    int BlocsSizeX = G_Gameboard_v1::getGameSquares()-2;
    int BlocsSizeY = G_Gameboard_v1::getGameSquares()-2;

    leftCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);

    leftCollideBox->setPen(Qt::NoPen);
    rightCollideBox->setPen(Qt::NoPen);
    bottomCollideBox->setPen(Qt::NoPen);
    topCollideBox->setPen(Qt::NoPen);

    lastMove = new QPoint(0,0);

    slideAble = true;

}
void P_Penguin_v1::setPos(int x, int y)
{
    int xPos = x*G_Gameboard_v1::getGameSquares()-G_Gameboard_v1::getGameSquares();
    int yPos = y*G_Gameboard_v1::getGameSquares()-G_Gameboard_v1::getGameSquares();

    C_Player_v1::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-G_Gameboard_v1::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+G_Gameboard_v1::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+G_Gameboard_v1::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-G_Gameboard_v1::getGameSquares()+1);
}

void P_Penguin_v1::moveBy(int x, int y)
{


//    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
//    animation->setDuration(1000);
//    animation->setStartValue(QPoint(this->pos().x(), this->pos().y()));
//    animation->setEndValue(QPoint(this->pos().x() + x*gameSquare, this->pos().y() + y*gameSquare));

//    animation->start();

    C_Player_v1::moveBy(x*G_Gameboard_v1::getGameSquares(),y*G_Gameboard_v1::getGameSquares());
    leftCollideBox->moveBy(x*G_Gameboard_v1::getGameSquares(),y*G_Gameboard_v1::getGameSquares());
    rightCollideBox->moveBy(x*G_Gameboard_v1::getGameSquares(),y*G_Gameboard_v1::getGameSquares());
    bottomCollideBox->moveBy(x*G_Gameboard_v1::getGameSquares(),y*G_Gameboard_v1::getGameSquares());
    topCollideBox->moveBy(x*G_Gameboard_v1::getGameSquares(),y*G_Gameboard_v1::getGameSquares());

    lastMove->setX(x);
    lastMove->setY(y);
}

void P_Penguin_v1::moveBack()
{
    moveBy(-lastMove->x(),-lastMove->y());
    lastMove->setX(0);
    lastMove->setY(0);

    qDebug() << "MoveBack" << x() << " " << y();
}

void P_Penguin_v1::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool P_Penguin_v1::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();
    bool slide = false;

    if(slideAble)
    {
        for(int i=0; i<CollidingItems.length(); i++)
        {
            if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice_v1).name())
            {
                slide = true;
            }
        }
    }
    return slide;
}

void P_Penguin_v1::setSlideAble(bool value)
{
    this->slideAble = value;
}

//Retour des listes des collisions
QList<QGraphicsItem *> P_Penguin_v1::CollidesRight()
{
    return rightCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin_v1::CollidesLeft()
{
    return leftCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin_v1::CollidesTop()
{
    return topCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin_v1::CollidesBottom()
{
    return bottomCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin_v1::CollidesCenter()
{
    return C_Player_v1::collidingItems();
}


//temporaire
QGraphicsRectItem* P_Penguin_v1::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* P_Penguin_v1::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* P_Penguin_v1::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* P_Penguin_v1::getBottomCB(){
     return bottomCollideBox;
}

C_Player_v1* P_Penguin_v1::getPlayer(){
     return this;
}

void P_Penguin_v1::addObjectToSacoche(G_Object_v1 *object)
{
    if(object->getName()=="Oeuf")
    {
        nbLives++;
    }
    else
    {
        tempSacoche.append(object);
        sacoche.append(object);
    }

}

void P_Penguin_v1::removeObjectFromSacoche(QString object)
{
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            sacoche.removeAt(i);
            return;
        }
    }
}

void P_Penguin_v1::printSacoche()
{
    qDebug() << "[PrintSacoche]";
    for (int i = 0; i < sacoche.size(); ++i) {
        qDebug() << sacoche.at(i)->getName();
    }
    qDebug() << " ";

    qDebug() << "[PrintSacocheTemp]";
    for (int i = 0; i < tempSacoche.size(); ++i) {
        qDebug() << tempSacoche.at(i)->getName();
    }
    qDebug() << " ";
}

QList<G_Object_v1*> P_Penguin_v1::getSacoche()
{
    return sacoche;
}

bool P_Penguin_v1::checkObjectSacoche(QString object, int quantity)
{
    int total = 0;
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            total++;
        }
    }

    if(total >= quantity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void P_Penguin_v1::emptyTempSacoche()
{
    tempSacoche.clear();
}

void P_Penguin_v1::emptySacoche()
{
    sacoche.clear();
}

void P_Penguin_v1::removeTempFromSacoche()
{
    for (int i = 0; i < tempSacoche.size(); ++i)
    {
        qDebug() << "Remove : " << tempSacoche.at(i)->getName();
        QString nom = tempSacoche.at(i)->getName();
        removeObjectFromSacoche(nom);
    }
    emptyTempSacoche();
}

QGraphicsRectItem* P_Penguin_v1::getCollideBloc(char sensDepl)
{
    if(sensDepl == 'b')
    {
        return bottomCollideBox;
    }
    else if(sensDepl == 'l')
    {
        return leftCollideBox;
    }
    else if(sensDepl == 'r')
    {
        return rightCollideBox;
    }
    else if(sensDepl == 't')
    {
        return topCollideBox;
    }
    return NULL;
}
