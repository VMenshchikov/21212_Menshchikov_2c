#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "startwindow.h"

#include <QPalette>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QtTest/QTest>

#include <iostream>
#include <regex>


gamewindow::gamewindow(StartWindow* start, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamewindow),
    startW(start),
    scene(QGraphicsScene(ui->graphicsView)
)
{
    std::cout << "gw" << std::endl;
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->move(0,0);
    QPixmap bckImg = QPixmap(QString::fromStdString("../resourses/table.jpg")).
                     scaled(size());
    bckImgObj = scene.addPixmap(bckImg);
    bckImgObj->setPos(0, 0);
    setPalette(CreatePalette(this->size(), "../resourses/table.jpg"));

    ui->splitButton->hide();
    checkStartConditional();
}


void gamewindow::newBank(int bank, int bet){
    QString tmp = QString::fromStdString(std::string("Bank: ") + std::to_string(bank)
                                         + std::string("\nBet: ") + std::to_string(bet));
    ui->bankInfo->setText(tmp);
    ui->bankInfo->show();
}

gamewindow::~gamewindow()
{
    delete ui;
    emit endGame();
}

QPalette gamewindow::CreatePalette(const QSize& size, const char* img){
    QImage bkgnd(img);
    bkgnd = bkgnd.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPalette p;
    p.setBrush(QPalette::Background, bkgnd);
    return p;
}

void gamewindow::clearCards() {
    //for (auto &i: cards){
        //scene.removeItem(i.card); //не работает
        //i.card->setPixmap(QPixmap());
    //}
    cards.clear();
    scene.clear();
    QPixmap bckImg = QPixmap(QString::fromStdString("../resourses/table.jpg")).
                     scaled(size());
    bckImgObj = scene.addPixmap(bckImg);
}

void gamewindow::endPart() {
    clearCards();
}

void gamewindow::resizeEvent(QResizeEvent *event){

    ui->verticalLayoutWidget->move(30, event->size().height() - 50);
    scene.setSceneRect(0, 0, event->size().width(), event->size().height());

    bckImgObj->setPixmap(QPixmap(QString::fromStdString("../resourses/table.jpg")).
                         scaled(event->size()));

    setPalette(CreatePalette(this->size(), "../resourses/table.jpg"));



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

    p.rx() = event->size().width() - ui->verticalLayoutWidget_6->size().width() - 10;
    p.ry() = 10;
    ui->verticalLayoutWidget_6->move(p);


    p.rx() = event->size().width() - ui->verticalLayoutWidget_7->size().width() - 20;
    p.ry() = event->size().height() - ui->verticalLayoutWidget_7->size().height() - 20;
    ui->verticalLayoutWidget_7->move(p);

    p.rx() = event->size().width()/2 + ui->verticalLayoutWidget_5->size().width() + 10;
    p.ry() = event->size().height() - 60;
    ui->bankInfo -> move(p);

    for (auto &i: cards) {
        updateCard(i);
    }

       ui->graphicsView->resize(event->size());
}



void gamewindow::on_backButton_clicked()
{
    startW->resize(this->size());
    startW->move(this->pos());
    this->hide();
    startW->show();

    game = true;
    cards.clear();
    changeMode();
    clearCards();
}




void gamewindow::on_lineName_textEdited(const QString &arg1)
{
    if (std::regex_match(arg1.toStdString(), std::regex("[0-9a-zA-Z!@#$%^&*()_+*?:№]{3,25}"))){
        ui->errorName->hide();
        nameConditional = true;
    } else {
        ui->errorName->show();
        nameConditional = false;
    }
    checkStartConditional();

}

bool gamewindow::checkStartConditional(){
    if (nameConditional) {
        QString onButton(QString::fromStdString("color : black"));
        ui->playButton->setStyleSheet(onButton);
        ui->turButton->setStyleSheet(onButton);
        return true;
    } else {
        QString offButton(QString::fromStdString("color : gray"));
        ui->playButton->setStyleSheet(offButton);
        ui->turButton->setStyleSheet(offButton);
        return false;
    }
}


void gamewindow::on_bankSpin_valueChanged(int arg1)
{
    ui->betSpin->setMaximum(arg1);
}

void gamewindow::on_playButton_clicked()
{
    if (checkStartConditional()){
        changeMode();
        emit startGame(ui->betSpin->value(), ui->bankSpin->value(), ui->partSpin->value());
    }
}

void gamewindow::changeMode(){
    if (game) {
        ui->verticalLayoutWidget_2->hide(); // стат/плей
        ui->verticalLayoutWidget_4->hide(); //error name
        ui->formLayoutWidget->hide(); //настройки


        ui->verticalLayoutWidget_5->show(); //player ico
        ui->verticalLayoutWidget_6->show();//кнопки игры
        ui->verticalLayoutWidget_3->show(); // diler ico


        ui->verticalLayoutWidget->show(); // back

    } else {
        ui->formLayoutWidget->show(); //настройки
        ui->verticalLayoutWidget_4->show(); //error name
        ui->verticalLayoutWidget_2->show(); //стат/плей


        ui->verticalLayoutWidget_6->hide(); //кнопки игры
        ui->verticalLayoutWidget_5->hide(); // player ico
        ui->verticalLayoutWidget_3->hide(); // diler ico



        ui->verticalLayoutWidget->show(); // back



    }
    game = !game;
}
void gamewindow::changeButtonColor(char c) {
    QString onButton(QString::fromStdString("color : black"));
    QString offButton(QString::fromStdString("color : gray"));

    //Hit Stand DD Surrender Split

    ui->hitButton->setStyleSheet((c & 1) ? onButton : offButton);
    ui->standButton->setStyleSheet((c & (1 << 1)) ? onButton : offButton);
    ui->ddButton->setStyleSheet((c & (1 << 2)) ? onButton : offButton);
    ui->surButton->setStyleSheet((c & (1 << 3)) ? onButton : offButton);
    ui->splitButton->setStyleSheet((c & (1 << 4)) ? onButton : offButton);

}

