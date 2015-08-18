#include "stateenemy_sleep.h"
#include "enemy.h"
#include "s_viewblockenemy.h"

StateEnemy_Sleep::StateEnemy_Sleep() : StateEnemy()
{
    initialisation = true;
}

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */
void StateEnemy_Sleep::step(Enemy* ennemi)
{
    if(initialisation)
    {
        foreach (S_ViewBlockEnemy* vb, ennemi->viewField)
        {
            vb->setActif(false);
        }
        initialisation = false;
    }
}
