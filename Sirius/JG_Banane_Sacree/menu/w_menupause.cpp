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

#include "../menu/w_menupause.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include "../menu/w_menu.h"
#include <QDebug>

W_MenuPause::W_MenuPause(QWidget *parent, G_Gameboard* gameboard)
{
    this->gameboard = gameboard;
    this->parent = (W_Menu*)parent;
    layoutMenuPause = new QFormLayout;

    btnMenuPauseResume = new QPushButton(tr("Reprendre la Partie"));
    btnMenuPauseRestartEnigma = new QPushButton(tr("Retourner au dernier checkpoint"));
    btnMenuPauseRestartLevel = new QPushButton(tr("Redémarrer la partie"));
    btnMenuPauseIsland = new QPushButton(tr("Aller sur l'île"));
    btnMenuPauseQuit = new QPushButton(tr("Quitter la partie"));
    btnMenuPauseBonus = new QPushButton(tr("Plus"));

    btnMenuPauseResume->setStyleSheet(W_Menu::styleBtn);
    btnMenuPauseRestartEnigma->setStyleSheet(W_Menu::styleBtn);
    btnMenuPauseQuit->setStyleSheet(W_Menu::styleBtn);
    btnMenuPauseIsland->setStyleSheet(W_Menu::styleBtn);
    btnMenuPauseRestartLevel->setStyleSheet(W_Menu::styleBtn);
    btnMenuPauseBonus->setStyleSheet(W_Menu::styleBtn);

    connect(btnMenuPauseQuit, SIGNAL(clicked()),gameboard, SLOT(exitGame()));
    connect(btnMenuPauseResume, SIGNAL(clicked()),gameboard, SLOT(resumeGame()));
    connect(btnMenuPauseRestartEnigma, SIGNAL(clicked()),gameboard, SLOT(restartEnigma()));
    connect(btnMenuPauseRestartLevel, SIGNAL(clicked()),gameboard, SLOT(restartLevel()));
    connect(btnMenuPauseIsland, SIGNAL(clicked()),gameboard, SLOT(returnIsland()));
    connect(btnMenuPauseBonus, SIGNAL(clicked()), (W_Menu*)parent, SLOT(loadBonus()));

    layoutMenuPause->addRow(btnMenuPauseResume);
    layoutMenuPause->addRow(btnMenuPauseRestartEnigma);
    layoutMenuPause->addRow(btnMenuPauseRestartLevel);
    layoutMenuPause->addRow(btnMenuPauseIsland);
    layoutMenuPause->addRow(btnMenuPauseBonus);
    layoutMenuPause->addRow(btnMenuPauseQuit);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);
}

void W_MenuPause::setUnableMenu(int levelValue)
{
    switch(levelValue)
    {
    case 0: btnMenuPauseIsland->setDisabled(true);
            btnMenuPauseIsland->setStyleSheet(W_Menu::styleBtnUnable);
            break;
    case 1: btnMenuPauseIsland->setDisabled(true);
            btnMenuPauseIsland->setStyleSheet(W_Menu::styleBtnUnable);
            btnMenuPauseRestartLevel->setDisabled(true);
            btnMenuPauseRestartLevel->setStyleSheet(W_Menu::styleBtnUnable);
            btnMenuPauseRestartEnigma->setDisabled(true);
            btnMenuPauseRestartEnigma->setStyleSheet(W_Menu::styleBtnUnable);
            break;
    default:
        btnMenuPauseResume->setDisabled(false);
        btnMenuPauseRestartEnigma->setDisabled(false);
        btnMenuPauseQuit->setDisabled(false);
        btnMenuPauseIsland->setDisabled(false);
        btnMenuPauseRestartLevel->setDisabled(false);
        btnMenuPauseBonus->setDisabled(false);
        btnMenuPauseResume->setStyleSheet(W_Menu::styleBtn);
        btnMenuPauseRestartEnigma->setStyleSheet(W_Menu::styleBtn);
        btnMenuPauseQuit->setStyleSheet(W_Menu::styleBtn);
        btnMenuPauseIsland->setStyleSheet(W_Menu::styleBtn);
        btnMenuPauseRestartLevel->setStyleSheet(W_Menu::styleBtn);
        btnMenuPauseBonus->setStyleSheet(W_Menu::styleBtn);
    }
}

void W_MenuPause::setTitleParent()
{
    parent->setTitle(tr("Pause"));
    parent->setSubTitle(tr("James Gouin prend sa pause..."));
}
