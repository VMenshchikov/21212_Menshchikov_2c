
#include "Factory.hpp"

#include <string>
#include <QPixmap>
#include <QString>
#include <QGuiApplication>


namespace {
    QPixmap* Create(std::string str) {
        QPixmap* tmp = new QPixmap(QString::fromStdString("../../resourses/") + QString::fromStdString(str));
        return tmp;
    }


    const bool A_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("A_1", Create("A_1"));
    const bool A_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("A_2", Create("A_2"));
    const bool A_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("A_3", Create("A_3"));
    const bool A_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("A_4", Create("A_4"));

    const bool q2_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("2_1", Create("2_1"));
    const bool q2_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("2_2", Create("2_2"));
    const bool q2_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("2_3", Create("2_3"));
    const bool q2_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("2_4", Create("2_4"));

    const bool q3_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("3_1", Create("3_1"));
    const bool q3_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("3_2", Create("3_2"));
    const bool q3_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("3_3", Create("3_3"));
    const bool q3_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("3_4", Create("3_4"));

    const bool q4_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("4_1", Create("4_1"));
    const bool q4_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("4_2", Create("4_2"));
    const bool q4_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("4_3", Create("4_3"));
    const bool q4_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("4_4", Create("4_4"));

    const bool q5_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("5_1", Create("5_1"));
    const bool q5_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("5_2", Create("5_2"));
    const bool q5_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("5_3", Create("5_3"));
    const bool q5_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("5_4", Create("5_4"));

    const bool q6_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("6_1", Create("6_1"));
    const bool q6_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("6_2", Create("6_2"));
    const bool q6_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("6_3", Create("6_3"));
    const bool q6_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("6_4", Create("6_4"));

    const bool q7_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("7_1", Create("7_1"));
    const bool q7_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("7_2", Create("7_2"));
    const bool q7_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("7_3", Create("7_3"));
    const bool q7_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("7_4", Create("7_4"));

    const bool q8_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("8_1", Create("8_1"));
    const bool q8_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("8_2", Create("8_2"));
    const bool q8_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("8_3", Create("8_3"));
    const bool q8_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("8_4", Create("8_4"));

    const bool q9_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("9_1", Create("9_1"));
    const bool q9_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("9_2", Create("9_2"));
    const bool q9_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("9_3", Create("9_3"));
    const bool q9_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("9_4", Create("9_4"));

    const bool q10_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("10_1", Create("10_1"));
    const bool q10_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("10_2", Create("10_2"));
    const bool q10_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("10_3", Create("10_3"));
    const bool q10_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("10_4", Create("10_4"));

    const bool B_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("B_1", Create("B_1"));
    const bool B_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("B_2", Create("B_2"));
    const bool B_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("B_3", Create("B_3"));
    const bool B_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("B_4", Create("B_4"));

    const bool D_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("D_1", Create("D_1"));
    const bool D_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("D_2", Create("D_2"));
    const bool D_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("D_3", Create("D_3"));
    const bool D_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("D_4", Create("D_4"));

    const bool K_1 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("K_1", Create("K_1"));
    const bool K_2 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("K_2", Create("K_2"));
    const bool K_3 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("K_3", Create("K_3"));
    const bool K_4 = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("K_4", Create("K_4"));

    const bool back = TFactory<std::string, QPixmap*, QPixmap*>::GetInstance()->Register("back", Create("back"));

}
