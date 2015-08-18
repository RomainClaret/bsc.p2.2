#ifndef STATEENNEMI_PATROL_H
#define STATEENNEMI_PATROL_H
#include "stateennemi.h"
class Ennemi;

/**
 * @brief Concrete class of the State Pattern for Ennemis
 * @details The ennemis patrol normaly with this state. Take care that "StateEnnemi_Patrol" is a Friend of "Ennemi"
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 */
class StateEnnemi_Patrol : public StateEnnemi
{
public:

    /**
     * @brief StateEnnemi_Patrol Constructor of StateEnnemi_Patrol
     */
    StateEnnemi_Patrol();

    /**
     * @brief step This is the brain of the Ennemi, it determinate the way of the ennemi and move him
     * @param ennemi
     */
    void step(Ennemi* ennemi);
};

#endif // STATEENNEMI_PATROL_H
