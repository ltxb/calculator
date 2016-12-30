#include "calculatorwidget.h"
#include "ui_calculatorwidget.h"

calculatorWidget::calculatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calculatorWidget)
{
    ui->setupUi(this);
    connect(ui->pB_0,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_1,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_2,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_3,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_4,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_5,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_6,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_7,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_8,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_9,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_dot,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));
    connect(ui->pB_sign,SIGNAL(clicked()),this,SLOT(slot_NumberClicked()));

    connect(ui->pB_add,SIGNAL(clicked()),this,SLOT(slot_OperatorClicked()));
    connect(ui->pB_sub,SIGNAL(clicked()),this,SLOT(slot_OperatorClicked()));
    connect(ui->pB_multiply,SIGNAL(clicked()),this,SLOT(slot_OperatorClicked()));
    connect(ui->pB_divide,SIGNAL(clicked()),this,SLOT(slot_OperatorClicked()));
    connect(ui->pB_residue,SIGNAL(clicked()),this,SLOT(slot_OperatorClicked()));

    connect(ui->pB_equal,SIGNAL(clicked()),this,SLOT(slot_EqualClicked()));

    connect(ui->pB_clear,SIGNAL(clicked()),this,SLOT(slot_ClearClicked()));

    initialize();//初始化m_op1,m_op2,m_step,m_type;
}

calculatorWidget::~calculatorWidget()
{
    delete ui;
}

void calculatorWidget::slot_NumberClicked()
{
    QObject *tmpObj=sender();
    QString tmpStr=tmpObj->objectName();
    tmpStr=tmpStr.remove("pB_");
    if(isFirst)
    {
        AddToValue(m_op1,tmpStr);
        UpdateScreen(m_op1,m_op2,m_type,m_op1);
    }
    else
    {
        AddToValue(m_op2,tmpStr);
        UpdateScreen(m_op1,m_op2,m_type,m_op2);
    }
}

void calculatorWidget::AddToValue(QString &m_op,QString str)
{
    if(str=="dot")
    {
        if(m_op.contains("."))
            UpdateScreen(m_op1,m_op2,m_type,m_op1);
        else if(m_op=="")
            m_op="0.";
        else if(m_op=="-")
            m_op="-0.";
        else
            m_op+=".";
    }
    else if(str=="sign")
    {
        if(m_op[0]=='-')
            m_op.remove('-');
        else
            m_op.insert(0,'-');
    }
    else
    {
        if(m_op=="0")
            m_op=str;
        else if(m_op=="-0")
            m_op="-"+str;
        else
            m_op+=str;
    }
}

void calculatorWidget::slot_OperatorClicked()
{
    QObject *tmpObj=sender();
    QString tmpStr=tmpObj->objectName();
    if(m_op1=="-"||m_op1=="")
        tmp_m_op1=m_op1;
    else if(isFirst)
    {
        isFirst=false;
        m_type=GetType(tmpStr);
        UpdateScreen(m_op1,m_op2,m_type,m_op1);
    }
    else if(m_op1!=""&&m_op2=="")
    {
        m_type=GetType(tmpStr);
        UpdateScreen(m_op1,m_op2,m_type,m_op1);
    }
    else if(m_op2!="")
    {
        bool isOk=Calculate();
        if(isOk)
        {
            m_type=GetType(tmpStr);
            UpdateScreen(m_op1,m_op2,m_type,m_op1);
        }
        else
        {
            UpdateScreen("!","!",6,"operation error!");
        }
    }   
}

int  calculatorWidget::GetType(QString tmpStr)
{
    int x;
    if(tmpStr=="pB_add")
        x=1;
    else if(tmpStr=="pB_sub")
        x=2;
    else if(tmpStr=="pB_multiply")
        x=3;
    else if(tmpStr=="pB_divide")
        x=4;
    else
        x=5;
    return x;
}

void  calculatorWidget::slot_EqualClicked()
{
    if(m_op1!=""&&m_op2!="")
    {
        bool isOk=Calculate();
        if(isOk)
        {
            tmp_m_op2+=" =";
            UpdateScreen(tmp_m_op1,tmp_m_op2,m_type,m_op1);
        }
        else
            UpdateScreen("!","!",6,"operation error!");
        initialize();
    }
}

bool calculatorWidget::Calculate()
{
    double op1=m_op1.toDouble();
    double op2=m_op2.toDouble();
    double result=0;
    switch (m_type)
    {
        case 1:result=op1+op2;break;
        case 2:result=op1-op2;break;
        case 3:result=op1*op2;break;
        case 4:
        {
            if(op2!=0)
            {
                result=op1/op2;
                break;
            }
            else
            {
                initialize();
                return false;
            }
        }
        case 5:
        {
            if(!m_op1.contains(".")&&!m_op2.contains(".")&&op2!=0)
            {
                int x=m_op1.toInt();
                int y=m_op2.toInt();
                result=x%y;
            }
            else
            {
                initialize();
                return false;
            }
            break;
        }
    }
    tmp_m_op1=m_op1;
    tmp_m_op2=m_op2;
    m_op1=QString::number(result,'g',15);
    m_op2="";
    return true;
}

void calculatorWidget::slot_ClearClicked()
{
    initialize();
    UpdateScreen(m_op1,m_op2,m_type,"");
}

void calculatorWidget::initialize()
{
    m_op1="";
    m_op2="";
    isFirst=true;
    m_type=0;
    tmp_m_op1=m_op1;
    tmp_m_op2=m_op2;
}

void calculatorWidget::UpdateScreen(QString strFirst,QString strSecond,int symbol,QString strShow)
{
    ui->label_first->setText(strFirst);
    ui->label_second->setText(strSecond);
    ui->lable_show->setText(strShow);
    if(symbol==0)
        ui->label_symbol->setText("");
    else if(symbol==1)
        ui->label_symbol->setText("+");
    else if(symbol==2)
        ui->label_symbol->setText("-");
    else if(symbol==3)
        ui->label_symbol->setText("*");
    else if(symbol==4)
        ui->label_symbol->setText("/");
    else if(symbol==5)
        ui->label_symbol->setText("%");
    else
        ui->label_symbol->setText("!");
}
