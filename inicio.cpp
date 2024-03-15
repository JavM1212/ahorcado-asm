#include "inicio.h"
#include "ui_inicio.h"
#include <QPixmap>
#include <QFile>
#include <iostream>

using namespace std;

Inicio::Inicio(QWidget *parent) : QMainWindow(parent), ui(new Ui::Inicio) {
    ui->setupUi(this);
    on_closeButton_clicked();
}

Inicio::~Inicio() {
    delete ui;
}

/**
 * @brief Función para cambiar a pantalla de ajustes
*/
void Inicio::on_startButton_clicked() {
    hide();
    settings settingUI;
    settingUI.setModal(true);
    settingUI.exec();
}



/**
 * @brief Función para mostrar instrucciones
*/
void Inicio::on_instButton_clicked()
{
    this->ui->HowToPlay->show();
    this->ui->closeButton->show();
}



/**
 * @brief Función para ocultar informacion adicional
*/
void Inicio::on_closeButton_clicked()
{
    this->ui->HowToPlay->hide();
    this->ui->closeButton->hide();
    this->ui->Credits->hide();
    this->ui->Highscores->hide();
    this->ui->topClassic->hide();
    this->ui->midClassic->hide();
    this->ui->botClassic->hide();
    this->ui->topSurvival->hide();
    this->ui->midSurvival->hide();
    this->ui->botSurvival->hide();

}



/**
 * @brief Función para mostrar creditos
*/
void Inicio::on_creditsButton_clicked()
{
    this->ui->Credits->show();
    this->ui->closeButton->show();
}


/**
 * @brief Función para mostrar puntajes
*/
void Inicio::on_highscoresButton_clicked()
{
    QString topScoreCName;
    int topScoreC = 0;
    QString midScoreCName;
    int midScoreC = 0;
    QString botScoreCName;
    int botScoreC = 0;

    QString topScoreSName;
    int topScoreS = 0;
    QString midScoreSName;
    int midScoreS = 0;
    QString botScoreSName;
    int botScoreS = 0;

    QFile archivoC(":/scores/classicScores.txt");
    if (!archivoC.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "No se encontro el archivo" << endl;
    } else {
        QTextStream in(&archivoC);

        // Leer y procesar los nombres y números
        QString line1 = in.readLine();
        QStringList parts1 = line1.split(" - ");
        topScoreCName = parts1[0];
        topScoreC = parts1[1].toInt();

        QString line2 = in.readLine();
        QStringList parts2 = line2.split(" - ");
        midScoreCName = parts2[0];
        midScoreC = parts2[1].toInt();

        QString line3 = in.readLine();
        QStringList parts3 = line3.split(" - ");
        botScoreCName = parts3[0];
        botScoreC = parts3[1].toInt();

        archivoC.close();
    }

    QFile archivoS(":/scores/survivalScores.txt");
    if (!archivoS.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "No se encontro el archivo" << endl;
    } else {
        QTextStream in(&archivoS);

        // Leer y procesar los nombres y números
        QString line1 = in.readLine();
        QStringList parts1 = line1.split(" - ");
        topScoreSName = parts1[0];
        topScoreS = parts1[1].toInt();

        QString line2 = in.readLine();
        QStringList parts2 = line2.split(" - ");
        midScoreSName = parts2[0];
        midScoreS = parts2[1].toInt();

        QString line3 = in.readLine();
        QStringList parts3 = line3.split(" - ");
        botScoreSName = parts3[0];
        botScoreS = parts3[1].toInt();

        archivoS.close();
    }


    this->ui->topClassic->setText(topScoreCName + ": " + QString::number(topScoreC));
    this->ui->midClassic->setText(midScoreCName + ": " + QString::number(midScoreC));
    this->ui->botClassic->setText(botScoreCName + ": " + QString::number(botScoreC));

    this->ui->topSurvival->setText(topScoreSName + ": " + QString::number(topScoreS));
    this->ui->midSurvival->setText(midScoreSName + ": " + QString::number(midScoreS));
    this->ui->botSurvival->setText(botScoreSName + ": " + QString::number(botScoreS));

    this->ui->Highscores->show();
    this->ui->closeButton->show();
    this->ui->topClassic->show();
    this->ui->midClassic->show();
    this->ui->botClassic->show();
    this->ui->topSurvival->show();
    this->ui->midSurvival->show();
    this->ui->botSurvival->show();
}





/**
 * @brief Función para salir del juego
*/
void Inicio::on_exitButton_clicked()
{
    this->hide();
    this->~Inicio();
}

