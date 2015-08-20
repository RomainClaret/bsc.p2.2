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

#ifndef W_MENUCODE_H
#define W_MENUCODE_H

#include <QWidget>
#include <QHash>

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;
class W_Menu;
class W_MenuCode_LineEdit;
class QLabel;

/**
 * @brief Code Menu, which appears when the "Code" button is clicked on Bonus Menu.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 19 August 2015
 * @todo code all the class
 */
class W_MenuCode : public QWidget
{
    Q_OBJECT
public:
    W_MenuCode(QWidget *parent);
    void setTitleParent();
    void refuseCode();
    void acceptCode();

    void keyPressEvent(QKeyEvent *event);

    static const int CODE_HELLO = 1;
    static const int CODE_BANANA = 2;
    static const int CODE_HAPPYFEET = 3;
    static const int CODE_HOTHOTHOT = 4;
    static const int CODE_MADAGASCAR = 5;
    static const int CODE_SECRETAGENT = 6;

    static bool BANANASPECIAL;

private:
    QFormLayout *layoutMenuPause;

    QPushButton *btnBonusReturn;
    QPushButton *btnCodeValidate;
    QLabel* labelCodeResult;

    W_MenuCode_LineEdit* lineEditCode;

    W_Menu* parent;
    QHash<QString,int> hash;

signals:

public slots:
    void validateCode();

};

#endif // W_MENUCODE_H
