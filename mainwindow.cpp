#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QTimer"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));

    connect(ui->pushButton_plusOrMinus, SIGNAL(clicked()), this, SLOT(PlusOrMinusDigits()));
    connect(ui->pushButton_procent, SIGNAL(clicked()), this, SLOT(PlusOrMinusDigits()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(MathOperations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(MathOperations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(MathOperations()));
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(MathOperations()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

double numFirst;
QString currNum;
QString firstNum;

void MainWindow::SetCheckedOp() {
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_division->setChecked(false);
}

QString CheckActiveOp(Ui::MainWindow *ui) {
    if (ui->pushButton_plus->isChecked()) {
        return ui->pushButton_plus->text();
    }
    if (ui->pushButton_minus->isChecked()) {
        return ui->pushButton_minus->text();
    }
    if (ui->pushButton_mult->isChecked()) {
        return ui->pushButton_mult->text();
    }
    if (ui->pushButton_division->isChecked()) {
        return ui->pushButton_division->text();
    }
    return "";
};

double Result(Ui::MainWindow *ui, QPushButton* button = nullptr) {
    double first = firstNum.toDouble();
    double second = currNum.toDouble();

    if (ui->pushButton_plus->isChecked()) {
        first += second;
        ui->pushButton_plus->setChecked(false);

    }
    if (ui->pushButton_minus->isChecked()) {
        first -= second;
        ui->pushButton_minus->setChecked(false);
    }
    if (ui->pushButton_mult->isChecked()) {
        first *= second;
        ui->pushButton_mult->setChecked(false);
    }
    if (ui->pushButton_division->isChecked()) {
        if (second == 0) {
            ui->pushButton_division->setChecked(false);
            return 0;
        }
        first /= second;
        ui->pushButton_division->setChecked(false);
    }
    return first;
};

void MainWindow::DigitsNumbers() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    if (currNum.contains(".") && button->text() == "0") {
        currNum = currNum + button->text();
        if (firstNum.size() != 0) {
            QString op = CheckActiveOp(ui);
            ui->label_ans->setText(firstNum + " " + op + " " + currNum);
            return;
        }
        ui->label_ans->setText(currNum);
        return;
    }

    QString op = CheckActiveOp(ui);
    if (firstNum.size() != 0 && op == "") {
        currNum = firstNum;
        firstNum = "";
        currNum = currNum + button->text();
        ui->label_ans->setText(currNum);
        return;
    }
    currNum = currNum.size() == 0 || currNum == "0" ? button->text() : currNum + button->text();
    if (firstNum.size() != 0) {
        ui->label_ans->setText(firstNum + " " + op + " " + QString::number(currNum.toDouble(), 'g', 15));
        return;
    }
    ui->label_ans->setText(QString::number(currNum.toDouble(), 'g', 15));
}

void MainWindow::on_pushButton_dot_clicked() {
    QString op = CheckActiveOp(ui);
    if (firstNum.size() != 0 && op == "") {
        currNum = firstNum;
        firstNum = "";
    }
    if (currNum == "") {
        currNum = "0.";
    }
    if (!(currNum.contains("."))) {
        currNum += ".";
    }
    if (firstNum.size() != 0) {
        QString op = CheckActiveOp(ui);
        ui->label_ans->setText(firstNum + " " + op + " " + currNum);
    } else {
        ui->label_ans->setText(currNum);
    }
}

void MainWindow::PlusOrMinusDigits() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString op = CheckActiveOp(ui);
    if (firstNum.size() != 0 && op == "") {
        currNum = firstNum;
        firstNum = "";
    }
    double num = currNum.toDouble();

    if (button->text() == "+/-") {
        num *= -1;
    }
    if (button->text() == "%") {
        num *= 0.01;
    }
    currNum = QString::number(num, 'g', 15);
    if (firstNum.size() != 0) {
        QString op = CheckActiveOp(ui);
        ui->label_ans->setText(firstNum + " " + op + " " + currNum);
    } else {
        ui->label_ans->setText(currNum);
    }
}

QPushButton* prevOp = nullptr;

void MainWindow::MathOperations() {
    if (currNum.size() == 0 && firstNum.size() == 0) {
        SetCheckedOp();
        return;
    }
    QPushButton* button = static_cast<QPushButton*>(sender());
    if (prevOp != button) {
        prevOp = button;
        button->setChecked(false);
    } else {
        button->setChecked(true);
    }

    if (currNum.size() == 0 && firstNum.size() != 0) {
        SetCheckedOp();
        button->setChecked(true);
        ui->label_ans->setText(firstNum + " " + button->text());
        return;
    }

    if (currNum.size() == 0) {
        return;
    }

    if (firstNum.size() != 0) {
        double result = Result(ui);
        if (result == 0) {
            firstNum = "0";
            currNum = "";
            ui->label_ans->setText(firstNum + " " + button->text());
            button->setChecked(true);
            return;
        }
        firstNum = QString::number(result, 'g', 15);
    } else {
        firstNum = currNum;
    }
    ui->label_ans->setText(firstNum + " " + button->text());
    currNum = "";
    button->setChecked(true);
}

void MainWindow::on_pushButton_ac_clicked() {
    SetCheckedOp();
    currNum = "";
    firstNum = "";
    ui->label_ans->setText("0");
}

void MainWindow::on_pushButton_equally_clicked() {
    if (firstNum.size() == 0) {
        ui->label_ans->setText(currNum);
        return;
    }
    double result = Result(ui);
    ui->label_ans->setText(QString::number(result, 'g', 15));
    currNum = "";
    firstNum = result == 0 ? "" : QString::number(result, 'g', 15);
}
