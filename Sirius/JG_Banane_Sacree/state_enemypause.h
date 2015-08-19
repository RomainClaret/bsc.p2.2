#ifndef STATE_ENEMYPAUSE_H
#define STATE_ENEMYPAUSE_H

#include "state_enemy.h"
class C_Enemy;

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
class State_EnemyPause
{
public:
    /**
     * @brief StateNPC_Pause Constructor
     */
    State_EnemyPause();

    /**
     * @brief step is the brain of the npc, in this case the npc just freeze
     * @param npc
     */
    void step(C_Enemy* npc);
};

#endif // STATE_ENEMYPAUSE_H
