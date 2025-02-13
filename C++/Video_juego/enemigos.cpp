// enemigos.cpp
#include "enemigos.h"
#include <QPainter>

Enemigos::Enemigos(QObject *parent)
    : QObject{parent}
{
 // O cualquier otra configuración necesaria
    setData(0, QVariant(UserType + 1)); // Configura el tipo de usuario
    timer = new QTimer();

    ancho = 100;
    alto = 101;
    pixmap = new QPixmap(":/Imagenes/alien-sv-2_1 (1).png");

    timer->start(15);
    connect(timer, &QTimer::timeout, this, &Enemigos::Actualizacion);




}



QRectF Enemigos::boundingRect() const
{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}

void Enemigos::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-ancho / 2, -alto / 2, *pixmap, 0, 0, ancho, alto);
}
void Enemigos::setVelocidad(int velocidad) {
    // Validar la nueva velocidad según tus requerimientos, si es necesario
    velocidadEnemigo=velocidad;
}
void Enemigos::Actualizacion()
{
    setPos(x(), y() + velocidadEnemigo); // Movimiento hacia abajo en este ejemplo
}

void Enemigos::actualizacion2()
{
    setPos(x()+velocidadEnemigo,y());
}

