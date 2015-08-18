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

#ifndef C_PENGUIN_H
#define C_PENGUIN_H
#include "g_player.h"
#include "g_object.h"
#include <QList>

class QGraphicsItem;
class QPoint;
class QGraphicsScene;

/**
 * @brief Playable character: Penguin.
 * @details This character is playable.
 * It contains the direction control from the keyboard.
 * It controls player's bag, which contains objects.
 * The collision detection is done by cross, with smaller blocks.
 * Sliding or MoveBy (walking) is here.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 */

class C_Penguin  : public G_Player
{
//    Q_PROPERTY(QPoint pos READ pos WRITE setPos)

private:

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    QList<G_Object *> sacoche;
    QList<G_Object *> tempSacoche;
    QPoint* lastMove;

    bool slideAble;

    int nbLives;

public:
    C_Penguin();

    void setPos(int, int);
    void moveBy(int, int);
    void moveBack();

    void addToScene(QGraphicsScene*);
    void addObjectToBag(G_Object *object);
    void removeObjectFromSacoche(QString object);
    void removeTempFromSacoche();
    bool checkObjectSacoche(QString object, int quantity = 1);
    QList<G_Object*> getBag();
    void printSacoche();
    void emptyTempBag();
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
    G_Player* getPlayer();

};

#endif // C_PENGUIN_H
