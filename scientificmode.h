#ifndef SCIENTIFICMODE_H
#define SCIENTIFICMODE_H
#include "calculator.h"
#include "Display.h"
#include <QGridLayout>
#include <QVBoxLayout>
class calculator;
class scientificMode : public QMainWindow
{
    Q_OBJECT
public:
    scientificMode(QWidget *parent);
private:
    QWidget *window;
    Display *display;
    QGridLayout *layout;
    QVBoxLayout *displayAndButton;
    button *number;
    button *operation;

private slots:

};

#endif // SCIENTIFICMODE_H
