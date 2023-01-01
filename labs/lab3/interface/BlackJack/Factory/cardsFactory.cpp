
#include "Factory.hpp"

#include <string>
#include <functional>
#include <iostream>
#include <cstdio>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QLayout>


namespace {
    QLabel* Create(std::string str) {
        QLabel* tmp = new QLabel();
        tmp->setPixmap(QPixmap(QString::fromStdString("../../resourses/") + QString::fromStdString(str)));
        return tmp;
    }


    const bool A_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register("A_1", Create);
    const bool A_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("A_2"), Create);
    const bool A_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("A_3"), Create);
    const bool A_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("A_4"), Create);

    const bool q2_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("2_1"), Create);
    const bool q2_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("2_2"), Create);
    const bool q2_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("2_3"), Create);
    const bool q2_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("2_4"), Create);

    const bool q3_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("3_1"), Create);
    const bool q3_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("3_2"), Create);
    const bool q3_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("3_3"), Create);
    const bool q3_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("3_4"), Create);

    const bool q4_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("4_1"), Create);
    const bool q4_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("4_2"), Create);
    const bool q4_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("4_3"), Create);
    const bool q4_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("4_4"), Create);

    const bool q5_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("5_1"), Create);
    const bool q5_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("5_2"), Create);
    const bool q5_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("5_3"), Create);
    const bool q5_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("5_4"), Create);

    const bool q6_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("6_1"), Create);
    const bool q6_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("6_2"), Create);
    const bool q6_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("6_3"), Create);
    const bool q6_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("6_4"), Create);

    const bool q7_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("7_1"), Create);
    const bool q7_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("7_2"), Create);
    const bool q7_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("7_3"), Create);
    const bool q7_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("7_4"), Create);

    const bool q8_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("8_1"), Create);
    const bool q8_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("8_2"), Create);
    const bool q8_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("8_3"), Create);
    const bool q8_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("8_4"), Create);

    const bool q9_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("9_1"), Create);
    const bool q9_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("9_2"), Create);
    const bool q9_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("9_3"), Create);
    const bool q9_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("9_4"), Create);

    const bool q10_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("10_1"), Create);
    const bool q10_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("10_2"), Create);
    const bool q10_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("10_3"), Create);
    const bool q10_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("10_4"), Create);

    const bool B_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("B_1"), Create);
    const bool B_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("B_2"), Create);
    const bool B_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("B_3"), Create);
    const bool B_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("B_4"), Create);

    const bool D_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("D_1"), Create);
    const bool D_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("D_2"), Create);
    const bool D_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("D_3"), Create);
    const bool D_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("D_4"), Create);

    const bool K_1 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("K_1"), Create);
    const bool K_2 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("K_2"), Create);
    const bool K_3 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("K_3"), Create);
    const bool K_4 = TFactory<std::string, std::function<QLabel*(std::string)>, std::function
    <QLabel*(std::string)>>::GetInstance()->Register(std::string("K_4"), Create);

    //std::cout << A_1 << " " << A_2 << " " K_3 << " " q7_2 << std::endl;
    //printf("%i%i%i%i", A_1, A_2, K_3, q7_2);
}
