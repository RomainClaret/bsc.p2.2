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
    soundThreadWalking = new A_Sound();
    soundThreadMovableSliding = new A_Sound();
    soundThreadMovableMoving = new A_Sound();
    soundThreadObject = new A_Sound();
    soundThreadSunk = new A_Sound();
    soundThread = new A_Sound();

    musicThread = new A_Music();
    musicPlaylistMenuThread = new A_MusicPlaylist();
    musicPlaylistInGameThread = new A_MusicPlaylist();

    usableAll(true);
    //usableMusics(true);
    //usableSounds(true);
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
    soundThread->playSound(sound);
}

void Singleton_Audio::playSoundBlockSliding()
{
    soundThreadMovableSliding->playSound("movable_sliding");
}

void Singleton_Audio::playSoundBlockStopSliding()
{
    soundThreadMovableSliding->playSound("movable_stop_sliding");
}

void Singleton_Audio::playSoundPlayerSliding()
{
    soundThreadWalking->playSound("player_sliding");
}

void Singleton_Audio::playSoundPlayerWalking()
{
    soundThreadWalking->playSound("walking_in_snow");
}

void Singleton_Audio::playSoundGetObject()
{
    soundThreadObject->playSound("get_object");
}

void Singleton_Audio::playSoundSunk()
{
    soundThreadSunk->playSound("movable_in_water");
}

void Singleton_Audio::playSoundEventRestartCheckpoint()
{
    soundThread->playSound("restart_checkpoint");
}

void Singleton_Audio::playSoundEventLostLevel()
{
    soundThread->playSound("lost_level");
}

void Singleton_Audio::playSoundEventStartGame()
{
    soundThread->playSound("start_game");
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

void Singleton_Audio::playMusicPlaylist()
{
    musicPlaylistInGameThread->playMusicPlaylist();
}

void Singleton_Audio::playMusicPlaylist(int value)
{
    musicPlaylistInGameThread->playMusicPlaylist(value);
}

void Singleton_Audio::playMusicPlaylistMenu()
{
    musicPlaylistMenuThread->playMusicPlaylist();
}

void Singleton_Audio::playMusicPlaylistMenu(int value)
{
    musicPlaylistMenuThread->playMusicPlaylist(value);
}

void Singleton_Audio::pauseMusicPlaylistMenu()
{
    musicPlaylistMenuThread->pauseMusicPlaylist();
}

void Singleton_Audio::playSoundPlayerSlidingMovable()
{
    soundThread->playSound("player_sliding_movable");
}

void Singleton_Audio::playSoundPlayerSlidingStop()
{
    soundThread->playSound("player_stop_sliding");
}

int Singleton_Audio::getMusicsVolume()
{
    int value = musicThread->getMusicVolume();
    musicPlaylistInGameThread->setMusicVolume(value);
    musicPlaylistMenuThread->setMusicVolume(value);
    return value;
}

int Singleton_Audio::getSoundsVolume()
{
    int value = soundThread->getSoundVolume();
    soundThreadWalking->setSoundVolume(value);
    soundThreadMovableSliding->setSoundVolume(value);
    soundThreadMovableMoving->setSoundVolume(value);
    soundThreadObject->setSoundVolume(value);
    soundThreadSunk->setSoundVolume(value);
    return value;
}

void Singleton_Audio::setMusicsVolume(int value)
{
    musicThread->setMusicVolume(value);
    setMusicPlaylistVolume(value);
}

void Singleton_Audio::setMusicPlaylistVolume(int value)
{
    musicPlaylistInGameThread->setMusicVolume(value);
    musicPlaylistMenuThread->setMusicVolume(value);
}

void Singleton_Audio::setSoundsVolume(int value)
{
    soundThreadWalking->setSoundVolume(value);
    soundThreadMovableSliding->setSoundVolume(value);
    soundThreadMovableMoving->setSoundVolume(value);
    soundThreadObject->setSoundVolume(value);
    soundThreadSunk->setSoundVolume(value);
    soundThread->setSoundVolume(value);
}

void Singleton_Audio::muteMusics(bool status)
{
    if(status)
    {
        musicPlaylistInGameThread->muteMusicPlaylist();
        musicPlaylistMenuThread->muteMusicPlaylist();
        musicThread->muteMusic();
    }
    else
    {
        musicPlaylistInGameThread->unmuteMusicPlaylist();
        musicPlaylistMenuThread->unmuteMusicPlaylist();
        musicThread->unmuteMusic();
    }
}

void Singleton_Audio::muteSounds(bool status)
{
    if(status)
    {
        soundThreadWalking->muteSound();
        soundThreadMovableSliding->muteSound();
        soundThreadMovableMoving->muteSound();
        soundThreadObject->muteSound();
        soundThreadSunk->muteSound();
        soundThread->muteSound();
    }
    else
    {
        soundThreadWalking->unmuteSound();
        soundThreadMovableSliding->unmuteSound();
        soundThreadMovableMoving->unmuteSound();
        soundThreadObject->unmuteSound();
        soundThreadSunk->unmuteSound();
        soundThread->unmuteSound();
    }
}

void Singleton_Audio::muteAll(bool status)
{
    muteMusics(status);
    muteSounds(status);
}

void Singleton_Audio::usableMusics(bool status)
{
    musicPlaylistInGameThread->setUsable(status);
    musicPlaylistMenuThread->setUsable(status);
    musicThread->setUsable(status);
}

void Singleton_Audio::usableSounds(bool status)
{
    soundThreadWalking->setUsable(status);
    soundThreadMovableSliding->setUsable(status);
    soundThreadMovableMoving->setUsable(status);
    soundThreadObject->setUsable(status);
    soundThreadSunk->setUsable(status);
    soundThread->setUsable(status);
}

void Singleton_Audio::usableAll(bool status)
{
    usableMusics(status);
    usableSounds(status);
}

void Singleton_Audio::playMusicPlaylistWithIntro()
{
    musicPlaylistInGameThread->playMusicPlaylist();
}

void Singleton_Audio::pauseMusicPlaylist()
{
    musicPlaylistInGameThread->pauseMusicPlaylist();
}

void Singleton_Audio::resumeMusicPlaylist()
{
    musicPlaylistInGameThread->playMusicPlaylist();
}

void Singleton_Audio::musicPlaylistRemoveIntro()
{
    musicPlaylistInGameThread->musicPlaylistRemoveIntro();
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
