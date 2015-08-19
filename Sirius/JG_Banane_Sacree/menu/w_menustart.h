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

#ifndef W_MENUSTART_H
#define W_MENUSTART_H

#include <QWidget>
#include "../g_profil.h"

class QPushButton;
class QVBoxLayout;
class QSignalMapper;
class QLineEdit;
class QLabel;

/**
 * @brief Main menu, which appears at the game startup.
 * @details It allows the user to select or create a profil and run a game.
 * Games are saved in a json file type. Saves are found in:
 * MacOSX : "Game.app/Contents/MacOS/save.json",
 * Windows : Dans le meme dossier que Game.exe.
 * Save files are not encrypted.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo encrypt save files
 * @todo add credits
 */

class W_MenuStart : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Overlay widget to display the start menu.
     * @param parent if need
     */
    explicit W_MenuStart(QWidget *parent = 0);

    QList<QPushButton*> *listButtonProfil;
    QPushButton* buttonNew;
    QVBoxLayout* layoutMenu;
    QLineEdit* username;
    QPushButton* validate;
    QLabel *textPseudo;

    /**
     * @brief Save the current level to the given profil.
     * @param currentUser profil to save into
     */
    static void saveGame(G_Profil* currentUser);

    /**
     * @brief Load the profil.
     * @return true if it worked
     */
    bool getProfil();

signals:
    /**
     * @brief Start the game with with G_Profil
     */
    void startGame(G_Profil*);

    /**
     * @brief Reload the game menu on maingame.
     */
    void refreshGameMenu();

public slots:
    /**
     * @brief Load the given level.
     * @param value number of the level to load.
     */
    void loadGame(QString value);

    /**
     * @brief Create a new game, and its profil.
     */
    void newGame();

    /**
     * @brief Display of hide the interaction to create a new game.
     */
    void newGameForm();

private :
    QSignalMapper* signalMapper;
    int totalForms;
    int maxTotalForms;
    G_Profil *user;


};

#endif // W_MENUSTART_H
