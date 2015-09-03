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

#ifndef W_MENUAUDIO_H
#define W_MENUAUDIO_H

#include <QWidget>
#include <QHash>

class QLabel;
class QPushButton;
class QGridLayout;
class QGraphicsDropShadowEffect;
class W_Menu;
class QLabel;
class QSlider;
class Singleton_Audio;

/**
 * @brief Code Menu, which appears when the "Code" button is clicked on Bonus Menu.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 20 August 2015
 */
class W_MenuAudio : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent (W_Menu*)
     */
    W_MenuAudio(QWidget *parent);

    /**
     * @brief Set the W_Menu title and subtitle
     */
    void setTitleParent();

private:
    // Layout
    QGridLayout *layoutMenuPause;

    // Elements
    QPushButton *btnBonusReturn;
    QSlider *sldMusics;
    QSlider *sldSounds;
    QLabel *lbMusics;
    QLabel *lbSounds;
    QLabel *lbMusicsValue;
    QLabel *lbSoundsValue;

    // Parent
    W_Menu* parent;
    Singleton_Audio *audioSingleton;

    int getSoundsVolume();
    int getMusicsVolume();


    void showEvent(QShowEvent *);
signals:

public slots:
    void setValueMusicsVolume(int value);
    void setValueSoundsVolume(int value);

};

#endif // W_MENUAUDIO_H
