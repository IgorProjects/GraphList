#include "clickablelabel.h"

ClickableLabel::ClickableLabel(const QString& text)
    : QLabel(text)
{
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    event->ignore();
    emit doubleClicked();
}
