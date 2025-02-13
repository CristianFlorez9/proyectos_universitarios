#include "morty.h"

Morty::Morty(QObject *parent) : QGraphicsObject()
{
    timer = new QTimer(this);
    filas = 0;
    columnas = 0;
    pixmap.load(":/Imagenes/SpriteMorty (1).png");

    // Dimensiones de cada una de las imágenes
    ancho = 100;
    alto = 100;

    timer->start(200); // Tiempo en que se va a iterar sobre las imágenes

    connect(timer, &QTimer::timeout, this, &Morty::actualizacion);
}


void Morty::actualizacion()
{
    columnas += 100;
    if (columnas >= 400) {
        columnas = 0; // Esto significa que ya se salió de la imagen (columnas), por lo tanto, es necesario que empiece desde cero
    }

    update(-ancho / 2, -alto / 2, ancho, alto);
}

QRectF Morty::boundingRect() const
{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}

void Morty::cambiarDirrecion(int numero)
{
   switch (numero) {

        case 100: // Derecha
            dirrecion  = numero;
            setPos(x() - velocidad, y());

            break;
        case 200: // Arriba
            dirrecion  = numero;
            setPos(x()+velocidad, y());

            break;

        default:
            break;
        }
}


void Morty::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho / 2, -alto / 2, pixmap, columnas, dirrecion, ancho, alto);
}



