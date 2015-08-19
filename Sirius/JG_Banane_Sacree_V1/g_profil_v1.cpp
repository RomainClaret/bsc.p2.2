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

#include "g_profil_v1.h"
#include <qDebug>
#include <QDateTime>

int G_Profil_v1::NBMAXVIE = 99;

G_Profil_v1::G_Profil_v1()
{
    this->username = "Nouveau";
    QDateTime current = QDateTime::currentDateTime();
    this->startDate = current.toString("dd:MM:yyyy:hh:mm");
    this->gameTime = "00:00:0000:00:00:00";
    this->saveDate = current.toString("dd:MM:yyyy:hh:mm");
    this->loadDate = current.toString("dd:MM:yyyy:hh:mm");
    this->level = 0;
    this->nbLive = 1;
    this->difficulty = 1;

    for(int i = 0; i < 8; i++)
    {
        power.append(0);
    }
}

G_Profil_v1::G_Profil_v1(const QString &username)
{
    this->username = username;
}

QString G_Profil_v1::getUsername()
{
    return this->username;
}

QString G_Profil_v1::getStartDate()
{
    return this->startDate;
}

QString G_Profil_v1::getSaveDate()
{
    return this->saveDate;
}

QString G_Profil_v1::getGameTime()
{
    return this->gameTime;
}

QString G_Profil_v1::getLoadDate()
{
    return this->loadDate;
}

int G_Profil_v1::getLevel()
{
    return this->level;
}

QList<int> G_Profil_v1::getPower()
{
    return this->power;
}

int G_Profil_v1::getNbLive()
{
    return this->nbLive;
}

int G_Profil_v1::getDifficulty()
{
    return this->difficulty;
}

void G_Profil_v1::setUsername(QString dataUsername)
{
    this->username = dataUsername;
}

void G_Profil_v1::setStartDate(QString dataStartDate)
{
    this->startDate = dataStartDate;
}

void G_Profil_v1::setSaveDate(QString dataSaveDate)
{
    this->saveDate = dataSaveDate;
}

void G_Profil_v1::setGameTime(QString dataGameTime)
{
    this->gameTime = dataGameTime;
}

void G_Profil_v1::setLevel(int dataLevel)
{
    this->level = dataLevel;
}

void G_Profil_v1::setPower(QList<int> dataPower)
{
    this->power = dataPower;
}

void G_Profil_v1::setNbLive(int dataNbLive)
{
    this->nbLive = dataNbLive;
}

void G_Profil_v1::setDifficulty(int dataDifficulty)
{
    this->difficulty = dataDifficulty;
}

void G_Profil_v1::read(const QJsonObject &json)
{
    this->username = json["username"].toString();
    this->startDate = json["startDate"].toString();
    this->gameTime = json["gameTime"].toString();
    this->saveDate = json["saveDate"].toString();
    this->level = json["level"].toInt();
    this->nbLive = json["nbLive"].toInt();
    this->difficulty = json["difficulty"].toInt();

    QString strpower = json["power"].toString();
    QStringList list = strpower.split("");
    power.clear();
    for(int i = 1; i < strpower.length(); i++)
    {
        int value = strpower.at(i).digitValue();
        this->power.append(value);
    }
}

void G_Profil_v1::print()
{
    qDebug() << "Username : " << this->username;
    qDebug() << "Start Date : " << this->startDate;
    qDebug() << "Game Time : " << this->gameTime;
    qDebug() << "Save Date : " << this->saveDate;
    qDebug() << "Load Date : " << this->loadDate;
    qDebug() << "Level : " << this->level;
    qDebug() << "Nb Live : " << this->nbLive;
    qDebug() << "Difficulté : " << this->difficulty;
    qDebug() << "Power : " << power;
}


void G_Profil_v1::write(QJsonObject &json) const
{
    json["username"] = username;
    json["startDate"] = startDate;
    json["gameTime"] = gameTime;
    json["saveDate"] = saveDate;
    json["level"] = level;
    json["nbLive"] = nbLive;
    json["difficulty"] = difficulty;

    QString strpower;
    for(int i = 0; i < power.length(); i++)
    {
        int value = power.at(i);
        strpower.append(QString::number(value));
    }
    json["power"] = strpower;
}
