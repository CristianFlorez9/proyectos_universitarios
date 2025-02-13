/*"Este código implementa todas las funcionalidades que se mostraron en el video, además de incluir las funcionalidades relacionadas con el historial de partidas.
Estas últimas no se profundizaron en el video debido a limitaciones de tiempo, pero están completamente incorporadas en el código."*/

#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>


using namespace std;

class Tablero {
private:
    char tableroJuego[9][9];
    int fichasNegrasA=0;
    int fichasBlancasA=0;
    string ganadorA;


public:
    // Constructor
    Tablero() {
        inicializar();
    }


    void inicializar() {
        cout << "BIENVENIDO A OTHELLO" << endl;

        // Etiquetas de la primera fila (números del 1 al 8)
        for (int j = 0; j <= 8; j++) {

            tableroJuego[0][j] = '0'+j;
        }

        // Etiquetas de la primera columna (números del 1 al 8)


        for (int i = 1; i <= 8; i++) {
            tableroJuego[i][0] = '0' + i; //cambio a cha
        }

        // Inicializar el tablero
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                if ((i == 4 && j == 4) || (i == 5 && j == 5)) {
                    tableroJuego[i][j] = '+';
                } else if ((i == 5 && j == 4) || (i == 4 && j == 5)) {
                    tableroJuego[i][j] = '*';
                } else {
                    tableroJuego[i][j] = '_';
                }
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << tableroJuego[i][j]<<" "; // Imprimir un espacio en blanco y agregar un espacio
            }
            cout <<endl; // Saltar a la siguiente línea después de imprimir una fila completa
        }

    }




    int juegoterminado(){

        int contJugadas=0;

        for (int i = 1; i < 8; i++) {
            for (int j=1;j<8;j++){

                if (tableroJuego[i][j]!='_'){
                    contJugadas++;
                }

            }
        }
        return contJugadas;

    }




    int turnos(int turnoAnt){


        if(turnoAnt%2==0){
            return turnoAnt;

        }
        else if(turnoAnt%2!=0){
            return turnoAnt;



        }
    }

    bool jugadaValidaAndMovimientoSandwich(int fila, int columna, int turno) {
        char jugador;
        char adversario;
        if (turno % 2 != 0) {
            jugador = '*';
            adversario = '+';
        } else {
            jugador = '+';
            adversario = '*';
        }

        if (tableroJuego[fila][columna] != '_') {
            return false; // La casilla no está vacía
        }

        // Definir las 8 direcciones posibles (arriba, abajo, izquierda, derecha, diagonales)
        int dirFilas[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dirColumnas[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        /*dirFilas[i] y dirColumnas[i] son:
        {-1, -1}: Movimiento diagonal superior izquierda (-1 en fila, -1 en columna).
        {-1, 0}: Movimiento hacia arriba (-1 en fila, 0 en columna).
        {-1, 1}: Movimiento diagonal superior derecha (-1 en fila, 1 en columna).
        {0, -1}: Movimiento hacia la izquierda (0 en fila, -1 en columna).
        {0, 1}: Movimiento hacia la derecha (0 en fila, 1 en columna).
        {1, -1}: Movimiento diagonal inferior izquierda (1 en fila, -1 en columna).
        {1, 0}: Movimiento hacia abajo (1 en fila, 0 en columna).
        {1, 1}: Movimiento diagonal inferior derecha (1 en fila, 1 en columna).






            */
        bool movimientoValido = false;

        for (int i = 0; i < 8; i++) {
            int filaActual = fila + dirFilas[i];
            int columnaActual = columna + dirColumnas[i];

            bool hayFichasAdversarioEnLaDireccion = false;
            std::vector<std::pair<int, int>> fichasParaCambiar; // Almacena las fichas para cambiar en esta dirección

            while (filaActual >= 0 && filaActual < 8 && columnaActual >= 0 && columnaActual < 8) {
                if (tableroJuego[filaActual][columnaActual] == adversario) {
                    // Encontramos una ficha del adversario, marcamos que hay fichas adversarias en esta dirección
                    hayFichasAdversarioEnLaDireccion = true;
                    fichasParaCambiar.push_back(std::make_pair(filaActual, columnaActual));
                } else if (tableroJuego[filaActual][columnaActual] == jugador) {
                    // Encontramos una ficha propia, el movimiento es válido si hay fichas adversarias en esta dirección
                    if (hayFichasAdversarioEnLaDireccion) {
                        // Realizamos los cambios en el tablero
                        for (const auto& ficha : fichasParaCambiar) {
                            tableroJuego[ficha.first][ficha.second] = jugador;
                        }
                        tableroJuego[fila][columna] = jugador;
                        movimientoValido = true;
                    }
                    break;
                } else {
                    // Encontramos una casilla vacía, no hay un movimiento válido en esta dirección
                    break;
                }

                // Avanzamos en la dirección
                filaActual += dirFilas[i];
                columnaActual += dirColumnas[i];
            }

            if (movimientoValido) {
                break; // No es necesario verificar otras direcciones si ya encontramos un movimiento válido.
            }
        }

        return movimientoValido;
    }




    void colocarFicha() {
        int columna, fila, turnoAnt = 1;

        bool condTerminacionJue = true;

        while (condTerminacionJue) {
            int turno = turnos(turnoAnt);
            if (turno % 2 != 0) {
                cout << "Turno de las negras" << endl;

                cout << "Ingresa posicion donde quieras la ficha. ejemplo posicon (2,3) fila 2 columna 3):";
                cout << "fila:";
                cin >> fila;
                cout << "columna:";
                cin >> columna;
                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


                bool posibleJugada = jugadaValidaAndMovimientoSandwich(fila, columna,turno);

                if (posibleJugada) {

                    turnoAnt++;
                    //tableroJuego[fila][columna] = ficha;


                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            cout << tableroJuego[i][j] << " "; // Imprimir un espacio en blanco y agregar un espacio
                        }
                        cout << endl; // Saltar a la siguiente línea después de imprimir una fila completa


                    }
                }
                else {
                    cout << "JUGADA NO VALIDA, INTENTALO DE NUEVO" << endl;
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            cout << tableroJuego[i][j] << " "; // Imprimir un espacio en blanco y agregar un espacio
                        }
                        cout << endl; // Saltar a la siguiente línea después de imprimir una fila completa
                    }
                }
            }

            else{
                cout << "Turno de las Blancas" << endl;


                cout << "Ingresa posicion donde quieras la ficha. ejemplo posicon (2,3) fila 2 columna 3):";
                cout << "fila:";
                cin >> fila;
                cout << "columna:";
                cin >> columna;
                cout << "------------------------------------------------------------------------------------------------------------------------" << endl;



                bool posibleJugada = jugadaValidaAndMovimientoSandwich(fila, columna,turno);
                if (posibleJugada) {

                    turnoAnt++;



                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            cout << tableroJuego[i][j] << " "; // Imprimir un espacio en blanco y agregar un espacio
                        }
                        cout << endl; // Saltar a la siguiente línea después de imprimir una fila completa
                    }


                }
                else {
                    cout << "JUGADA NO VALIDA, INTENTALO DE NUEVO" << endl;
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            cout << tableroJuego[i][j] << " "; // Imprimir un espacio en blanco y agregar un espacio
                        }
                        cout << endl; // Saltar a la siguiente línea después de imprimir una fila completa
                    }
                }
            }
            int numeroDeJugadas=juegoterminado();
            if(numeroDeJugadas==64){
                condTerminacionJue=false;
            }
        }


    }




    int obtenerJugadorGanador() {
        int fichasNegras = 0;
        int fichasBlancas = 0;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (tableroJuego[i][j] == '*') {
                    fichasNegras++;
                } else if (tableroJuego[i][j] == '+') {
                    fichasBlancas++;
                }
            }
        }

        fichasBlancasA=fichasBlancas;
        fichasNegrasA=fichasNegras;

        cout << "Fichas Negras: " << fichasNegras << endl;
        cout << "Fichas Blancas: " << fichasBlancas << endl;

        if(fichasNegras>fichasBlancas){
            cout<<"El ganador son las fichas Negras"<<endl;
            string ganador="Negras";
            ganadorA=ganador;

        }
        if(fichasBlancas>fichasNegras){
            cout<<"El ganador son las fichas Blancas"<<endl;
            string ganador="Blancas";
            ganadorA=ganador;
        }
        if(fichasBlancas==fichasNegras){
            cout<<"Empate"<<endl;
            string ganador="Empate";
            ganadorA=ganador;
        }



    }


    int mostrarFichasBlancas(){
        int fichasBlancas=fichasBlancasA;
        return fichasBlancas;
    }

    int mostrarFichasNegras(){
        int fichasBlancas=fichasNegrasA;
        return fichasBlancas;
    }

    string mostrarGanador(){
        string ganador=ganadorA;
        return ganador;
    }



};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Partida {
    string fecha, hora, nombre, color, nombre2, color2, ganador;
    int cantidadFichas, cantidadFichas2;
};


