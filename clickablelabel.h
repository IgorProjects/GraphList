#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(const QString& text="");
    ~ClickableLabel() override{}
signals:
    void doubleClicked();
protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABEL_H
