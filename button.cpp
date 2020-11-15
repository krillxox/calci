#include "button.h"

button::button(const QString &text) : QPushButton(text)
{
    QFont font;
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    QSize(200, 200);
    // setStyleSheet("border:none");
    font.setPointSize(16);
    font.setFamily("Noto Sans");
    font.setBold(true);
    font.setWeight(75);
    setFont(font);
    // setStyleSheet("border : 0px");
    setText(text);
}
