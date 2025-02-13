#ifndef FISICAS_H
#define FISICAS_H

#include <QTimer>
#include <cmath>

class Fisicas
{
public:
    Fisicas();

    const float gravedad=9.8;
    float tiempoParabola=0;
    float velocidadIni;
    float AnguloIni;
    float movimentoParabolicoX();
    float movimientoParabolicoY();
};

#endif // FISICAS_H
