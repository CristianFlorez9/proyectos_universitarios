#include "nivelesjump.h"
#include "ui_nivelesjump.h"

NivelesJump::NivelesJump(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NivelesJump),

    rick(new Rick()),
    enemigo(new Enemigos()),
    diamante(new Items()),
    contadorLabel(new QLabel("Diamantes: 0")),  // Inicializamos el QLabel con el texto inicial
    contadorDiamantes(0)
{
    ui->setupUi(this);
    // Obtén las dimensiones de la pantalla principal
    QRect Desktop = QGuiApplication::primaryScreen()->geometry();
    x = Desktop.x();
    y = Desktop.y();
    ancho = Desktop.width() - 100;
    alto = Desktop.height() - 100;

    // Crea una escena gráfica con las dimensiones obtenidas
    scene = new QGraphicsScene(0, 0, ancho, alto);
    ui->graphicsView->setScene(scene);


    scene->addItem(rick);
    rick->setPos(200,700);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(contadorLabel);
    layout->addStretch();  // Agrega espacio flexible para centrar el QLabel en la ventana
    ui->graphicsView->setLayout(layout);
    // Ajustar el tamaño de la fuente para hacer el QLabel más grande

    contadorLabel->setFont(QFont("Arial", 16));  // Puedes ajustar el tamaño de la fuente según tus necesidades
    contadorLabel->setStyleSheet("color: white;");

    // O ajustar directamente el tamaño del QLabel
    contadorLabel->setFixedSize(200, 50);  // Puedes ajustar el ancho y alto según tus necesidades

    contadorLabel->setText("Diamantes: 0");






    connect(rick, &Rick::ColisionRickEnemigo, this, &NivelesJump::ColisionRickEnemigo);
    connect(rick, &Rick::colisionRickItem, this, &NivelesJump::colisionRickItem);

    QTimer *enemigoTimer = new QTimer(this);

    enemigoTimer->start(500);  // Llama a agregarEnemigo cada 300 milisegundos

    connect(enemigoTimer, &QTimer::timeout, this, &NivelesJump::agregarEnemigo);





    //////////////////////// agregar item

    QTimer *ItemTimer = new QTimer(this);
    ItemTimer->start(6000);
    connect(ItemTimer, &QTimer::timeout, this, &NivelesJump::agregarDiamante);

}

void NivelesJump::agregarEnemigo()
{
    Enemigos *enemigo = new Enemigos();
    scene->addItem(enemigo);

    // Posiciona el enemigo en una ubicación inicial
    // Puedes ajustar esto según tus necesidades
    enemigo->setPos(rand() % static_cast<int>(ancho), 0); // Posición aleatoria en la parte superior


}


void NivelesJump::agregarDiamante()
{
    Items *diamante = new Items();
    scene->addItem(diamante);

    // Posiciona el enemigo en una ubicación inicial
    // Puedes ajustar esto según tus necesidades
    diamante->setPos(rand() % static_cast<int>(ancho),rand() % static_cast<int>(alto)); // Posición aleatoria en la parte superior


}



// Función llamada cuando se presiona una tecla
void NivelesJump::keyPressEvent(QKeyEvent *event)
{
    // Manejo de las teclas de dirección para mover el personaje hacia un lado u otro
    if (event->key() == Qt::Key_D && rick->x() < ancho)
    {
        rick->cambiarDirrecion(300);  // Mover a la izquierda

        rick->verificarColisionConEnemigo();
        rick->verificarColisionConItem();
    }
    if (event->key() == Qt::Key_A && rick->x() > 0)
    {
        rick->cambiarDirrecion(100);  // Mover a la derecha
        rick->verificarColisionConEnemigo();
        rick->verificarColisionConItem();
    }

    if(event->key() == Qt::Key_W&& rick->y() > 0){
        rick->cambiarDirrecion(200);
        rick->verificarColisionConEnemigo();
        rick->verificarColisionConItem();
    }
    if(event->key()==Qt::Key_S && rick->y() < alto){
        rick->cambiarDirrecion(0);
        rick->verificarColisionConEnemigo();
        rick->verificarColisionConItem();
    }
}

// Función llamada cuando se presiona el botón del mouse
void NivelesJump::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Obtiene la posición actual de Rick
        QPointF rickPos = rick->pos();

        float dx = event->pos().x() - rickPos.x();
        float dy = event->pos().y() - rickPos.y();

        // Utiliza atan2 para calcular el ángulo en radianes y conviértelo a grados
        float angle = qRadiansToDegrees(qAtan2(dy, dx));

        // Ajusta el ángulo para que esté en el rango [0, 360)
        if (angle < 0)
        {
            angle += 360;
        }

        // Crea un proyectil con la dirección calculada
        Proyectil *disparo = new Proyectil(angle);
        scene->addItem(disparo);

        // Posiciona el proyectil en la posición actual de Rick
        disparo->setPos(rickPos);
        // Conéctate a la señal proyectilAlcanzoEnemigo

        connect(disparo, &Proyectil::proyectilAlcanzoEnemigo, this, &NivelesJump::enemigoAlcanzadoPorProyectil);


    }
}

void NivelesJump::enemigoAlcanzadoPorProyectil(QGraphicsItem *proyectil, QGraphicsItem *enemigo)
{
    // Elimina el proyectil y el enemigo de la escena
    scene->removeItem(proyectil);
    scene->removeItem(enemigo);

    // Libera la memoria ocupada por el proyectil y el enemigo
    delete proyectil;
    delete enemigo;


}

void NivelesJump::ColisionRickEnemigo(QGraphicsItem *rick, QGraphicsItem *enemigo)
{
    scene->removeItem(rick);
    scene->removeItem(enemigo);

    delete rick;
    delete enemigo;

    mostrarPantallaGameOver();
    close();

}
void NivelesJump::colisionRickItem(QGraphicsItem *rick, QGraphicsItem *item)
{
    contadorDiamantes += 1;
    qDebug() << "Diamantes: " << contadorDiamantes;

    // Actualizar el texto del QLabel con el nuevo valor del contador
    contadorLabel->setText("Diamantes: " + QString::number(contadorDiamantes));

    scene->removeItem(item);
    delete item;

    if (contadorDiamantes == 10) {
        mostrarPantallaGanador();
        close();
    }
}


void NivelesJump::mostrarPantallaGameOver()
{
    // Crear un cuadro de diálogo de mensaje con un botón "OK"
    QMessageBox mensaje;
    mensaje.setWindowTitle("Game Over");
    mensaje.setText("¡Has perdido! El juego ha terminado.");
    mensaje.setIcon(QMessageBox::Critical);
    mensaje.setStandardButtons(QMessageBox::Ok);

    // Mostrar el cuadro de diálogo y esperar a que se cierre
    mensaje.exec();
}

void NivelesJump::mostrarPantallaGanador()
{
    // Crear un cuadro de diálogo de mensaje con un botón "OK"
    QMessageBox mensaje;
    mensaje.setWindowTitle("GANADOR");
    mensaje.setText("¡HAS GANADO EL JUEGO! El juego ha terminado.");
        mensaje.setIcon(QMessageBox::Critical);
    mensaje.setStandardButtons(QMessageBox::Ok);

    // Mostrar el cuadro de diálogo y esperar a que se cierre
    mensaje.exec();
}


NivelesJump::~NivelesJump()
{
    delete ui;
}


