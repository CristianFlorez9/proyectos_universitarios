// En el archivo items.cpp
#include "items.h"

Items::Items(QObject *parent) : QGraphicsObject()
{
    pixmap.load(":/Imagenes/diamanteY.png");

    // Dimensiones de cada una de las imágenes
    ancho = 60;
    alto = 60;
}

QRectF Items::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void Items::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(0, 0, pixmap);
}
