#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include "nivelesjump.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonJugarNivelesJump_clicked()
{
    qDebug()<<"Entrando a niveles de salto";

    NivelesJump nivelesJump;

    nivelesJump.setModal(true);
    nivelesJump.exec();
}



void MainWindow::on_pushButtonJugarNivelesPersecucion_clicked()
{
    qDebug()<<"Entrando a niveles de persecucion";

    NivelesPersecucion nivelesPersecucion;

    nivelesPersecucion.setModal(true);
    nivelesPersecucion.exec();
}

