#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

//activate these slots when the buttons are excuted
private slots :
    void NumbersPressed();
    void MathBtnPressed();
    void EqualBtnPressed();
    void ChangeNumbSign();
    void Decimal();
    void ClearDisplay();




};


#endif // CALCULATOR_H
