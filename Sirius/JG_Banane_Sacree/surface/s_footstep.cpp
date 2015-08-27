#include "s_footstep.h"
#include <QBrush>
S_Footstep::S_Footstep(int xpos, int ypos, char sens, int lifetime, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    this->lifetime = lifetime;
    this->itime = 0;

    QBrush bg;
    switch (sens) {
    case 't':
            bg.setTexture(QPixmap(""));
        break;
    case 'b':
            bg.setTexture(QPixmap(""));
        break;
    case 'l':
            bg.setTexture(QPixmap(""));
        break;
    case 'r':
            bg.setTexture(QPixmap(""));
        break;
    default:
        break;
    }

    this->setBrush(bg);
}

void S_Footstep::advance(int step)
{
    if(step == 1)
    {
        itime ++;
        if(lifetime > itime)
        {
            this->setBrush(Qt::NoBrush);
            delete this;
        }
    }
}
