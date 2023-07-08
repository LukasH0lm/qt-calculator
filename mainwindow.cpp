#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <math.h>       /* sqrt */

#include <locale>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::cout.imbue(std::locale("en_US.utf8"));
    std::cin.imbue(std::locale("en_US.utf8"));

    QLocale::setDefault(QLocale::C);

    const char* locale = "C";
    std::locale::global(std::locale(locale));


    std::cout << "----------- Start of digit slot assigning -----------\n";

    QGridLayout* numbergrid = ui->numberGrid;

    for (double i = 0; i < numbergrid->count(); ++i){
        QLayoutItem *but = numbergrid->itemAt(i);

        std::cout << but->widget()->objectName().toStdString() << "\n";

        QWidget* widget = but->widget();


        QPushButton* button = qobject_cast<QPushButton *>(widget);

        if (button->objectName().toStdString() == "DotButton" ||
            button->objectName().toStdString() == "PercentButton"){
            continue;
        }

        button->setObjectName(button->text()); //sloppy but makes it easier later

        connect(button, SIGNAL(clicked()), this, SLOT(digitClicked()));


    }

    std::cout << "------------ End of digit slot assigning ------------\n";



    QGridLayout* operatorGrid = ui->operatorGrid;



    for (double i = 0; i < operatorGrid->count(); ++i){
        QLayoutItem *but = operatorGrid->itemAt(i);



        //std::cout << but->widget()->objectName().toStdString();
/*
        QWidget* widget = but->widget();


        QPushButton* button = qobject_cast<QPushButton *>(widget);



        button->setObjectName(button->text()); //sloppy but makes it easier later

        connect(button, SIGNAL(clicked()), this, SLOT(digitClicked()));

*/
    }

    QBoxLayout* plusMinusBox = ui->plusMinusBox;

    std::cout << "----------- Start of Operator slot assigning -----------\n";


    for (double i = 0; i < plusMinusBox->count(); ++i){
        QLayoutItem *but = plusMinusBox->itemAt(i);
        std::cout << but->widget()->objectName().toStdString() << "\n";

        QWidget* widget = but->widget();


        QPushButton* button = qobject_cast<QPushButton *>(widget);


        button->setObjectName(button->text()); //sloppy but makes it easier later

        connect(button, SIGNAL(clicked()), this, SLOT(operatorClicked()));


    }

    std::cout << "----------- Start of Operator slot assigning -----------\n";


    //ui->ResultLineEdit->setLocale(QLocale::English);

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool hasPreviousValue = false;

double previousValue = 0;

enum Operation {none, plus, minus, multiply, divide, modulus};

Operation currentOperation;

void checkIfZero(QLineEdit *resultBox);




// TODO
void MainWindow::on_RightBracketButton_clicked()
{

    QString currentString = ui->ResultLineEdit->text();

    ui->ResultLineEdit->setText(currentString);

}

void checkIfZero(QLineEdit* resultBox){

    double number = resultBox->text().toDouble();
    if (number == 0.0){
        resultBox->clear();
    }

}




void MainWindow::digitClicked(){

    QObject *senderObj = sender(); // This will give Sender object

    // This will give obejct name for above it will give "A", "B", "C"
    QString senderObjName = senderObj->objectName();



    std::cout << "\n" << senderObjName.toStdString() << " button clicked\n";





    double currentNumber = ui->ResultLineEdit->text().toDouble();

    if (currentNumber == 0.0){
        ui->ResultLineEdit->clear();
    }


    QString currentString = ui->ResultLineEdit->text();

    ui->ResultLineEdit->setText(currentString.append(senderObj->objectName()));




}


void MainWindow::operatorClicked(){

    QObject *senderObj = sender();

    std::string senderObjName = senderObj->objectName().toStdString();


    std::cout << senderObjName << " operator clicked\n";


    double currentValue = ui->ResultLineEdit->text().toDouble();

    double result;

    /*

    if (senderObjName == "+"){

        if (hasPreviousValue == true){
            result = previousValue + currentValue;

        }else{

        }

    }

    if (senderObjName == "-"){

        if (hasPreviousValue == true){
            result = previousValue + currentValue;
        }

    }*/


    /*if (hasPreviousValue == true){



        //ui->ResultLineEdit->setText(QString::fromStdString(std::to_string((double) result))); //temp conversion to make testing easier

    }else{*/

        previousValue = ui->ResultLineEdit->text().toDouble();
        hasPreviousValue = true;


        if (senderObjName == "+"){


            currentOperation = Operation::plus;
        }

        if (senderObjName == "-"){

            currentOperation = Operation::minus;

        }


        ui->ResultLineEdit->clear();



    //}





}



void MainWindow::on_EqualButton_clicked()
{


    std::cout << "= button clicked\n";

    QString text = ui->ResultLineEdit->text();

    double number = text.toDouble();


    double result;

    if (currentOperation == Operation::none){
            return;
    }

    if (currentOperation == Operation::plus){
        result = previousValue + number;
    }

    if (currentOperation == Operation::minus){
       result = previousValue - number;
    }

    if (currentOperation == Operation::multiply){
        result = previousValue * number;
    }

    if (currentOperation == Operation::divide){
        result = previousValue / number;
    }

    if (currentOperation == Operation::modulus){
        result = std::fmod(previousValue, number);
    }

    setResult(result);


}





void MainWindow::on_MultiplyButton_clicked()
{

    previousValue = ui->ResultLineEdit->text().toDouble();

    currentOperation = Operation::multiply;

    ui->ResultLineEdit->clear();

}

void MainWindow::on_DivideButton_clicked()
{

    previousValue = ui->ResultLineEdit->text().toDouble();

    currentOperation = Operation::divide;

    ui->ResultLineEdit->clear();

}


void MainWindow::on_ModButton_clicked()
{

    previousValue = ui->ResultLineEdit->text().toDouble();

    currentOperation = Operation::modulus;

    ui->ResultLineEdit->clear();

}




void MainWindow::on_SquareButton_clicked()
{

    std::cout << "square button clicked\n";

    double result = ui->ResultLineEdit->text().toDouble();

    result = result * result;

    setResult(result);

    currentOperation = Operation::none; //is this a good idea?

}


void MainWindow::on_SquareRootButton_clicked()
{

    std::cout << "square root button clicked\n";


    double input = ui->ResultLineEdit->text().toDouble();



    if (input >= 0.0){

    setResult(sqrt(input));

    currentOperation = Operation::none;

    }else{

    std::cout << "ERROR: CAN'T SQUARE NEGATIVE NUMBER\n";

    ui->ResultLineEdit->setText("Error");

    }

}




void MainWindow::setResult(double input){

    std::cout << "setting result to: " << input << "\n";

    double intpart;
    double fractionalpart = std::modf(input, &intpart);

    std::string str = std::to_string(input);

    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );

    ui->ResultLineEdit->setText(QString::fromStdString(str));

    /*
    if (fractionalpart == 0.0){
        ui->ResultLineEdit->setText(QString::fromStdString(std::to_string((int)intpart)));
    }else{
        ui->ResultLineEdit->setText(QString::fromStdString(std::to_string(input)));

    }*/


}


void MainWindow::on_PiButton_clicked()
{

    QString result = QString::fromStdString(std::to_string(M_PI));

    ui->ResultLineEdit->setText(result);

}


void MainWindow::on_DeleteButton_clicked()
{

    std::string text = ui->ResultLineEdit->text().toStdString();

    if (!text.empty()){
    text.pop_back();
    ui->ResultLineEdit->setText(QString::fromStdString(text));
    }


}




