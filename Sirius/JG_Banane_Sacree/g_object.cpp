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

#include <QDebug>

G_Object::G_Object(int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    setDesign();
}

G_Object::G_Object(QString name, int xpos, int ypos, QGraphicsItem *parent) : G_Surface(xpos, ypos, parent)
{
    this->nom = new QString(name);
    setZValue(11);
    setDesign();
}

G_Object::G_Object(QString name, QGraphicsItem *parent): G_Surface(0, 0, parent)
{
    this->nom = new QString(name);
    setZValue(11);
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

void G_Object::repaintElement()
{
    if(W_MenuCode::BANANASPECIAL && this->nom == OBJECT_EGG)
    {
        qDebug() << "PAINT";
        this->nom = new QString(OBJECT_BANANA);
        setDesign();
    }
    update();
}

QString G_Object::OBJECT_EGG = "EGG";
QString G_Object::OBJECT_SHOES = "SHOES";
QString G_Object::OBJECT_FISH = "FISH";
QString G_Object::OBJECT_BANANA = "BANANA";
