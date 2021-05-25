#include "Display.h"

Display::Display(){
    setText(QString::number(0));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setAlignment(Qt::AlignRight);
    // setAlignment(Qt::AlignBottom);
    // cur;
    setStyleSheet("font : 28px");
}