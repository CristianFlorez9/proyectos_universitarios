#ifndef NIVELESPERCUTION_H
#define NIVELESPERCUTION_H

#include <QWidget>
#include <morty.h>

namespace Ui {
class NivelesPercution;
}

class NivelesPercution : public QWidget
{
    Q_OBJECT

public:
    explicit NivelesPercution(QWidget *parent = nullptr);
    ~NivelesPercution();

private:
    Ui::NivelesPercution *ui;
};

#endif // NIVELESPERCUTION_H
