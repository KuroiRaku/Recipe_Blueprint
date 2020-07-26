#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *background = new QWidget(this);
    background->setGeometry(0, 0, 700, 600);
    background->setStyleSheet("backgroud-image: url(/background/Hackathon_image.png)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

