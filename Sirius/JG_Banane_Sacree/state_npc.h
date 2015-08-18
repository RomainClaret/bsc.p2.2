#ifndef STATE_NPC_H
#define STATE_NPC_H

class G_NPC;

/**
 * @brief Abstract class of the Pattern State to manage the "Ennemis"
 * @details "Ennemis" can be tune with the State Pattern, StateEnnemi is a FRIEND of Ennemi
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 */
class State_NPC
{
public:
    /**
     * @brief StateEnemy Constructor of StateEnemy
     */
    State_NPC(){}

    /**
     * @brief ~StateEnemy Virtual destuctor of StateEnemy
     */
    virtual ~State_NPC(){}

    /**
     * @brief step Vitual methode, each stateEnnemi must implements "step" this is the brain of the ennemi
     * @param npc
     */
    virtual void step(G_NPC* npc) = 0;
};

#endif // STATE_NPC_H
