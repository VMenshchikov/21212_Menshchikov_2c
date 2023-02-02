#include <QResizeEvent>
#include <QStyle>
#include <QRgb>
#include <QMovie>
#include <QtUiTools/QUiLoader>
#include <QFile>


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


#include "gamewindow.h"
#include "startwindow.h"
#include "gamewindow.h"
#include "ui_startwindow.h"
#include "Factory/Factory.hpp"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
    , game(new gamewindow(this, this))
{
    std::cout << "sw" << std::endl;
    ui->setupUi(this);
    ui->verticalLayoutWidget->move(0,0);
    ui->verticalLayoutWidget_3->hide();
    ui->verticalLayoutWidget_3->setStyleSheet(QString::fromStdString("background-color: rgb(200,200,200,100)"));

}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::resizeEvent(QResizeEvent *event){

    ui->verticalLayoutWidget->resize(event->size()); //background

    {
    QPoint newPos;
    newPos.setX(event->size().width() - 200 - event->size().width() * 0.03);
    newPos.setY(ui->verticalLayoutWidget_2->pos().y());
    ui->verticalLayoutWidget_2->move(newPos);
    }// buttoms

}


void StartWindow::on_GameButton_clicked()
{
    this->hide();
    game->resize(this->size());
    game->move(this->pos());
    game->changeMode();
    game->show();

}

bool cmpLeaedrs(const std::pair<std::string, int>& a, const std::pair<std::string, int> b ){
    return a.second > b.second;
}


QString StartWindow::ParserLeaders(std::ifstream& inputFile){
    std::vector<std::pair<std::string, int>> leaders;
    std::string line;
    while(std::getline(inputFile, line)) {
        std::pair<std::string, int> data;
        std::istringstream parser(line);
        parser >> data.first >> data.second;
        leaders.push_back(data);
    }
    std::sort(leaders.begin(), leaders.end(), cmpLeaedrs);
    std::string result = "";

    int count = 1;
    for (auto i: leaders){
        while (i.first.size() < 20) {
            i.first += " ";
        }

        result += std::to_string(count) + std::string(".  ") + i.first
                + std::string("\t") + std::to_string(i.second) += "\n";
        count++;
        if (count == 12) {
            leaders.erase(leaders.begin() + 11, leaders.end());
            std::ofstream outFile;
            outFile.open("../resourses/leaders.txt", std::ios_base::out);
            for (auto i: leaders) {
                outFile << i.first << " " << i.second << "\n";
            }
            outFile.close();
            return QString::fromStdString(result);
        }
    }

    return QString::fromStdString(result);
}



void StartWindow::on_StatButton_clicked()
{
    if(ui->verticalLayoutWidget_3->isHidden()){
        ui->verticalLayoutWidget_3->show();
        ui->LeadersList->clear();
        //std::ofstream test("./test.txt");
        std::ifstream inputFile;
        inputFile.open("../resourses/leaders.txt", std::ios_base::in);
        ui->LeadersList->setText(ParserLeaders(inputFile));
    }
    else {
        ui->verticalLayoutWidget_3->hide();
    }
}
