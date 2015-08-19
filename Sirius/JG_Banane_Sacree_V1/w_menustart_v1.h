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

#ifndef MENUSTART_V1_H
#define MENUSTART_V1_H

#include <QWidget>
#include "g_profil_v1.h"

class QPushButton;
class QVBoxLayout;
class QSignalMapper;
class QLineEdit;
class QLabel;

/**
 * \brief Premier menu (start) que le joueur voie en lancant le jeu.
 *
 * QWidget du menu principal du jeu. Celui-ci permet de
 * créer un profile d'utilisateur et de lancer un partie
 * déjà existante dans un profile existant.
 * Les sauvegardes sont sauvées dans le repertoire :
 * MacOSX : Game.app/Contents/MacOS/save.json
 * Windows : Dans le meme dossier que Game.exe
 * A noter que la sauvegarde est en texte et n'est pas encrypté.
 */

class W_MenuStart_v1 : public QWidget
{
    Q_OBJECT
public:
    explicit W_MenuStart_v1(QWidget *parent = 0);

    QList<QPushButton*> *listButtonProfil;
    QPushButton* buttonNew;
    QVBoxLayout* layoutMenu;
    QLineEdit* username;
    QPushButton* validate;
    QLabel *textPseudo;

    static void saveGame(G_Profil_v1* currentUser);
    bool getProfil();

signals:
    void startGame(G_Profil_v1*);
    void refreshGameMenu();

public slots:
    void loadGame(QString value);
    void newGame();
    void newGameForm();

private :
    QSignalMapper* signalMapper;
    int totalForms;
    int maxTotalForms;
    G_Profil_v1 *user;


};

#endif // MENUSTART_V1_H
