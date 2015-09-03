#ifndef FACTORY_CHARACTER_H
#define FACTORY_CHARACTER_H

class G_Character;
class C_Enemy;
class C_Player;
class QGraphicsScene;
class Observer_Enemy;
class G_Gameboard;

#include <QString>
#include <QList>
#include <QPoint>

/**
 * @brief Pattern Factory to create Characters
 * @details You can build Enemy or Player
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 19 august 2015
 */

//@bug no bugs
//@warning no warnings

class Factory_Character
{
public:
    static QString ENEMY_WOLF;
    static QString ENEMY_FOX;
    static QString ENEMY_WALRUS;
    static QString ENEMY_OTTER;

    /**
     * @brief createEnemy generate a Enemy, add it to the scene and to the observer
     * @param type type of enemy, static String available
     * @param path path of the enemy (points list)
     * @param g gameboard
     * @param observer the observer of the ennemies of the lvl
     * @param scene
     * @return an enemy
     */
    static C_Enemy* createEnemy(QString type, QString position, QPoint* startPoint, QList<QPoint> path, G_Gameboard *g, Observer_Enemy* observer, QGraphicsScene* scene);

    /**
     * @brief createPlayer generate a Player and add it to the scene
     * @param scene
     * @return a player
     */
    static C_Player* createPlayer(int x, int y, QGraphicsScene* scene, G_Gameboard* game);
};

#endif // FACTORY_CHARACTER_H
