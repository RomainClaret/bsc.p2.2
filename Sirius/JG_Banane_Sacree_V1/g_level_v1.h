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

#ifndef LEVEL_V1_H
#define LEVEL_V1_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;
class G_Gameboard_v1;
class QStringList;

#include <QList>

#include "w_dialog_v1.h"

//#include "gameboard.h"


class G_Level_v1
{
public:
    G_Level_v1(int levelNumber, G_Gameboard_v1 *game);
    QGraphicsScene *populateScene();
    QPoint* getStartingPoint();
    QPoint getViewStart();
    int changeLevel(int levelNumber);
    int getLevelNumber();
    QString getDialogText(int value);
    QPoint getUnlockEndPoint();

private:
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;
    QPoint* unlockEnd;

    G_Gameboard_v1 *game;

    int maxBlocksHeight;
    int maxBlocksWidth;

    void getSceneSize();
    void getSceneDialog();

    QList<QList<QPoint> > ennemi;
    QStringList dialogList;
    int dialogValue;
};

#endif // LEVEL_V1_H
