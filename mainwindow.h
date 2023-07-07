#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_RightBracketButton_clicked();




    void on_actionNumberClicked_triggered();

    void digitClicked();

    void operatorClicked();

    void on_EqualButton_clicked();


    void on_pushButton_clicked();

    void on_DeleteButton_clicked();

    void on_MultiplyButton_clicked();

    void on_SquareButton_clicked();

    void on_SquareRootButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
