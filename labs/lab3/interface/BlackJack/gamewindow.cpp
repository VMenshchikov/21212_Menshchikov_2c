#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "startwindow.h"
#include "./Factory/Factory.hpp"


#include <QPalette>
#include <QResizeEvent>

#include <iostream>
#include <regex>


gamewindow::gamewindow(StartWindow* start, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamewindow),
    startW(start)
{
    ui->setupUi(this);
    setPalette(CreatePalette(this->size(), "../resourses/table.jpg"));



}

gamewindow::~gamewindow()
{
    delete ui;
}

QPalette gamewindow::CreatePalette(const QSize& size, const char* img){
    QImage bkgnd(img);
    bkgnd = bkgnd.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p;
    p.setBrush(QPalette::Background, bkgnd);
    return p;
}

void gamewindow::resizeEvent(QResizeEvent *event){
    setPalette(CreatePalette(event->size(), "../resourses/table.jpg"));
    ui->verticalLayoutWidget->move(30, event->size().height() - 50);

    QPoint p;
    p.rx() = event->size().width() - ui->verticalLayoutWidget_2->size().width() - 30;
    p.ry() = ui->verticalLayoutWidget_2->pos().y();
    ui->verticalLayoutWidget_2->move(p);

    p.rx() = p.rx() = event->size().width() - ui->verticalLayoutWidget_4->size().width() - 30;
    p.ry() = ui->verticalLayoutWidget_4->pos().y();
    ui->verticalLayoutWidget_4->move(p);

    p.rx() = event->size().width()/2 - ui->verticalLayoutWidget_3->size().width()/2;
    p.ry() = ui->verticalLayoutWidget_3->pos().y();
    ui->verticalLayoutWidget_3->move(p);

    p.rx() = event->size().width()/2 - ui->verticalLayoutWidget_5->size().width()/2;
    p.ry() = event->size().height() - 10 - ui->verticalLayoutWidget_5->size().height();
    ui->verticalLayoutWidget_5->move(p);



}


void gamewindow::on_backButton_clicked()
{
    startW->resize(this->size());
    startW->move(this->pos());
    this->hide();
    startW->show();
}




void gamewindow::on_lineName_textEdited(const QString &arg1)
{
    if (std::regex_match(arg1.toStdString(), std::regex("[0-9a-zA-Z!@#$%^&*()_+*?:№]{3,20}"))){
        ui->errorName->hide();
        conditional.name = true;
    } else {
        ui->errorName->show();
        conditional.name = false;
    }
    checkStartConditional();

}

bool gamewindow::checkStartConditional(){
    if (conditional.name && conditional.bet && conditional.bank && conditional.parts) {
        QString onButton(QString::fromStdString("color : black"));
        ui->playButton->setStyleSheet(onButton);
        return true;
    } else {
        QString offButton(QString::fromStdString("color : gray"));
        ui->playButton->setStyleSheet(offButton);
        return false;
    }
}


void gamewindow::on_bankSpin_valueChanged(int arg1)
{
    ui->betSpin->setMaximum(arg1);
}
