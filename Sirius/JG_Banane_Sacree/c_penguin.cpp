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

#include "c_penguin.h"
#include "g_gameboard.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "s_ice.h"
#include "g_object.h"

#include <QPropertyAnimation>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

C_Penguin::C_Penguin() : G_Player()
{
    int BlocsSizeX = G_Gameboard::getGameSquares()-2;
    int BlocsSizeY = G_Gameboard::getGameSquares()-2;

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
void C_Penguin::setPos(int x, int y)
{
    int xPos = x*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();
    int yPos = y*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();

    G_Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-G_Gameboard::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+G_Gameboard::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+G_Gameboard::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-G_Gameboard::getGameSquares()+1);
}

void C_Penguin::moveBy(int x, int y)
{


//    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
//    animation->setDuration(1000);
//    animation->setStartValue(QPoint(this->pos().x(), this->pos().y()));
//    animation->setEndValue(QPoint(this->pos().x() + x*gameSquare, this->pos().y() + y*gameSquare));

//    animation->start();

    G_Player::moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    leftCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    rightCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    bottomCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    topCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());

    lastMove->setX(x);
    lastMove->setY(y);
}

void C_Penguin::moveBack()
{
    moveBy(-lastMove->x(),-lastMove->y());
    lastMove->setX(0);
    lastMove->setY(0);

    qDebug() << "MoveBack" << x() << " " << y();
}

void C_Penguin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool C_Penguin::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();
    bool slide = false;

    if(slideAble)
    {
        for(int i=0; i<CollidingItems.length(); i++)
        {
            if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
            {
                slide = true;
            }
        }
    }
    return slide;
}

void C_Penguin::setSlideAble(bool value)
{
    this->slideAble = value;
}

//Retour des listes des collisions
QList<QGraphicsItem *> C_Penguin::CollidesRight()
{
    return rightCollideBox->collidingItems();
}
QList<QGraphicsItem *> C_Penguin::CollidesLeft()
{
    return leftCollideBox->collidingItems();
}
QList<QGraphicsItem *> C_Penguin::CollidesTop()
{
    return topCollideBox->collidingItems();
}
QList<QGraphicsItem *> C_Penguin::CollidesBottom()
{
    return bottomCollideBox->collidingItems();
}
QList<QGraphicsItem *> C_Penguin::CollidesCenter()
{
    return G_Player::collidingItems();
}


//temporaire
QGraphicsRectItem* C_Penguin::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* C_Penguin::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* C_Penguin::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* C_Penguin::getBottomCB(){
     return bottomCollideBox;
}

G_Player* C_Penguin::getPlayer(){
     return this;
}

void C_Penguin::addObjectToBag(G_Object *object)
{
    if(object->getName()== G_Object::OBJECT_EGG)
    {
        nbLives++;
    }
    else
    {
        tempSacoche.append(object);
        sacoche.append(object);
    }

}

void C_Penguin::removeObjectFromSacoche(QString object)
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

void C_Penguin::printSacoche()
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

QList<G_Object*> C_Penguin::getBag()
{
    return sacoche;
}

bool C_Penguin::checkObjectSacoche(QString object, int quantity)
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

void C_Penguin::emptyTempBag()
{
    tempSacoche.clear();
}

void C_Penguin::emptySacoche()
{
    sacoche.clear();
}

void C_Penguin::removeTempFromSacoche()
{
    for (int i = 0; i < tempSacoche.size(); ++i)
    {
        qDebug() << "Remove : " << tempSacoche.at(i)->getName();
        QString nom = tempSacoche.at(i)->getName();
        removeObjectFromSacoche(nom);
    }
    emptyTempBag();
}

QGraphicsRectItem* C_Penguin::getCollideBloc(char sensDepl)
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
