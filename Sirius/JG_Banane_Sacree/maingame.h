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

#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include "gameboard.h"
#include "m_menustart.h"
#include "profil.h"

class QGraphicsView;
class QLabel;


/**
 * @mainpage  James Gouin et la Banane Sacrée
 *
 * FRANCAIS:
 * Jeu d’infiltration en 2D sans combats sous forme de puzzle game.
 * Le joueur manipule un pingouin agent-secret envoyé sur un iceberg pour récupérer la « banane sacrée » volée par un singe.
 * Son personnage peut marcher et glisser dans les quatre directions.
 * Il fera face à un niveau de tutoriel, 6 niveaux normaux et un niveau final.
 * Il a pour objectif de récupérer des blocs de glace auprès du boss normal de chaque niveau afin de se créer un passage jusqu’à l’iceberg central abritant l’igloo du singe.
 * Pour cela, le joueur devra résoudre des problèmes logiques en se frayant un chemin tout en évitant d’entrer dans le champs de vision des ennemis.
 *
 * ENGLISH:
 * 2D infiltration puzzle game without fights.
 * The player plays at penguin character, which is a special agent sent on an iceberg to retrive the "holy banana" which was stolen by a monkey.
 * The penguin can walk and slide in four directions.
 * He will have to beat 8 levels including the tutorial and the final.
 * He has as objective to retrive special ice blocks on mini bosses at the end of each level.
 * Those blocks unlock a road to the last level in the middle of the iceberg, where the final boss is waiting.
 * To win those blocks the player will have to solve logical problems and find his way out of the level while avoiding enemies' field of view.
 *            <p/> <br/>
 */


/**
 * @brief Managing the backend of the game.
 * @details It shows the main menu, MenuStart.
 * It does the transition between the MenuStart and the Gameboard.
 * Gives the graphical structure for the video game and the OS on which it's run.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo Manage the close event correctly, because it's painful when just in the MenuStart.
 */

class MainGame : public QWidget
{
    Q_OBJECT
public:
    explicit MainGame(QWidget *parent = 0);
    ~MainGame();

private:

    QPushButton* quitGame;  /**< \var Boutton pour quitter le jeu completement */

    Gameboard *theGame;

    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    int windowSizeY;
    int windowSizeX;
    int viewPositionX;
    int viewPositionY;
    static int gameSquares;
    QString windowTitle;

    Level* currentLevel;

    int menuSizeX;
    int menuSizeY;

    int quitBtnSizeX;
    int quitBtnSizeY;

    int titleSizeX;
    int titleSizeY;

    MenuStart *menuStart;

    QGraphicsProxyWidget *menuStartProxy;

    QLabel *gameTitle;

    void resizeEvent ( QResizeEvent * event );

    bool toggleGameCreated;
    bool toggleFirstStart;

    void closeEvent (QCloseEvent *event);

signals:

public slots:
    void startGame(Profil *user);
    void refreshGameMenu();

};

#endif // MAINGAME_H
