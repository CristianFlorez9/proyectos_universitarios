#ifndef NIVELESJUMP_H
#define NIVELESJUMP_H

#include <QDialog>
#include <QGuiApplication>
#include <QGraphicsItem>
#include <QRectF>
#include <QDebug>
#include <QScreen>
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

#include "rick.h"
#include "plataformas.h"
#include "proyectil.h"
#include "enemigos.h"
#include "items.h"

namespace Ui {
class NivelesJump;
}

class NivelesJump : public QDialog
{
    Q_OBJECT

public:
    explicit NivelesJump(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void agregarEnemigo();
    void agregarDiamante();

    //void AgregarPlataforma();

    void mostrarPantallaGameOver();

    int contadorDiamantes=0;

    QLabel *contadorLabel;

    void mostrarPantallaGanador();


    ~NivelesJump();

private:
    Ui::NivelesJump *ui;
    QGraphicsScene *scene;

   Rick *rick;
   Enemigos *enemigo;
   Items *diamante;
   // Plataformas *plataforma;
    float x, y, ancho, alto;

public slots:
    void enemigoAlcanzadoPorProyectil(QGraphicsItem *proyectil, QGraphicsItem *enemigo);
    void ColisionRickEnemigo(QGraphicsItem *rick ,QGraphicsItem *enemigo);
    void colisionRickItem(QGraphicsItem *rick,QGraphicsItem *item);


};

#endif // NIVELESJUMP_H
