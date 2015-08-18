#include "state_npcsleep.h"
#include "g_npc.h"
#include "s_viewblocknpc.h"

State_NPCSleep::State_NPCSleep() : State_NPC()
{
    initialisation = true;
}

/**
 * @details Desactivate the view of the ennemi at the first run and do nothing after
 */
void State_NPCSleep::step(G_NPC* ennemi)
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
