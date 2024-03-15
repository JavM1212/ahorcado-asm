#include "ingame.h"
#include "ui_ingame.h"
#include <iostream>
#include <QInputDialog>
extern "C" char* devolver_palabra(int indice, int difficult);
extern "C" bool* buscar_rellenar_letra(char letra);
extern "C" int get_all_letras_adivinadas();
extern "C" int get_intentos();
extern "C" int get_intentos_survival();
extern "C" void restart_section_data();
extern "C" void restart_survival_data();

/**
 * @brief Constructor de la clase InGame
*/
InGame::InGame(QWidget *parent, std::string gamemode, int difficulty) :
    QDialog(parent),
    ui(new Ui::InGame)
{
    //QString nombreUsuario = getNombreUsuario();
    //qDebug() << "Nombre de Usuario: " << nombreUsuario;

    puntaje= 100;
    this->gamemode = gamemode;
    this->difficulty = difficulty;
    ui->setupUi(this);
    this->restart_palabra(); // funciones que esconden labels de la interfaz
    this->restart_muneco();
    this->restart_hearts();
    this->restart_in_game_menu();
    this->restart_labels();


    rondas=0; //inicia rondas en 0, imprime +1 para que no se vea ronda 0
    std::string msg2 = "Ronda: " + std::to_string(this->rondas+1);
    QString str2 = QString::fromUtf8(msg2.c_str());
    this->ui->pushButton_34->setText(str2);

    if (gamemode == "c"){
        this->ui->label_24->show();
        this->ui->label_25->hide();
        cant_rondas = rondas_input("Introduce la cantidad de rondas que quieres jugar:");
    }

    cronometro_funcion();

    srand(static_cast<unsigned>(time(nullptr)));
    int numeroAleatorio = rand() %  8; // obtener numero aleatorio
    this->palabra_ptr = devolver_palabra(numeroAleatorio, difficulty); // obtener palabra elegida;

    if(this->difficulty == 1){
        this->ui->graphicsView_34->hide();
        this->ui->graphicsView_35->hide();
         this->doAction(' ');
    }
    else if(this->difficulty == 2){
        this->ui->graphicsView_35->hide();
          this->doAction(' ');
    }
}

/**
 * @brief Función para inicializar el cronómetro
*/
void InGame::cronometro_funcion(){

    cronometro = new QTimer(this);
    if (this->gamemode == "s") {
        segundos_restantes = 300;
        this->ui->pushButton_34->hide();
        this->ui->label_24->hide();
        this->ui->label_25->show();
    } else {
        segundos_restantes = 120;
        this->ui->label_24->show();
        this->ui->label_25->hide();
    }
    cronometro->setInterval(1000);  // Intervalo de actualización de 1 segundo
    connect(cronometro, &QTimer::timeout, this, &InGame::manejar_tiempo);
    connect(this, &InGame::tiempo_agotado, this, &InGame::manejar_tiempo_agotado);
    cronometro->start();
}

/**
 * @brief Destructor de la clase InGame
*/
InGame::~InGame() {
    delete ui;
}

int InGame::rondas_input(const QString& mensaje, int valorPredeterminado) {
    bool ok;
    int inputValue = QInputDialog::getInt(nullptr, "Entrada de usuario", mensaje, valorPredeterminado, -100, 100, 1, &ok);

    if (!ok) {
        qDebug() << "El usuario canceló la entrada.";
    }
    return inputValue;
}

/**
 * @brief Función para reiniciar la palabra
*/
void InGame::restart_palabra() {
    this->ui->label->setText("");
    this->ui->label_2->setText("");
    this->ui->label_3->setText("");
    this->ui->label_4->setText("");
    this->ui->label_5->setText("");
    this->ui->label_6->setText("");
    this->ui->label_7->setText("");
    this->ui->label_8->setText("");
}

/**
 * @brief Función para reiniciar el muneco
*/
void InGame::restart_muneco() {
    this->ui->graphicsView_5->hide();
    this->ui->graphicsView_6->hide();
    this->ui->graphicsView_7->hide();
    this->ui->graphicsView_8->hide();
    this->ui->graphicsView_9->hide();
    this->ui->graphicsView_10->hide();
    this->ui->graphicsView_11->hide();
    this->ui->graphicsView_20->show();
    this->ui->graphicsView_21->show();
    this->ui->graphicsView_22->show();
    this->ui->graphicsView_23->show();
    this->ui->graphicsView_24->show();
    this->ui->graphicsView_25->show();
    this->ui->graphicsView_26->show();
}

