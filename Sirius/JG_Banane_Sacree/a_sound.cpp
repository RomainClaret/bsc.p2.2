#include "a_sound.h"
#include <QDebug>
#include <QMediaPlayer>

A_Sound::A_Sound()
{
    soundPlayer = new QMediaPlayer;
    setSound("");
    connect(this, SIGNAL(finished()), this, SLOT(terminate()));
}

void A_Sound::playSound()
{
    start();
}

void A_Sound::stopSound()
{
    exit();
}

void A_Sound::playSound(QString sound)
{
    setSound(sound);
    start();
}

void A_Sound::run()
{
//    soundPlayer->play();
}

void A_Sound::setSound(QString sound)
{
    this->soundQUrl = "qrc:/sound/";

    if(sound.isEmpty())
    {
        sound = "dialog_interaction";
    }

    this->soundQUrl.append(sound);
    this->soundQUrl.append(".wav");

    soundPlayer->setMedia(QUrl(this->soundQUrl));
}
