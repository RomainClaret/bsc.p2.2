#ifndef T_LEVEL_H
#define T_LEVEL_H

#include <QWidget>
#include <QtTest/QtTest>

class T_Level : public QWidget
{
    Q_OBJECT

public:
    T_Level(QWidget *parent = 0);
    ~T_Level();

private slots:
//    void benchmarkInsertion();
//    void benchmarkQuick();

};

#endif // T_LEVEL_H
