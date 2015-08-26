#ifndef C_AI_H
#define C_AI_H

class C_Enemy;

#include <QList>
class QString;

class C_AI
{
public:
    C_AI();

    /**
     * @brief Set the brain of the character
     * @param brain name of the behavior to take
     * @return true if the behavior is correct
     */
    bool setBrain(QString brain);

private:
    QString brain;
    QList<QString> brainsList;

};

#endif // C_AI_H
