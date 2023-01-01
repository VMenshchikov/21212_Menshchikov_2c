#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class StartWindow;

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(StartWindow* start, QWidget *parent = nullptr);
    ~gamewindow();

    virtual void resizeEvent(QResizeEvent *event) override;
    QPalette CreatePalette(const QSize& size, const char* img);

private slots:

    void on_backButton_clicked();

    void on_lineName_textEdited(const QString &arg1);

    void on_bankSpin_valueChanged(int arg1);

private:
    Ui::gamewindow *ui;
    StartWindow* startW;

    struct TStartConditionl {
        bool name = false;
        bool bet = true;
        bool bank = true;
        bool parts = true;
    } conditional;

    bool checkStartConditional();

};

#endif // GAMEWINDOW_H
