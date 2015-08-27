#include "g_character.h"

#include <QPainter>
#include <QDebug>
#include <QRectF>

#include "../g_gameboard.h"

G_Character::G_Character()
{
    currentMove='n';

    this->timerMover = new QTimer();
    connect(timerMover, SIGNAL(timeout()), this, SLOT(stepMove()));

    setZValue(10);
}

void G_Character::moveWithTimer(char orientation)
{
    if(currentMove == 'n')
    {
        startCurrentMove = QPointF(this->pos().x(),this->pos().y());
        currentMove = orientation;
        timerMover->start(5);
    }
    else
    {
        qDebug() << "mouvement en cours";
    }
}

void G_Character::advance(int)
{
    //Todo
}

void G_Character::stepMove()
{
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
