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

#ifndef G_GAMEBOARD_H
#define G_GAMEBOARD_H

#include <QWidget>

#include "character/p_penguin.h"
#include "surface/b_movable.h"
#include "menu/w_menupause.h"
#include "g_level.h"
#include "widget/w_object.h"
#include "widget/dialog/w_dialog.h"
#include "g_profil.h"
#include "widget/w_life.h"

#include "observer_enemy.h"
#include "surface/b_movable_simple.h"

#include <QGLWidget>

class W_Menu;
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
class Singleton_Audio;


/**
 * @brief Structure used in Gameboard.
 * @details Used for blocks when they slides into a direction ("l":left, "r":right, "t":top, "b":bottom).
 * @todo integrate with DP Factory
 */
struct SlidingBlock{
    B_MovableSimple* slidingMovable;
    char direction; //l, r, t, b
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
class G_Gameboard : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Constructor of the Gameboard.
     * @param parent QWidget to depend on
     */
    G_Gameboard(QWidget *parent = 0);

    //Destructor
    /**
      * @brief Remove all items on it.
      */
    ~G_Gameboard();

    static int getGameSquares();

    /**
     * @brief getSizeX
     * @return the size X of the scene (the map)
     */
    static int getSizeX();
    /**
     * @brief getSizeY
     * @return the size Y of the scene (the map)
     */
    static int getSizeY();

    static int sizeX;
    static int sizeY;

    /**
     * @brief Load info from the profil into the Gameboard
     * @param playerProfil Profil of the player
     */
    void setPlayerProfil(G_Profil* playerProfil);

    void endMoveCheck(char sens);

    QGraphicsScene* getGraphicsScene();

    /**
     * @brief Show the dialog "popup" with the text in param
     * @param text Will be written in the popup
     * @param image Will be shown under the popup
     */
    void showDialog(QString text, QString image);

    /**
     * @brief Move self to given direction
     * @param direction direction to move to
     */
    void moveBlock(char direction);

    /**
     * @brief isMovableSet determinate if the penguin is in contact with a movable
     * @return true if the attribut "movable" is not NULL
     */
    bool isMovableSet();

    /**
     * @brief getMovable get the attribut "movable"
     * @return
     */
    B_MovableSimple* getMovable();

    void setIsSliding(bool isSliding);

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

    //Methods related to proxy management (overlay of widgets)
    /**
     * @brief Position the widget at the bottom right of the Gameboard
     * @param widget widget to position at the bottom right
     */
    void setWidgetPositionBottomRight(QWidget* widget);

    /**
     * @brief Position the widget in the middle of the Gameboard
     * @param widget widget to position in the middle
     */
    void setWidgetPositionCenter(QWidget* widget);

    /**
     * @brief Position the widget at the top left of the Gameboard
     * @param widget widget to position at the top left
     */
    void setWidgetPositionTopLeft(QWidget* widget);

    //Methods related to the playable character displacement
    /**
     * @brief Move the playable character to the left.
     * @return true if the playable character can move in the left
     */
    bool movePlayableCharacterPingouinToLeft();

    /**
     * @brief Move the playable character to the right.
     * @return true if the playable character can move in the right
     */
    bool movePlayableCharacterPingouinToRight();

    /**
     * @brief Move the playable character to the top.
     * @return true if the playable character can move in the top
     */
    bool movePlayableCharacterPingouinToTop();

    /**
     * @brief Move the playable character to the bottom.
     * @return true if the playable character can move in the bottom
     */
    bool movePlayableCharacterToBottom();

    /**
     * @brief Moves the playable character into the given direction.
     * @param CollidingItems QList of boxes in cross around the playable character
     * @param directionDepl direction to move (l,r,t,b)
     * @return true if the playable character moved
     */
    bool movePlayableCharacter(QList<QGraphicsItem *> CollidingItems, char directionDepl);

    //Methods related to the playable character sliding

    /**
     * @brief Validate the place of a movable block.
     * @param b block to validate
     */
    void fixMovable(B_MovableSimple *b);

    /**
     * @brief Check if the conditions required to change view is validated.
     * @param direction direction to move to
     */
    void checkChangeView(char direction);

    /**
     * @brief Change the view of the player
     * @param direction direction to move to
     */
    void changeView(char direction);

    /**
     * @brief Check event of self position.
     */
    void checkPositionEvents(char);

    /**
     * @brief Delete all items from self.
     */
    void removeAllItems();


    /**
     * @brief Show the dialog "popup" with the text and sound in param
     * @param text Will be written in the popup
     * @param sound name of the sound to play
     */
    void showDialog(QString text, QString image, QString sound);


    /*
     * ATTRIBUTES
    */

    //Sound Singelton
    Singleton_Audio *audioSingleton;
    int soundStepCounter;

    //Scene & Playable Character
    QGraphicsScene *mainScene;
    QGraphicsView *playerView;
    P_Penguin *playableCharacter;

    //Window
    int windowSizeY;
    int windowSizeX;

    //Positioning and level management
    G_Level* currentLevel;
    Observer_Enemy* observerEnemy;
    QPoint* checkpoint;
    QPoint viewRequested;
    int viewPositionX;
    int viewPositionY;
    G_Profil* playerProfil;
    bool endable;

    //Widgets & Proxies
    W_Menu *menuPauseInGame;
    QGraphicsProxyWidget *proxy;
    bool toggleMenuPause;

    W_Object *objectList;
    QGraphicsProxyWidget *objectListProxy;

    W_Life *lifeList;
    QGraphicsProxyWidget *lifeListProxy;

    W_Dialog *dialog;
    QGraphicsProxyWidget* dialogProxy;
    bool dialogToogle;

    //Sliding & Displacement
    char directionPlayableCharacter;
    bool isSliding;
    B_MovableSimple *movable;
    QList<SlidingBlock> listSlindingBlocks;
    QTimer *timer;
    QTimer *timerPlayableCharacterSlide;
    QTimer *timerBlockDisplacementSlide;

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

    void refreshMenu();

public slots:
    /**
     * @brief SLOT: Resume the Game after pause
     */
    void resumeGame();

    /**
     * @brief SLOT: Slide the playable character.
     */
    void slidePlayableCharacter();

    /**
     * @brief SLOT: Slide blocks in the List of sliding blocks.
     */
    void slideBlock();

    /**
     * @brief SLOT: Ask for profil save, and destruct self.
     */
    void exitGame();

    /**
     * @brief SLOT: Restart the level at the last checkpoint->
     */
    void restartEnigma();

    /**
     * @brief Restart the level at the last checkpoint with a custom text and sound if life left
     * @param text to display
     * @param sound to play
     */
    void restartEnigma(QString text, QString sound);

    /**
     * @brief SLOT: Restart the level at the beginning
     */
    void restartLevel();

    /**
     * @brief SLOT: Load the Island Level.
     */
    void returnIsland();

    /**
     * @brief SLOT: Change the usual menu into the "Bonus" menu
     */
    void loadBonus();

    /**
     * @brief SLOT: Enable the pause menu.
     */
    void pauseMenu();

    /**
     * @brief SLOT: Called when the user want to delete his party
     */
    void deleteGame();
};

#endif // G_GAMEBOARD_H
