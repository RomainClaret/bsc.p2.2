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

#ifndef MENUSTART_H
#define MENUSTART_H

#include <QWidget>
#include "profil.h"

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

class MenuStart : public QWidget
{
    Q_OBJECT
public:
    explicit MenuStart(QWidget *parent = 0);

    QList<QPushButton*> *listButtonProfil;
    QPushButton* buttonNew;
    QVBoxLayout* layoutMenu;
    QLineEdit* username;
    QPushButton* validate;
    QLabel *textPseudo;

    static void saveGame(Profil* currentUser);
    bool getProfil();

signals:
    void startGame(Profil*);
    void refreshGameMenu();

public slots:
    void loadGame(QString value);
    void newGame();
    void newGameForm();

private :
    QSignalMapper* signalMapper;
    int totalForms;
    int maxTotalForms;
    Profil *user;


};

#endif // MENUSTART_H
