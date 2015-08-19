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
#include "w_menupause.h"
#include "w_menubonus.h"
#include "w_menucode.h"

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;

/**
 * @brief Bonus Menu, which appears when the bonus button is clicked on Pause Menu.
 * @details It allows the user to:
 * Use Bonus Codes,
 * ...
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 19 August 2015
 * @todo code all the class
 */
class W_Menu : public QWidget
{
    Q_OBJECT
public:
    W_Menu(QWidget *parent);

    static QString styleBtn;
    static QString styleBtnUnable;

    void setTitle(QString title);
    void setSubTitle(QString subTitle);

    void showEvent(QShowEvent*);

    void setUnableMenu(int levelValue);

private:
    QFormLayout *layoutMenuPause;
    QLabel *titleMenuPause;
    QLabel *undertitleMenuPause;

    W_MenuPause* menuPause;
    W_MenuBonus* menuBonus;
    W_MenuCode* menuCode;

    QGraphicsDropShadowEffect* shadowbtn();
    void paintEvent(QPaintEvent *pe);

signals:

public slots:
    void loadBonus();
    void loadPause();

};

#endif // W_MENU_H
