#ifndef NIVELESPERSECUTION_H
#define NIVELESPERSECUTION_H

#include <QDialog>

namespace Ui {
class NivelesPersecution;
}

class NivelesPersecution : public QDialog
{
    Q_OBJECT

public:
    explicit NivelesPersecution(QWidget *parent = nullptr);
    ~NivelesPersecution();

private:
    Ui::NivelesPersecution *ui;
};

#endif // NIVELESPERSECUTION_H
