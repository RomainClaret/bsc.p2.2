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

#ifndef S_VIEWTRANSITION_V1_H
#define S_VIEWTRANSITION_V1_H

#include "g_surface_v1.h"

class QGraphicsItem;

class S_Door_v1 : public G_Surface_v1
{
public:
    S_Door_v1(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Door_v1(QGraphicsItem *parent = 0);

    bool isEndLevel();
    void setLevelEnd(bool value);
    void setNeededItem(QString value);

    QString getNeededItem();
    bool isNeedingItem();

    void setNbItem(int nb);
    int getNbItem();

    void setNextLevel(int nb);
    int getNextLevel();

private:
    void setDesign();
    bool levelEnd;
    int nextLevel;

    bool needItem;
    int nbItem;
    QString* neededItem;
};

#endif // S_VIEWTRANSITION_V1_H
