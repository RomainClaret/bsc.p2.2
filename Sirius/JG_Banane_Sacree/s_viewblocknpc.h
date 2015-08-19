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
    S_ViewBlockNPC(int ligne, int colonne, C_Enemy* owner, QGraphicsItem *parent = 0);
    int getLine();
    int getColonne();
    bool isActive();
    void setActive(bool actif);

    C_Enemy* owner;

    void playableCharacterOn();
    void blockOn();
    void setStylePlayableCharacterOn();

private:
    int ligne;      //.. -2, -1, 0, 1, 2 ..
    int colonne;    // 0,1,2..
    bool actif;

    void setStyleDesactivated();
    void setStyleActivated();

};

#endif // S_VIEWBLOCKNPC_H
