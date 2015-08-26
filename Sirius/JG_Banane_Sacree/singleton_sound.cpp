#include "singleton_sound.h"

#include <QMediaPlayer>
#include <QDebug>

Singleton_Sound* Singleton_Sound::instance = NULL;

Singleton_Sound::Singleton_Sound()
{
    player = new QMediaPlayer;
    setSound("");
}

Singleton_Sound::~Singleton_Sound()
{
//    qDebug()<<"Destruction G_Sound";
}

Singleton_Sound* Singleton_Sound::getInstance()
{
    if(instance == NULL)
    {
        instance = new Singleton_Sound();
    }
    return instance;
}

void Singleton_Sound::setPlayable(bool playableStatus)
{
    this->playable = playableStatus;
}

void Singleton_Sound::setSound(QString sound)
{
    this->sound = "qrc:/sound/";

    if(sound.isEmpty())
    {
        sound = "dialog_interaction";
    }

    this->sound.append(sound);
    this->sound.append(".wav");

    player->setMedia(QUrl(this->sound));
}

void Singleton_Sound::playSound()
{
    player->play();
}

bool Singleton_Sound::getPlayble()
{
    return playable;
}
