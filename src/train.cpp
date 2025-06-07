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
а если это добавить? int Train::getLength() {
  countOp = 0;
  Car* currentCar;
  while (true) {
    currentCar = first;
    int countedCars = 0;
    if (!currentCar->light) {
      currentCar->light = true;
    }
    currentCar = currentCar->next;
    countOp += 2;
    while (!currentCar->light) {
      currentCar = currentCar->next;
      countOp += 2;
      countedCars++;
    }
    currentCar->light = false;
    if (!first->light) {
      return countedCars + 1;
    }
  }
}
