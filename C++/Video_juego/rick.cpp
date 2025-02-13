#include "rick.h"


Rick::Rick(QObject *parent) : QGraphicsObject()
{
    timer = new QTimer(this);
    filas = 0;
    columnas = 0;
    pixmap.load(":/Imagenes/Pocket_Mortys-Super_Fan_Rick-side1-1.7.1 (2).png");

    // Dimensiones de cada una de las imágenes
    ancho = 100;
    alto = 100;

    timer->start(150); // Tiempo en que se va a iterar sobre las imágenes

    connect(timer, &QTimer::timeout, this, &Rick::actualizacion);
}


void Rick::actualizacion()
{
    columnas += 100;
    if (columnas >= 400) {
        columnas = 0; // Esto significa que ya se salió de la imagen (columnas), por lo tanto, es necesario que empiece desde cero
    }

    update(-ancho / 2, -alto / 2, ancho, alto);
}

QRectF Rick::boundingRect() const
{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}

void Rick::cambiarDirrecion(int numero)
{
    switch (numero) {
    case 0://abajo
        dirrecion=numero;
        setPos(x(),y()+velocidad);
        break;
    case 100: // Derecha
        dirrecion  = numero;
        setPos(x() -velocidad, y());

        break;
    case 200: // Arriba
        dirrecion  = numero;
        setPos(x(), y()-velocidad);

        break;
    case 300://izquierda
        dirrecion=numero;
        setPos(x()+velocidad,y());

    default:
        break;
    }
}

void Rick::verificarColisionConEnemigo()
{
    // Obtén una lista de elementos en colisión con Rick
    QList<QGraphicsItem *> listaElementosEnColision = collidingItems();

    // Itera a través de la lista de elementos en colisión
    for (QGraphicsItem *item : listaElementosEnColision)
    {
        // Verifica si el elemento en colisión es una instancia de Enemigo
        Enemigos *enemigo = dynamic_cast<Enemigos *>(item);
        if (enemigo)
        {
            // Emite la señal de colisión, pasando Rick y el Enemigo como parámetros
            emit ColisionRickEnemigo(this, enemigo);
        }
    }
}

void Rick::verificarColisionConItem() {
    QList<QGraphicsItem *> listaElementosEnColision = collidingItems();

    // Itera a través de la lista de elementos en colisión
    for (QGraphicsItem *item : listaElementosEnColision) {
        // Verifica si el elemento en colisión es una instancia de Items
        Items *itemColisionado = dynamic_cast<Items *>(item);
        if (itemColisionado) {
            // Emite la señal de colisión, pasando Rick y el Item como parámetros
            emit colisionRickItem(this, itemColisionado);
        }
    }
}




void Rick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho / 2, -alto / 2, pixmap, columnas, dirrecion, ancho, alto);
}



