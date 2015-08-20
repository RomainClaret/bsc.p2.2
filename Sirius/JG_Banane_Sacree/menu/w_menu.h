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

#ifndef W_MENU_H
#define W_MENU_H

#include <QWidget>
#include "../menu/w_menupause.h"
#include "../menu/w_menubonus.h"
#include "../menu/w_menucode.h"
#include "../menu/w_menucredits.h"

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;

/**
 * @brief Menu, which will contain Menu Widget.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 20 August 2015
 */
class W_Menu : public QWidget
{
    Q_OBJECT

public:
    W_Menu(QWidget *parent);

    // Styling Strings for buttons
    static QString styleBtn;
    static QString styleBtnUnable;

    /**
     * @brief KeyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief PaintEvent used for the bordering
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Set the Menu Title with param's value
     * @param title QString containing the new title
     */
    void setTitle(QString title);

    /**
     * @brief Set the Menu Subtitle with param's value
     * @param subTitle QString containing the new subtitle
     */
    void setSubTitle(QString subTitle);

    /**
     * @brief ShowEvent called when the widget is hidded or shown.
     */
    void showEvent(QShowEvent*);

    /**
     * @brief Immediately link to the W_MenuPause's setUnableMenu method
     * @param levelValue Int containing the level's number
     */
    void setUnableMenu(int levelValue);

private:
    //Layout
    QFormLayout *layoutMenuPause;
    QLabel *titleMenuPause;
    QLabel *undertitleMenuPause;

    //Different Menu Widget inside
    W_MenuPause* menuPause;
    W_MenuBonus* menuBonus;
    W_MenuCode* menuCode;
    W_MenuCredits* menuCredits;

signals:

public slots:
    /**
     * @brief SLOT: Called when Bonus Widget need to be placed in the menu
     */
    void loadBonus();

    /**
     * @brief SLOT: Called when Pause Widget need to be placed in the menu
     */
    void loadPause();

    /**
     * @brief SLOT: Called when Code Widget need to be placed in the menu
     */
    void loadCode();

    /**
     * @brief SLOT: Called when Credits Widget need to be placed in the menu
     */
    void loadCredits();

};

#endif // W_MENU_H
