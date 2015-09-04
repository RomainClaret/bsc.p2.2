#ifndef S_FOOTSTEP_H
#define S_FOOTSTEP_H
#include "g_surface.h"
class G_Gameboard;

/**
 * @brief Penguin footsteps
 * @details footsteps created by snow
 * @author Claret Romain, romain.claret@rocla.ch
 * @author Divernois Margaux, margaux.divernois@gmail.com
 * @author Visinand Steve, visinandst@gmail.com
 * @copyright Custom License + NDA
 * @version 1.0
 * @date 27 august 2015
 */
class S_Footstep : public G_Surface
{
public:
    /**
     * @brief S_Footstep Main Constructor
     * @param xpos pos X on Scene
     * @param ypos pos Y on Scene
     * @param sens Scene
     * @param lifetime time before fade out
     * @param game is the gameboard
     * @param parent dad or mom ;)
     */
    S_Footstep(int xpos, int ypos, char sens, int lifetime, G_Gameboard* game, QGraphicsItem *parent = 0);

private:
    int lifetime;
    int itime;

protected:
    void advance(int step);
};

#endif // S_FOOTSTEP_H
