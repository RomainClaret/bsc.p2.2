#include "stateennemi_sleep.h"
#include "ennemi.h"
#include "s_viewblocennemi.h"

StateEnnemi_Sleep::StateEnnemi_Sleep() : StateEnnemi()
{
    initialisation = true;
}

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */
void StateEnnemi_Sleep::step(Ennemi* ennemi)
{
    if(initialisation)
    {
        foreach (S_ViewBlocEnnemi* vb, ennemi->champVue)
        {
            vb->setActif(false);
        }
        initialisation = false;
    }
}
