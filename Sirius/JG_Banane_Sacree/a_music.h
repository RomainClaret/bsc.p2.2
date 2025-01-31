#ifndef A_MUSIC_H
#define A_MUSIC_H

class QMediaPlayer;

#include <QThread>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define MY_OS 0
#else
    #define MY_OS 1
#endif

class A_Music : public QThread
{
public:
    A_Music();

    void playMusic();

    void stopMusic();
    void setMusic(QString music);
    void pauseMusic();
    void muteMusic();
    void unmuteMusic();
    void setUsable(bool usable);
    void setMusicVolume(int value);
    int getMusicVolume();

private:
   void run();

   QMediaPlayer* musicPlayer;
   QString musicQUrl;

   bool usableMusic;

signals:

public slots:
};

#endif // A_MUSIC_H
