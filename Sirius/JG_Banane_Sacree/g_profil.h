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

#ifndef G_PROFIL_H
#define G_PROFIL_H

#include <QString>
#include <QJsonObject>
#include <QList>

class Singleton_Audio;

/**
 * @brief Player's profil management.
 * @details Read and write a json file for the profils, which are the saves for the game.
 * It saves player's information and its game advancement and stats.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */

class G_Profil
{
public:
    //Constructors
    /**
     * @brief Default constructor
     */
    G_Profil();

    /**
     * @brief Constructor with username
     * @param username Name of the player
     */
    G_Profil(const QString &username);

    /**
     * @brief Get the username from self.
     * @return username
     */
    QString getUsername();

    /**
     * @brief Get the start date from self.
     * @return start date
     */
    QString getStartDate();

    /**
     * @brief Get the save date from self.
     * @return save date
     */
    QString getSaveDate();

    /**
     * @brief Get the game time from self.
     * @return game time
     */
    QString getGameTime();

    /**
     * @brief Get the load date from self.
     * @return load date
     */
    QString getLoadDate();

    /**
     * @brief Get the level from self.
     * @return level
     */
    int getLevel();

    /**
     * @brief Get the powers from self.
     * @return list of powers
     */
    QList<int> getPower();

    /**
     * @brief Get the number of lives from self.
     * @return lives
     */
    int getNbLive();

    /**
     * @brief Get the difficulty from self.
     * @return difficulty
     */
    int getDifficulty();

    /**
     * @brief Set the username to self.
     */
    void setUsername(QString);

    /**
     * @brief Set the start date to self.
     */
    void setStartDate(QString);

    /**
     * @brief Set the save date to self.
     */
    void setSaveDate(QString);

    /**
     * @brief Set the game time to self.
     */
    void setGameTime(QString);

    /**
     * @brief Set the level to self.
     */
    void setLevel(int);

    /**
     * @brief Set the powers to self.
     */
    void setPower(QList<int>);

    /**
     * @brief Set the lives to self.
     */
    void setNbLive(int);

    /**
     * @brief Set the difficulty to self.
     */
    void setDifficulty(int);

    /**
     * @brief Read a JSON file.
     * @param json file
     */
    void read(const QJsonObject &json);

    /**
     * @brief Write in a JSON file.
     * @param json file
     */
    void write(QJsonObject &json) const;

    /**
     * @brief Print informations in the debug
     */
    void printDebug();

    void setMusicsVolume(int value);
    void setSoundsVolume(int value);
    int getMusicsVolume();
    int getSoundsVolume();

    static int NBMAXVIE;

private :
    QString username;
    QString startDate;
    QString saveDate;
    QString gameTime;
    QString loadDate;
    int level;
    QList<int> power;
    int nbLive;
    int difficulty;
    int volumeMusics;
    int volumeSounds;
    Singleton_Audio *audioSingleton;
};

#endif // G_PROFIL_H
