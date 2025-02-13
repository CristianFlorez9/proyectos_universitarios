#include "nivelespercution.h"
#include "ui_nivelespercution.h"

NivelesPercution::NivelesPersecution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NivelesJump)
{
    ui->setupUi(this);
}

NivelesPercution::~NivelesPersecution()
{
    delete ui;
}
