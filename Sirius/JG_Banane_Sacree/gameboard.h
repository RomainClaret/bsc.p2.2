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

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>

#include "p_penguin.h"
#include "b_movable.h"
#include "m_pause.h"
#include "level.h"
#include "w_object.h"
#include "w_dialog.h"
#include "profil.h"
#include "w_life.h"

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
    B_Movable *slidingMovable;
    char sens; //l, r, t, b
};

/**
 * @brief Game Board. Where the game happens.
 * @details This is the QWidget which is giving life to the game.
 * Managing the level transition, the player, enemies, objects, blocs, dialogs, pause menu, and interactions.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo update
 */

class Gameboard : public QWidget
{
    Q_OBJECT
public:
    Gameboard(QWidget *parent = 0);
    ~Gameboard();

    static int getGameSquares();
    static int sizeX;
    static int sizeY;

    void setPlayerProfil(Profil* playerProfil);

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

    void fixeMovable(B_Movable *b);
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
    Pingouin *pingouin;

    //Fenêtre
    int windowSizeY;
    int windowSizeX;

    //Positionnement et gestion du niveau
    Level* currentLevel;
    QPoint* checkpoint;
    QPoint viewRequested;
    int viewPositionX;
    int viewPositionY;
    Profil* playerProfil;
    bool endable;

    //Widgets et Proxy
    M_Pause *menuPauseInGame;
    QGraphicsProxyWidget *proxy;
    bool toggleMenuPause;

    WidgetObject *objectList;
    QGraphicsProxyWidget *objectListProxy;

    WidgetLife *lifeList;
    QGraphicsProxyWidget *lifeListProxy;

    WidgetDialog *dialog;
    QGraphicsProxyWidget* dialogProxy;
    bool dialogToogle;

    //Glissement & Déplacements
    char cSensPingouinSlide;
    bool isSliding;
    B_Movable *moveBloc;
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

#endif // GAMEBOARD_H
