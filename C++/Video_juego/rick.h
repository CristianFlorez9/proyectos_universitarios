#ifndef RICK_H
#define RICK_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include "Fisicas.h"
#include<enemigos.h>
#include <items.h>



class Rick: public QGraphicsObject{
    Q_OBJECT

public:
    explicit Rick(QObject *parent = nullptr);
    void cambiarDirrecion(int numero);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int velocidad=15;
    int dirrecion;
    int masa=10; // Peso=masa por gravedad

    void verificarColisionConEnemigo();
    void verificarColisionConItem();

    QTimer *timer;
    QPixmap pixmap;
    int tecla;
    float filas;
    float columnas;
    float ancho;
    float alto;

signals:
    void ColisionRickEnemigo(QGraphicsItem *rick ,QGraphicsItem *enemigo);
    void colisionRickItem(QGraphicsItem *rick ,QGraphicsItem *item);

public slots:
    void actualizacion();




};

#endif // RICK_H

