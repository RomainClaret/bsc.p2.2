#ifndef STATE_NPCSLEEP_H
#define STATE_NPCSLEEP_H
#include "state_npc.h"
class ennemi;

/**
 * @brief Concrete class of the State Pattern for Ennemis
 * @details The ennemis sleep in this state (off state). Take care that "StateEnnemi_Sleep" is a Friend of "Ennemi"
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 */
class State_NPCSleep : public State_NPC
{
public:

    /**
     * @brief StateNPC_Sleep Constructor of StateNPC_Sleep
     */
    State_NPCSleep();

    /**
     * @brief step This is the brain of the npc, in this case it only desactivate the view of the npc at the first run
     * @param npc
     */
    void step(G_NPC* npc);

private:
    bool initialisation;
};

#endif // STATE_NPCSLEEP_H
