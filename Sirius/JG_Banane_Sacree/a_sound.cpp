#include "a_sound.h"
#include <QDebug>
#include <QMediaPlayer>

A_Sound::A_Sound()
{
    setUsable(true);
    soundPlayer = new QMediaPlayer;
    setSound("");
    connect(this, SIGNAL(finished()), this, SLOT(terminate()));
}

A_Sound::~A_Sound()
{
    delete soundPlayer;
}

void A_Sound::playSound()
{
    if(usableSound)
    {
       start();
    }
}

void A_Sound::stopSound()
{
    exit();
}

void A_Sound::muteSound()
{
    soundPlayer->setMuted(true);
}

void A_Sound::unmuteSound()
{
    soundPlayer->setMuted(false);
}

void A_Sound::setUsable(bool usable)
{
    usableSound = usable;
}

void A_Sound::setSoundVolume(int value)
{
    if(usableSound && value > 0)
    {
       soundPlayer->setVolume(value);
    }
    else if(value == 0)
    {
        setUsable(false);
    }
    else
    {
        setUsable(true);
        soundPlayer->setVolume(value);
    }
}

int A_Sound::getSoundVolume()
{
    return soundPlayer->volume();
}


void A_Sound::playSound(QString sound)
{
    if(usableSound)
    {
        this->wait();
        setSound(sound);
        start();
    }
}

void A_Sound::run()
{
    soundPlayer->play();
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
