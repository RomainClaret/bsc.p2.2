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

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;
class W_Menu;
class W_MenuCode_LineEdit;

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

    void keyPressEvent(QKeyEvent *event);

private:
    QFormLayout *layoutMenuPause;

    QPushButton *btnBonusReturn;
    QPushButton *btnCodeValidate;

    W_MenuCode_LineEdit* lineEditCode;

    W_Menu* parent;

signals:

public slots:

};

#endif // W_MENUCODE_H
