#include "c_ai.h"

#include <QDebug>

C_AI::C_AI()
{
    brainsList << "killer" << "chase" << "follow";
}

bool C_AI::setBrain(QString brain)
{
    this->brain = brain;

    int i = brainsList.indexOf(brain);
    if (i != -1)
    {
        qDebug() << "Brain found : " << brain;
        return true;
    }

    qDebug() << "Brain NOT found : " << brain;
    return false;
}

