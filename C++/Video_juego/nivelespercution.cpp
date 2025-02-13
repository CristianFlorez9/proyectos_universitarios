#include "nivelespercution.h"
#include "ui_nivelespercution.h"

NivelesPercution::NivelesPercution(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NivelesPercution)
{
    ui->setupUi(this);
}

NivelesPercution::~NivelesPercution()
{
    delete ui;
}
