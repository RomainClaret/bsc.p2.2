#ifndef OBSERVER_NPC_H
#define OBSERVER_NPC_H

/**
 * @brief Pattern Observer to manage the "Ennemis"
 * @details "Ennemis" can be tune with the State Pattern
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.1
 * @date 02 september 2015
 * @todo add management of State pattern, remplace timer by thread in "NPC"
 * @Warning DELETE and CREATE un new ObservablesNPC for the next level ! ObservablesNPCs will delete all the npc of the level automaticaly
 */

//@bug no bugs
//@warning no warnings

#include "character/c_enemy.h"
#include <QList>
#include <QHash>
#include <QPoint>

class Observer_Enemy
{
public:
    static QString STATE_PATROL;
    static QString STATE_PAUSE;
    static QString STATE_SLEEP;
    /**
     * @brief ObservablesNPC Constructor of ObservablesNPCs
     */
    Observer_Enemy();

    /**
     * @brief ObservablesEnnemis Destuctor delete all the npcs
     */
    ~Observer_Enemy();

    /**
     * @brief addEnnemiObserver add npc as observer
     * @param ennemi the new observer
     */
    void addNPCObserver(C_Enemy* ennemi);

    void removeNPCObserver(C_Enemy* ennemi);

    /**
     * @brief changeNPCState change the state of the npcs in the LEVEL PHASE
     * @param state the state, check the static attr for differents states
     * @param posPlayer is the position of the player
     */
    void changeNPCState(QString state, QPoint phase);

    /**
     * @brief changeNPCState change the state of ALL npcs in the level
     * @param state the state, check the static attr for differents states
     */
    void changeNPCState(QString state);

    /**
     * @brief switchToState change the state of the npcs in the LEVEL PHASE and save the old. Call switchBackToState to reload the old
     * @param state the new state
     * @param posPlayer is the position of the player
     */
    void switchToState(QString state, QPoint phase);

    /**
     * @brief switchBackToState reload the old states saved of the npcs
     */
    void switchBackToState(QPoint phase);

    /**
     * @brief switchAllToPause switch to the state Pause all the enemies
     */
    void switchAllToPause();

    /**
     * @brief clear delete all enemys
     */
    void clear();

private:
    QList<C_Enemy*> list_ennemisObserver;

    QHash<C_Enemy*, State_Enemy*> hash_enemyPreviousState;

};

#endif // OBSERVER_NPC_H
