#include "s_viewblocennemi.h"

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include "ennemi.h"
#include "gameboard.h"


S_ViewBlocEnnemi::S_ViewBlocEnnemi(int ligne, int colonne, Ennemi* proprietaire, QGraphicsItem *parent) : Surface(0, 0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent)
{
    this->ligne = ligne;
    this->colonne = colonne;
    this->proprietaire = proprietaire;
    this->setZValue(2);
}

void S_ViewBlocEnnemi::setActif(bool actif)
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

int S_ViewBlocEnnemi::getLine()
{
    return ligne;
}

int S_ViewBlocEnnemi::getColonne()
{
    return colonne;
}

bool S_ViewBlocEnnemi::isActif()
{
    return actif;
}

void S_ViewBlocEnnemi::pinguinOn()
{
    setStylePinguinOn();
    proprietaire->pinguinOnViewBloc();
}

void S_ViewBlocEnnemi::setStylePinguinOn()
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

void S_ViewBlocEnnemi::setStyleUnactivated()
{
    QBrush brush;
    brush.setStyle(Qt::Dense6Pattern);
    brush.setColor(Qt::green);

    QPen pen;
    pen.setStyle(Qt::NoPen);

    this->setBrush(brush);
    this->setPen(pen);
}

void S_ViewBlocEnnemi::setStyleActivated()
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
