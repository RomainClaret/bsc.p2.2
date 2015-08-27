#ifndef A_MUSIC_H
#define A_MUSIC_H

class QMediaPlayer;

#include <QThread>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define MY_OS "UNIX"
#else
    #define MY_OS "OTHER"
#endif

class A_Music : public QThread
{
public:
    A_Music();

    void playMusic();

    void stopMusic();
    void setMusic(QString music);
    void pauseMusic();

private:
   void run();

   QMediaPlayer* musicPlayer;
   QString musicQUrl;

signals:

public slots:
};

#endif // A_MUSIC_H
