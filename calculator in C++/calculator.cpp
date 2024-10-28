#include "calculator.h"
#include "ui_calculator.h"

#include "QFile"
#include "QFileDialog"

//store calculator current value
double calcValue = 0.0;
bool userIsTypingSecondNumber = false;
//define last clicked mathbtn
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    //diplay values
    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10];

    for(int i = 0; i < 10; ++i){
            QString buttonName = "Btn" + QString::number(i);
            numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);

            connect(numButtons[i], SIGNAL(released()), this,
                    SLOT(NumbersPressed()));
        }




        connect(ui->BtnAdd, SIGNAL(released()), this,
                SLOT(MathBtnPressed()));
        connect(ui->BtnSubstract, SIGNAL(released()), this,
                SLOT(MathBtnPressed()));
        connect(ui->BtnMultiply, SIGNAL(released()), this,
                SLOT(MathBtnPressed()));
        connect(ui->BtnDivide, SIGNAL(released()), this,
                SLOT(MathBtnPressed()));
        connect(ui->BtnEqual, SIGNAL(released()), this,
                SLOT(EqualBtnPressed()));
        connect(ui->ChangeSign, SIGNAL(released()), this,
                SLOT(ChangeNumbSign()));
        connect(ui->BtnDot, SIGNAL(released()), this,
                SLOT(Decimal()));
        connect(ui->BtnClear, SIGNAL(released()), this,
                SLOT(ClearDisplay()));


}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumbersPressed(){

    QPushButton *button = (QPushButton *)sender();

    double labelMember;
    QString newLabel;

    if((ui->BtnAdd->isChecked() || ui->BtnSubstract->isChecked() || ui->BtnMultiply->isChecked() ||
        ui->BtnMultiply->isChecked()) && (!userIsTypingSecondNumber))
    {
        labelMember = button->text().toDouble();
        newLabel = QString::number(labelMember,'g',15);
        userIsTypingSecondNumber = true;

    }
    else
    {
        if(ui->Display->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->Display->text() + button->text();
        }
        else
        {
            labelMember =  (ui->Display->text() + button->text()).toDouble();
            newLabel = QString::number(labelMember,'g',15);
        }
    }

    ui->Display->setText(newLabel);

//    QString butValue = button->text();
//    QString displayValue = ui->Display->text();

//    if((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){
//        ui->Display->setText(butValue);

//    } else {
//        QString newValue = displayValue + butValue;
//        double doublNewValue = newValue.toDouble();
//        ui->Display->setText(QString::number( doublNewValue, 'g', 15));
//    }
}

void Calculator::MathBtnPressed(){

    // delete privios cliked values
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayValue = ui->Display->text();
    calcValue = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butValue = button->text();

    if(QString::compare(butValue, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butValue, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butValue, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }

    // Clear display
    ui->Display->setText("");

}

void Calculator::EqualBtnPressed(){

    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger ){
        if(addTrigger){
            solution = calcValue + dblDisplayVal;
        } else if(subTrigger){
            solution = calcValue - dblDisplayVal;
        } else if(multTrigger){
            solution = calcValue * dblDisplayVal;
        } else {
            solution = calcValue / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));

}

void Calculator::ChangeNumbSign(){

    QString displayVal = ui->Display->text();


    QRegExp reg("[-+]?[0-9.]*");

    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}

void Calculator::Decimal(){

    ui->Display->setText(ui->Display->text() + ".");
}

void Calculator::ClearDisplay(){

    ui->Display->setText("0");
}

