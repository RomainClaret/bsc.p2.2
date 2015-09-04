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

#include "g_object.h"
#include "surface/g_surface.h"
#include <QBrush>
#include <QGraphicsItem>
#include <QPaintEvent>
#include <menu/w_menucode.h>
#include "memento.h"

#include <QDebug>

G_Object::G_Object(int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : G_Surface(xpos, ypos, game, parent)
{
    setDesign();
}

G_Object::G_Object(QString name, int xpos, int ypos, G_Gameboard* game, QGraphicsItem *parent) : G_Surface(xpos, ypos, game, parent)
{
    this->nom = new QString(name);
    setZValue(5);
    setDesign();
    Memento::getInstance()->setPosSurface(this,new QPoint(xpos, ypos));

    if(name == OBJECT_EGG)
    {
        Memento::getInstance()->addSpecialItemEgg(this);
    }
}

G_Object::G_Object(QString name, G_Gameboard* game, QGraphicsItem *parent): G_Surface(0, 0, game, parent)
{
    this->nom = new QString(name);
    setZValue(5);
    setDesign();
}

void G_Object::setDesign()
{
    objectSkin = new QBrush();
    QString img = ":/items/items/";
    img.append(this->nom->toLower());
    img.append(".png");
    objectSkin->setTexture(QPixmap(img));
    setBrush(*objectSkin);
}

QString G_Object::getName()
{
    return *nom;
}

QPixmap G_Object::getTexture()
{
    return objectSkin->texture();
}

void G_Object::setSpecialTexture(bool value)
{
    if(value)
    {
        QString img = ":/items/items/banana.png";
        objectSkin->setTexture(QPixmap(img));
        setBrush(*objectSkin);
    }
    else
    {
        setDesign();
    }
}

QString G_Object::OBJECT_EGG = "EGG";
QString G_Object::OBJECT_SHOES = "SHOES";
QString G_Object::OBJECT_FISH = "FISH";
QString G_Object::OBJECT_BANANA = "BANANA";
