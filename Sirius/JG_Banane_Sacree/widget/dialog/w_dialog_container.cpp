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

#include "w_dialog_container.h"
#include "w_dialog_text.h"
#include <QHBoxLayout>

W_DialogContainer::W_DialogContainer(QWidget *parent)
{  
    textWidget = new W_DialogText(this);

    QHBoxLayout* box = new QHBoxLayout(this);
    box->addStretch();
    box->addWidget(textWidget);
    box->addStretch();
    box->setSpacing(0);
}

void W_DialogContainer::setText(QString text, int type)
{
    this->textWidget->setText(text, type);
}

QString W_DialogContainer::getText()
{
    return this->textWidget->getText();
}
