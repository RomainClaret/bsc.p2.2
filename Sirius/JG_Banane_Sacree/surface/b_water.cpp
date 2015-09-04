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

#include "../surface/b_water.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "../g_level.h"

B_Water::B_Water(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : S_SurfaceAutoTexture(xpos, ypos, game, parent)
{
    setDesign();
}

void B_Water::calculateTextures(int** mapSurfaces, int width, int height)
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
        addTexture(QPixmap(":/surfaces/surfaces/water_ltAnd_collideSnow.png"));
    }
    else if(collideLeft && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_l_collideSnow.png"));
    }
    else if(collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_t_collideSnow.png"));
    }
    else if(collideLeftTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_ltOnly_collideSnow.png"));
    }

    if(collideRight && collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_rtAnd_collideSnow.png"));
    }
    else if(collideRight && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_r_collideSnow.png"));
    }
    else if(collideTop && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_t_collideSnow.png"));
    }
    else if(collideRightTop && !collideTop)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_rtOnly_collideSnow.png"));
    }

    if(collideBottom && collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_lbAnd_collideSnow.png"));
    }
    else if(collideBottom && !collideRight && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_b_collideSnow.png"));
    }
    else if(collideLeftBottom && !collideLeft && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_lbOnly_collideSnow.png"));
    }

    if(collideBottom && collideRight)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_rbAnd_collideSnow.png"));
    }
    else if(collideBottom && !collideRight && !collideLeft)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_b_collideSnow.png"));
    }
    else if(collideRightBottom && !collideRight && !collideBottom)
    {
        addTexture(QPixmap(":/surfaces/surfaces/water_rbOnly_collideSnow.png"));
    }

    //qDebug() << "calculating a texture...";
//    if(isCollidingWithWater(leftTopCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }
//    if(isCollidingWithWater(rightTopCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }
//    if(isCollidingWithWater(leftBottomCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }
//    if(isCollidingWithWater(rightBottomCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }

//    if(isCollidingWithWater(bottomCollideBox))
//    {
//        addTexture(QPixmap(":/surfaces/surfaces/water_b_collideSnow.png"));
//    }
//    if(isCollidingWithWater(topCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }
//    if(isCollidingWithWater(leftCollideBox))
//    {
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }
//    if(isCollidingWithWater(rightCollideBox))
//    {
//        //qDebug() << "COLLIDING RIGHT !";
//        //addTexture(QPixmap(":/surfaces/surfaces/movable_init.png"));
//    }

//    destroyCollidingBoxes();
}

//bool B_Water::isCollidingWithWater()
//{
////    bool collidingWater = false;
////    QList<QGraphicsItem *> CollidingItems = bloc->collidingItems();

////    for(int i=0; i<CollidingItems.length(); i++)
////    {
////        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
////        {
////            collidingWater = true;
////        }
////    }

////    return collidingWater;
//    return false;
//}

/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
B_Water::B_Water(G_Gameboard* game, QGraphicsItem *parent) : S_SurfaceAutoTexture(0, 0, game, parent)
{
    setDesign();
}

void B_Water::setDesign()
{
    texture_init = QPixmap(":/surfaces/surfaces/water_init_00.png");

    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_01.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_02.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_03.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_04.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_05.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_06.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_07.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_08.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_09.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_10.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_11.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_12.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_13.png"));
    texturesAnim.append(QPixmap(":/surfaces/surfaces/water_init_14.png"));
    texturesAnim.append(texture_init);

    QBrush brush;
    brush.setTexture(texture_init);
    setBrush(brush);

//    texture_l_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_lb_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_b_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_rb_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_r_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_rt_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_t_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
//    texture_lt_Collide = QPixmap(":/surfaces/surfaces/movable_init.png");
}
