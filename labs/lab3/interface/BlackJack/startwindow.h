#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <fstream>
#include "gamewindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

    const gamewindow* getGameWindow() const { return game; }

    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_GameButton_clicked();

    void on_StatButton_clicked();

private:

    Ui::StartWindow *ui;
    gamewindow *game;
    QString ParserLeaders(std::ifstream& inputFile);


};

#endif // STARTWINDOW_H