/**
 * @brief Función para reiniciar los corazones
*/
void InGame::restart_hearts() {
    this->ui->label_9->show();
    this->ui->label_10->show();
    this->ui->label_11->show();
    this->ui->label_12->show();
    this->ui->label_13->show();
    this->ui->label_14->hide();
    this->ui->label_15->hide();
    this->ui->label_16->hide();
    this->ui->label_17->hide();
    this->ui->label_18->hide();
}

/**
 * @brief Función para esconder el menú de pausa
*/
void InGame::restart_in_game_menu() {
    this->ui->graphicsView_16->hide();
    this->ui->pushButton_28->hide();
    this->ui->pushButton_29->hide();
    this->ui->pushButton_30->hide();
    this->ui->graphicsView_17->hide();
    this->ui->graphicsView_18->hide();
    this->ui->graphicsView_28->show();
    this->ui->graphicsView_29->show();
    this->ui->graphicsView_30->show();
    this->ui->graphicsView_31->show();
    this->ui->graphicsView_32->show();
    this->ui->graphicsView_33->show();
    this->ui->graphicsView_34->show();
    this->ui->graphicsView_35->show();
    if(this->difficulty == 1){
        this->ui->graphicsView_34->hide();
        this->ui->graphicsView_35->hide();
    }
    else if(this->difficulty == 2){
        this->ui->graphicsView_35->hide();
    }
}

/**
 * @brief Función para esconder mensajes de ganar o perder y botones de salir y reiniciar
*/
void InGame::restart_labels(){
    this->ui->label_20->hide();
    this->ui->label_21->hide();
    this->ui->label_22->hide();
    this->ui->label_20->hide();
    this->ui->label_24->hide();
    this->ui->pushButton_31->hide();
    this->ui->pushButton_32->hide();
}

/**
 * @brief Función para esconder el botón de pausa cuando se termina la partida
*/
void InGame::restart_menu(){
    this->ui->graphicsView_13->hide();
    this->ui->graphicsView_14->hide();
    this->ui->graphicsView_15->hide();
    this->ui->pushButton_27->hide();
}

/**
 * @brief Funcion para settear una posicion de las letras del ahorcado
*/
void InGame::setLetra(char letra, int pos) {
    std::string s(1, letra);
    QString str = QString::fromUtf8(s.c_str());

    switch(pos) {
    case 0:
        this->ui->label->setText(str);
        break;
    case 1:
        this->ui->label_2->setText(str);
        break;
    case 2:
        this->ui->label_3->setText(str);
        break;
    case 3:
        this->ui->label_4->setText(str);
        break;
    case 4:
        this->ui->label_5->setText(str);
        break;
    case 5:
        this->ui->label_6->setText(str);
        break;
    case 6:
        this->ui->label_7->setText(str);
        break;
    case 7:
        this->ui->label_8->setText(str);
        break;

    }
}

/**
 * @brief Funcion que controla si settear o no una letra
*/
bool InGame::update_letters(char letra) {
    bool fallido = true;

    for (int i = 0; i < 8; i++) {
        if (this->posiciones_encontradas[i] == 1) {
            fallido = false;
            this->setLetra(letra, i);
        }
    }

    return fallido;
}

/**
 * @brief Funcion para manejar el estado de la partida
*/
void InGame::doAction(char letra) {
    this->posiciones_encontradas = buscar_rellenar_letra(letra);
    bool fallido = update_letters(letra);

    if (fallido) {
        this->analizar_intentos();
    }
    else{
        int letrasAdivinadas = get_all_letras_adivinadas();
        if (letrasAdivinadas == 8) {
            puntaje += 100;  // Aumenta el puntaje solo cuando se adivina toda la palabra
            std::string msg = "Puntos: " + std::to_string(puntaje);
            QString str = QString::fromUtf8(msg.c_str());
            this->ui->pushButton_33->setText(str);
        }
    }
    this->revisar_estado_partida();
}

