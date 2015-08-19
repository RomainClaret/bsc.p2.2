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

#ifndef P_PINGOUIN_V1_H
#define P_PINGOUIN_V1_H
#include "c_player_v1.h"
#include "g_object_v1.h"
#include <QList>

class QGraphicsItem;
class QPoint;
class QGraphicsScene;


class P_Penguin_v1  : public C_Player_v1
{
//    Q_PROPERTY(QPoint pos READ pos WRITE setPos)

private:

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    QList<G_Object_v1 *> sacoche;
    QList<G_Object_v1 *> tempSacoche;
    QPoint* lastMove;

    bool slideAble;

    int nbLives;

public:
    P_Penguin_v1();

    void setPos(int, int);
    void moveBy(int, int);
    void moveBack();

    void addToScene(QGraphicsScene*);
    void addObjectToSacoche(G_Object_v1 *object);
    void removeObjectFromSacoche(QString object);
    void removeTempFromSacoche();
    bool checkObjectSacoche(QString object, int quantity = 1);
    QList<G_Object_v1*> getSacoche();
    void printSacoche();
    void emptyTempSacoche();
    void emptySacoche();

    bool isSlide();
    void setSlideAble(bool value);

    QGraphicsRectItem* getCollideBloc(char sensDepl);

    QList<QGraphicsItem *> CollidesRight();
    QList<QGraphicsItem *> CollidesLeft();
    QList<QGraphicsItem *> CollidesTop();
    QList<QGraphicsItem *> CollidesBottom();
    QList<QGraphicsItem *> CollidesCenter();

    //temporaire
    QGraphicsRectItem* getLeftCB();
    QGraphicsRectItem* getRightCB();
    QGraphicsRectItem* getTopCB();
    QGraphicsRectItem* getBottomCB();
    C_Player_v1* getPlayer();

};

#endif // P_PINGOUIN_V1_H