void gamewindow::decision(char actions) {
    permissibleActions = actions;
    changeButtonColor(actions);
}

void gamewindow::dilerCard(int card) {
    newCard(card, "Diler", true, false, 0);
}

void gamewindow::newCard(int card, std::string name, bool visible, bool pos, int count) {
    cards.push_back(TCard(count, pos, name));
    if (!visible) {
        cards.back().cardsAddres = "../resourses/cards/back.png";
    } else {
        std::string cardName;
        if (card < 10) {
            cardName = std::to_string(card);
        } else {
            if (card == 11) {
                cardName = "A";
            } else {
                std::string n[4] = {"10", "B", "Q", "K"};
                cardName = n[rand() % 4];
            }
        }
        cardName += std::string("_") += std::to_string(rand() % 4 + 1);
        cards.back().cardsAddres = std::string("../resourses/cards/") += cardName += ".png";
    }

    updateCard(cards.back());
    QTest::qWait(500);

}

void gamewindow::updateCard(TCard& cur) {
    if (cur.card != nullptr){
        cur.card->setPixmap(QPixmap(QString::fromStdString(cur.cardsAddres))
                                   .scaled(this->size() * 0.15, Qt::KeepAspectRatio));
    } else {
        cur.card = scene.addPixmap(QPixmap(QString::fromStdString(cur.cardsAddres))
                                  .scaled(this->size() * 0.15, Qt::KeepAspectRatio));
    }


    QPoint defPos;
    if (cur.name == "Diler") {
        defPos.setX(this->size().width() * 0.4);
        defPos.setY(this->size().height() * 0.43 - cur.card->pixmap().size().height());
    } else {
        defPos.setX(this->size().width() * 0.45 - cur.card->pixmap().size().width() - this->width() / 100);
        defPos.setY(this->size().height() * 0.80 - cur.card->pixmap().size().height());
    }

    cur.card->setPos(defPos.x() + (cur.card->pixmap().size().width() + 5) * cur.count * (cur.name == "Diler"),
          defPos.y() + cur.count * (cur.card->pixmap().size().height() * 0.15) * (cur.name != "Diler"));
}

void gamewindow::finalResult(int startBank, int bank) {
    QMessageBox info;
    std::string text;
    text = "Начальный банк: " + std::to_string(startBank) +
            "\nТекущий банк: " + std::to_string(bank) + "\n";
    if (startBank > bank) {
        text += "Вы обеднели на ";
        info.addButton(QString::fromStdString("Ne ok"), QMessageBox::DestructiveRole);

    } else {
        text += "Вы разбогатели на ";
        info.addButton(QString::fromStdString("Ok"), QMessageBox::DestructiveRole);

    }
    text += std::to_string( std::abs(100 - (double)bank / ((double)startBank/100))) + "%";
    info.setText(QString::fromStdString(text));
    info.resize(300, 400);
    info.move(pos().x() + info.size().width()/2, pos().y() + info.size().height()/2);
    info.setWindowTitle(QString::fromStdString("Результат"));
    info.exec();

    if (tournamentName != "") {
        std::ofstream outFile;
        outFile.open("../resourses/leaders.txt", std::ios_base::app);
        outFile << tournamentName << " " << bank << "\n";
        outFile.close();
        tournamentName = "";
    }
}


void gamewindow::on_hitButton_clicked() {
    if (permissibleActions & 1) {
        act = true;
        permissibleActions = 0;
        changeButtonColor(permissibleActions);
        emit sendAction("H");
    }
}

void gamewindow::on_splitButton_clicked()
{
    if(permissibleActions & (1 << 4)) {
        permissibleActions = 0;
        changeButtonColor(permissibleActions);
        cards.back().pos = true;
        cards.back().count = 0;
        updateCard(cards.back());
        emit sendAction("Sp");
    }
}

void gamewindow::on_ddButton_clicked()
{
    if(permissibleActions & (1 << 2)) {
        permissibleActions = 0;
        changeButtonColor(permissibleActions);
        emit sendAction("DD");
    }
}


void gamewindow::on_standButton_clicked()
{
    if(permissibleActions & (1 << 1)) {
        permissibleActions = 0;
        changeButtonColor(permissibleActions);
        emit sendAction("St");
    }
}

void gamewindow::on_surButton_clicked()
{
    if(permissibleActions & (1 << 3)) {
        permissibleActions = 0;
        changeButtonColor(permissibleActions);
        emit sendAction("Su");
    }
}


void gamewindow::on_horizontalSlider_sliderMoved(int position)
{
    emit newRevPause(position);
}

void gamewindow::on_turButton_clicked()
{
    if (!checkStartConditional()) { return; }
    tournamentBank = 0;
    tournamentName = ui->lineName->text().toStdString();
    ui->bankSpin->setValue(200);
    ui->betSpin->setValue(25);
    ui->partSpin->setValue(20);
    ui->playButton->click();
}
