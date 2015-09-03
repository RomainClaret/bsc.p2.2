
#include "../state/state_enemypause.h"
#include "../character/c_enemy.h"
State_EnemyPause::State_EnemyPause() : State_Enemy()
{
}

/**
 * @details Freeze the enemy
 */
void State_EnemyPause::step(C_Enemy*)
{
    //nothing
}
