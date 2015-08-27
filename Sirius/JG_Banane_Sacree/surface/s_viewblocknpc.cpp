#include "../surface/s_viewblocknpc.h"

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include "../character/c_enemy.h"
#include "../g_gameboard.h"


S_ViewBlockNPC::S_ViewBlockNPC(int ligne, int colonne, C_Enemy* proprietaire, QGraphicsItem *parent) : G_Surface(0, 0, G_Gameboard::getGameSquares()-2, G_Gameboard::getGameSquares()-2, parent)
{
    this->line = ligne;
    this->column = colonne;
    this->owner = proprietaire;
    this->setZValue(11);    this->hasStyling = true;

    setStyleActivated();
}

void S_ViewBlockNPC::setActive(bool actif)
{
    this->actif = actif;

    //Style
    if(actif)
    {
        setStyleActivated();
    }
    else
    {
        setStyleDesactivated();
    }
}

int S_ViewBlockNPC::getLine()
{
    return line;
}

int S_ViewBlockNPC::getColonne()
{
    return column;
}

bool S_ViewBlockNPC::isActive()
{
    return actif;
}

//the playable character moved on the block of detection
void S_ViewBlockNPC::playableCharacterOn()
{
    if(actif)
    {
        setStylePlayableCharacterOn();
        owner->playableCharacterOnViewBlock(); //relai de l'info
    }
    else
    {
        //TEST FOR THE OTTER
        owner->playableCharacterOnViewBlock();
    }
}

void S_ViewBlockNPC::blockOn()
{
    //recalculated the view field of the enemy
    if(actif)
    {
        owner->viewBlockActive();
    }
}

void S_ViewBlockNPC::setStylePlayableCharacterOn()
{
    if(hasStyling)
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
}

void S_ViewBlockNPC::setStyleDesactivated()
{
    if(hasStyling)
    {
        QBrush brush;
        brush.setStyle(Qt::Dense6Pattern);
        brush.setColor(Qt::green);

        QPen pen;
        pen.setStyle(Qt::NoPen);

        this->setBrush(brush);
        this->setPen(pen);
     }
}

void S_ViewBlockNPC::setStyleActivated()
{
    if(hasStyling)
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
}

void S_ViewBlockNPC::setStyleNone()
{
    this->setBrush(Qt::NoBrush);
    this->setPen(Qt::NoPen);
    hasStyling = false;
}

