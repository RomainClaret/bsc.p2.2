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

#include "../surface/s_ice.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "../g_level.h"

S_Ice::S_Ice(int xpos, int ypos, QGraphicsItem *parent) : S_SurfaceAutoTexture(xpos, ypos, parent)
{
    setDesign();
}
S_Ice::S_Ice(QGraphicsItem *parent) : S_SurfaceAutoTexture(0, 0, parent)
{
    setDesign();
}
void S_Ice::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::yellow);

//    setBrush(brush);

    texture_init = QPixmap(":/surfaces/surfaces/ice_init.png");
    QBrush brush;
    brush.setTexture(texture_init);
    setBrush(brush);
    setZValue(1);
}

void S_Ice::calculateTextures(int** mapSurfaces, int width, int height)
{
    bool collideLeft = this->collideLeft(G_Level::S_SNOW, mapSurfaces);
    bool collideLeftTop = this->collideLeftTop(G_Level::S_SNOW, mapSurfaces);
    bool collideLeftBottom = this->collideLeftBottom(G_Level::S_SNOW, mapSurfaces, height);
    bool collideRight = this->collideRight(G_Level::S_SNOW, mapSurfaces, width);
    bool collideRightTop = this->collideRightTop(G_Level::S_SNOW, mapSurfaces, width);
    bool collideRightBottom = this->collideRightBottom(G_Level::S_SNOW, mapSurfaces, width, height);
    bool collideBottom = this->collideBottom(G_Level::S_SNOW, mapSurfaces, height);
    bool collideTop = this->collideTop(G_Level::S_SNOW, mapSurfaces);

    if(collideLeft && collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_lt.png"));
    }
    else if(collideLeft && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_l.png"));
    }
    else if(collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_t.png"));
    }
    else if(collideLeftTop)
    {
       addTexture(QPixmap(":/surfaces/surfaces/ice_ltOut.png"));
    }

    if(collideRight && collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_rt.png"));
    }
    else if(collideRight && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_r.png"));
    }
    else if(collideTop && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_t.png"));
    }
    else if(collideRightTop && !collideRight && !collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_rtOut.png"));
    }

    if(collideBottom && collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_lb.png"));
    }
    else if(collideBottom && !collideRight && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_b.png"));
    }
    else if(collideLeftBottom && !collideLeft && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_lbOut.png"));
    }

    if(collideBottom && collideRight)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_rb.png"));
    }
    else if(collideBottom && !collideRight && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_b.png"));
    }
    else if(collideRightBottom && !collideRight && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/ice_rbOut.png"));
    }


}