/**
 * @brief Función que revisa el estado de la partida, si se ganó o se perdió por intentos o tiempo
*/
void InGame::revisar_estado_partida(){
    int estado = get_all_letras_adivinadas();
    int intentos = get_intentos();
    if (estado == 8) { // gano

        if (this->gamemode == "s") {
            // agregar logica de almacenar puntaje
            this->restart_survival();
            this->puntaje += 1;
            std::string msg = "Puntos: " + std::to_string(this->puntaje);
            QString str = QString::fromUtf8(msg.c_str());
            this->ui->pushButton_33->setText(str);

        } else if (this->gamemode == "c"){
                this->puntaje += 1;
                std::string msg = "Puntos: " + std::to_string(this->puntaje);
                QString str = QString::fromUtf8(msg.c_str());
                this->ui->pushButton_33->setText(str);

                this->rondas += 1;
                std::string msg2 = "Ronda: " + std::to_string(this->rondas+1);
                QString str2 = QString::fromUtf8(msg2.c_str());
                this->ui->pushButton_34->setText(str2);

                this->cronometro->stop();
                this->restart_classic();

                if (rondas == cant_rondas){
                    this->cronometro->stop();
                    escribirPuntaje(getNombreUsuario(), puntaje);
                    this->restart_menu();
                    this->ui->label_20->show();
                    this->ui->pushButton_31->show();
                    this->ui->pushButton_32->show();
                }
                else if (rondas < cant_rondas){
                    this->restart_classic();
                }
            }
        }
    else if (estado < 8) {
        if (this->gamemode == "s") {
            if (intentos == 5){
                this->cronometro->stop();
                escribirPuntaje(getNombreUsuario(), puntaje);
                this->restart_menu();
                this->ui->label_21->show();
                this->ui->pushButton_31->show();
                this->ui->pushButton_32->show();
            }
        }
        else if (this->gamemode == "c") {
                if (intentos == 5) {
                    this->rondas += 1;
                    std::string msg2 = "Ronda: " + std::to_string(this->rondas+1);
                    QString str2 = QString::fromUtf8(msg2.c_str());
                    this->ui->pushButton_34->setText(str2);

                    this->cronometro->stop();
                    this->restart_classic();

                    if (rondas == cant_rondas){
                        this->cronometro->stop();
                        escribirPuntaje(getNombreUsuario(), puntaje);
                        this->restart_menu();
                        this->ui->label_20->show();
                        this->ui->pushButton_31->show();
                        this->ui->pushButton_32->show();
                    }
                }
        }
    }
    else if (!cronometro->isActive()) { // se acabo el tiempo
           this->manejar_tiempo_agotado();
    }
}

/**
 * @brief Función que analiza los intentos y muestra el progreso del muñeco
*/
void InGame::analizar_intentos() {
    int intentos = get_intentos();
    int intentos_survival = get_intentos_survival();
    if (intentos == 1) {
        this->ui->label_13->hide();
        this->ui->label_14->show();
    } else if (intentos == 2) {
        this->ui->label_12->hide();
        this->ui->label_15->show();
    } else if (intentos == 3) {
        this->ui->label_11->hide();
        this->ui->label_16->show();
    } else if (intentos == 4) {
        this->ui->label_10->hide();
        this->ui->label_17->show();
    } else if (intentos == 5) {
        this->ui->label_9->hide();
        this->ui->label_18->show();
    }

    if (intentos_survival == 1) {
        this->ui->graphicsView_5->show();
        this->ui->graphicsView_6->show();
        this->ui->graphicsView_7->show();
        this->ui->graphicsView_20->hide();
        this->ui->graphicsView_21->hide();
        this->ui->graphicsView_22->hide();
    } else if (intentos_survival == 2) {
        this->ui->graphicsView_8->show();
        this->ui->graphicsView_23->hide();
    } else if (intentos_survival == 3) {
        this->ui->graphicsView_9->show();
        this->ui->graphicsView_24->hide();
    } else if (intentos_survival == 4) {
        this->ui->graphicsView_11->show();
        this->ui->graphicsView_25->hide();
        this->ui->graphicsView_27->hide();
    } else if (intentos_survival == 5) {
        this->ui->graphicsView_10->show();
        this->ui->graphicsView_26->hide();
    }
}

/**
 * @brief Función que maneja el tiempo del cronómetro
*/
void InGame::manejar_tiempo() {
    segundos_restantes--;

    if (segundos_restantes >= 0) {
        int minutos = segundos_restantes / 60;
        int segundos = segundos_restantes % 60;

        this->ui->lcdNumber->display(QString("%1:%2")
                                         .arg(minutos, 2, 10, QChar('0'))
                                         .arg(segundos, 2, 10, QChar('0')));
        puntaje--;  // Disminuye el puntaje en 1 cada segundo
        std::string msg = "Puntos: " + std::to_string(puntaje);
        QString str = QString::fromUtf8(msg.c_str());
        this->ui->pushButton_33->setText(str);
    } else {
        emit tiempo_agotado();
    }
}

