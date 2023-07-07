#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QGridLayout* numbergrid = ui->numberGrid;

    for (int i = 0; i < numbergrid->count(); ++i){
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


    QGridLayout* operatorGrid = ui->operatorGrid;


    for (int i = 0; i < operatorGrid->count(); ++i){
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


    for (int i = 0; i < plusMinusBox->count(); ++i){
        QLayoutItem *but = plusMinusBox->itemAt(i);
        std::cout << but->widget()->objectName().toStdString() << "\n";

        QWidget* widget = but->widget();


        QPushButton* button = qobject_cast<QPushButton *>(widget);


        button->setObjectName(button->text()); //sloppy but makes it easier later

        connect(button, SIGNAL(clicked()), this, SLOT(operatorClicked()));


    }


}

MainWindow::~MainWindow()
{
    delete ui;
}


bool hasPreviousValue = false;

int previousValue = 0;

enum Operation {plus, minus, multiply, divide};

Operation currentOperation;

void checkIfZero(QLineEdit *resultBox);




// TODO
void MainWindow::on_RightBracketButton_clicked()
{

    QString currentString = ui->ResultLineEdit->text();

    ui->ResultLineEdit->setText(currentString);

}

void checkIfZero(QLineEdit* resultBox){

    float number = resultBox->text().toFloat();
    if (number == 0.0){
        resultBox->clear();
    }

}




void MainWindow::digitClicked(){

    QObject *senderObj = sender(); // This will give Sender object

    // This will give obejct name for above it will give "A", "B", "C"
    QString senderObjName = senderObj->objectName();



    std::cout << "\n" << senderObjName.toStdString() << " button clicked\n";





    float currentNumber = ui->ResultLineEdit->text().toInt();

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


    float currentValue = ui->ResultLineEdit->text().toFloat();

    float result;

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


    if (hasPreviousValue == true){



        ui->ResultLineEdit->setText(QString::fromStdString(std::to_string((int) result))); //temp conversion to make testing easier

    }else{

        previousValue = ui->ResultLineEdit->text().toInt();
        hasPreviousValue = true;


        if (senderObjName == "+"){


            currentOperation = Operation.plus;
        }

        if (senderObjName == "-"){

            currentOperation = Operation.minus;

        }


        ui->ResultLineEdit->clear();



    }





}



void MainWindow::on_actionNumberClicked_triggered()
{


    std::cout << senderSignalIndex();



}


void MainWindow::on_EqualButton_clicked()
{


    std::cout << "= button clicked\n";

    if (currentOperation == Operation.plus){


        QString text = ui->ResultLineEdit->text();

        int number = text.toInt();

        ui->ResultLineEdit->setText(QString(std.to_string(previousValue + number)));



    }


}




void MainWindow::on_pushButton_clicked()
{
    std::cout << "ahhh";
}

