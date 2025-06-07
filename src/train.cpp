// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr), current(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* car = first;
    Car* next;
    do {
        next = car->next;
        delete car;
        car = next;
    } while (car != first);
}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

void Train::moveForward() {
    if (!current) current = first;
    current = current->next;
    countOp++;
}

void Train::moveBackward() {
    if (!current) current = first;
    current = current->prev;
    countOp++;
}

void Train::toggleLight() {
    if (!current) current = first;
    current->light = !current->light;
}

bool Train::getLightState() const {
    if (!current) return first->light;
    return current->light;
}

void Train::resetPosition() {
    current = first;
}

int Train::getOpCount() const {
    return countOp;
}

int Train::getLength() {
    if (!first) return 0;
    resetPosition();
    countOp = 0;
    // Включаем лампочку в стартовом вагоне, если она выключена
    if (!getLightState()) {
        toggleLight();
    }
    int length = 0;
    while (true) {
        moveForward();
        length++;
        // Если нашли включённую лампочку
        if (getLightState()) {
            toggleLight(); // Выключаем её
            // Возвращаемся назад, считая шаги
            int steps = 0;
            while (steps < length) {
                moveBackward();
                steps++;
            }
            // Если стартовая лампочка выключена - это и есть длина
            if (!getLightState()) {
                return length;
            }
            // Иначе продолжаем поиск
            length = steps;
            toggleLight(); // Включаем лампочку снова
        }
    }
}
