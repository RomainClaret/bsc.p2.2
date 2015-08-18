#ifndef STATEENNEMI_H
#define STATEENNEMI_H

class Ennemi;

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
class StateEnnemi
{
public:
    /**
     * @brief StateEnnemi Constructor of StateEnnemi
     */
    StateEnnemi(){}

    /**
     * @brief ~StateEnnemi Virtual destuctor of StateEnnemi
     */
    virtual ~StateEnnemi(){}

    /**
     * @brief step Vitual methode, each stateEnnemi must implements "step" this is the brain of the ennemi
     * @param ennemi
     */
    virtual void step(Ennemi* ennemi) = 0;
};

#endif // STATEENNEMI_H
