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

#ifndef MECHANT_H
#define MECHANT_H

#include <QGraphicsItem>
#include "stateennemi.h"


class QPoint;
class QGraphicsRectItem;
class Gameboard;

class S_ViewBlocEnnemi;

class StateEnnemi;
class StateEnnemi_Patrol;
class StateEnnemi_Sleep;

/**
 * @brief Enemy Class
 * @details Parent class for enemies.
 * Contains the orientation, the path, the skin, the definition, and the specification.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
class Ennemi : public QGraphicsItem
{
    friend class StateEnnemi;
    friend class StateEnnemi_Patrol;
    friend class StateEnnemi_Sleep;
    friend class StateEnnemi_Pause;

public:
    //Constructors
    /**
     * @brief Constructor with path setup.
     * @param path QList of QPoint for the path
     * @param g Gameboard to construct on
     */
    Ennemi(QList<QPoint>, Gameboard *g);

    //Destructor
    /**
      * @brief Destrucation of the blocks used for the vision.
      */
    ~Ennemi();

    //Methods related to the scene
    /**
     * @brief Add self to the scene.
     */
    void addToScene(QGraphicsScene*);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //Methods related to self
    /**
     * @brief Set the orientation of self to the top.
     */
    void setOrientation_top();

    /**
     * @brief Set the orientation of self to the bottom
     */
    void setOrientation_bottom();

    /**
     * @brief Set the orientation of self to the left
     */
    void setOrientation_left();

    /**
     * @brief Set the orientation of self to the right
     */
    void setOrientation_right();

    /**
     * @brief Set the path of self for the automatic displacement.
     */
    void setPath(QList<QPoint>);

    /**
     * @brief Restart game is Playable character is detected.
     */
    void pinguinOnViewBloc();

    /**
     * @brief Enable or Disable vision blocks.
     */
    void viewBlocActif();

    /**
     * @brief getEnemyPos return the position with the correct coords on the map
     * @return position of the enemy
     */
    QPoint getEnemyPos();

    /**
     * @brief changeState replace the state of the enemy with newState
     * @param newState
     */
    void changeState(StateEnnemi* newState);

protected:
    /**
     * @brief Moves self by an amount.
     * @param step amount to move self
     */
    void advance(int step);
    int speed;

    QList<QPoint> path;
    QList<S_ViewBlocEnnemi* > champVue;

    /**
     * @brief Set the position of the block "S_ViewBlocEnnemi"
     * @param bloc self is positioned to this S_ViewBlocEnnemi
     * @param p
     */
    void setPosViewBloc(S_ViewBlocEnnemi* bloc, QPoint p);

    //Les skins sont les images attribué au méchant
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;

    QBrush *ennemiSkin;

private:
    int iDestPoint;
    bool sens;
    bool detectPinguin;
    int time;
    char orientation;

    /**
     * @brief Move self by x and y values.
     * @param x move this amount on the x-axis
     * @param y move this amount on the y-axis
     */
    void moveBy(int x, int y);

    /**
     * @brief Set the position of self with the x and y values.
     * @param x set the postion on the x-axis
     * @param y set the postion on the y-axis
     */
    void setPos(int x, int y);

    /**
     * @brief Convert QPointF to QPoint.
     * @param psrc QPointF to convet
     * @return converted QPoint
     */
    QPoint convertPosPoint(QPointF psrc);

    /**
     * @brief Check of collison with self.
     * @return true if self collides
     */
    bool collide();

    /**
     * @brief Get the next point in the list.
     * @return id of the next point in the list of points
     */
    int nextPoint();

    /**
     * @brief Detect if the Playable character Pingouin is in the vision.
     */
    void pinguinDetection();

    Gameboard *game;

    StateEnnemi* state;


};

#endif // MECHANT_H
