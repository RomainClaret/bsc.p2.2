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

#ifndef C_ENEMY_H
#define C_ENEMY_H

#include <QDebug>
#include <QGraphicsItem>
#include "../state/state_enemy.h"
#include "../character/c_ai.h"
#include "../character/g_character.h"

#include <QStringList>

class QPoint;
class QGraphicsRectItem;
class G_Gameboard;

class S_ViewBlockNPC;

class State_Enemy;
class State_EnemyPatrol;
class State_EnemySleep;
class State_EnemyPause;
class State_EnemyWalrus;
class State_EnemyFriendly;

/**
 * @brief Enemy Class
 * @details Parent class for Non Player Characters.
 * Contains the orientation, the path, the skin, the definition, and the specification.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 January 2015
 * @todo integrate with DP Factory
 */
class C_Enemy : public G_Character
{
    friend class State_Enemy;
    friend class State_EnemyPatrol;
    friend class State_EnemySleep;
    friend class State_EnemyPause;
    friend class State_EnemyWalrus;
    friend class State_EnemyFriendly;

    friend class C_AI;

public:
    //Constructors
    /**
     * @brief Constructor with path setup.
     * @param path QList of QPoint for the path
     * @param g Gameboard to depend on
     */
    C_Enemy(QString orientation, QList<QPoint> path, G_Gameboard *g);

    //Destructor
    /**
      * @brief Destruction of the blocks used for the vision.
      */
    ~C_Enemy();

    //Methods related to the scene
    /**
     * @brief Add self to the scene.
     */
    void addToScene(QGraphicsScene*);

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
    void playableCharacterOnViewBlock();

    /**
     * @brief Enable or Disable vision blocks.
     */
    void viewBlockActive();

    /**
     * @brief getEnemyPos return the position with the correct coords on the map
     * @return position of the enemy
     */
    QPoint getNPCPos();

    /**
     * @brief changeState replace the state of the enemy with newState
     * @param newState
     */
    virtual void changeState(State_Enemy* newState);

    virtual void action() { }

    void moveByPixel(int x, int y);

    virtual void checkPenguin();

    void addDialog(QString text);

    void resetDefaultOrientation();

    /**
     * @brief Set the position of self with the x and y values.
     * @param x set the postion on the x-axis
     * @param y set the postion on the y-axis
     */
    void setPos(int x, int y);

    void setDetectPlayableCharacter(bool value);

    virtual void setSpecialTexture(bool value);

protected:
    /**
     * @brief Moves self by an amount.
     * @param step amount to move self
     */
    void advance(int step);
    int speed;

    QList<QPoint> path;
    QList<S_ViewBlockNPC* > viewField;

    /**
     * @brief Set the position of the block "S_ViewBlocNPC"
     * @param bloc self is positioned to this S_ViewBlocNPC
     * @param p
     */
    void setPosViewBloc(S_ViewBlockNPC* block, QPoint p);

    C_AI *brain;

    State_Enemy* state;
    bool detectPlayableCharacter;
    QStringList dialogList;

private:
    void stepMoveCharacter()
    {
        //rien temporaire
    }

    int iDestPoint;
    bool direction;
    int time;

    /**
     * @brief Move self by x and y values.
     * @param x move this amount on the x-axis
     * @param y move this amount on the y-axis
     */
    void moveBy(int x, int y);

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

    virtual bool collide();

    /**
     * @brief Get the next point in the list.
     * @return id of the next point in the list of points
     */
    int nextPoint();

    /**
     * @brief Detect if the Playable character Pingouin is in the vision.
     */
    virtual void playableCharacterDetection();

    QString defaultOrientation;
};

#endif // C_ENEMY_H
