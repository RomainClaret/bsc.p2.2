#ifndef W_MENUCODE_LINEEDIT_H
#define W_MENUCODE_LINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class W_MenuCode_LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit W_MenuCode_LineEdit(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);

signals:

public slots:

};

#endif // W_MENUCODE_LINEEDIT_H
