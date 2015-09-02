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
#include <QLineEdit>
#include <QDebug>
#include <QKeyEvent>
#include "../menu/w_menucode_lineedit.h"
#include <QLabel>

#include "../memento.h"

W_MenuCode::W_MenuCode(QWidget *parent)
{
   this->parent = (W_Menu*)parent;
   setTitleParent();

   btnCodeValidate = new QPushButton(tr("Valider le code"));
   lineEditCode = new W_MenuCode_LineEdit;
   lineEditCode->setEnabled(true);
   lineEditCode->setFocusPolicy(Qt::StrongFocus);

   btnBonusReturn = new QPushButton(tr("Retourner aux Bonus"));
   labelCodeResult = new QLabel("");
   labelCodeResult->setStyleSheet("border: none;");

   btnBonusReturn->setStyleSheet(W_Menu::styleBtn);
   btnCodeValidate->setStyleSheet(W_Menu::styleBtn);

   connect(btnBonusReturn, SIGNAL(clicked()),parent, SLOT(loadBonus()));
   connect(btnCodeValidate, SIGNAL(clicked()),this, SLOT(validateCode()));

   layoutMenuPause = new QFormLayout;
   layoutMenuPause->addRow(labelCodeResult);
   layoutMenuPause->addRow(lineEditCode);
   layoutMenuPause->addRow(btnCodeValidate);
   layoutMenuPause->addRow(btnBonusReturn);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);

   hash.insert("Hello World!",1);
   hash.insert("Je veux des bananes",2);
   hash.insert("Happy Feet",3);
   hash.insert("Ici, il fait chaud",4);
   hash.insert("I am not from Madagascar",5);
   hash.insert("I am a secret agent",6);
   hash.insert("Même pas peur",7);
   hash.insert("May the 4th be with you",8);
   hash.insert("Penguin's force is better",9);
   hash.insert("Maman!!",10);
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

void W_MenuCode::validateCode()
{
    QString code = lineEditCode->text();
    qDebug() << code;

    if(hash.contains(code))
    {
        acceptCode();
        switch(hash[code])
        {
        case W_MenuCode::CODE_HELLO: qDebug() << "HELLO WORLD"; break;

        case W_MenuCode::CODE_BANANA:
            Memento::getInstance()->setSpecialTextureEgg(true);
            break;

        case W_MenuCode::CODE_HAPPYFEET: qDebug() << "HAPPY FEET"; break;
        case W_MenuCode::CODE_HOTHOTHOT: qDebug() << "HOTHOTHOT"; break;
        case W_MenuCode::CODE_MADAGASCAR: qDebug() << "madagascar"; break;
        case W_MenuCode::CODE_SECRETAGENT: qDebug() << "secret agent"; break;

        case W_MenuCode::CODE_NOTSCARED:
            Memento::getInstance()->setSpecialTextureEnemy(true);
            break;

        case W_MenuCode::CODE_IMSCARED:
            Memento::getInstance()->setSpecialTextureEnemy(false);
            break;

        case W_MenuCode::CODE_THE4TH:
            Singleton_Audio::getInstance()->playMusicCheatCode();
            break;

        case W_MenuCode::CODE_PENGUINFORCE:
            Singleton_Audio::getInstance()->stopMusicCheatCode();
            break;

        default: refuseCode();
        }
    }
    else
    {
        refuseCode();
    }
}

void W_MenuCode::refuseCode()
{
    labelCodeResult->setText("Try again...");
    Singleton_Audio::getInstance()->playSoundCheatCodeUnvalide();
}

void W_MenuCode::acceptCode()
{
    labelCodeResult->setText("Code validé! Découvre son action sur ton jeu ;)");
    Singleton_Audio::getInstance()->playSoundCheatCodeValide();
}

bool W_MenuCode::BANANASPECIAL = false;
