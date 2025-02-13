#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>

class Personajes : public QObject

{
   Q_OBJECT

   public:

       explicit Personajes(QObject *parent = nullptr);



       QTimer *timer;
       QPixmap *pixmap;

       float filas, columnas, ancho, alto;

       void cambiarFlecha(int numero);

       QRectF boundingRect();

       void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);




};

#endif // PERSONAJES_H


