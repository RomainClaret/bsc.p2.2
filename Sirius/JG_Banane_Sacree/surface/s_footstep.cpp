#include "s_footstep.h"
#include <QBrush>
#include <QDebug>
S_Footstep::S_Footstep(int xpos, int ypos, char sens, int lifetime, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    this->lifetime = lifetime;
    this->itime = 0;

    QBrush bg;
    switch (sens) {
    case 't':
            bg.setTexture(QPixmap(":/characters/characters/player_step_t.png"));
        break;
    case 'b':
            bg.setTexture(QPixmap(":/characters/characters/player_step_b.png"));
        break;
    case 'l':
            bg.setTexture(QPixmap(":/characters/characters/player_step_l.png"));
        break;
    case 'r':
            bg.setTexture(QPixmap(":/characters/characters/player_step_r.png"));
        break;
    default:
        break;
    }

    this->setBrush(bg);
    this->setOpacity(0.3);

    setZValue(5);
}

void S_Footstep::advance(int step)
{
    if(step == 1)
    {
        itime ++;
        if(lifetime < itime)
        {
            double opa = (double)(itime - lifetime) / 10;
            if((0.3 - opa) < 0)
            {
                this->setBrush(Qt::NoBrush);
                delete this;
            }
            else
            {
                setOpacity((0.3 - opa));
            }
        }
    }
}
