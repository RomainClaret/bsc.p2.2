#ifndef G_SOUND_H
#define G_SOUND_H

#include <QString>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define MY_OS "UNIX"
#else
    #define MY_OS "OTHER"
#endif

class QMediaPlayer;
class QMediaPlaylist;

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
    void stopMusic();
    bool getPlaybleSound();
    void setMusicPlaylist(QString playlist);
    void playMusicPlaylist();
    void playMusicPlaylistWithIntro();
    void pauseMusicPlaylist();
    void resumeMusicPlaylist();


private:
//    Singleton_Audio& operator= (const Singleton_Audio&){}
    Singleton_Audio (const Singleton_Audio&){}
    static Singleton_Audio* instance;
    Singleton_Audio();
    virtual ~Singleton_Audio();

    QMediaPlayer* soundPlayer;
    QMediaPlayer* musicPlayer;
    QMediaPlaylist* musicPlaylist;
    bool playableSound;
    QString soundQUrl;
    QString musicQUrl;
    void musicPlaylistRemoveIntro();

};

#endif // G_SOUND_H
