// enemigos.h
#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QGraphicsItem>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Enemigos : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Enemigos(QObject *parent = nullptr);

    void setVelocidad(int velocidad);

private:
    QTimer *timer;

    QPixmap *pixmap;
    float ancho;
    float alto;
    int velocidadEnemigo = 5;

public slots:
    void Actualizacion();
    void actualizacion2();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // ENEMIGOS_H

