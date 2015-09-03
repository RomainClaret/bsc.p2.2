#ifndef STATE_ENEMYPATROL_H
#define STATE_ENEMYPATROL_H
#include "../state/state_enemy.h"
class C_Enemy;

/**
 * @brief Concrete class of the State Pattern for npc
 * @details The npc patrol normaly with this state. Take care that "StateEnemy_Patrol" is a Friend of "npc"
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 */
class State_EnemyPatrol : public State_Enemy
{
public:

    /**
     * @brief StateEnemy_Patrol Constructor of StateEnemy_Patrol
     */
    State_EnemyPatrol();

    /**
     * @brief step This is the brain of the npc, it determinate the way of the npc and move him
     * @param mpc
     */
    void step(C_Enemy* npc);
};

#endif // STATE_ENEMYPATROL_H
