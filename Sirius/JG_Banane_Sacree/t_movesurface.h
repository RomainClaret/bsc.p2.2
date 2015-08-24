#ifndef T_MOVESURFACE_H
#define T_MOVESURFACE_H

#include <QObject>
class G_Surface;
class QGraphicsScene;
class QTimer;

class T_MoveSurface : public QObject
{
    Q_OBJECT
public:
    T_MoveSurface(G_Surface* surface, QGraphicsScene* scene, QObject *parent = 0);

public slots:
    void move();

private:
    G_Surface* surface;
    QTimer* timer;

};

#endif // T_MOVESURFACE_H
