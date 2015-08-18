#include "s_viewblockenemy.h"

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include "enemy.h"
#include "gameboard.h"


S_ViewBlockEnemy::S_ViewBlockEnemy(int ligne, int colonne, Enemy* proprietaire, QGraphicsItem *parent) : Surface(0, 0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent)
{
    this->ligne = ligne;
    this->colonne = colonne;
    this->proprietaire = proprietaire;
    this->setZValue(2);

    setStyleActivated();
}

void S_ViewBlockEnemy::setActif(bool actif)
{
    this->actif = actif;

    //Style
    if(actif)
    {
        setStyleActivated();
    }
    else
    {
        setStyleUnactivated();
    }
}

int S_ViewBlockEnemy::getLine()
{
    return ligne;
}

int S_ViewBlockEnemy::getColonne()
{
    return colonne;
}

bool S_ViewBlockEnemy::isActif()
{
    return actif;
}

//le pinguoin s'est déplacé sur un bloc de détection
void S_ViewBlockEnemy::pinguinOn()
{
    if(actif)
    {
        setStylePinguinOn();
        proprietaire->playableCharacterOnViewBloc(); //relai de l'info
    }
}

void S_ViewBlockEnemy::blocOn()
{
    //recalcul le champs de vision de l'ennemi
    if(actif)
    {
        proprietaire->viewBlockActive();
    }
}

void S_ViewBlockEnemy::setStylePinguinOn()
{
    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);
    brush.setColor(Qt::yellow);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::yellow);

    this->setBrush(brush);
    this->setPen(pen);
}

void S_ViewBlockEnemy::setStyleUnactivated()
{
    QBrush brush;
    brush.setStyle(Qt::Dense6Pattern);
    brush.setColor(Qt::green);

    QPen pen;
    pen.setStyle(Qt::NoPen);

    this->setBrush(brush);
    this->setPen(pen);
}

void S_ViewBlockEnemy::setStyleActivated()
{
    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);
    brush.setColor(Qt::red);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);

    this->setBrush(brush);
    this->setPen(pen);
}
