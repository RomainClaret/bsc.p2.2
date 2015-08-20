#include "w_menucode_lineedit.h"

W_MenuCode_LineEdit::W_MenuCode_LineEdit(QWidget *parent) : QLineEdit(parent)
{

}

void W_MenuCode_LineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
}
