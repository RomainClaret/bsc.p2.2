#ifndef OBSERVER_NPC_H
#define OBSERVER_NPC_H

/**
 * @brief Pattern Observer to manage the "Ennemis"
 * @details "Ennemis" can be tune with the State Pattern
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 * @todo add management of State pattern, remplace timer by thread in "NPC"
 * @Warning DELETE and CREATE un new ObservablesNPC for the next level ! ObservablesNPCs will delete all the npc of the level automaticaly
 */

//@bug no bugs
//@warning no warnings

#include "c_enemy.h"
#include <QList>
#include <QPoint>

class Observer_NPC
{
public:
    /**
     * @brief ObservablesNPC Constructor of ObservablesNPCs
     */
    Observer_NPC();

    /**
     * @brief ObservablesEnnemis Destuctor delete all the npcs
     */
    ~Observer_NPC();

    /**
     * @brief addEnnemiObserver add npc as observer
     * @param ennemi the new observer
     */
    void addNPCObserver(C_Enemy* ennemi);

    /**
     * @brief changeNPCState change the state of the npcs in the LEVEL PHASE
     * @param ennemi the new observer
     * @param posPlayer is the position of the player
     */
    void changeNPCState(State_Enemy* state, QPoint posPlayer);

    /**
     * @brief changeNPCState change the state of ALL npcs in the level
     * @param state the new observer
     */
    void changeNPCState(State_Enemy* state);

private:
    QList<C_Enemy*> list_ennemisObserver;

};

#endif // OBSERVER_NPC_H
