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

#ifndef M_PAUSE_V1_H
#define M_PAUSE_V1_H

#include <QWidget>

class QLabel;
class QPushButton;
class QFormLayout;
class QGraphicsDropShadowEffect;



class W_MenuPause_v1 : public QWidget
{
    Q_OBJECT
public:
    W_MenuPause_v1(QWidget *parent);

    void setUnableMenu(int levelValue);

private:
    QFormLayout *layoutMenuPause;
    QLabel *titleMenuPause;
    QLabel *undertitleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseIsland;
    QPushButton *btnMenuPauseQuit;
    QPushButton *btnMenuPauseRestartEnigma;
    QPushButton *btnMenuPauseRestartLevel;

    QString styleBtn;

    QGraphicsDropShadowEffect* shadowbtn();
    void paintEvent(QPaintEvent *pe);

signals:

public slots:

};

#endif // M_PAUSE_V1_H
