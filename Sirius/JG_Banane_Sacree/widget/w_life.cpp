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

#include "../widget/w_life.h"
#include "../g_object.h"
#include "../g_gameboard.h"

#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QWidget>
#include <QDebug>

#include <menu/w_menucode.h>

W_Life::W_Life(QWidget *)
{
    totalLife = 0;
    this->resize(G_Gameboard::getGameSquares(),G_Gameboard::getGameSquares());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void W_Life::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    QString img;
    if(W_MenuCode::BANANASPECIAL)
    {
        img = ":/items/items/banana.png";
    }
    else
    {
        img = ":/items/items/egg.png";
    }

    QString totalLifeString = QString::number(totalLife);
    totalLifeString.append("x");

    QBrush brush;
    brush.setColor(Qt::black);

    QFont font;
    font.setWeight(QFont::Bold);
    font.setFamily("Century Gothic");
    font.setPointSize(11);

    paint.drawPixmap(0,0,G_Gameboard::getGameSquares(),G_Gameboard::getGameSquares(),QPixmap(img));
    paint.setBrush(brush);
    paint.setFont(font);
    paint.drawText(G_Gameboard::getGameSquares()+5, G_Gameboard::getGameSquares()/2+5, totalLifeString);
}

void W_Life::updateHearts(int value)
{
    this->totalLife = value;
    this->resize(value*G_Gameboard::getGameSquares(),G_Gameboard::getGameSquares());
    update();
}
