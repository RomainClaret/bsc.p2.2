#ifndef STATEENNEMI_SLEEP_H
#define STATEENNEMI_SLEEP_H
#include "stateennemi.h"
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
class StateEnnemi_Sleep : public StateEnnemi
{
public:

    /**
     * @brief StateEnnemi_Sleep Constructor of StateEnnemi_Sleep
     */
    StateEnnemi_Sleep();

    /**
     * @brief step This is the brain of the Ennemi, in this case it only desactivate the view of the ennemi at the first run
     * @param ennemi
     */
    void step(Ennemi* ennemi);

private:
    bool initialisation;
};

#endif // STATEENNEMI_SLEEP_H
