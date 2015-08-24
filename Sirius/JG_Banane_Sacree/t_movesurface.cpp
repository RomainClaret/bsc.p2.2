#include "t_movesurface.h"

#include <QGraphicsScene>
#include <QTimer>
#include "surface/g_surface.h"
#include "g_gameboard.h"

T_MoveSurface::T_MoveSurface(G_Surface* surface, QGraphicsScene* scene, QObject *parent): QObject(parent)
{
//    qDebug() << "CREATED";
//    this->surface = surface;

//    timer = new QTimer();
//    timer->setInterval(1000);
//    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
////    timer->start();
//    qDebug() << "END OF CREATED";
}

void T_MoveSurface::move()
{
    qDebug() <<"OK";
    surface->setPos(surface->getPos().x(),surface->getPos().y()+1);
}
