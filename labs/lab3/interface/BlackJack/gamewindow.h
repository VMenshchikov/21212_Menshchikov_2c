#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>


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
    void changeMode();

  private slots:

    void on_backButton_clicked();

    void on_lineName_textEdited(const QString &arg1);

    void on_bankSpin_valueChanged(int arg1);

    void on_playButton_clicked();

    void on_hitButton_clicked();

    void on_splitButton_clicked();

    void on_ddButton_clicked();

    void on_standButton_clicked();

    void on_surButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_turButton_clicked();

public slots:
    void decision (char actions);
    void newCard(int card, std::string name, bool visible, bool pos, int count);
    void newBank(int bank, int bet);
    void endPart();
    void dilerCard(int card);
    void finalResult(int startBank, int currentBank);

  signals:
    void startGame(size_t, size_t, size_t);
    void sendAction(std::string);
    void endGame();
    void newRevPause(int);

  private:
    Ui::gamewindow *ui;
    StartWindow* startW;
    bool nameConditional = false;
    QGraphicsScene scene;
    QGraphicsPixmapItem* bckImgObj = nullptr;
    bool checkStartConditional();
    std::string tournamentName = "";
    int tournamentBank = 0;
    bool game = false;
    bool act = false;
    char permissibleActions;
    void changeButtonColor(char c);

    struct TCard {
        TCard(int count, bool pos, std::string name) :
                count(count), pos(pos), name(name){};
        std::string name;
        std::string cardsAddres;
        QGraphicsPixmapItem* card = nullptr;
        bool pos = false; //false = left, true = right (only split)
        int count;
    };
    std::vector<TCard> cards;
    void updateCard(TCard& cur);
    void clearCards();
};

#endif // GAMEWINDOW_H
