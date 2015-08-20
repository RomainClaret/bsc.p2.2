#ifndef T_CHARACTERMOVER_H
#define T_CHARACTERMOVER_H

#include <QThread>

#include <QDebug>

class G_Gameboard;
class P_Penguin;
#include <QPointF>
#include <QMutex>

class t_CharacterMover : public QThread
{
    Q_OBJECT

    void run();
public:
    t_CharacterMover(P_Penguin* character, QObject *parent = 0);
    void moveCharacter(char orientation);

private :
    P_Penguin* character;
    char orientation;
    QPointF startPos;
    int gs;
    unsigned long speed;
    QMutex lock;

signals:

public slots:

};

#endif // T_CHARACTERMOVER_H
