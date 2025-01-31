#include "a_music.h"
#include <QDebug>
#include <QMediaPlayer>

A_Music::A_Music()
{
    setUsable(true);
    musicPlayer = new QMediaPlayer;
    setMusic("");
}

void A_Music::playMusic()
{
    if (usableMusic)
    {
        start();
    }
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

void A_Music::muteMusic()
{
    musicPlayer->setMuted(true);
}

void A_Music::unmuteMusic()
{
    musicPlayer->setMuted(false);
}

void A_Music::setUsable(bool usable)
{
    usableMusic = usable;
}

void A_Music::setMusicVolume(int value)
{
    if(usableMusic && value > 0)
    {
       musicPlayer->setVolume(value);
    }
    else if(value == 0)
    {
        setUsable(false);
    }
    else
    {
        setUsable(true);
        musicPlayer->setVolume(value);
    }
}

int A_Music::getMusicVolume()
{
    return musicPlayer->volume();
}

void A_Music::setMusic(QString music)
{
    if (MY_OS == 0)
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
    this->musicQUrl.append(".wav");
    musicPlayer->setMedia(QUrl(this->musicQUrl));
}

