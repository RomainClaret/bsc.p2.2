#include "s_surfaceautotexture.h"

#include "g_gameboard.h"
#include <QPen>
#include <QDebug>

S_SurfaceAutoTexture::S_SurfaceAutoTexture(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : G_Surface(xpos, ypos, game, parent)
{
    iCurrentTexture = 0;
    speed = 5;
    time = 0;
//    leftCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos+1,size-2, size-2);
//    leftTopCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos-size+1,size-2, size-2);
//    rightCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos+1,size-2, size-2);
//    rightTopCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos-size+1,size-2, size-2);
//    bottomCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos+size+1, size-2, size-2);
//    rightBottomCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos+size+1,size-2, size-2);
//    topCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos-size+1, size-2, size-2);
//    leftBottomCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos+size+1,size-2, size-2);

//    leftCollideBox->setPen(Qt::NoPen);
//    leftTopCollideBox->setPen(Qt::NoPen);
//    rightCollideBox->setPen(Qt::NoPen);
//    rightTopCollideBox->setPen(Qt::NoPen);
//    bottomCollideBox->setPen(Qt::NoPen);
//    rightBottomCollideBox->setPen(Qt::NoPen);
//    topCollideBox->setPen(Qt::NoPen);
//    leftBottomCollideBox->setPen(Qt::NoPen);
}

void S_SurfaceAutoTexture::advance(int step)
{
    if(step == 0)
    {
        time ++;
        if(!texturesAnim.empty() && time % speed == 0)
        {
            QBrush brush;
            brush.setTexture(texturesAnim.at(iCurrentTexture));
            setBrush(brush);
            iCurrentTexture = (iCurrentTexture+1) % texturesAnim.size();
        }
    }
}

bool S_SurfaceAutoTexture::collideLeft(int type, int** mapSurfaces)
{
    if(this->getPos().x()-1 >= 0)
    {
        return (mapSurfaces[this->getPos().x()-1][this->getPos().y()] == type); //collide left
    }
    return false;
}
bool S_SurfaceAutoTexture::collideRight(int type, int** mapSurfaces, int width)
{
    if(this->getPos().x() + 1 < width)
    {
        return (mapSurfaces[this->getPos().x()+1][this->getPos().y()] == type); //collide right
    }
    return false;
}
bool S_SurfaceAutoTexture::collideTop(int type, int** mapSurfaces)
{
    if(this->getPos().y() - 1 >= 0)
    {
        return (mapSurfaces[this->getPos().x()][this->getPos().y()-1] == type); //collide top
    }
    return false;
}
bool S_SurfaceAutoTexture::collideBottom(int type, int** mapSurfaces, int height)
{
    if(this->getPos().y() + 1 <= height)
    {
        return (mapSurfaces[this->getPos().x()][this->getPos().y()+1] == type); //collide bottom
    }
    return false;
}

bool S_SurfaceAutoTexture::collideLeftTop(int type, int** mapSurfaces)
{
    if(this->getPos().y()-1 >= 0 && this->getPos().x()-1 >= 0)
    {
        return (mapSurfaces[this->getPos().x()-1][this->getPos().y()-1] == type); //collide left-top
    }
    return false;
}
bool S_SurfaceAutoTexture::collideLeftBottom(int type, int** mapSurfaces, int height)
{
    if(this->getPos().y()+1 <= height && this->getPos().x()-1 >= 0)
    {
        return (mapSurfaces[this->getPos().x()-1][this->getPos().y()+1] == type); //collide left-bottom
    }
    return false;
}
bool S_SurfaceAutoTexture::collideRightTop(int type, int** mapSurfaces, int width)
{
    if(this->getPos().y()-1 >= 0 && this->getPos().x() + 1 < width)
    {
        return (mapSurfaces[this->getPos().x()+1][this->getPos().y()-1] == type); //collide right-top
    }
    return false;
}
bool S_SurfaceAutoTexture::collideRightBottom(int type, int** mapSurfaces, int width, int height)
{
    if(this->getPos().y()+1 <= height && this->getPos().x() + 1 < width)
    {
        return (mapSurfaces[this->getPos().x()+1][this->getPos().y()+1] == type); //collide right-bottom
    }
    return false;
}

void S_SurfaceAutoTexture::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);

//    scene->addItem(leftCollideBox);
//    scene->addItem(leftTopCollideBox);
//    scene->addItem(rightCollideBox);
//    scene->addItem(rightTopCollideBox);
//    scene->addItem(bottomCollideBox);
//    scene->addItem(rightBottomCollideBox);
//    scene->addItem(topCollideBox);
//    scene->addItem(leftBottomCollideBox);

    this->scene = scene;
}

//void S_SurfaceAutoTexture::destroyCollidingBoxes()
//{
//    scene->removeItem(leftCollideBox);
//    scene->removeItem(leftTopCollideBox);
//    scene->removeItem(rightCollideBox);
//    scene->removeItem(rightTopCollideBox);
//    scene->removeItem(bottomCollideBox);
//    scene->removeItem(rightBottomCollideBox);
//    scene->removeItem(topCollideBox);
//    scene->removeItem(leftBottomCollideBox);

//    delete leftCollideBox;
//    delete leftTopCollideBox;
//    delete rightCollideBox;
//    delete rightTopCollideBox;
//    delete bottomCollideBox;
//    delete rightBottomCollideBox;
//    delete topCollideBox;
//    delete leftBottomCollideBox;
//}

void S_SurfaceAutoTexture::addTexture(QPixmap pixmap)
{
    QGraphicsRectItem* texture = new QGraphicsRectItem(this->QGraphicsRectItem::pos().x(), this->QGraphicsRectItem::pos().y(), this->QGraphicsRectItem::rect().width(), this->QGraphicsRectItem::rect().height());

    QBrush brush;
    brush.setTexture(pixmap);
    texture->setBrush(brush);

    texture->setPen(Qt::NoPen);
    texture->setZValue(2);

    addedTextures.append(texture);

    scene->addItem(texture);
}
void S_SurfaceAutoTexture::changeTexture(QPixmap pixmap)
{
    QBrush brush;
    brush.setTexture(pixmap);
    setBrush(brush);
}
