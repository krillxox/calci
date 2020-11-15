#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include "button.h"
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
#include <bits/stdc++.h>
class calculator : public QMainWindow
{
    Q_OBJECT;

public:
    calculator(QWidget *parent = nullptr);
    // ~calculator();
private:
    // QStringList number;
    std::vector<button *> number;
    button *operation[8];
    QLabel *display;
    QString internalString;
    QWidget *window;
    QGridLayout *layout;
    QVBoxLayout *displayAndButton;
    void setNumpad();
    void setDisplay();
    void updateNumberDisplay(double digit, int value);
    void updateOperatorDisplay(QString op);
    void setOperation();
    bool waitingOperator = true;
    // bool eventFilter(QObject *object, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
private slots:
    void digitClicked();
    void clearClicked();
    void operatorClicked();
    void pointClicked();
    void acClicked();
    void equalClicked();
    void backspaceClicked();
    void changeSignClicked();
// protected:
//     bool eventFilter(QObject *obj, QEvent *event);
};
#endif // CALCULATOR_H
