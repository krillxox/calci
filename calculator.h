#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "button.h"
#include "scientificmode.h"
#include "Display.h"
#include "QLineEdit"
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QMenuBar>
#include <bits/stdc++.h>
class calculator : public QMainWindow
{
    Q_OBJECT;

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private:
    // QStringList number;
    Display *display;
    QMenu *switchMode;
    QGridLayout *layout;
    QVBoxLayout *displayAndButton;
    std::vector<button *> number;
    button *operation[8];
    QString internalString;
    QWidget *window;
    void setNumpad();
    void setDisplay();
    void updateNumberDisplay(double digit, int value);
    void updateOperatorDisplay(QString op);
    void setOperation();
    bool waitingOperator = true;
    void keyPressEvent(QKeyEvent *event);
public slots:
    void digitClicked();
    void clearClicked();
    void operatorClicked();
    void pointClicked();
    void acClicked();
    void equalClicked();
    void backspaceClicked();
    void changeSignClicked();
    void openScientificMode();
};
#endif // CALCULATOR_H
