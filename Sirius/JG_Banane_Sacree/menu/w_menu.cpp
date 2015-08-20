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

#include "../menu/w_menu.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QDebug>

QString W_Menu::styleBtn = "border-style: none;"
        "border-radius: 5px;"
        "padding: 6px;"
        "margin: 5px;"
        "font-family: Century Gothic;"
        "background-color: white;"
        "color: white;"
        "font-weight: bold;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00A5FF, stop: 1 #3087F2);";

QString W_Menu::styleBtnUnable = "border-style: none;"
                   "border-radius: 5px;"
                   "padding: 6px;"
                   "margin: 5px;"
                   "font-family: Century Gothic;"
                   "background-color: white;"
                   "color: white;"
                   "font-weight: bold;"
                   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #c6c6c6, stop: 1 #b3b3b3);";

W_Menu::W_Menu(QWidget *parent)
{
    this->setStyleSheet(
                        "text-align: center;"
                        "color: #2e2e2e;"
                        "background-color: #ffffff;"
                        "border-style: solid;"
                        "border-color: #d3d3d3;"
                        "border-width: 1px;"
                        "border-radius: 8px;"
                        );

    layoutMenuPause = new QFormLayout;
    titleMenuPause = new QLabel(tr("James Gouin"));
    titleMenuPause->setAlignment(Qt::AlignCenter);
    titleMenuPause->setStyleSheet(
                                  "margin-left: auto;"
                                  "font-family: Century Gothic;"
                                  "margin-right : auto;"
                                  "color: #2e2e2e;"
                                  "font: bold 50px;"
                                  "border-style: none;"
                                  );


   undertitleMenuPause = new QLabel(tr("James Gouin et la banane sacrée..."));
   undertitleMenuPause->setAlignment(Qt::AlignCenter);
   undertitleMenuPause->setStyleSheet(
                                 "margin-left: auto;"
                                 "font-family: Century Gothic;"
                                 "margin-right : auto;"
                                 "color: #2e2e2e;"
                                 "font: bold 12px;"
                                 "border-style: none;"
                                 );

   menuPause = new W_MenuPause(this, (G_Gameboard*)parent);
   menuBonus = new W_MenuBonus(this);
   menuCode = new W_MenuCode(this);
   menuBonus->setVisible(false);
   menuCode->setVisible(false);

   layoutMenuPause->addRow(titleMenuPause);
   layoutMenuPause->addRow(undertitleMenuPause);
   layoutMenuPause->addRow(menuPause);
   layoutMenuPause->addRow(menuBonus);
   layoutMenuPause->addRow(menuCode);

   this->setMinimumWidth(400);
   this->setMinimumHeight(400);
   this->resize(400,400);
   this->setLayout(layoutMenuPause);
}

void W_Menu::paintEvent(QPaintEvent *)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(
  QStyle::PE_Widget, &o, &p, this);
}

void W_Menu::setTitle(QString title)
{
    titleMenuPause->setText(title);
}

void W_Menu::setSubTitle(QString subTitle)
{
    undertitleMenuPause->setText(subTitle);
}

void W_Menu::loadBonus()
{
    menuPause->setVisible(false);
    menuCode->setVisible(false);
    menuBonus->setVisible(true);
    menuBonus->setTitleParent();
    adjustSize();
}

void W_Menu::loadPause()
{
    menuPause->setVisible(true);
    menuCode->setVisible(false);
    menuBonus->setVisible(false);
    menuPause->setTitleParent();
    adjustSize();
}

void W_Menu::loadCode()
{
    menuCode->setVisible(true);
    menuPause->setVisible(false);
    menuBonus->setVisible(false);
    menuCode->setTitleParent();
    adjustSize();
}

/**
 * @details Call loadPause() method
 */
void W_Menu::showEvent(QShowEvent*)
{
    loadPause();
}

void W_Menu::setUnableMenu(int levelValue)
{
    menuPause->setUnableMenu(levelValue);
}

void W_Menu::keyPressEvent(QKeyEvent *event)
{
    menuCode->keyPressEvent(event);
}
