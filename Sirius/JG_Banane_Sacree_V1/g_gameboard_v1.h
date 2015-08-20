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

#ifndef GAMEBOARD_V1_H
#define GAMEBOARD_V1_H

#include <QWidget>

#include "p_penguin_v1.h"
#include "b_movable_v1.h"
#include "w_menupause_v1.h"
#include "g_level_v1.h"
#include "w_object_v1.h"
#include "w_dialog_v1.h"
#include "g_profil_v1.h"
#include "w_life_v1.h"

class QGraphicsProxyWidget;
class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QPixmap;
class QKeyEvent;
class QFormLayout;
class QGroupBox;
class QMessageBox;
class QLabel;
class QPushButton;
class QPoint;
class QTimer;

struct slideBloc{
    B_Movable_v1 *slidingMovable;
    char sens; //l, r, t, b
};

/**
 * \brief La platefrome du jeu.
 *
 * C'est LE QWidget qui donne vie au jeu ! Il gère les
 * transistion de niveaux, le joueur, les ennemis, les
 * objets, les blocs, les dialogues, le menu pause, et
 * les interactions.
 */

class G_Gameboard_v1 : public QWidget
{
    Q_OBJECT
public:
    G_Gameboard_v1(QWidget *parent = 0);
    ~G_Gameboard_v1();

    static int getGameSquares();
    static int sizeX;
    static int sizeY;

    void setPlayerProfil(G_Profil_v1* playerProfil);

private:

    /*
     * METHODES PRIVÉES
    */

    void keyPressEvent(QKeyEvent *event);

    //Méthodes de construction
    void setProxy();
    void loadLevel();
    void setLevel(int value);
    void setTimer();
    void disconnectTimer();

    //Positionnement et gestion du niveau
    void setViewPosition();
    bool checkPosition(QGraphicsItem *object);
    void saveCheckpoint();
    void loadCheckpoint();
    void setFirstDialog();

    //Gestion des proxy / widgets
    void setPositionBottom(QWidget* widget);
    void setPositionCenter(QWidget* widget);
    void setPositionTop(QWidget* widget);

    //Déplacement du Pingouin
    bool MovePingouinToLeft();
    bool MovePingouinToRight();
    bool MovePingouinToTop();
    bool MovePingouinToBottom();
    bool MovePingouin(QList<QGraphicsItem *>, char);

    //Glissement du Pingouin
    QTimer *timerPingouinSlide;
    QTimer *timerBlocDeplSlide;

    void MoveBloc(char);

    void fixeMovable(B_Movable_v1 *b);
    void checkChangeView(char);
    void ChangeView(char sens);
    bool checkGameOver();
    void checkPositionEvents();
    void pauseMenu();

    void removeAllItems();

    /*
     * ATTRIBUTS
    */

    //Scene & Pingouin
    QGraphicsScene *mainScene;
    QGraphicsView *playerView;
    P_Penguin_v1 *pingouin;

    //Fenêtre
    int windowSizeY;
    int windowSizeX;

    //Positionnement et gestion du niveau
    G_Level_v1* currentLevel;
    QPoint* checkpoint;
    QPoint viewRequested;
    int viewPositionX;
    int viewPositionY;
    G_Profil_v1* playerProfil;
    bool endable;

    //Widgets et Proxy
    W_MenuPause_v1 *menuPauseInGame;
    QGraphicsProxyWidget *proxy;
    bool toggleMenuPause;

    W_Object_v1 *objectList;
    QGraphicsProxyWidget *objectListProxy;

    W_Life_v1 *lifeList;
    QGraphicsProxyWidget *lifeListProxy;

    W_Dialog_v1 *dialog;
    QGraphicsProxyWidget* dialogProxy;
    bool dialogToogle;

    //Glissement & Déplacements
    char cSensPingouinSlide;
    bool isSliding;
    B_Movable_v1 *moveBloc;
    QList<slideBloc> listSlindingBlocs;
    QTimer *timer;

    //Static
    static int gameSquares;

    //Menu Pause
    QString windowTitle;
    QFormLayout *layoutMenuPause;
    QGroupBox *groupBoxMenuPause;
    QLabel *titleMenuPause;
    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseConfigure;
    QPushButton *btnMenuPauseQuit;

protected:

signals:

public slots:
    void resumeGame();
    void SlidePingouin();
    void SlideBloc();

    void exitGame();
    void restartEnigma();
    void restartLevel();
    void returnIsland();
};

#endif // GAMEBOARD_V1_H
