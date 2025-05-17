// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (first) {
    Car* currentCar = first;
    do {
      Car* tempCar = currentCar->next;
      delete currentCar;
      currentCar = tempCar;
    } while (currentCar != first);
  }
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* lastCar = first->prev;
    lastCar->next = newCar;
    newCar->prev = lastCar;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
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

int Train::getOpCount() {
  return countOp;
}
