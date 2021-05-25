#include "calculator.h"
#include "button.h"
#include <QApplication>
#include <QGridLayout>
#include <QStack>
#include <QChar>
#include <QKeyEventTransition>
#include <QDebug>

calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(400, 500);
    // setDisplay();
    display = new Display();
    setWindowTitle(QString("Calculator"));
    QAction *scientificMode = new QAction(QString("Scientific Mode"), this);
    switchMode = menuBar()->addMenu("Switch Mode");
    switchMode->addAction(scientificMode);
    connect(scientificMode, SIGNAL(triggered()), this, SLOT(openScientificMode()));
    window = new QWidget();
    layout = new QGridLayout();
    layout->setSpacing(0);
    internalString = "";
    setOperation();
    setNumpad();
    displayAndButton = new QVBoxLayout();
    displayAndButton->addWidget(display);
    displayAndButton->addLayout(layout);
    
    window->setLayout(displayAndButton);
    setCentralWidget(window);
    
}

calculator::~calculator()
{
    delete window;
}


void calculator::setNumpad(){
    
    number.push_back(new button(QString::fromStdString("±")));
    QObject::connect(number[0], SIGNAL(released()), this, SLOT(changeSignClicked()));
    number.push_back(new button(QString::number(0)));
    QObject::connect(number[1], SIGNAL(released()), this, SLOT(digitClicked()));
    number.push_back(new button(QString::fromStdString(".")));
    QObject::connect(number[2], SIGNAL(released()), this, SLOT(pointClicked()));


    for (int i = 1, j = 3; i < 10; i++, j++)
    {
        number.push_back(new button(QString::number(i)));
        QObject::connect(number[j], SIGNAL(released()), this, SLOT(digitClicked()));
        // QObject::connect(number[j], SIGNAL(QKeyEvent(Qt::N)), display, )
    }

    int x = 4;

    // setOperation();
    
    for (int i = 0, j = 0, k = 0; i < 4; i++, --x)
    {
        for (j = 0; j < 3; j++, ++k)
        {
            layout->addWidget(number[k], x, j);
        }
    }
    // layout->addWidget(operation[0], 0, 3);
    // layout->addWidget(operation[1], 0, 4);
    // layout->addWidget(operation[2], 1, 3);
    // layout->addWidget(operation[3], 1, 4);
    // layout->addWidget(operation[4], 2, 3, 2, 4);
    // layout->addWidget(operation[5], 3, 3, 3, 4);
}

// void calculator::setDisplay(){
//     display = new QLabel(this);
//     display->setText(QString::number(0));
//     display->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
//     // display->isRightToLeft();
//     display->setAlignment(Qt::AlignRight);
//     // display->setAlignment(Qt::AlignBottom);
//     // display->cur;
//     display->setStyleSheet("font : 28px");
// }

void calculator::setOperation(){
    operation[0] = new button(QString::fromStdString("AC"));
    operation[1] = new button(QString::fromStdString("C"));
    operation[2] = new button(QString::fromStdString("⌫"));
    operation[3] = new button(QString::fromStdString("/"));
    operation[4] = new button(QString::fromStdString("*"));
    operation[5] = new button(QString::fromStdString("-"));
    operation[6] = new button(QString::fromStdString("+"));
    operation[7] = new button(QString::fromStdString("="));
    for (int i = 3; i < 7; i++)
    {
        QObject::connect(operation[i], SIGNAL(released()), this, SLOT(operatorClicked()));
    }

    for (int i = 0; i < 4; i++)
    {
        layout->addWidget(operation[i], 0, i);
    }
    

    for (int i = 4, j = 1; i < 8; i++, ++j)
    {
        layout->addWidget(operation[i], j, 3);
    }

    QObject::connect(operation[1], SIGNAL(released()), this, SLOT(clearClicked()));
    QObject::connect(operation[2], SIGNAL(released()), this, SLOT(backspaceClicked()));
    QObject::connect(operation[7], SIGNAL(released()), this, SLOT(equalClicked()));
    QObject::connect(operation[0], SIGNAL(released()), this, SLOT(acClicked()));
    
}

void calculator::digitClicked(){
    double digit = display->text().toDouble();
    button *clickedButton = qobject_cast<button *>(sender());
    int pressedDigit = clickedButton->text().toInt();
    updateNumberDisplay(digit, pressedDigit);
    // if(waitingOperator){
    //     display->setText(display->text() + QString::number(pressedDigit));
    //     waitingOperator = true;
    //     return;
    // }
    // std::cout << "digit";
    
}

void calculator::clearClicked(){
    display->setText(QString::number(0));
    waitingOperator = true;
    internalString = "";
}

