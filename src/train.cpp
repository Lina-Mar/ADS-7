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
    
    // Оптимизация: пропуск ненужных итераций
    if (getLightState()) {
        toggleLight();
    } else {
        toggleLight();  // Гарантированно включаем лампочку
    }

    int length = 0;
    while (true) {
        moveForward();
        length++;
        
        if (getLightState()) {
            toggleLight();
            int steps = 0;
            while (steps++ < length) {
                moveBackward();
            }
            
            if (!getLightState()) {
                return length;
            }
            
            // Оптимизация: уменьшаем количество проходов
            length = (length + steps) / 2;
            toggleLight();
        }
    }
}
