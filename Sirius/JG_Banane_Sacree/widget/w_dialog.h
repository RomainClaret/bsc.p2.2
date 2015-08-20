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

#ifndef W_DIALOG_H
#define W_DIALOG_H

#include <QWidget>
class QLabel;
class QMediaPlayer;

/**
 * @brief Dialog popup.
 * @details Widget shown on top of the game which contains a dialog.
 * It can be dismissed by pressing a key on the keyboard.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */
class W_Dialog : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Overlay widget to display the dialog.
     * @param parent if need
     */
    W_Dialog(QWidget *parent = 0);

    /**
     * @brief Set text to self.
     * @param text text to set
     * @param type type of the text
     */
    void setText(QString text, int type);

    /**
     * @brief Get the text from self.
     * @return text of the dialog
     */
    QString getText();

    /**
     * @brief Listen to the paint event
     * @param pe event
     */
    void paintEvent(QPaintEvent *pe);

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

signals:

public slots:

private:
    int type;
    QLabel* title;
    QLabel* text;
    QLabel* escapeText;
    QMediaPlayer* player;

};

#endif // W_DIALOG_H
