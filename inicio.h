#ifndef INICIO_H
#define INICIO_H

#include <QMainWindow>
#include <QDir>
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Inicio; }
QT_END_NAMESPACE

class Inicio : public QMainWindow
{
    Q_OBJECT

public:
    Inicio(QWidget *parent = nullptr);
    ~Inicio();

private slots:

    void on_startButton_clicked();

    void on_instButton_clicked();

    void on_closeButton_clicked();

    void on_creditsButton_clicked();

    void on_exitButton_clicked();

    void on_highscoresButton_clicked();

private:
    Ui::Inicio *ui;

};
#endif // INICIO_H
