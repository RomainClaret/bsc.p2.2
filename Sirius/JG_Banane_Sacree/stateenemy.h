#ifndef STATEENNEMI_H
#define STATEENNEMI_H

class Enemy;

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
class StateEnemy
{
public:
    /**
     * @brief StateEnnemi Constructor of StateEnnemi
     */
    StateEnemy(){}

    /**
     * @brief ~StateEnnemi Virtual destuctor of StateEnnemi
     */
    virtual ~StateEnemy(){}

    /**
     * @brief step Vitual methode, each stateEnnemi must implements "step" this is the brain of the ennemi
     * @param ennemi
     */
    virtual void step(Enemy* ennemi) = 0;
};

#endif // STATEENNEMI_H
