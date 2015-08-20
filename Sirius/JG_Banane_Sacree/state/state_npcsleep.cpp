#include "../state/state_enemysleep.h"
#include "../character/c_enemy.h"
#include "../surface/s_viewblocknpc.h"
State_EnemySleep::State_EnemySleep() : State_Enemy()
{
    initialisation = true;
}

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */
void State_EnemySleep::step(C_Enemy* ennemi)
{
    if(initialisation)
    {
        foreach (S_ViewBlockNPC* vb, ennemi->viewField)
        {
            vb->setActive(false);
        }
        initialisation = false;
    }
}
