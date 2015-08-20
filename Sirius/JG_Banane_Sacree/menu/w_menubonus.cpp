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

#include "../menu/w_menubonus.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include "../menu/w_menu.h"

W_MenuBonus::W_MenuBonus(QWidget *parent)
{
   this->parent = (W_Menu*)parent;
   setTitleParent();

   btnBonusCode = new QPushButton(tr("Entrer un code spécial"));
   btnBonusCredits = new QPushButton(tr("Voir les crédits"));
   btnBonusReturn = new QPushButton(tr("Retourner au menu pause"));

   btnBonusCode->setStyleSheet(W_Menu::styleBtn);
   btnBonusCredits->setStyleSheet(W_Menu::styleBtn);
   btnBonusReturn->setStyleSheet(W_Menu::styleBtn);

    connect(btnBonusCode, SIGNAL(clicked()),parent, SLOT(loadCode()));
//    connect(btnBonusCredits, SIGNAL(clicked()),parent, SLOT(resumeGame()));
    connect(btnBonusReturn, SIGNAL(clicked()),parent, SLOT(loadPause()));

   layoutMenuPause = new QFormLayout;
   layoutMenuPause->addRow(btnBonusCode);
   layoutMenuPause->addRow(btnBonusCredits);
   layoutMenuPause->addRow(btnBonusReturn);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);
}

void W_MenuBonus::setTitleParent()
{
    parent->setTitle(tr("Bonus"));
    parent->setSubTitle(tr("James Gouin profite des Bonus..."));
}
