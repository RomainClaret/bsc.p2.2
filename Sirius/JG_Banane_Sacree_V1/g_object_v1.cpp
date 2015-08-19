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

#include "g_object_v1.h"
#include "g_surface_v1.h"
#include <QBrush>
#include <QGraphicsItem>

G_Object_v1::G_Object_v1(int xpos, int ypos, QGraphicsItem *parent) : G_Surface_v1(xpos, ypos, parent)
{
    setDesign();

}
G_Object_v1::G_Object_v1(QString new_nom, QGraphicsItem *parent) : G_Surface_v1(0, 0, parent)
{
    this->nom = new QString(new_nom);
    setZValue(2);
    setDesign();
}

void G_Object_v1::setDesign()
{
    objectSkin = new QBrush();
    QString img = ":/items/items/";
    img.append(this->nom->toLower());
    img.append(".png");
    objectSkin->setTexture(QPixmap(img));

    setBrush(*objectSkin);
}

QString G_Object_v1::getName()
{
    return *nom;
}

QPixmap G_Object_v1::getTexture()
{
    return objectSkin->texture();
}
