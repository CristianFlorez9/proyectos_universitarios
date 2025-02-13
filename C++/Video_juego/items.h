// En el archivo items.h
#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <enemigos.h>

class Items : public QGraphicsObject{
    Q_OBJECT

public:
    explicit Items(QObject *parent = nullptr);

    QPixmap pixmap;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int ancho,alto; // Agrega la declaración de la variable filas
};

#endif // ITEMS_H


