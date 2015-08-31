#include "b_wall_group.h"
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QList>
#include "../g_level.h"

B_Wall_Group::B_Wall_Group(int xpos, int ypos, QGraphicsItem *parent) : B_Wall(xpos, ypos, parent)
{
    setDesign();
}

/**
 * @details No other choice that use FICTIVE positions x and y. Here set at 0.
 */
B_Wall_Group::B_Wall_Group(QGraphicsItem *parent) : B_Wall(parent)
{
    setDesign();
}

void B_Wall_Group::setDesign()
{
    setZValue(4);

    QBrush texture;
    texture.setTexture(QPixmap(":/surfaces/surfaces/wallGroup_init.png"));

    this->setBrush(texture);
}

void B_Wall_Group::calculateTextures(int** mapSurfaces, int width, int height)
{
    bool buddyLeft = this->collideLeft(G_Level::B_WALL_GROUP, mapSurfaces);
    bool buddyRight = this->collideRight(G_Level::B_WALL_GROUP, mapSurfaces, width);
    bool buddyBottom = this->collideBottom(G_Level::B_WALL_GROUP, mapSurfaces, height);
    bool buddyTop = this->collideTop(G_Level::B_WALL_GROUP, mapSurfaces);

    QString strTexture = "";

    if(buddyTop && buddyRight && (!buddyBottom && !buddyLeft))
    {
        strTexture = ":/surfaces/surfaces/wallGroup_lb.png";
    }
    else if(buddyTop && buddyLeft && (!buddyBottom && !buddyRight))
    {
        strTexture = ":/surfaces/surfaces/wallGroup_rb.png";
    }
    else if((buddyTop && buddyLeft && buddyRight) && !buddyBottom)
    {
        strTexture = ":/surfaces/surfaces/wallGroup_b.png";
    }
    else if((!buddyTop && !buddyLeft) && buddyBottom && buddyRight)
    {
        strTexture = ":/surfaces/surfaces/wallGroup_lt.png";
    }
    else if((!buddyTop && !buddyRight) && buddyBottom && buddyLeft)
    {
        strTexture = ":/surfaces/surfaces/wallGroup_rt.png";
    }
    else if(!buddyTop && buddyLeft && buddyRight && buddyBottom)
    {
        strTexture = ":/surfaces/surfaces/wallGroup_t.png";
    }
    else if(!buddyLeft && buddyRight && buddyTop && buddyBottom)
    {
         strTexture = ":/surfaces/surfaces/wallGroup_l.png";
    }
    else if(buddyLeft && !buddyRight && buddyTop && buddyBottom)
    {
         strTexture = ":/surfaces/surfaces/wallGroup_r.png";
    }

    if(strTexture != "")
    {
        QBrush texture;
        texture.setTexture(QPixmap(strTexture));
        this->setBrush(texture);
    }
}
