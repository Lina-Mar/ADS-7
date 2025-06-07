// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include "train.h"

using namespace std;
using namespace std::chrono;

void experimentAllLightsOff(int max_n, const string& filename) {
    ofstream dataFile(filename);
    
    for (int n = 2; n <= max_n; n++) {
        Train train;
        // Все лампочки выключены
        for (int i = 0; i < n; i++) {
            train.addCar(false);
        }
        
        auto start = high_resolution_clock::now();
        int calculatedLength = train.getLength();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        dataFile << n << " " << train.getOpCount() << " " << duration.count() << endl;
    }
    
    dataFile.close();
}

void experimentAllLightsOn(int max_n, const string& filename) {
    ofstream dataFile(filename);
    
    for (int n = 2; n <= max_n; n++) {
        Train train;
        // Все лампочки включены
        for (int i = 0; i < n; i++) {
            train.addCar(true);
        }
        
        auto start = high_resolution_clock::now();
        int calculatedLength = train.getLength();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        dataFile << n << " " << train.getOpCount() << " " << duration.count() << endl;
    }
    
    dataFile.close();
}

void experimentRandomLights(int max_n, const string& filename) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1);
    
    ofstream dataFile(filename);
    
    for (int n = 2; n <= max_n; n++) {
        Train train;
        // Случайное состояние лампочек
        for (int i = 0; i < n; i++) {
            train.addCar(distrib(gen) == 1);
        }
        
        auto start = high_resolution_clock::now();
        int calculatedLength = train.getLength();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        dataFile << n << " " << train.getOpCount() << " " << duration.count() << endl;
    }
    
    dataFile.close();
}

int main() {
    const int MAX_N = 100;
    
    // Проводим эксперименты
    experimentAllLightsOff(MAX_N, "data_off.txt");
    experimentAllLightsOn(MAX_N, "data_on.txt");
    experimentRandomLights(MAX_N, "data_random.txt");
    return 0;
}
