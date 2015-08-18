#ifndef STATEENEMY_PAUSE_H
#define STATEENEMY_PAUSE_H

#include "stateenemy.h"
class Enemy;

/**
 * @brief Concrete class of the State Pattern for Ennemis
 * @details Freeze the enemy
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 */
class StateEnemy_Pause
{
public:
    /**
     * @brief StateEnemy_Pause Constructor
     */
    StateEnemy_Pause();

    /**
     * @brief step is the brain of the enemy, in this case the enemy just freeze
     * @param ennemi
     */
    void step(Enemy* ennemi);
};

#endif // STATEENEMY_PAUSE_H
