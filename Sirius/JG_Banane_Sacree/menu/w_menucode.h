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
 * @version 1.1
 * @date 20 August 2015
 */
class W_MenuCode : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent (W_Menu*)
     */
    W_MenuCode(QWidget *parent);

    /**
     * @brief Set the W_Menu title and subtitle
     */
    void setTitleParent();

    /**
     * @brief Refuse the code inserted  in the QLineEdit
     */
    void refuseCode();

    /**
     * @brief Accept the code inserted in the QLineEdit
     */
    void acceptCode();

    /**
     * @brief KeyPressEvent, used to send events to the QLineEdit
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    //Static Const Element
    static const int CODE_HELLO = 1;
    static const int CODE_BANANA = 2;
    static const int CODE_HAPPYFEET = 3;
    static const int CODE_HOTHOTHOT = 4;
    static const int CODE_MADAGASCAR = 5;
    static const int CODE_SECRETAGENT = 6;
    static const int CODE_NOTSCARED = 7;
    static const int CODE_THE4TH = 8;
    static const int CODE_PENGUINFORCE = 9;
    static const int CODE_IMSCARED = 10;

private:
    // Layout
    QFormLayout *layoutMenuPause;

    // Elements
    QPushButton *btnBonusReturn;
    QPushButton *btnCodeValidate;
    QLabel* labelCodeResult;

    // Personnal QLineEdit
    W_MenuCode_LineEdit* lineEditCode;

    // Parent
    W_Menu* parent;

    // Hash <Code, Value>
    QHash<QString,int> hash;

signals:

public slots:
    /**
     * @brief SLOT: Check if the code is validate or not
     */
    void validateCode();

};

#endif // W_MENUCODE_H
