#ifndef NIVELESPERSECUCION_H
#define NIVELESPERSECUCION_H

#include <QDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGuiApplication>
#include <QRect>
#include <QVBoxLayout>

#include "ui_nivelespersecucion.h"
#include "morty.h"
#include "proyectilparabolico.h"
#include "enemigos.h"

class NivelesPersecucion : public QDialog {
    Q_OBJECT

public:
    NivelesPersecucion(QWidget *parent = nullptr);
    ~NivelesPersecucion();

    void agregarEnemigo();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::NivelesPersecucion *ui;
    Morty *morty;
    Enemigos *enemigos;
    QGraphicsScene *myScene;
    int x;
    int y;
    int ancho;
    int alto;

public slots:
     void enemigoAlcanzadoPorProyectilParabolico(QGraphicsItem *proyectil, QGraphicsItem *enemigo);
};

#endif // NIVELESPERSECUCION_H
