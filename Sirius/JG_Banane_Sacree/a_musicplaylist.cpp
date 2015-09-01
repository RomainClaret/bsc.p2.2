#include "a_musicplaylist.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>

A_MusicPlaylist::A_MusicPlaylist()
{
    setUsable(true);
    musicPlayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist;
    setMusicPlaylist("");
}

void A_MusicPlaylist::playMusicPlaylist()
{
    if(usableMusicPlaylist)
    {
        start();
    }

}

void A_MusicPlaylist::playMusicPlaylist(QString playlist)
{
    setMusicPlaylist(playlist);
    start();
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

}

void A_MusicPlaylist::setMusicPlaylist(QString playlist)
{
    if (MY_OS == "UNIX")
    {
        this->musicQUrl = "qrc:/music/";
    }
    else
    {
        this->musicQUrl = "music/";
    }

    if(playlist.isEmpty())
    {
        playlist = "tutorial";
    }

    if (playlist == "tutorial")
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee_with_intro.wav"));
        for (int i = 0; i<5; i++)
        {
            musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.wav"));
        }
        musicPlaylist->setCurrentIndex(1);
    }
    musicPlayer->setPlaylist(musicPlaylist);
}

void A_MusicPlaylist::setMusicPlaylist(int value)
{
    if (MY_OS == "UNIX")
    {
        this->musicQUrl = "qrc:/music/";
    }
    else
    {
        this->musicQUrl = "music/";
    }

    if(value != -1)
    {
        value = -1;
    }

    if (value == -1)
    {
        musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee_with_intro.wav"));
        for (int i = 0; i<5; i++)
        {
            musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.wav"));
        }
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

void A_MusicPlaylist::pauseMusicPlaylist()
{
    musicPlayer->pause();
}

void A_MusicPlaylist::musicPlaylistRemoveIntro()
{
    musicPlaylist->removeMedia(0);
}
