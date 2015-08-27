#ifndef A_SOUND_H
#define A_SOUND_H

class QMediaPlayer;

#include <QThread>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #define MY_OS "UNIX"
#else
    #define MY_OS "OTHER"
#endif

class A_Sound : public QThread
{
public:
    A_Sound();

    void playSound();
    void playSound(QString sound);
    void setSound(QString sound);
    void stopSound();

private:
    void run();

    QMediaPlayer* soundPlayer;
    QString soundQUrl;

signals:

public slots:
};

#endif // A_SOUND_H
