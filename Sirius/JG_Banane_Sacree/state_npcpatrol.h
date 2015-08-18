#ifndef STATE_NPCPATROL_H
#define STATE_NPCPATROL_H
#include "state_npc.h"
class G_NPC;

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
class State_NPCPatrol : public State_NPC
{
public:

    /**
     * @brief StateEnemy_Patrol Constructor of StateEnemy_Patrol
     */
    State_NPCPatrol();

    /**
     * @brief step This is the brain of the npc, it determinate the way of the npc and move him
     * @param mpc
     */
    void step(G_NPC* npc);
};

#endif // STATE_NPCPATROL_H
