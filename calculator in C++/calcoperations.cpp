#include "calcoperations.h"
#include "calculator.h"
CalcOperations::CalcOperations()
{

}
void CalcOperations::NumbersPressed(){

    QPushButton *button = (QPushButton *)sender();
    QString butValue = button->text();
    QString displayValue = ui->Display->text();

    if((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){
        ui->Display->setText(butValue);

    } else {
        QString newValue = displayValue + butValue;
        double doublNewValue = newValue.toDouble();
        ui->Display->setText(QString::number( doublNewValue, 'g', 15));
    }
}

void CalcOperations::MathBtnPressed(){

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

void CalcOperations::EqualBtnPressed(){

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

void CalcOperations::ChangeNumbSign(){

    QString displayVal = ui->Display->text();


    QRegExp reg("[-+]?[0-9.]*");

    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}
