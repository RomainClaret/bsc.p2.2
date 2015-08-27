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

#include "w_dialog.h"
#include "w_dialog_image.h"
#include "w_dialog_container.h"
#include "../../singleton_audio.h"
#include <QPainter>
#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QLabel>
#include <QStyleOption>

W_Dialog::W_Dialog(QWidget *)
{
    audioSingleton = Singleton_Audio::getInstance();
    audioSingleton->setSound("dialog_interaction");
    audioSingleton->setPlayableSounds(false); //avoid to have a sounds at map loading while it's opening and hiding

    image = new W_DialogImage("loutre.png", this);
    textWidget = new W_DialogContainer(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(textWidget);
    layout->addWidget(image);
    layout->setSpacing(0);

    this->setLayout(layout);

    title = new QLabel(tr("Ordre de mission de James Gouin"));
    title->setStyleSheet(
                "font: bold 20px;"
                "border-style: none;"
                );

    text = new QLabel();
    text->setStyleSheet(
                "font-size: 14px;"
                "border-style: none;"
                );
    text->setWordWrap(true);

    escapeText = new QLabel(tr("Espace pour continuer"));
    escapeText->setStyleSheet(
                "font: bold 12px;"
                "border-style: none;"
                );

    escapeText->setAlignment(Qt::AlignCenter);

    title->setAlignment(Qt::AlignCenter);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_PaintOnScreen);

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void W_Dialog::setText(QString text, int type)
{
    textWidget->setText(text, type);
}

void W_Dialog::setImage(QString imageName)
{
    image->setImage(imageName);
    update();
}

QString W_Dialog::getText()
{
    return textWidget->getText();
}

void W_Dialog::showEvent(QShowEvent *)
{


}

void W_Dialog::hideEvent(QHideEvent *)
{

}
