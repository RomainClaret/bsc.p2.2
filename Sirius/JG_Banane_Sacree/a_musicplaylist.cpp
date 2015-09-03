#include "a_musicplaylist.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>

A_MusicPlaylist::A_MusicPlaylist()
{
    setUsable(true);
    musicPlayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist;
}

void A_MusicPlaylist::playMusicPlaylist()
{
    if(usableMusicPlaylist)
    {
        start();
    }
}

void A_MusicPlaylist::playMusicPlaylist(int value)
{
    if(usableMusicPlaylist)
    {
        setMusicPlaylist(value);
        start();
    }
}

void A_MusicPlaylist::run()
{
    musicPlayer->play();
}

void A_MusicPlaylist::stopMusicPlaylist()
{
    musicPlayer->stop();
    musicPlaylist->clear();
}

void A_MusicPlaylist::setMusicPlaylist(int value)
{
    qDebug() << "value: " << value;
    if (MY_OS == "UNIX")
    {
        this->musicQUrl = "qrc:/music/";
    }
    else
    {
        this->musicQUrl = "music/";
    }

    if (value == -2)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "menu.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == -1)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "menu.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 0)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_tutorial_with_intro.wav"));
        for (int i = 0; i<2; i++)
        {
            musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_tutorial.wav"));
        }
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 1)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_island.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 2)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_1.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 3)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_1_boss.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 4)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_2.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 5)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "level_3.wav"));
        musicPlaylist->setCurrentIndex(1);
    }

    if (value == 42)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "cheatcode_cantina.wav"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "cheatcode_imperialmarch.wav"));
        musicPlaylist->setCurrentIndex(1);
    }



    musicPlayer->setPlaylist(musicPlaylist);
}

void A_MusicPlaylist::muteMusicPlaylist()
{
    musicPlayer->setMuted(true);
}

void A_MusicPlaylist::unmuteMusicPlaylist()
{
    musicPlayer->setMuted(false);
}

void A_MusicPlaylist::setUsable(bool usable)
{
    usableMusicPlaylist = usable;
}

void A_MusicPlaylist::setMusicVolume(int value)
{
    if(usableMusicPlaylist && value > 0)
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

int A_MusicPlaylist::getMusicVolume()
{
    return musicPlayer->volume();
}

bool A_MusicPlaylist::getMusicUsablePlaylist()
{
    return usableMusicPlaylist;
}

void A_MusicPlaylist::pauseMusicPlaylist()
{
    musicPlayer->pause();
}

void A_MusicPlaylist::musicPlaylistRemoveIntro()
{
    musicPlaylist->removeMedia(0);
}
