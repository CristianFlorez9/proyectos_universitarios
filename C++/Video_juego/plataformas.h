/*#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H

#include <QObject>
#include <QObject>
#include <QGraphicsObject>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Plataformas : public QObject
 {
    Q_OBJECT

public:
    explicit Plataformas(QObject *parent = nullptr);




signals:

public slots:


protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);



private:
    QTimer *timer;
    QPixmap pixmap;
    float filas;
    float columnas;
    float ancho;
    float alto;
};


#endif // PLATAFORMAS_H
*/
