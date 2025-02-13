// Incluye los archivos de encabezado necesarios
#include "proyectil.h"
#include <QPainter>

// Constructor de la clase Proyectil
Proyectil::Proyectil(int direction, QObject *parent) : QObject(parent), direction(direction)
{
    // Establece la bandera para permitir la selección del proyectil
    setFlag(ItemIsSelectable);

    // Configura un temporizador para mover el proyectil
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Proyectil::mover);
    timer->start(50);  // Ajusta la velocidad del proyectil según sea necesario
}

// Define el rectángulo de colisión del proyectil
QRectF Proyectil::boundingRect() const
{
    return QRectF(0, 0, 10, 10);  // Ajusta el tamaño del proyectil según sea necesario
}

// Pinta el proyectil en la escena
void Proyectil::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::darkRed);  // Ajusta el color del proyectil según sea necesario
    painter->drawEllipse(boundingRect());
}



// Mueve el proyectil y verifica colisiones con enemigos
void Proyectil::mover()
{
    int velocidad = 35;
    float dx = velocidad * qCos(qDegreesToRadians(direction));
    float dy = velocidad * qSin(qDegreesToRadians(direction));
    setPos(x() + dx, y() + dy);
/////////////////////////////////////////////////////////////////////Parte de colisiones de proyectil con enemigos
    QList<QGraphicsItem *> items = collidingItems();

        foreach (QGraphicsItem *item, items) {

        if (item->type() == UserType && item->data(0).toInt() == UserType + 1) {

                emit proyectilAlcanzoEnemigo(this, item);
            return;
        }
        }
}










