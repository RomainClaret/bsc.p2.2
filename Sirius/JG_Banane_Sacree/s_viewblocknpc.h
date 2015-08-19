#ifndef S_VIEWBLOCKNPC_H
#define S_VIEWBLOCKNPC_H

class QGraphicsRectItem;
class QGraphicsItem;
class C_Enemy;

#include "g_surface.h"

/**
 * @brief View Block for NPC characters.
 * @details This surface is used by the NPC for their vision.
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 18 August 2015
 */
class S_ViewBlockNPC : public G_Surface
{
public:
    //Constructor
    /**
     * @brief
     * @param xpos set the postion on the x-axis
     * @param ypos set the postion on the y-axis
     * @param parent QGraphicsItem parent
     */
    /**
     * @brief Constructor to position this vision block to given enemy.
     * @param line lign in the matix
     * @param column column in the matrix
     * @param owner enemy the vison is attached to
     * @param parent QGraphicsItem parent if need
     */
    S_ViewBlockNPC(int line, int column, C_Enemy* owner, QGraphicsItem *parent = 0);

    /**
     * @brief Get the line of self in the matrix view of the enemy.
     * @return line number
     */
    int getLine();

    /**
     * @brief Get the column of self in the matrix view of the enemy.
     * @return column number
     */
    int getColonne();

    /**
     * @brief Get if self is active for detection.
     * @return true if self is currently active
     */
    bool isActive();

    /**
     * @brief Set self vision.
     * @param actif true if active
     */
    void setActive(bool actif);

    C_Enemy* owner;

    /**
     * @brief The playable character has been detected.
     */
    void playableCharacterOn();

    /**
     * @brief A block has been detected.
     */
    void blockOn();

    /**
     * @brief Change self skin if playable character has been detected.
     */
    void setStylePlayableCharacterOn();

private:
    int line;      //.. -2, -1, 0, 1, 2 ..
    int column;    // 0,1,2..
    bool actif;

    /**
     * @brief Set the desactivated skin of self.
     */
    void setStyleDesactivated();

    /**
     * @brief Set the activated skin of self.
     */
    void setStyleActivated();

};

#endif // S_VIEWBLOCKNPC_H