class HistorialPartidas {
private:
    Partida* partidas;
    int capacidad;
    int cantidadPartidas;

public:
    HistorialPartidas() : partidas(nullptr), capacidad(300), cantidadPartidas(0) { ///nullptr inicializar un puntero desde, no se coloca cero para eviatr ambiguedade
        partidas = new Partida[capacidad];
    }

    ~HistorialPartidas() {
        delete[] partidas;
    }

    void agregarPartida(const Partida& partida) {
        // Verifica si la cantidad actual de partidas alcanzó la capacidad máxima.
        if (cantidadPartidas >= capacidad) {
            // Si es así, duplica la capacidad.
            capacidad *= 2;

            // Crea un nuevo arreglo dinámico de Partida con la nueva capacidad.
            Partida* temp = new Partida[capacidad];

            // Copia los elementos actuales al nuevo arreglo usando std::memcpy.
            // Esto implica copiar la memoria cruda de un lugar a otro.
            std::memcpy(temp, partidas, cantidadPartidas * sizeof(Partida));

            // Libera la memoria del arreglo antiguo.
            delete[] partidas;

            // Asigna el puntero del nuevo arreglo a la variable miembro partidas.
            partidas = temp;
        }

        // Agrega la nueva partida al final del arreglo.
        partidas[cantidadPartidas] = partida;

        // Incrementa el contador de la cantidad de partidas.
        cantidadPartidas++;
    }

