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
    // 1. Делаем стартовую лампочку уникальной (включаем, если выключена)
    bool start_light_was_off = !getLightState();
    if (start_light_was_off) {
        toggleLight();
    }
    int length = 0;
    while (true) {
        // 2. Двигаемся вперёд, пока не найдём включённую лампочку
        moveForward();
        length++;
        if (getLightState()) {
            // 3. Выключаем найденную лампочку
            toggleLight();
            // 4. Возвращаемся назад, считая шаги
            int steps = 0;
            while (steps < length) {
                moveBackward();
                steps++;
            }
            // 5. Проверяем стартовую лампочку
            if ((start_light_was_off && !getLightState()) ||
                (!start_light_was_off && getLightState())) {
                return length;
            }
            // 6. Если не совпало, продолжаем поиск
            length = 0;
            if (start_light_was_off) {
                toggleLight(); // Восстанавливаем исходное состояние
            }
        }
    }
}
