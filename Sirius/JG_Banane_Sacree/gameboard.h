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
#include "level2.h"
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

/**
 * @brief Structure used in Gameboard.
 * @details Used for blocks when they slides into a direction ("l":left, "r":right, "t":top, "b":bottom).
 * @todo integrate with DP Factory
 */
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
 * @todo create a translation file
 */
class Gameboard : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Constructor of the Gameboard.
     * @param parent QWidget to depend on
     */
    Gameboard(QWidget *parent = 0);

    //Destructor
    /**
      * @brief Remove all items on it.
      */
    ~Gameboard();

    static int getGameSquares();
    static int sizeX;
    static int sizeY;

    /**
     * @brief Load info from the profil into the Gameboard
     * @param playerProfil Profil of the player
     */
    void setPlayerProfil(Profil* playerProfil);

private:

    /*
     * PRIVATE METHODS
    */

    /**
     * @brief Listen to keyboard events
     * @param event event from the keyboard
     */
    void keyPressEvent(QKeyEvent *event);

    //Methods related to construction
    /**
     * @brief Place the Pause Menu, Dialog, Life, and Object QWidgets on the Gameboard.
     */
    void setProxy();

    /**
     * @brief Load the level information and populate the scene
     */
    void loadLevel();

    /**
     * @brief Select the level
     * @param value level value
     */
    void setLevel(int value);

    /**
     * @brief Set the time already spent in-game
     */
    void setTimer();

    /**
     * @brief Stop the time recording
     */
    void disconnectTimer();

    //Methods related to positioning and level management
    /**
     * @brief Set the view of the player on the scene.
     */
    void setViewPosition();

    /**
     * @brief Check is the playable character can move on a given QGraphicsItem.
     * @param object QGraphicsItem to check
     * @return true if the playable character can move on it.
     */
    bool checkPosition(QGraphicsItem *object);

    /**
     * @brief Remember if the checkpoint is passed.
     */
    void saveCheckpoint();

    /**
     * @brief Get last checkpoint.
     */
    void loadCheckpoint();

    /**
     * @brief Display a dialog when the level is loaded
     * @todo Redo the first dialog, shoing OK at the moment
     */
    void setFirstDialog();

    //Methods related to proxy management (overlay of widgets)
    /**
     * @brief Position the widget at the bottom right of the Gameboard
     * @param widget widget to position at the bottom right
     * @todo refactor the method to setPositionBottomRight
     */
    void setPositionBottom(QWidget* widget);

    /**
     * @brief Position the widget in the middle of the Gameboard
     * @param widget widget to position in the middle
     */
    void setPositionCenter(QWidget* widget);

    /**
     * @brief Position the widget at the top left of the Gameboard
     * @param widget widget to position at the top left
     * @todo refactor the method to setPositionTopLeft
     */
    void setPositionTop(QWidget* widget);

    //Methods related to the playable character displacement
    /**
     * @brief Move the playable character to the left.
     * @return true if the playable character can move in the left
     */
    bool MovePingouinToLeft();

    /**
     * @brief Move the playable character to the right.
     * @return true if the playable character can move in the right
     */
    bool MovePingouinToRight();

    /**
     * @brief Move the playable character to the top.
     * @return true if the playable character can move in the top
     */
    bool MovePingouinToTop();

    /**
     * @brief Move the playable character to the bottom.
     * @return true if the playable character can move in the bottom
     */
    bool MovePingouinToBottom();

    /**
     * @brief Moves the playable character into the given direction.
     * @param CollidingItems QList of boxes in cross around the playable character
     * @param sensDepl direction to move (l,r,t,b)
     * @return true if the playable character moved
     */
    bool MovePingouin(QList<QGraphicsItem *> CollidingItems, char sensDepl);

    //Methods related to the playable character sliding
    /**
     * @brief Move self to given direction
     * @param sens direction to move to
     */
    void MoveBloc(char sens);

    /**
     * @brief Validate the place of a movable block.
     * @param b block to validate
     */
    void fixeMovable(B_Movable *b);

    /**
     * @brief Check if the conditions required to change view is validated.
     * @param sens direction to move to
     */
    void checkChangeView(char sens);

    /**
     * @brief Change the view of the player
     * @param sens direction to move to
     */
    void ChangeView(char sens);

    /**
     * @brief Check event of self position.
     */
    void checkPositionEvents();

    /**
     * @brief Enable the pause menu.
     */
    void pauseMenu();

    /**
     * @brief Delete all items from self.
     */
    void removeAllItems();

    /*
     * ATTRIBUTES
    */

    //Scene & Playable Character
    QGraphicsScene *mainScene;
    QGraphicsView *playerView;
    Pingouin *pingouin;

    //Window
    int windowSizeY;
    int windowSizeX;

    //Positioning and level management
    Level2* currentLevel;
    QPoint* checkpoint;
    QPoint viewRequested;
    int viewPositionX;
    int viewPositionY;
    Profil* playerProfil;
    bool endable;

    //Widgets & Proxies
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

    //Sliding & Displacement
    char cSensPingouinSlide;
    bool isSliding;
    B_Movable *moveBloc;
    QList<slideBloc> listSlindingBlocs;
    QTimer *timer;
    QTimer *timerPingouinSlide;
    QTimer *timerBlocDeplSlide;

    //Static
    static int gameSquares;

    //Pause Menu
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
    /**
     * @brief SLOT: Resume the Game after pause
     */
    void resumeGame();

    /**
     * @brief SLOT: Slide the playable character.
     */
    void SlidePingouin();

    /**
     * @brief SLOT: Slide blocks in the List of sliding blocks.
     */
    void SlideBloc();

    /**
     * @brief SLOT: Ask for profil save, and destruct self.
     */
    void exitGame();

    /**
     * @brief SLOT: Restart the level at the last checkpoint->
     */
    void restartEnigma();

    /**
     * @brief SLOT: Restart the level at the beginning
     */
    void restartLevel();

    /**
     * @brief SLOT: Load the Island Level.
     */
    void returnIsland();
};

#endif // GAMEBOARD_H
