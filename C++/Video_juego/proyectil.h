#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>


class Proyectil : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    int velocidad = 10;
    int direction; // Almacena la dirección del proyectil

    Proyectil(int direction, QObject *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void mover();


signals:
    void proyectilAlcanzoEnemigo(QGraphicsItem *Proyectil, QGraphicsItem *Enemigo);





};

#endif // PROYECTIL_H

