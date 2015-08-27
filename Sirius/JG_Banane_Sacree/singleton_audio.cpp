#include "singleton_audio.h"
#include "a_music.h"
#include "a_sound.h"
#include "a_musicplaylist.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QDebug>
#include <QThread>

Singleton_Audio* Singleton_Audio::instance = NULL;

Singleton_Audio::Singleton_Audio()
{
    soundThread = new A_Sound();
    musicThread = new A_Music();
    musicPlaylistThread = new A_MusicPlaylist();
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
    soundThread->setSound(sound);
}

void Singleton_Audio::playSound()
{
    soundThread->playSound();
}

void Singleton_Audio::playSound(QString sound)
{
    A_Sound *tmpSoundThread = new A_Sound();
    tmpSoundThread->playSound(sound);
}

void Singleton_Audio::stopSound()
{
    soundThread->stopSound();
}

void Singleton_Audio::stopMusic()
{
    musicThread->stopMusic();
}

void Singleton_Audio::pauseMusic()
{
    musicThread->pauseMusic();
}

void Singleton_Audio::playMusic()
{
    musicThread->playMusic();
}

void Singleton_Audio::playMusic(QString music)
{
    musicThread->setMusic(music);
    musicThread->playMusic();
}

void Singleton_Audio::setMusic(QString music)
{
    musicThread->setMusic(music);
}

void Singleton_Audio::setMusicPlaylist(QString playlist)
{
    musicPlaylistThread->setMusicPlaylist(playlist);
}

void Singleton_Audio::playMusicPlaylist()
{
    musicPlaylistThread->playMusicPlaylist();
}

void Singleton_Audio::playMusicPlaylist(QString playlist)
{
    musicPlaylistThread->playMusicPlaylist(playlist);
}

void Singleton_Audio::playMusicPlaylist(int value)
{
    musicPlaylistThread->playMusicPlaylist(value);
}

void Singleton_Audio::playMusicPlaylistWithIntro()
{
    musicPlaylistThread->playMusicPlaylist();
}

void Singleton_Audio::pauseMusicPlaylist()
{
    musicPlaylistThread->pauseMusicPlaylist();
}

void Singleton_Audio::resumeMusicPlaylist()
{
    musicPlaylistThread->playMusicPlaylist();
}

void Singleton_Audio::musicPlaylistRemoveIntro()
{
    musicPlaylistThread->musicPlaylistRemoveIntro();
}

bool Singleton_Audio::getPlaybleSound()
{
    return playableSound;
}

bool Singleton_Audio::getPlaybleMusicPlaylist()
{
    return playableMusicPlaylist;
}

void Singleton_Audio::setPlayableMusicPlaylist(bool playable)
{
    this->playableMusicPlaylist = playable;
}
