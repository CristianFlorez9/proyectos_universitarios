#include "fisicas.h"

Fisicas::Fisicas()
{

}


float Fisicas::movimentoParabolicoX()
{
    float velocidadInicial = 80;
    float angulo = 45;
    float finalX;

    finalX=velocidadInicial * cos(angulo * M_PI / 180) * tiempoParabola;
    tiempoParabola+=1;

    return finalX;
}

float Fisicas::movimientoParabolicoY()
{
    float velocidadInicial = 80;
    float angulo = 45;
    float finalY;

   finalY = velocidadInicial * sin(angulo * M_PI / 180) * tiempoParabola- 0.5 * gravedad * pow(tiempoParabola, 2);

    return finalY;
}
