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
    void playSound();
    void playSound(QString soundQUrl);
    void playMusic();
    void playMusic(QString music);
    void pauseMusic();
    void stopMusic();
    bool getPlaybleSound();
    void setMusicPlaylist(QString playlist);
    void playMusicPlaylist();
    void playMusicPlaylistWithIntro();
    void pauseMusicPlaylist();
    void resumeMusicPlaylist();
    void stopSound();
    void playMusicPlaylist(QString playlist);
    void setPlayableMusicPlaylist(bool playable);
    bool getPlaybleMusicPlaylist();
    void playSoundPlayerWalking();
    void playSoundBlockSliding();
    void playSoundBlockStopSliding();
    void playSoundPlayerSliding();

    void playMusicPlaylist(int value);
private:
//    Singleton_Audio& operator= (const Singleton_Audio&){}
    Singleton_Audio (const Singleton_Audio&){}
    static Singleton_Audio* instance;
    Singleton_Audio();
    virtual ~Singleton_Audio();

    A_Sound *soundThread;
    A_Sound *soundThreadWalking;
    A_Sound *soundThreadMovableSliding;
    A_Sound *soundThreadMovableMoving;
    A_Music *musicThread;
    A_MusicPlaylist *musicPlaylistThread;
    bool playableSound;
    bool playableMusic;
    bool playableMusicPlaylist;

    void musicPlaylistRemoveIntro();

};

#endif // G_SOUND_H
