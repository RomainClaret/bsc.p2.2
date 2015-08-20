/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#ifndef W_OBJECT_V1_H
#define W_OBJECT_V1_H

#include <QWidget>
#include "g_object_v1.h"
#include <QList>
#include <QMap>

class W_Object_v1 : public QWidget
{
    Q_OBJECT
public:
    W_Object_v1(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void reloadObjectList(QList<G_Object_v1*> objectList);

signals:

public slots:

private:
    QList<G_Object_v1* > sacoche;
    QMap<QString, int> map;

};

#endif // W_OBJECT_V1_H
