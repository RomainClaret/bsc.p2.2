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

#include "w_menubonus.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include "w_menu.h"

#include <QDebug>
#include <QKeyEvent>
#include "menu/w_menucode_lineedit.h"

W_MenuCode::W_MenuCode(QWidget *parent)
{
   this->parent = (W_Menu*)parent;
   setTitleParent();

   btnCodeValidate = new QPushButton(tr("Valider le code"));
   lineEditCode = new W_MenuCode_LineEdit;
   lineEditCode->setEnabled(true);
   lineEditCode->setFocusPolicy(Qt::StrongFocus);

   btnBonusReturn = new QPushButton(tr("Retourner aux Bonus"));

   btnBonusReturn->setStyleSheet(W_Menu::styleBtn);
   btnCodeValidate->setStyleSheet(W_Menu::styleBtn);

   connect(btnBonusReturn, SIGNAL(clicked()),parent, SLOT(loadBonus()));

   layoutMenuPause = new QFormLayout;
   layoutMenuPause->addRow(lineEditCode);
   layoutMenuPause->addRow(btnCodeValidate);
   layoutMenuPause->addRow(btnBonusReturn);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);
}

void W_MenuCode::setTitleParent()
{
    parent->setTitle(tr("Chut..."));
    parent->setSubTitle(tr("Entrez votre code spécial afin d'obtenir des bonus"));
}

void W_MenuCode::keyPressEvent(QKeyEvent *event)
{
    lineEditCode->keyPressEvent(event);
}