    Partida* obtenerPartidas() const {  //funcion que develve un puntero al arrlego de partidas almacenadas
        return partidas;
    }

    int getCantidadPartidas() const { //const  porque no modifica el estado interno del objeto ,estado interno cambios en los atributos
        return cantidadPartidas;
    }

    void guardarPartidasEnArchivo() {
        string fecha, hora, nombre, color, nombre2, color2, ganador;
        int cantidadFichas, cantidadFichas2;

        std::ofstream archivo("C:\\Users\\ASUS\\Desktop\\archivoBmetodo1.txt", std::ios::app);// fue necesario colocar la ruta , por que de otro modo no se modificaba el archivo

        //ios app flujo de salida del archivo, es para que si el archivo ya exite los nuevos datsos se copien al final del archivo
        if (archivo.is_open()) {
            for (int i = 0; i < cantidadPartidas; ++i) {
                archivo << "Fecha: " << partidas[i].fecha << ", Hora: " << partidas[i].hora << "\n";
                archivo << "Jugador 1: " << partidas[i].nombre << ", Color: " << partidas[i].color << ", Cantidad de fichas: " << partidas[i].cantidadFichas << "\n";
                archivo << "Jugador 2: " << partidas[i].nombre2 << ", Color: " << partidas[i].color2 << ", Cantidad de fichas: " << partidas[i].cantidadFichas2 << "\n";
                archivo << "Ganador: " << partidas[i].ganador << "\n\n";
            }
            archivo.close();
            std::cout << "Historial de partidas guardado en historial_partidas.txt" << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo para guardar el historial de partidas." << std::endl;
        }
    }



    void imprimirArchivoTexto() {
        string nombreArchivo = "historial.txt";
        ifstream archivo("C:\\Users\\ASUS\\Desktop\\archivoBmetodo1.txt"); //abrir archivos
        cout<< "\n";
        cout<<"HISTORIAL"<<endl;
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl; //cerr , para error, solo para errores
            return;
        }

        string linea; //almacena cada una de las lineas del archivo
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }

        archivo.close();
    }

    int main() {
        imprimirArchivoTexto();

        return 0;
    }

};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void jugarPartida() {
    HistorialPartidas historial;
    string hora, fecha, nombre1, nombre2, fichaGanadora;
    int fichasNegras, fichasBlancas;

    cout << "Bienvenido a OTHELLO" << endl;

    cout << "Ingrese fecha: ";
    getline(cin, fecha);

    cout << "Ingrese hora, agregue Pm o Am o hora militar: ";
    getline(cin, hora);

    cout << "Ingrese jugador 1: ";
    getline(cin, nombre1);

    cout << "\n";

    cout << "Ingrese jugador 2: ";
    getline(cin, nombre2);


    cout << "Por defecto, jugador 1 con fichas blancas y jugador 2 con fichas negras" << endl;

    int verHistorial;

    cout << "Desea ver el historial de partidas? Ingrese 1 para verlo, o cualquier numero para jugar:";
    cin >> verHistorial;
    cout << "\n";
    if (verHistorial == 1) {
        historial.imprimirArchivoTexto();
    }

    bool valor = true;

    while (valor) {
        Tablero juego;

        juego.colocarFicha();
        juego.obtenerJugadorGanador();
        fichasBlancas = juego.mostrarFichasBlancas();
        fichasNegras = juego.mostrarFichasNegras();
        fichaGanadora = juego.mostrarGanador();

        Partida partida1 = {fecha, hora, nombre1, "negras", nombre2, "blancas", fichaGanadora, fichasNegras, fichasBlancas};
        historial.agregarPartida(partida1);
        historial.guardarPartidasEnArchivo();

        cout << "\n";
        cout << "\n";
        cout << "Para volver a jugar ingrese 1, para mirar el historial de partidas ingrese 2, para salir ingrese cualquier numero:";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            valor = true;
        } else if (opcion == 2) {
            historial.imprimirArchivoTexto();
            int opcion;
            cout << "\n";
            cout << "¿Quieres volver a jugar? Ingresa 1 para volver a jugar, cualquier numero para salir:" << endl;
                        cin >> opcion;
            if (opcion == 1) {
                valor = true;
            } else {
                valor = false;
            }
        } else {
            valor = false;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------







int main() {
    jugarPartida();
    return 0;
}
