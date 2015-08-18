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

#ifndef LEVEL2_H
#define LEVEL2_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;
class Gameboard;
class QStringList;

#include <QList>

#include "w_dialog.h"
#include <QDomElement>
#include <QDomDocument>

//#include "gameboard.h"

class Level2
{
public:
    Level2(int levelNumber, Gameboard *game);
    QGraphicsScene* populateScene();
    QPoint* getStartingPoint();
    QPoint getViewStart();
    int changeLevel(int levelNumber);
    int getLevelNumber();
    QPoint getUnlockEndPoint();

    void addLevelInformation(QDomElement elem);
    void addLevelItem(QGraphicsScene* scene, QDomElement elem, int x, int y);

private:
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;
    QPoint* unlockEnd;

    Gameboard *game;

    int maxBlocksHeight;
    int maxBlocksWidth;

    QString fileName;
    QDomDocument* doc;
};

#endif // LEVEL2_H
