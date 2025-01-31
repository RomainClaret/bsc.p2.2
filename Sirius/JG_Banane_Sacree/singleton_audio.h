#ifndef G_SOUND_H
#define G_SOUND_H

#include <QString>

class QMediaPlayer;
class QMediaPlaylist;
class A_Sound;
class A_Music;
class A_MusicPlaylist;

class Singleton_Audio
{
public:
    static Singleton_Audio* getInstance();

    void setPlayableSounds(bool playableStatus);
    void setSound(QString soundQUrl);
    void setMusic(QString music);
    void playMusic();
    void playMusic(QString music);
    void pauseMusic();
    void stopMusic();
    bool getPlaybleSound();
    void playMusicPlaylist();
    void playMusicPlaylistWithIntro();
    void pauseMusicPlaylist();
    void resumeMusicPlaylist();
    void setPlayableMusicPlaylist(bool playable);
    bool getPlaybleMusicPlaylist();
    void playSoundPlayerWalking();
    void playSoundBlockSliding();
    void playSoundBlockStopSliding();
    void playSoundPlayerSliding();
    void playSoundGetObject();
    void playSoundSunk();
    void playSoundEventRestartCheckpoint();
    void playSoundEventLostLevel();
    void playSoundEventStartGame();
    void playMusicPlaylist(int value);
    void playSoundPlayerSlidingMovable();

    void muteMusics(bool status);
    void muteSounds(bool status);
    void muteAll(bool status);

    void usableMusics(bool status);
    void usableSounds(bool status);
    void usableAll(bool status);
    void playSoundPlayerSlidingStop();

    int getMusicsVolume();
    int getSoundsVolume();

    void setMusicsVolume(int value);
    void setMusicPlaylistVolume(int value);
    void setSoundsVolume(int value);

    void playMusicPlaylistMenu();
    void playMusicPlaylistMenu(int value);
    void pauseMusicPlaylistMenu();
    void stopMusicPlaylist();

    bool getUsableMusicsPlaylistMenu();
    void setUsableMusicPlaylistMenu(int value);
    void playSoundInteraction();
    void playSoundEventWaterFall();

    void playMusicCheatCode();
    void stopMusicCheatCode();
    void playSoundValideCheatCode();
    void playSoundUnvalideCheatCode();

    void pauseMusicPlaylists();
private:

    Singleton_Audio (const Singleton_Audio&){}
    static Singleton_Audio* instance;
    Singleton_Audio();
    virtual ~Singleton_Audio();

    A_Sound *soundThreadStartGame;
    A_Sound *soundThreadLoseLife;
    A_Sound *soundThreadRestart;
    A_Sound *soundThreadWaterFall;
    A_Sound *soundThreadInteraction;
    A_Sound *soundThreadWalking;
    A_Sound *soundThreadSliding;
    A_Sound *soundThreadMovableSliding;
    A_Sound *soundThreadMovableMoving;
    A_Sound *soundThreadObject;
    A_Sound *soundThreadSunk;
    A_Sound *soundThreadSlidingMovable;
    A_Sound *soundThreadSlidingStop;
    A_Sound *soundThreadMovableStopSliding;
    A_Sound *soundThreadCheatCodeValide;
    A_Sound *soundThreadCheatCodeUnvalide;

    A_Music *musicThread;
    A_MusicPlaylist *musicPlaylistInGameThread;
    A_MusicPlaylist *musicPlaylistMenuThread;
    A_MusicPlaylist *musicPlaylistCheatCode;
    bool playableSound;
    bool playableMusic;
    bool playableMusicPlaylist;

    bool muteMusicsToggle;
    bool muteSoundsToggle;
    bool muteAllToggle;

    void musicPlaylistRemoveIntro();

};

#endif // G_SOUND_H
