#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>

namespace Ui {
class calculatorWidget;
}

class calculatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit calculatorWidget(QWidget *parent = 0);
    ~calculatorWidget();

public slots:
    void slot_NumberClicked();         //The slot function by clicked button "1,2,3,4,5,6,7,8,9,0,'+/-','.'".
    void slot_OperatorClicked();       //The slot function by clicked button "+,-,*,/,%".
    void slot_EqualClicked();          //The slot function by clicked button "=".
    void slot_ClearClicked();          //The slot function by clicked button "AC".

private:
    void AddToValue(QString &m_op,QString str);   //According to string "str", add character to reference string "m_op".
    int  GetType(QString tmpStr);                 //According to string "str",get the value of the variable "m_type".
    bool Calculate();                             //According to the variable "m_op1" and "m_op2" and "m_type",calculate result.
    void initialize();                            //initialize all private variables.
    void UpdateScreen(QString strFirst,QString strSecond,int symbol,QString strShow); //Update the text for four QLable objects.
    Ui::calculatorWidget *ui;
    QString m_op1;                     //Used to store the first operand.
    QString m_op2;                     //Used to store the second operand.
    QString tmp_m_op1,tmp_m_op2;       //Used to temporary store variable "m_op1" and "m_op2".
    bool    isFirst;                   //Used to indicate whether be operating the first number.
    int     m_type;                    //Used to store the type of operator.
};

#endif // CALCULATORWIDGET_H
