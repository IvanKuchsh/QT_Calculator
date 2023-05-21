
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
    void SetCheckedOp();

private:
    Ui::MainWindow *ui;

private slots:
    void DigitsNumbers();
    void PlusOrMinusDigits();
    void MathOperations();
    void on_pushButton_dot_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_equally_clicked();
};

#endif // MAINWINDOW_H
