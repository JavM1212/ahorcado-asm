#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include  "ingame.h"
#include "inicio.h"

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_hardButton_clicked();

    void on_normalButton_clicked();

    void on_easyButton_clicked();

    void showSet2();


private:
    Ui::settings *ui;
    std::string gamemode;
};

#endif // SETTINGS_H
