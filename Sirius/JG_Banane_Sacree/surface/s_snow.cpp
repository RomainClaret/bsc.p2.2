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

#include "../surface/s_snow.h"
#include "../surface/b_movable_simple.h"
#include "../surface/s_footstep.h"
#include "../g_gameboard.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

S_Snow::S_Snow(int xpos, int ypos, QGraphicsScene* scene, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    setDesign();
    this->scene = scene;
    this->setZValue(2);

    speed = 20;
    iTime = rand() % 50;
    movableSunk = false;
}
S_Snow::S_Snow(QGraphicsScene* scene, QGraphicsItem *parent) : G_Surface(0, 0, parent)
{
    setDesign();
    this->scene = scene;
    this->setZValue(2);
}

void S_Snow::setMovableSunk(B_MovableSimple *b)
{
    this->setBrush(Qt::NoBrush);

    QPixmap pixmap = QPixmap(":/surfaces/surfaces/movable_snow.png");

    int rotation = b->getRotationTexture();
    QTransform transform;
    QTransform trans = transform.rotate(rotation);

    QBrush brush;
    brush.setTexture(QPixmap(pixmap.transformed(trans)));
    setBrush(brush);

    this->setZValue(1);

    movableSunk = true;
}

void S_Snow::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}

S_Footstep* S_Snow::showFootPrint(char sens)
{
    S_Footstep* footstep = new S_Footstep(this->getPos().x(), this->getPos().y(), sens, 30);
    return footstep;
}

void S_Snow::advance(int step)
{
//    if(step = 1 && !movableSunk)
//    {
//        if(rand() % 2 == 1)
//        {
//            iTime ++;
//            if(iTime % speed == 0)
//            {
//                QBrush brush;

//                int iRandRotate = 90*(rand() % 4);

//                QTransform transform;
//                QTransform trans = transform.rotate(iRandRotate);
//                brush.setTexture(QPixmap(QPixmap(":/surfaces/surfaces/snowSpark.png").transformed(trans)));

//                setBrush(brush);
//            }
//        }
//    }
}
