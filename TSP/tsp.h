// ---------------- tsp.h ----------------
#ifndef TSP_H
#define TSP_H

#include "city.h"
#include <QVector>
#include <QString>

class TSPSolver {
public:
    static double bruteForce(const QVector<City>& cities, QVector<int>& path);
    static double heldKarp(const QVector<City>& cities, QVector<int>& path);
    static double greedy(const QVector<City>& cities, QVector<int>& path);
};

#endif // TSP_H
