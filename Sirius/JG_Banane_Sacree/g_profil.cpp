/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#include "g_profil.h"
#include <qDebug>
#include <QDateTime>
#include "./singleton_audio.h"

int G_Profil::NBMAXVIE = 99;

G_Profil::G_Profil()
{
    audioSingleton = Singleton_Audio::getInstance();

    this->username = "Nouveau";
    QDateTime current = QDateTime::currentDateTime();
    this->startDate = current.toString("dd:MM:yyyy:hh:mm");
    this->gameTime = "00:00:0000:00:00:00";
    this->saveDate = current.toString("dd:MM:yyyy:hh:mm");
    this->loadDate = current.toString("dd:MM:yyyy:hh:mm");
    this->level = 0;
    this->nbLive = 1;
    this->difficulty = 1;
    this->volumeMusics = 100;
    this->volumeSounds = 100;
    this->lastPlayed = 0;

    for(int i = 0; i < 8; i++)
    {
        power.append(0);
    }
}

G_Profil::G_Profil(const QString &username)
{
    audioSingleton = Singleton_Audio::getInstance();

    this->username = username;
}

QString G_Profil::getUsername()
{
    return this->username;
}

QString G_Profil::getStartDate()
{
    return this->startDate;
}

QString G_Profil::getSaveDate()
{
    return this->saveDate;
}

QString G_Profil::getGameTime()
{
    return this->gameTime;
}

QString G_Profil::getLoadDate()
{
    return this->loadDate;
}

int G_Profil::getLevel()
{
    return this->level;
}

QList<int> G_Profil::getPower()
{
    return this->power;
}

int G_Profil::getNbLive()
{
    return this->nbLive;
}

int G_Profil::getDifficulty()
{
    return this->difficulty;
}

void G_Profil::setUsername(QString dataUsername)
{
    this->username = dataUsername;
}

void G_Profil::setStartDate(QString dataStartDate)
{
    this->startDate = dataStartDate;
}

void G_Profil::setSaveDate(QString dataSaveDate)
{
    this->saveDate = dataSaveDate;
}

void G_Profil::setGameTime(QString dataGameTime)
{
    this->gameTime = dataGameTime;
}

void G_Profil::setLevel(int dataLevel)
{
    this->level = dataLevel;
}

void G_Profil::setPower(QList<int> dataPower)
{
    this->power = dataPower;
}

void G_Profil::setNbLive(int dataNbLive)
{
    this->nbLive = dataNbLive;
}

void G_Profil::setDifficulty(int dataDifficulty)
{
    this->difficulty = dataDifficulty;
}

void G_Profil::read(const QJsonObject &json)
{
    this->username = json["username"].toString();
    this->startDate = json["startDate"].toString();
    this->gameTime = json["gameTime"].toString();
    this->saveDate = json["saveDate"].toString();
    this->level = json["level"].toInt();
    this->nbLive = json["nbLive"].toInt();
    this->difficulty = json["difficulty"].toInt();
    this->volumeMusics = json["volumeMusics"].toInt();
    this->volumeSounds = json["volumeSounds"].toInt();
    this->lastPlayed = json["lastPlayed"].toInt();

    QString strpower = json["power"].toString();
    QStringList list = strpower.split("");
    power.clear();
    for(int i = 1; i < strpower.length(); i++)
    {
        int value = strpower.at(i).digitValue();
        this->power.append(value);
    }
}

void G_Profil::printDebug()
{
    qDebug() << "Username : " << this->username;
    qDebug() << "Start Date : " << this->startDate;
    qDebug() << "Game Time : " << this->gameTime;
    qDebug() << "Save Date : " << this->saveDate;
    qDebug() << "Load Date : " << this->loadDate;
    qDebug() << "Level : " << this->level;
    qDebug() << "Nb Live : " << this->nbLive;
    qDebug() << "Difficulté : " << this->difficulty;
    qDebug() << "Volume Musics : " << this->volumeMusics;
    qDebug() << "Volume Sounds : " << this->volumeSounds;
    qDebug() << "Was I Played last : " << this->lastPlayed;
    qDebug() << "Power : " << power;
}

void G_Profil::setMusicsVolume(int value)
{
    this->volumeMusics = value;
}

void G_Profil::setSoundsVolume(int value)
{
    this->volumeSounds = value;
}

int G_Profil::getMusicsVolume()
{
    //return audioSingleton->getMusicsVolume();
    return volumeMusics;
}

int G_Profil::getSoundsVolume()
{
    //return audioSingleton->getSoundsVolume();
    return volumeSounds;
}

void G_Profil::setLastPlayed(int value)
{
    this->lastPlayed = value;
}

int G_Profil::getLastPlayed()
{
    return this->lastPlayed;
}

int G_Profil::getActualMusicsVolume()
{
    return audioSingleton->getMusicsVolume();
}

int G_Profil::getActualSoundsVolume()
{
    return audioSingleton->getSoundsVolume();
}


void G_Profil::write(QJsonObject &json)
{
    json["username"] = username;
    json["startDate"] = startDate;
    json["gameTime"] = gameTime;
    json["saveDate"] = saveDate;
    json["level"] = level;
    json["nbLive"] = nbLive;
    json["difficulty"] = difficulty;
    json["volumeMusics"] = this->getActualMusicsVolume();
    json["volumeSounds"] = this->getActualSoundsVolume();
    json["lastPlayed"] = lastPlayed;

    QString strpower;
    for(int i = 0; i < power.length(); i++)
    {
        int value = power.at(i);
        strpower.append(QString::number(value));
    }
    json["power"] = strpower;
}
