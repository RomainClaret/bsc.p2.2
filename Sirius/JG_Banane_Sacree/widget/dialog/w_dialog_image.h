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

#ifndef W_DIALOG_IMAGE_H
#define W_DIALOG_IMAGE_H

#include <QWidget>
class QMediaPlayer;
class QLabel;

/**
 * @brief Dialog popup.
 * @details Widget shown on top of the game which contains a dialog.
 * It can be dismissed by pressing a key on the keyboard.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 21 August 2015
 */
class W_DialogImage : public QWidget
{
    Q_OBJECT
public:
    //Constructor
    /**
     * @brief Overlay widget to display the dialog.
     * @param parent if need
     */
    W_DialogImage(QString imageName, QWidget *parent= 0);

    void setImage(QString new_imageName);

signals:

public slots:

private:
    QString imageName;
    QLabel* myimage;

};

#endif // W_DIALOG_IMAGE_H
