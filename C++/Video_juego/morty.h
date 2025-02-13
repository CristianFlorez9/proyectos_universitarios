#ifndef MORTY_H
#define MORTY_H

#include <QGraphicsObject>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Morty : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Morty(QObject *parent = nullptr);
    void cambiarDirrecion(int numero);

    int velocidad=15;
    int dirrecion;
    int masa=10; // Peso=masa por gravedad

signals:

public slots:
    void actualizacion();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



private:
    QTimer *timer;
    QPixmap pixmap;
    int tecla;
    float filas;
    float columnas;
    float ancho;
    float alto;
};

#endif // MORTY_H