void calculator::operatorClicked(){
    button *pressedOperator = qobject_cast<button *>(sender());
    QString tmp = display->text();
    // qDebug() << tmp[(int)tmp.size() - 1];
    // if (tmp.size() >= 2)
    // {
    //     if((tmp[(int)tmp.size() - 1] == '-') && ((tmp[(int)tmp.size() - 2] == '-') || (tmp[(int)tmp.size() - 2] == '+') 
    //     || (tmp[(int)tmp.size() - 2] == '*') || (tmp[(int)tmp.size() - 2] == '/'))){
    //         internalString += "#";
    //     }
    // }
    updateOperatorDisplay(pressedOperator->text());
    // if (tmp[(int)tmp.size() - 1].isDigit())
    // {
    //     if (tmp.size() >= 1)
    //     {
    //         if ((tmp[(int)tmp.size() - 1] == '-') || (tmp[(int)tmp.size() - 1] == '+') 
    //         || (tmp[(int)tmp.size() - 1] == '*') || (tmp[(int)tmp.size() - 1] == '/'))
    //         {
    //             internalString += "#";
    //         }else
    //         {
    //             internalString += pressedOperator->text();
    //         }
    //     }
    // // qDebug() << internalString;
    //     // if (display->text() == "0")
    //     // {
    //     //     display->clear();
    //     //     display->setText(display->text() + pressedOperator->text());
    //     // }else
    //     // {
    //     display->setText(display->text() + pressedOperator->text());
    //     // }
    // }
    
    // waitingOperator = false;
}

void calculator::pointClicked(){
    button *point = qobject_cast<button *>(sender());
    display->setText(display->text() + '.');
    internalString += ".";
}

void calculator::acClicked(){
    QApplication::quit();
}

double applyOp(double val1, double val2, QChar op){
    switch (op.unicode())
    {
    case '+':
        return val1 + val2;
    
    case '-':
        return val1 - val2;

    case '*':
        return val1 * val2;

    case '/':
        return val1 / val2;

    default:
        break;
    }
    return 0;
}

int precedence(QChar op){
    if (op.unicode() == '+' || op.unicode() == '-')
    {
        return 1;
    }
    if (op.unicode() == '*' || op.unicode() == '/')
    {
        return 2;
    }
    return 2;
}

void calculator::equalClicked(){
    QStack<double> number;
    QStack<QChar> ops;
    qDebug() << internalString;
    number.push(0);
    // QString expression = display->text();
    QChar s = '0';
    for (int i = 0; i < internalString.length(); i++)
    {
        // qDebug() << number.top();
        if(internalString[i] == '#'){
            ++i;
            // qDebug() << "check";
            double val = 0;
            while ((i < internalString.length()) && (internalString[i].isDigit()))
            {
                val = (val*10) + internalString[i].digitValue();
                ++i;
            }
            number.push(-1*val);
            --i;
        }else if (internalString[i] == '(')
        {
            ops.push(internalString[i]);
        }else if (internalString[i].isDigit())
        {
            double val = 0;
            while ((i < internalString.length()) && (internalString[i].isDigit()))
            {
                val = (val*10) + internalString[i].digitValue();
                ++i;
            }
            number.push(val);
            --i;
        }else if (internalString[i] == ')')
        {
            while ((!ops.empty()) && (ops.top() != '('))
            {
                double val2 = number.pop();
                double val1 = number.pop();
                QChar op = ops.pop();
                number.push(applyOp(val1, val2, op));
            }
            if(!ops.empty()){
                ops.pop();
            }
        }else if(internalString[i] == '.'){
            int c = 0;
            double value = 0;
            while (internalString[++i].isDigit())
            {
                value = (value * 10) + internalString[i].digitValue();
                ++c;
            }
            --i;
            value /= pow(10, c);
            if(number.top() >= 0){
                value += number.top();
            }else{
                value -= number.top();
            }
            number.pop();
            // std::cout << value;
            number.push(value);
            std::cout << number.top();
            
        }else
        {
            while ((!ops.empty()) && (precedence(ops.top()) >= precedence(internalString[i])))
            {
                double val2 = number.top();
                number.pop();
                double val1 = number.top();
                number.pop();
                // std::cout << val1 << " " << val2;
                QChar op = ops.top();
                ops.pop();
                number.push(applyOp(val1, val2, op));
            }
            ops.push(internalString[i]);
            
        }
    }
    while (!ops.empty())
    {
        double val2 = number.top();
        number.pop();
        double val1 = number.top();
        number.pop();
        // std::cout << val1 << " " << val2;
        QChar op = ops.top();
        ops.pop();
        number.push(applyOp(val1, val2, op));
    }
        // std::cout << number.top();
        display->clear();
        display->setText(QString::number(number.top()));
        internalString = QString::number(number.top());
}

