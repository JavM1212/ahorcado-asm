#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->easyButton->hide();
    ui->normalButton->hide();
    ui->hardButton->hide();
    ui->settingsBg_2->hide();
}

settings::~settings()
{
    delete ui;
}

void settings::showSet2()
{
    ui->settingsBg->hide();
    ui->easyButton->show();
    ui->normalButton->show();
    ui->hardButton->show();
    ui->settingsBg_2->show();
}

void settings::on_pushButton_clicked()
{
    this->gamemode = "s";
    showSet2();
}

void settings::on_pushButton_2_clicked()
{
    this->gamemode = "c";
    showSet2();
}

void settings::on_hardButton_clicked()
{
    hide();

    InGame gameUI(nullptr, this->gamemode, 3);
    gameUI.setModal(true);
    gameUI.exec();
    gameUI.gamemode = this->gamemode;
}


void settings::on_normalButton_clicked()
{
    hide();

    InGame gameUI(nullptr, this->gamemode, 2);
    gameUI.setModal(true);
    gameUI.exec();
    gameUI.gamemode = this->gamemode;
}


void settings::on_easyButton_clicked()
{
    hide();

    InGame gameUI(nullptr, this->gamemode, 1);
    gameUI.setModal(true);
    gameUI.exec();
    gameUI.gamemode = this->gamemode;
}

