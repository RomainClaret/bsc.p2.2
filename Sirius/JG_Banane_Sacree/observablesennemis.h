#ifndef OBSERVABLESENNEMIS_H
#define OBSERVABLESENNEMIS_H

/**
 * @brief Pattern Observer to manage the "Ennemis"
 * @details "Ennemis" can be tune with the State Pattern
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 august 2015
 * @todo add management of State pattern, remplace timer by thread in "Ennemi"
 * @Warning DELETE and CREATE un new ObservableEnnemis for the next level ! ObservableEnnemis will delete all the enemy of the level automaticaly
 */

//@bug no bugs
//@warning no warnings

#include "ennemi.h"
#include <QList>
#include <QPoint>

class ObservablesEnnemis
{
public:
    /**
     * @brief ObservablesEnnemis Constructor of ObervablesEnnemis
     */
    ObservablesEnnemis();

    /**
     * @brief ObservablesEnnemis Destuctor delete all the enemis
     */
    ~ObservablesEnnemis();

    /**
     * @brief addEnnemiObserver add ennemi as observer
     * @param ennemi the new observer
     */
    void addEnnemiObserver(Ennemi* ennemi);

    /**
     * @brief changeEnnemiState change the state of the ennemis in the LEVEL PHASE
     * @param ennemi the new observer
     * @param posPlayer is the position of the player
     */
    void changeEnnemiState(StateEnnemi* state, QPoint posPlayer);

    /**
     * @brief changeEnnemiState change the state of ALL ennemis in the level
     * @param ennemi the new observer
     */
    void changeEnnemiState(StateEnnemi* state);

private:
    QList<Ennemi*> list_ennemisObserver;

};

#endif // OBSERVABLESENNEMIS_H
