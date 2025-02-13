#ifndef PROYECTILPARABOLICO_H
#define PROYECTILPARABOLICO_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>

class ProyectilParabolico : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    ProyectilParabolico(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void movimientoParabolico();

    float gravedad=9.8;
    float tiempo=0;
    float velocidadInicial=20;

public slots:
    void moverParabolico();

signals :
    void proyectilParabolicoAlcanzoEnemigo(QGraphicsItem *Proyectil, QGraphicsItem *Enemigo);

};

#endif // PROYECTILPARABOLICO_H
