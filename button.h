#ifndef BUTTON_H
#define BUTTON_H
#include "QPushButton"

class button : public QPushButton
{
    Q_OBJECT;
public:
    button(const QString &text);
    // ~button();
    // QSize sizeHint() const override;
};

#endif // BUTTON_H
