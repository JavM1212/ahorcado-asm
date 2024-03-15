#ifndef INGAME_H
#define INGAME_H

#include <QDialog>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <iostream>
#include "settings.h"
#include "string"

namespace Ui {
class InGame;
}

class InGame : public QDialog
{
    Q_OBJECT

public:
    std::string gamemode;
    int difficulty;
    explicit InGame(QWidget *parent = nullptr, std::string gamemode = "a", int difficulty = 2);
    ~InGame();
    void restart_palabra();
    void restart_muneco();
    void restart_hearts();
    void restart_in_game_menu();
    void restart_labels();
    void restart_menu();
    bool* posiciones_encontradas;
    char* palabra_ptr = new char[8];
    void setLetra(char letra, int pos);
    bool update_letters(char letra);
    void revisar_estado_partida();
    void get_ronda();
    QString getNombreUsuario();
    void escribirPuntaje(const QString& nombre, int puntaje);
    void doAction(char letra);
    void analizar_intentos();
    void manejar_tiempo();
    void manejar_tiempo_agotado();
    void restart_survival();
    void restart_classic();
    void restart_teclado();
    void cronometro_funcion();
    int rondas_input(const QString& mensaje, int valorPredeterminado = 0);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();


private:
    Ui::InGame *ui;
    int segundos_restantes;
    QTimer* cronometro;
    int puntaje;
    int cant_rondas;
    int rondas;
signals:
    void tiempo_agotado();
};


#endif // INGAME_H
