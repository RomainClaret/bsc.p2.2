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

#ifndef W_DIALOG_V1_H
#define W_DIALOG_V1_H

#include <QWidget>
class QLabel;

class W_Dialog_v1 : public QWidget
{
    Q_OBJECT
public:
    W_Dialog_v1(QWidget *parent = 0);
    void setText(QString text, int type);
    QString getText();
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    int type;
    QLabel* title;
    QLabel* text;
    QLabel* escapeText;

};

#endif // W_DIALOG_V1_H
