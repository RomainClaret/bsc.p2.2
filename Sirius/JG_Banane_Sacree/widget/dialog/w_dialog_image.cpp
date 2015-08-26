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

#include "w_dialog_image.h"
#include <QPainter>
#include <QDebug>

#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>

W_DialogImage::W_DialogImage(QString imageName, QWidget *)
{
    myimage = new QLabel();
    setImage(imageName);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(myimage);
    setLayout(layout);

    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_PaintOnScreen);

    setAttribute(Qt::WA_TransparentForMouseEvents);

}

void W_DialogImage::setImage(QString new_imageName)
{
//    this->imageName = ":/dialog/dialog/";
    this->imageName = "qrc:/dialog/dialog/";

    if(new_imageName.isEmpty())
    {
        qDebug() << "OK";
        new_imageName = "empty.png";
    }

    this->imageName.append(new_imageName);

    QPixmap pix(this->imageName);
    myimage->setPixmap(pix);

}
