#ifndef SCIENTIFICMODE_H
#define SCIENTIFICMODE_H

#include <QMainWindow>
// #include <QObject>
#include <QWidget>

class scientificMode : public QMainWindow
{
    Q_OBJECT
public:
    scientificMode(QWidget *parent = nullptr);
    QWidget *window;
    QLabel * display;
};

#endif // SCIENTIFICMODE_H
