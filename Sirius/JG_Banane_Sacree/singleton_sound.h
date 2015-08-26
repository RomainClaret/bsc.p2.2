#ifndef G_SOUND_H
#define G_SOUND_H

#include <QString>

class QMediaPlayer;

class Singleton_Sound
{
public:
    static Singleton_Sound* getInstance();

    void setPlayable(bool playableStatus);
    void setSound(QString sound);
    void playSound();
    bool getPlayble();


private:
    Singleton_Sound& operator= (const Singleton_Sound&){}
    Singleton_Sound (const Singleton_Sound&){}
    static Singleton_Sound* instance;
    Singleton_Sound();
    ~Singleton_Sound();

    QMediaPlayer* player;
    bool playable;
    QString sound;

};

#endif // G_SOUND_H