void calculator::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Backspace){
        // std::cout << event->text().toInt();
        // changeDisplay()
        // if(display->text().toDouble() == 0){
            // display->clear();
            backspaceClicked();
        // }
    }
    if ((event->key() == Qt::Key_0) || (event->key() == Qt::Key_1) || (event->key() == Qt::Key_2) || (event->key() == Qt::Key_3) || 
    (event->key() == Qt::Key_4) || (event->key() == Qt::Key_5) || (event->key() == Qt::Key_6) || (event->key() == Qt::Key_7) || 
    (event->key() == Qt::Key_8) || (event->key() == Qt::Key_9))
    {
        double digit = display->text().toDouble();
        int value = event->key() - 48;
        updateNumberDisplay(digit, value);
    }
    
    if(event->key() == Qt::Key_Period){
        // std::cout << "po";
        pointClicked();
    }

    if (event->key() == Qt::Key_Return)
    {
        equalClicked();
    }
    
    if ((event->key() == Qt::Key_Plus) || (event->key() == Qt::Key_Minus) || (event->key() == Qt::Key_Asterisk)
     ||(event->key() == Qt::Key_Slash))
    {
    // QString tmp = display->text();
    //     if (tmp.size() >= 1)
    // {
    //     if ((tmp[(int)tmp.size() - 1] == '-') || (tmp[(int)tmp.size() - 1] == '+') 
    //     || (tmp[(int)tmp.size() - 1] == '*') || (tmp[(int)tmp.size() - 1] == '/'))
    //     {
    //         internalString += "#";
    //     }else
    //     {
    //         internalString += event->key();
    //     }
        
    //     if (display->text() == "0")
    //     {
    //         display->clear();
    //         display->setText(display->text() + event->key());
    //     }else
    //     {
    //         display->setText(display->text() + event->key());
    //     }
        
    // }
    updateOperatorDisplay((QString)event->key());
    
    }
    

}

void calculator::updateNumberDisplay(double digit, int value){
    
    // qDebug() << digit;
    if((digit == 0)){
        if (waitingOperator)
        {
            display->clear();
            display->setText(display->text() + QString::number(value));
            waitingOperator = false;
        }else
        {
            display->setText(display->text() + QString::number(value));
        }
    }else{
        display->setText(display->text() + QString::number(value));
    }
    internalString += QString::number(value);
    // qDebug() << internalString;
}

void calculator::backspaceClicked(){
    QString digit = display->text();
    digit.chop(1);
    display->setText(digit);
    internalString.chop(1);

}

void calculator::updateOperatorDisplay(QString op){
    QString tmp = display->text();
    if (!tmp.isEmpty())
    {
        if (tmp[(int)tmp.size() - 1].isDigit())
        {
            // qDebug() << tmp[(int)tmp.size() - 1].isDigit();
            // if (tmp.size() >= 1)
            // {
            // if ((tmp[(int)tmp.size() - 1] == '-') || (tmp[(int)tmp.size() - 1] == '+') ||
            //  (tmp[(int)tmp.size() - 1] == '*') || (tmp[(int)tmp.size() - 1] == '/'))
            // {
            //     internalString += "#";
            //     qDebug() << internalString; 
            // }
            // else
            // {
                internalString += op;
            // }

            // }
            // qDebug() << internalString;
            // if (display->text() == "0")
            // {
            //     display->clear();
            //     display->setText(display->text() + pressedOperator->text());
            // }else
            // {
                qDebug() << "Checo";
            display->setText(display->text() + op);
            // }
        }
        else
        {
            tmp.chop(1);
            internalString.chop(1);
            internalString += op;
            display->setText(tmp + op);
        }
    }else
    {
        display->setText(op);
    }

        // display->setText(display->text() + event->key());
        waitingOperator = false;
}

void calculator::changeSignClicked(){
     QString tmp = display->text();
     QString pre = "";
    if ((tmp.size() == 1) && (tmp == "0"))
    {
        return;
    }
    
     int i = tmp.size() - 1, j = 0;
    // qDebug() << tmp.chop(3);
     while (i >= 0)
     {
        //  qDebug() << "xhexk";
         if (tmp[i].isDigit() || tmp[i] == '.')
         {
             pre = tmp[i] + pre;
             tmp.chop(1);
             internalString.chop(1);
             --i;
             continue;
         }
         break;
     }
    //  qDebug() << i;
    if (i > 0) 
    {
        if(tmp[i] == '-'){
            tmp.chop(1);
            internalString.chop(1);
            if (!tmp[i - 1].isDigit())
            {
                tmp += pre;
                internalString += pre;
            }else
            {
                tmp += "+" + pre;
                internalString += "+" + pre;
            }
        }else{
            //  tmp.chop(1);
            //  internalString.chop(1);
            internalString += "#" + pre;
            tmp += "-" + pre;
     }



    }else 
    {
        // if(tmp[0] == '-'){
        //     tmp.chop(1);
        //     internalString.chop(1);
        //     tmp += pre;
        //     internalString += pre;
        // }else{
        //     internalString += "#" + pre;
        //     tmp += "-" + pre;
        // }
        if (tmp.isEmpty())
        {
            internalString += "#" + pre;
            tmp += "-" + pre;
        }else
        {
            tmp.chop(1);
            internalString.chop(1);
            tmp += pre;
            internalString += pre;
        }
    }
    
    
     display->setText(tmp);
    //  qDebug() << pre;
}


void calculator::openScientificMode()
{
    scientificMode *window = new scientificMode(this);
    window->show();
    this->hide();

}