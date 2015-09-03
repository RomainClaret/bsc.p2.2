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

#ifndef W_MENUBONUS_H
#define W_MENUBONUS_H

#include <QWidget>

#include "../g_gameboard.h"

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;
class W_Menu;

/**
 * @brief Bonus Menu, which appears when the bonus button is clicked on Pause Menu.
 * @details It allows the user to:
 * Use Bonus Codes,
 * ...
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 20 August 2015
 */
class W_MenuBonus : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent (W_Menu*), gameboard
     */
    W_MenuBonus(QWidget *parent, G_Gameboard *gameboard);

    /**
     * @brief Set the W_Menu title and subtitle
     */
    void setTitleParent();

private:
    //Layout
    QFormLayout *layoutMenu;

    //Buttons
    QPushButton *btnBonusCode;
    QPushButton *btnBonusCredits;
    QPushButton *btnBonusReturn;
    QPushButton *btnBonusAudio;
    QPushButton *btnMenuPauseDelete;

    //Parent
    W_Menu* parent;
    G_Gameboard* gameboard;

signals:

public slots:

};

#endif // W_MENUBONUS_H
