// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
private:
 struct Car {
    bool light; // состояние лампочки
    Car* next;
    Car* prev;
 };

    int countOp; // счетчик шагов
    Car* first; // первый вагон
    Car* current; // текущий вагон (для перемещения)

public:
 Train();
 ~Train();
    void addCar(bool light); // добавить вагон
    int getLength(); // вычислить длину поезда
    int getOpCount() const; // вернуть число переходов
    // Методы для перемещения по поезду
    void moveForward();
    void moveBackward();
    void toggleLight();
    bool getLightState() const;
    void resetPosition();
};

#endif  // INCLUDE_TRAIN_H_
