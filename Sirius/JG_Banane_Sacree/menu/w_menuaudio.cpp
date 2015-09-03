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

#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include "../menu/w_menu.h"
#include <QDebug>
#include "w_menuaudio.h"
#include "../singleton_audio.h"

W_MenuAudio::W_MenuAudio(QWidget *parent)
{
    audioSingleton = Singleton_Audio::getInstance();

   this->parent = (W_Menu*)parent;
   setTitleParent();

   btnBonusReturn = new QPushButton(tr("Retourner aux Bonus"));
   sldMusics = new QSlider(Qt::Horizontal);
   sldSounds = new QSlider(Qt::Horizontal);
   sldMusics->setValue(getMusicsVolume());
   sldSounds->setValue(getSoundsVolume());
   lbMusics = new QLabel(tr("Modifier le volume des musiques"));
   lbMusicsValue = new QLabel(QString::number(getMusicsVolume()));
   lbSounds = new QLabel(tr("Modifier le volume des sons"));
   lbSoundsValue = new QLabel(QString::number(getSoundsVolume()));

   btnBonusReturn->setStyleSheet(W_Menu::styleBtn);

   sldMusics->setTickPosition(QSlider::TicksAbove);
   sldSounds->setTickPosition(QSlider::TicksAbove);
   sldMusics->setTickInterval(1);
   sldSounds->setTickInterval(1);
   sldMusics->setRange(0,100);
   sldSounds->setRange(0,100);

   connect(btnBonusReturn, SIGNAL(clicked()),parent, SLOT(loadBonus()));

   layoutMenuPause = new QGridLayout;
   layoutMenuPause->addWidget(lbMusics);
   layoutMenuPause->addWidget(sldMusics,1,0);
   layoutMenuPause->addWidget(lbMusicsValue,1,1);
   layoutMenuPause->addWidget(lbSounds);
   layoutMenuPause->addWidget(sldSounds,3,0);
   layoutMenuPause->addWidget(lbSoundsValue,3,1);
   layoutMenuPause->addWidget(btnBonusReturn);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);

   connect(sldMusics, SIGNAL(valueChanged(int)),this, SLOT(setValueMusicsVolume(int)));
   connect(sldSounds, SIGNAL(valueChanged(int)),this, SLOT(setValueSoundsVolume(int)));

}

void W_MenuAudio::setTitleParent()
{
    parent->setTitle(tr("Le son..."));
    parent->setSubTitle(tr("Modifiez les paramètres liés aux sons ici"));
}

int W_MenuAudio::getSoundsVolume()
{
    return audioSingleton->getSoundsVolume();
}

int W_MenuAudio::getMusicsVolume()
{
    return audioSingleton->getMusicsVolume();
}

void W_MenuAudio::setValueMusicsVolume(int value)
{
    lbMusicsValue->setText(QString::number(value));
    audioSingleton->setMusicsVolume(value);
}

void W_MenuAudio::setValueSoundsVolume(int value)
{
    lbSoundsValue->setText(QString::number(value));
    audioSingleton->setSoundsVolume(value);
}

void W_MenuAudio::showEvent(QShowEvent *)
{
    sldMusics->setValue(getMusicsVolume());
    sldSounds->setValue(getSoundsVolume());
}
