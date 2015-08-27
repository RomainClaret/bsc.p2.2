#include "a_music.h"
#include <QDebug>
#include <QMediaPlayer>

A_Music::A_Music()
{
    musicPlayer = new QMediaPlayer;
    setMusic("");
}

void A_Music::playMusic()
{
    start();
}

void A_Music::run()
{
    musicPlayer->play();
}

void A_Music::stopMusic()
{
    musicPlayer->stop();
}

void A_Music::pauseMusic()
{
    musicPlayer->pause();
}

void A_Music::setMusic(QString music)
{
    if (MY_OS == "UNIX")
    {
        this->musicQUrl = "qrc:/music/";
    }
    else
    {
        this->musicQUrl = "music/";
    }

    if(music.isEmpty())
    {
        music = "Igazi_Jazz";
    }

    this->musicQUrl.append(music);
    this->musicQUrl.append(".mp3");
    musicPlayer->setMedia(QUrl(this->musicQUrl));
}

