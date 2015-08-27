#ifndef S_FOOTSTEP_H
#define S_FOOTSTEP_H
#include "g_surface.h"
class S_Footstep : public G_Surface
{
public:
    S_Footstep(int xpos, int ypos, char sens, int lifetime, QGraphicsItem *parent = 0);

private:
    int lifetime;
    int itime;

protected:
    void advance(int step);
};

#endif // S_FOOTSTEP_H
