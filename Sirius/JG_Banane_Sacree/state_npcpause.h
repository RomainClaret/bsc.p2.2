#ifndef STATE_NPCPAUSE_H
#define STATE_NPCPAUSE_H

#include "state_npc.h"
class G_NPC;

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
class State_NPCPause
{
public:
    /**
     * @brief StateNPC_Pause Constructor
     */
    State_NPCPause();

    /**
     * @brief step is the brain of the npc, in this case the npc just freeze
     * @param npc
     */
    void step(G_NPC* npc);
};

#endif // STATE_NPCPAUSE_H
