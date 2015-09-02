#include "g_character.h"

#include <QPainter>
#include <QDebug>
#include <QRectF>
#include "singleton_audio.h"

#include "../g_gameboard.h"

G_Character::G_Character(G_Gameboard* game)
{
    currentMove='c';

    this->timerMover = new QTimer();
    setTimer();

    setZValue(10);

    audioSingleton = Singleton_Audio::getInstance();

    this->game = game;
}

void G_Character::setTimer()
{
    connect(timerMover, SIGNAL(timeout()), this, SLOT(stepMove()));
}

void G_Character::disconnectTimer()
{
    disconnect(timerMover, SIGNAL(timeout()), this, SLOT(stepMove()));
}

void G_Character::moveWithTimer(char orientation)
{
    if(currentMove == 'n')
    {
        //        audioSingleton->playSoundPlayerWalking();
        startCurrentMove = QPointF(this->pos().x(),this->pos().y());
        currentMove = orientation;
        game->setIsMoving(true);
        qDebug() << "-----------------I will start the timer";
        timerMover->start(5);
    }
}

bool G_Character::isMoving()
{
    return !(currentMove == 'n');
}

void G_Character::stepMove()
{
    qDebug() << "CHARACTER : StepMove()";
    stepMoveCharacter();
}

void G_Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Draw the ennemi
    painter->setPen(Qt::transparent);

    skin = new QBrush();

    //Set ennemiSkin texture depending on ennemi's orientation
    switch (orientation) {
    case 'l':
        skin->setTexture(QPixmap(leftSkin));
        break;
    case 'r':
        skin->setTexture(QPixmap(rightSkin));
        break;
    case 't':
        skin->setTexture(QPixmap(upSkin));
        break;
    case 'b':
        skin->setTexture(QPixmap(downSkin));
        break;
    default:
        break;
    }

    QRectF characterBox = boundingRect();  //Setting ennemi's box

    painter->fillRect(characterBox,*skin);   //charger la couleur
    painter->drawRect(characterBox);
}

QRectF G_Character::boundingRect() const
{
    return QRectF(1,1,G_Gameboard::getGameSquares()-2,G_Gameboard::getGameSquares()-2);
}

void G_Character::setPosition(int xpos, int ypos)
{
    qDebug() << "xpos " << xpos << "ypos" << ypos;
    qDebug() << "x " << pos().x() << "y" << pos().y();

    moveBy(xpos - pos().x(), ypos - pos().y());
}
