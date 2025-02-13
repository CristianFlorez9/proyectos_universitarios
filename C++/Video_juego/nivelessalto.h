#ifndef NIVELESSALTO_H
#define NIVELESSALTO_H

#include <QWidget>

namespace Ui {
class NivelesSalto;
}

class NivelesSalto : public QWidget
{
    Q_OBJECT

public:
    explicit NivelesSalto(QWidget *parent = nullptr);

    ~NivelesSalto();

private:
    Ui::NivelesSalto *ui;
};

#endif // NIVELESSALTO_H
