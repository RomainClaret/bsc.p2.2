#include "singleton_audio.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QDebug>

Singleton_Audio* Singleton_Audio::instance = NULL;

Singleton_Audio::Singleton_Audio()
{
    soundPlayer = new QMediaPlayer;
    musicPlayer = new QMediaPlayer;
    musicPlaylist = new QMediaPlaylist;
    setSound("");
    setMusic("");
    setMusicPlaylist("");
}

Singleton_Audio::~Singleton_Audio()
{

}

Singleton_Audio* Singleton_Audio::getInstance()
{
    if(instance == NULL)
    {
        instance = new Singleton_Audio();
    }
    return instance;
}

void Singleton_Audio::setPlayableSounds(bool playable)
{
    this->playableSound = playable;
}

void Singleton_Audio::setSound(QString sound)
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

void Singleton_Audio::playSound()
{
    soundPlayer->play();
}

void Singleton_Audio::playSound(QString sound)
{
    setSound(sound);
    soundPlayer->play();
}

void Singleton_Audio::stopMusic()
{
    musicPlayer->stop();
}

void Singleton_Audio::playMusic()
{
    musicPlayer->play();
}

void Singleton_Audio::playMusic(QString music)
{
    setMusic(music);
    musicPlayer->play();
}

void Singleton_Audio::setMusic(QString music)
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

void Singleton_Audio::setMusicPlaylist(QString playlist)
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
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee_with_intro.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->addMedia(QUrl(this->musicQUrl + "Joyful_Jubilee.mp3"));
        musicPlaylist->setCurrentIndex(0);
    }
}

void Singleton_Audio::playMusicPlaylist()
{
    musicPlayer->setPlaylist(musicPlaylist);
    musicPlayer->play();
}

void Singleton_Audio::playMusicPlaylistWithIntro()
{
    musicPlayer->setPlaylist(musicPlaylist);
    musicPlayer->play();
}

void Singleton_Audio::pauseMusicPlaylist()
{
    musicPlayer->pause();
}

void Singleton_Audio::resumeMusicPlaylist()
{
    musicPlayer->play();
}

void Singleton_Audio::musicPlaylistRemoveIntro()
{
    musicPlaylist->removeMedia(0);
}

bool Singleton_Audio::getPlaybleSound()
{
    return playableSound;
}
