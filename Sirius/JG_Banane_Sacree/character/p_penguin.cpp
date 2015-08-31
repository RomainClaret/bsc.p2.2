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

#include "../character/p_penguin.h"
#include "../g_gameboard.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "../surface/s_ice.h"
#include "../g_object.h"
#include "../singleton_audio.h"

#include <QPropertyAnimation>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

P_Penguin::P_Penguin(G_Gameboard* game) : C_Player(game)
{
    audioSingleton = Singleton_Audio::getInstance();

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

    setZValue(10);
    iStepCompteur = -1;
    iStep = 0;
    stepsBottom.append(":/characters/characters/player_front_step01.png");
    stepsBottom.append(":/characters/characters/player_front_step02.png");

    stepsTop.append(":/characters/characters/player_back_step01.png");
    stepsTop.append(":/characters/characters/player_back_step02.png");

    stepsLeft.append(":/characters/characters/player_left_step01.png");
    stepsLeft.append(":/characters/characters/player_left.png");

    stepsRight.append(":/characters/characters/player_right_step01.png");
    stepsRight.append(":/characters/characters/player_right.png");

    iTimer = 0;
    iWaitAnim = 40;
    animSteps.append(":/characters/characters/player_front.png");
    animSteps.append(":/characters/characters/player_anim01.png");
    animSteps.append(":/characters/characters/player_anim02.png");
    animSteps.append(":/characters/characters/player_anim03.png");
    animSteps.append(":/characters/characters/player_anim04.png");
    animSteps.append(":/characters/characters/player_anim05.png");
    animSteps.append(":/characters/characters/player_front.png");
    animSteps.append(":/characters/characters/player_anim01.png");
    animSteps.append(":/characters/characters/player_anim02.png");
    animSteps.append(":/characters/characters/player_anim03.png");
    animSteps.append(":/characters/characters/player_anim04.png");
    animSteps.append(":/characters/characters/player_anim05.png");
    animSteps.append(":/characters/characters/player_front.png");

    iAdvanceSpeed = 0;

}
void P_Penguin::setPos(int x, int y)
{
    int xPos = x*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();
    int yPos = y*G_Gameboard::getGameSquares()-G_Gameboard::getGameSquares();

    C_Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-G_Gameboard::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+G_Gameboard::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+G_Gameboard::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-G_Gameboard::getGameSquares()+1);
}

void P_Penguin::advance(int step)
{
    if(step == 1)
    {
        iAdvanceSpeed++;
        if(iAdvanceSpeed % 2 == 0)
        {
            iTimer++;
            if(iTimer >= iWaitAnim && iTimer < iWaitAnim+animSteps.size())
            {
                downSkin = animSteps.at(iTimer-iWaitAnim);
                setPlayerOrientation('b');
                update();
            }
            else if(iTimer > iWaitAnim+animSteps.size())
            {
                iTimer = 0;
            }
        }
    }
}

void P_Penguin::stepMoveCharacter()
{
    iTimer = 0;
    int pas = 2;
    switch (currentMove) {
    case 'l':
        if(this->pos().x() > startCurrentMove.x() - G_Gameboard::getGameSquares())
        {
            iStepCompteur ++;
            if(iStepCompteur % 7 == 0)
            {
            iStep = (iStep + 1) % stepsLeft.length();
            leftSkin = stepsLeft.at(iStep);
            }

            this->moveByPixel(-pas,0);
        }
        else
        {
            endMove();
        }
        break;
    case 'r':
        if(this->pos().x() < startCurrentMove.x() + G_Gameboard::getGameSquares())
        {
            iStepCompteur ++;
            if(iStepCompteur % 7 == 0)
            {
            iStep = (iStep + 1) % stepsRight.length();
            rightSkin = stepsRight.at(iStep);
            }

            this->moveByPixel(pas,0);
        }
        else
        {
            endMove();
        }
        break;

    case 't':
        if(this->pos().y() > startCurrentMove.y() - G_Gameboard::getGameSquares())
        {
            iStepCompteur ++;
            if(iStepCompteur % 7 == 0)
            {
            iStep = (iStep + 1) % stepsTop.length();
            upSkin = stepsTop.at(iStep);
            }

            this->moveByPixel(0,-pas);
        }
        else
        {
            endMove();
        }
        break;
    case 'b':
        if(this->pos().y() < startCurrentMove.y() + G_Gameboard::getGameSquares())
        {
            iStepCompteur ++;
            if(iStepCompteur % 7 == 0)
            {
            iStep = (iStep + 1) % stepsBottom.length();
            downSkin = stepsBottom.at(iStep);
            }

            this->moveByPixel(0,pas);
        }
        else
        {
            endMove();
        }
        break;
    default:
        currentMove = 'n';
        timerMover->stop();
        break;
    }
}

void P_Penguin::endMove()
{
    game->endMoveCheck(currentMove);
    currentMove = 'n';
    timerMover->stop();
    iStepCompteur = -1;
}

void P_Penguin::moveBy(int x, int y)
{

    C_Player::moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    leftCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    rightCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    bottomCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());
    topCollideBox->moveBy(x*G_Gameboard::getGameSquares(),y*G_Gameboard::getGameSquares());

    lastMove->setX(x);
    lastMove->setY(y);
}

void P_Penguin::moveByPixel(int x, int y)
{
    C_Player::moveBy(x,y);
    leftCollideBox->moveBy(x,y);
    rightCollideBox->moveBy(x,y);
    bottomCollideBox->moveBy(x,y);
    topCollideBox->moveBy(x,y);

    lastMove->setX(x);
    lastMove->setY(y);
}

void P_Penguin::moveBack()
{
    moveBy(-lastMove->x(),-lastMove->y());
    lastMove->setX(0);
    lastMove->setY(0);

    qDebug() << "MoveBack" << x() << " " << y();
}

void P_Penguin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool P_Penguin::isSlide()
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
    if (slide)
    {
        //audioSingleton->playSoundPlayerSliding();
    }
    return slide;
}

void P_Penguin::setSlideAble(bool value)
{
    this->slideAble = value;
}

//Return lists of collisions
QList<QGraphicsItem *> P_Penguin::CollidesRight()
{
    return rightCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesLeft()
{
    return leftCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesTop()
{
    return topCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesBottom()
{
    return bottomCollideBox->collidingItems();
}
QList<QGraphicsItem *> P_Penguin::CollidesCenter()
{
    return C_Player::collidingItems();
}


//temp
QGraphicsRectItem* P_Penguin::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* P_Penguin::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* P_Penguin::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* P_Penguin::getBottomCB(){
     return bottomCollideBox;
}

C_Player* P_Penguin::getPlayer(){
     return this;
}

void P_Penguin::addObjectToBag(G_Object *object)
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

void P_Penguin::removeObjectFromSacoche(QString object)
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

void P_Penguin::printSacoche()
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

QList<G_Object*> P_Penguin::getBag()
{
    return sacoche;
}

bool P_Penguin::checkObjectSacoche(QString object, int quantity)
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

void P_Penguin::emptyTempBag()
{
    tempSacoche.clear();
}

void P_Penguin::emptySacoche()
{
    sacoche.clear();
}

void P_Penguin::removeTempFromSacoche()
{
    for (int i = 0; i < tempSacoche.size(); ++i)
    {
        qDebug() << "Remove : " << tempSacoche.at(i)->getName();
        QString nom = tempSacoche.at(i)->getName();
        removeObjectFromSacoche(nom);
    }
    emptyTempBag();
}

QGraphicsRectItem* P_Penguin::getCollideBloc(char sensDepl)
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
