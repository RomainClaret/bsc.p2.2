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

#include "w_object_v1.h"
#include "g_object_v1.h"
#include "p_penguin_v1.h"
#include "g_gameboard_v1.h"
#include <QWidget>
#include <QDebug>
//#include <QList>
//#include <QMap>
#include <QPainter>

W_Object_v1::W_Object_v1(QWidget *parent)
{
    this->resize(G_Gameboard_v1::getGameSquares(),G_Gameboard_v1::getGameSquares());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void W_Object_v1::paintEvent(QPaintEvent *)
{
    qDebug() << "PaintEvent";
    QPainter paint(this);

    int j = 0;
    QMap<QString, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd())
    {
         QString img = ":/items/items/";
         img.append(i.key().toLower());
         qDebug() << i.key();
         if(i.value()>1)
         {
            img.append(QString::number(i.value()));
         }

         img.append(".png");

         paint.drawPixmap(j*G_Gameboard_v1::getGameSquares(),0,G_Gameboard_v1::getGameSquares(),
                          G_Gameboard_v1::getGameSquares(),QPixmap(img));
         ++i;
         j++;
     }
}

void W_Object_v1::reloadObjectList(QList<G_Object_v1*> objectList)
{
    sacoche = objectList;
    map.clear();
    update();

    for(int i = 0; i < sacoche.size(); ++i)
    {
        if(map.contains(sacoche.at(i)->getName()))
        {
           map[sacoche.at(i)->getName()] = map.value(sacoche.at(i)->getName())+1;
        }
        else
        {
           map.insert(sacoche.at(i)->getName(),1);
        }
    }

    this->resize(map.size()*G_Gameboard_v1::getGameSquares(),G_Gameboard_v1::getGameSquares());

    qDebug() << "Call Update";
    update();
}
