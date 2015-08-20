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

#include "w_life_v1.h"
#include "g_object_v1.h"
#include "g_gameboard_v1.h"

#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QWidget>
#include <QDebug>

W_Life_v1::W_Life_v1(QWidget *parent)
{
    totalLife = 0;
    this->resize(G_Gameboard_v1::getGameSquares(),G_Gameboard_v1::getGameSquares());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void W_Life_v1::paintEvent(QPaintEvent *)
{
    qDebug() << "PaintEvent";
    QPainter paint(this);

    QString img = ":/items/items/oeuf.png";
    QString totalLifeString = QString::number(totalLife);
    totalLifeString.append("x");

    QBrush brush;
    brush.setColor(Qt::black);

    QFont font;
    font.setWeight(QFont::Bold);
    font.setFamily("Century Gothic");
    font.setPointSize(11);

    paint.drawPixmap(0,0,G_Gameboard_v1::getGameSquares(),G_Gameboard_v1::getGameSquares(),QPixmap(img));
    paint.setBrush(brush);
    paint.setFont(font);
    paint.drawText(G_Gameboard_v1::getGameSquares()+5, G_Gameboard_v1::getGameSquares()/2+5, totalLifeString);

//    for(int i = 0; i<totalLife; i++)
//    {
//        qDebug() << i*Gameboard::getGameSquares();
//        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
//                         Gameboard::getGameSquares(),QPixmap(img));
//    }
}

void W_Life_v1::updateHearts(int value)
{
    this->totalLife = value;
    this->resize(value*G_Gameboard_v1::getGameSquares(),G_Gameboard_v1::getGameSquares());
    update();
}
