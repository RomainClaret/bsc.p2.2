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
 * @version 1.0
 * @date 19 August 2015
 * @todo code all the class
 */
class W_MenuBonus : public QWidget
{
    Q_OBJECT
public:
    W_MenuBonus(QWidget *parent);
    void setTitleParent();

private:
    QFormLayout *layoutMenuPause;

    QPushButton *btnBonusCode;
    QPushButton *btnBonusCredits;
    QPushButton *btnBonusReturn;

    W_Menu* parent;

signals:

public slots:

};

#endif // W_MENUBONUS_H
