#ifndef VIEWBLOCENNEMI_H
#define VIEWBLOCENNEMI_H

class QGraphicsRectItem;
class QGraphicsItem;
class Ennemi;

#include "surface.h"

class S_ViewBlocEnnemi : public Surface
{
public:
    S_ViewBlocEnnemi(int ligne, int colonne, Ennemi* proprietaire, QGraphicsItem *parent = 0);
    int getLine();
    int getColonne();
    bool isActif();
    void setActif(bool actif);

    Ennemi* proprietaire;

    void pinguinOn();
    void blocOn();
    void setStylePinguinOn();

private:
    int ligne;      //.. -2, -1, 0, 1, 2 ..
    int colonne;    // 0,1,2..
    bool actif;

    void setStyleUnactivated();
    void setStyleActivated();

};

#endif // VIEWBLOCENNEMI_H