/**
 * @brief Función que muestra en pantalla que perdió por falta de tiempo
*/
void InGame::manejar_tiempo_agotado() {
    if (this->gamemode == "c"){
        this->rondas += 1;
        std::string msg2 = "Ronda: " + std::to_string(this->rondas+1);
        QString str2 = QString::fromUtf8(msg2.c_str());
        this->ui->pushButton_34->setText(str2);
        //this->cronometro->stop();
        this->restart_classic();

        if (rondas == cant_rondas){

            //this->cronometro->stop();
            escribirPuntaje(getNombreUsuario(), puntaje);
            this->restart_menu();
            this->ui->label_20->show();
            this->ui->pushButton_31->show();
            this->ui->pushButton_32->show();
        }
    }
        else{
            this->cronometro->stop();
            escribirPuntaje(getNombreUsuario(), puntaje);
            this->restart_menu();
            this->ui->label_22->show();
            this->ui->pushButton_31->show();
            this->ui->pushButton_32->show();
        }
}

/**
 * @brief Función que muestra el submenú de pausa
*/
void InGame::on_pushButton_27_clicked()
{
    this->cronometro->stop();
    this->ui->graphicsView_16->show();
    this->ui->pushButton_28->show();
    this->ui->pushButton_29->show();
    this->ui->pushButton_30->show();
    this->ui->graphicsView_28->hide();
    this->ui->graphicsView_29->hide();
    this->ui->graphicsView_30->hide();
    this->ui->graphicsView_31->hide();
    this->ui->graphicsView_32->hide();
    this->ui->graphicsView_33->hide();
    this->ui->graphicsView_34->hide();
    this->ui->graphicsView_35->hide();
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_clicked(){
    this->ui->pushButton->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton->setEnabled(false);
    this->doAction('a');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_2_clicked(){
    this->ui->pushButton_2->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_2->setEnabled(false);
    this->doAction('p');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_3_clicked(){
    this->ui->pushButton_3->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_3->setEnabled(false);
    this->doAction('l');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_4_clicked(){
    this->ui->pushButton_4->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_4->setEnabled(false);
    this->doAction('b');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_5_clicked(){
    this->ui->pushButton_5->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_5->setEnabled(false);
    this->doAction('r');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_6_clicked(){
    this->ui->pushButton_6->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_6->setEnabled(false);
    this->doAction('g');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_7_clicked(){
    this->ui->pushButton_7->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_7->setEnabled(false);
    this->doAction('c');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_8_clicked(){
    this->ui->pushButton_8->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_8->setEnabled(false);
    this->doAction('d');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_9_clicked(){
    this->ui->pushButton_9->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_9->setEnabled(false);
    this->doAction('e');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_10_clicked(){
    this->ui->pushButton_10->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_10->setEnabled(false);
    this->doAction('f');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_11_clicked(){
    this->ui->pushButton_11->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_11->setEnabled(false);
    this->doAction('h');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_12_clicked(){
    this->ui->pushButton_12->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_12->setEnabled(false);
    this->doAction('i');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_13_clicked(){
    this->ui->pushButton_13->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_13->setEnabled(false);
    this->doAction('j');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_14_clicked(){
    this->ui->pushButton_14->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_14->setEnabled(false);
    this->doAction('k');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_15_clicked(){
    this->ui->pushButton_15->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_15->setEnabled(false);
    this->doAction('m');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_16_clicked(){
    this->ui->pushButton_16->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_16->setEnabled(false);
    this->doAction('n');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_17_clicked(){
    this->ui->pushButton_17->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_17->setEnabled(false);
    this->doAction('o');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_18_clicked(){
    this->ui->pushButton_18->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_18->setEnabled(false);
    this->doAction('q');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_19_clicked(){
    this->ui->pushButton_19->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_19->setEnabled(false);
    this->doAction('s');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_20_clicked(){
    this->ui->pushButton_20->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_20->setEnabled(false);
    this->doAction('t');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_21_clicked(){
    this->ui->pushButton_21->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_21->setEnabled(false);
    this->doAction('u');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_22_clicked(){
    this->ui->pushButton_22->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_22->setEnabled(false);
    this->doAction('v');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_23_clicked(){
    this->ui->pushButton_23->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_23->setEnabled(false);
    this->doAction('w');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_24_clicked(){
    this->ui->pushButton_24->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_24->setEnabled(false);
    this->doAction('x');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_25_clicked(){
    this->ui->pushButton_25->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_25->setEnabled(false);
    this->doAction('y');
}

/**
 * @brief Función para mostrar las letras del teclado de la interfaz
*/
void InGame::on_pushButton_26_clicked(){
    this->ui->pushButton_26->setStyleSheet("background-color: #Dcd8d6; border: 1px solid #Aaa7aa");
    this->ui->pushButton_26->setEnabled(false);
    this->doAction('z');
}

/**
 * @brief Función para reanudar el juego
*/
void InGame::on_pushButton_28_clicked()
{
    this->restart_in_game_menu();
    this->cronometro->start();
}

/**
 * @brief Función para reiniciar el juego
*/
void InGame::on_pushButton_29_clicked()
{
    if (this->gamemode=="c"){
        this->hide();
        this->~InGame();
        restart_section_data();
        InGame gameUI(nullptr, "c", this->difficulty);
        gameUI.setModal(true);
        gameUI.exec();
        gameUI.gamemode = "c";
    }
    else if (this->gamemode=="s"){
        this->hide();
        this->~InGame();
        restart_section_data();
        InGame gameUI(nullptr, "s", this->difficulty);
        gameUI.setModal(true);
        gameUI.exec();
        gameUI.gamemode = "s";
    }
}

/**
 * @brief Función para salir del juego
*/
void InGame::on_pushButton_30_clicked()
{
    this->hide();
    this->~InGame();
}

/**
 * @brief Función que hace llamado para reiniciar juego
*/
void InGame::on_pushButton_31_clicked()
{
    this->on_pushButton_29_clicked();
}

/**
 * @brief Función que hace llamado para salir del juego
*/
void InGame::on_pushButton_32_clicked()
{
    this->on_pushButton_30_clicked();
}

/**
 * @brief Función que hace llamado para reiniciar juego en modalidad survival
*/
void InGame::restart_survival() {
    this->restart_labels();
    this->restart_palabra();
    this->restart_muneco();
    this->restart_teclado();
    restart_survival_data();
    srand(static_cast<unsigned>(time(nullptr)));
    int numeroAleatorio = rand() %  8; // obtener numero aleatorio
    this->palabra_ptr = devolver_palabra(numeroAleatorio, this->difficulty); // obtener palabra elegida;
    if(this->difficulty == 1 || this->difficulty == 2){
    this->doAction(' ');
    }
}

/**
 * @brief Función que hace llamado para reiniciar juego en modalidad classic
*/
void InGame::restart_classic() {
    this->restart_labels();
    this->restart_palabra();
    this->restart_muneco();
    this->restart_teclado();
    this->restart_hearts();
    restart_section_data();

    if (cronometro->isActive()) {
    cronometro->stop();
    }

    cronometro_funcion();
    srand(static_cast<unsigned>(time(nullptr)));
    int numeroAleatorio = rand() %  8; // obtener numero aleatorio
    this->palabra_ptr = devolver_palabra(numeroAleatorio, this->difficulty); // obtener palabra elegida;
    if(this->difficulty == 1 || this->difficulty == 2){
    this->doAction(' ');
    }
}

/**
 * @brief Función que reinicia el teclado
*/
void InGame::restart_teclado() {
    this->ui->pushButton->setStyleSheet(styleSheet());
    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setStyleSheet(styleSheet());
    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton_3->setStyleSheet(styleSheet());
    this->ui->pushButton_3->setEnabled(true);
    this->ui->pushButton_4->setStyleSheet(styleSheet());
    this->ui->pushButton_4->setEnabled(true);
    this->ui->pushButton_5->setStyleSheet(styleSheet());
    this->ui->pushButton_5->setEnabled(true);
    this->ui->pushButton_6->setStyleSheet(styleSheet());
    this->ui->pushButton_6->setEnabled(true);
    this->ui->pushButton_7->setStyleSheet(styleSheet());
    this->ui->pushButton_7->setEnabled(true);
    this->ui->pushButton_8->setStyleSheet(styleSheet());
    this->ui->pushButton_8->setEnabled(true);
    this->ui->pushButton_9->setStyleSheet(styleSheet());
    this->ui->pushButton_9->setEnabled(true);
    this->ui->pushButton_10->setStyleSheet(styleSheet());
    this->ui->pushButton_10->setEnabled(true);
    this->ui->pushButton_11->setStyleSheet(styleSheet());
    this->ui->pushButton_11->setEnabled(true);
    this->ui->pushButton_12->setStyleSheet(styleSheet());
    this->ui->pushButton_12->setEnabled(true);
    this->ui->pushButton_13->setStyleSheet(styleSheet());
    this->ui->pushButton_13->setEnabled(true);
    this->ui->pushButton_14->setStyleSheet(styleSheet());
    this->ui->pushButton_14->setEnabled(true);
    this->ui->pushButton_15->setStyleSheet(styleSheet());
    this->ui->pushButton_15->setEnabled(true);
    this->ui->pushButton_16->setStyleSheet(styleSheet());
    this->ui->pushButton_16->setEnabled(true);
    this->ui->pushButton_17->setStyleSheet(styleSheet());
    this->ui->pushButton_17->setEnabled(true);
    this->ui->pushButton_18->setStyleSheet(styleSheet());
    this->ui->pushButton_18->setEnabled(true);
    this->ui->pushButton_19->setStyleSheet(styleSheet());
    this->ui->pushButton_19->setEnabled(true);
    this->ui->pushButton_20->setStyleSheet(styleSheet());
    this->ui->pushButton_20->setEnabled(true);
    this->ui->pushButton_21->setStyleSheet(styleSheet());
    this->ui->pushButton_21->setEnabled(true);
    this->ui->pushButton_22->setStyleSheet(styleSheet());
    this->ui->pushButton_22->setEnabled(true);
    this->ui->pushButton_23->setStyleSheet(styleSheet());
    this->ui->pushButton_23->setEnabled(true);
    this->ui->pushButton_24->setStyleSheet(styleSheet());
    this->ui->pushButton_24->setEnabled(true);
    this->ui->pushButton_25->setStyleSheet(styleSheet());
    this->ui->pushButton_25->setEnabled(true);
    this->ui->pushButton_26->setStyleSheet(styleSheet());
    this->ui->pushButton_26->setEnabled(true);
}


/**
 * @brief Función para conseguir el nombre del usuario
*/
QString InGame::getNombreUsuario() {
    bool ok;
    QString nombre = QInputDialog::getText(this, "Nombre de Usuario", "Introduce tu nombre:", QLineEdit::Normal, "", &ok);

    if (!ok || nombre.isEmpty()) {
    qDebug() << "El usuario canceló la entrada o no proporcionó un nombre.";
    }

    return nombre;
}

void InGame::escribirPuntaje(const QString& nombre, int puntaje) {
    QString rutaArchivo;
    if (this->gamemode == "c") {
    rutaArchivo = ":/scores/classicScores.txt";
    } else if (this->gamemode == "s") {
    rutaArchivo = ":/scores/survivalScores.txt";
    }

    // Crear una lista para almacenar los puntajes existentes en el archivo
    QList<QPair<QString, int>> puntajesExistentes;

    // Leer los puntajes existentes
    QFile archivo(rutaArchivo);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&archivo);
    while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList partes = linea.split(" - ");
            if (partes.length() == 2) {
                    QString nombreExistente = partes[0];
                    int puntajeExistente = partes[1].toInt();
                    puntajesExistentes.append(QPair<QString, int>(nombreExistente, puntajeExistente));
            }
    }
    archivo.close();
    } else {
    qDebug() << "Error al abrir el archivo de puntajes.";
    return;
    }

    // Actualizar el puntaje solo si es más alto que el puntaje existente
    if (puntajesExistentes.isEmpty() || puntaje > puntajesExistentes.last().second) {
    // Agregar el nuevo puntaje a la lista existente
    puntajesExistentes.append(QPair<QString, int>(nombre, puntaje));

    // Limpiar la lista y escribir la lista actualizada en el archivo
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&archivo);
            for (const auto& puntaje : puntajesExistentes) {
                    out << puntaje.first << " - " << puntaje.second << "\n";
            }
            archivo.close();
    } else {
            //qDebug() << "Error en la escritura: " << archivo.error();
    }
    }
}


