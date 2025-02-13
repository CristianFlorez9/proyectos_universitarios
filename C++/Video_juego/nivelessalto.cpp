#include "nivelessalto.h"
#include "ui_nivelessalto.h"

NivelesSalto::NivelesSalto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NivelesSalto)
{
    ui->setupUi(this);
}

NivelesSalto::~NivelesSalto()
{
    delete ui;
}
