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

#ifndef W_MENUPAUSE_H
#define W_MENUPAUSE_H

#include <QWidget>
#include "../g_gameboard.h"

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;
class W_Menu;
class G_Gameboard;

/**
 * @brief Pause Menu, which appears when the game is paused.
 * @details It allows the user to:
 * Resume the game,
 * Go the main island to select another level,
 * Quit the game,
 * Restart the enigma,
 * Restart the level,
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 2.0
 * @date 19 August 2015
 */
class W_MenuPause : public QWidget
{
    Q_OBJECT
public:
    
    //Constructor
    /**
     * @brief Overlay widget to display the pause menu.
     * @param parent if need
     */
    W_MenuPause(QWidget *parent, G_Gameboard *gameboard);

    /**
     * @brief Lock and unable the pause menu.
     * @param levelValue number of the level
     */
    void setUnableMenu(int levelValue);
    void setTitleParent();

private:
    G_Gameboard *gameboard;

    //Layout
    QFormLayout *layoutMenuPause;

    //Labels
    QLabel *titleMenuPause;
    QLabel *undertitleMenuPause;

    //Buttons
    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseIsland;
    QPushButton *btnMenuPauseQuit;
    QPushButton *btnMenuPauseRestartEnigma;
    QPushButton *btnMenuPauseRestartLevel;
    QPushButton *btnMenuPauseBonus;

    W_Menu* parent;

signals:

public slots:

};

#endif // W_MENUPAUSE_H
