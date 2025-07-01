#include "tsp.h"
#include "haversine.h"
#include <algorithm>
#include <climits>
#include <QMap>
#include <QSet>

// Brute Force
double pathDistance(const QVector<City>& cities, const QVector<int>& path) {
    double total = 0;
    for (int i = 0; i < path.size() - 1; ++i)
        total += haversine(
            cities[path[i]].latitude,
            cities[path[i]].longitude,
            cities[path[i + 1]].latitude,
            cities[path[i + 1]].longitude);
    total += haversine(
        cities[path.back()].latitude,
        cities[path.back()].longitude,
        cities[path[0]].latitude,
        cities[path[0]].longitude);
    return total;
}

double TSPSolver::bruteForce(const QVector<City>& cities, QVector<int>& bestPath) {
    QVector<int> path;
    for (int i = 0; i < cities.size(); ++i)
        path.append(i);

    double minDist = INT_MAX;
    do {
        double d = pathDistance(cities, path);
        if (d < minDist) {
            minDist = d;
            bestPath = path;
        }
    } while (std::next_permutation(path.begin(), path.end()));

    return minDist;
}

// Greedy
double TSPSolver::greedy(const QVector<City>& cities, QVector<int>& path) {
    int n = cities.size();
    QVector<bool> visited(n, false);
    int current = 0; // Start from the first city
    path.append(current);
    visited[current] = true;

    for (int step = 1; step < n; ++step) {
        double minDist = INT_MAX;
        int nextCity = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double d = haversine(
                    cities[current].latitude, cities[current].longitude,
                    cities[i].latitude, cities[i].longitude);
                if (d < minDist) {
                    minDist = d;
                    nextCity = i;
                }
            }
        }
        current = nextCity;
        visited[current] = true;
        path.append(current);
    }
    return pathDistance(cities, path);
}

// Held-Karp (Dynamic Programming)
#include <map>
#include <bitset>

using namespace std;

double TSPSolver::heldKarp(const QVector<City>& cities, QVector<int>& path) {
    int n = cities.size();
    map<pair<int, int>, pair<double, int>> dp;

    // Initialize the dp table for base case
    for (int i = 1; i < n; ++i)
        dp[{1 << i, i}] = {haversine(cities[0].latitude, cities[0].longitude, cities[i].latitude, cities[i].longitude), 0};

    // Fill dp table
    for (int r = 2; r < n; ++r) {
        for (int subset = 0; subset < (1 << n); ++subset) {
            if (__builtin_popcount(subset) != r || !(subset & 1)) continue; // Ensure subset includes city 0
            for (int next = 1; next < n; ++next) {
                if (!(subset & (1 << next))) continue; // Skip if next city is not in subset
                int prevSubset = subset ^ (1 << next);
                double minDist = INT_MAX;
                int prevCity = -1;
                for (int end = 1; end < n; ++end) {
                    if (end == next || !(prevSubset & (1 << end))) continue;
                    double dist = dp[{prevSubset, end}].first + haversine(cities[end].latitude, cities[end].longitude, cities[next].latitude, cities[next].longitude);
                    if (dist < minDist) {
                        minDist = dist;
                        prevCity = end;
                    }
                }
                dp[{subset, next}] = {minDist, prevCity};
            }
        }
    }

    // Find the minimum tour by looking for the best path that ends at city 0
    double minTour = INT_MAX;
    int lastCity = -1;
    int fullSet = (1 << n) - 1;
    for (int i = 1; i < n; ++i) {
        double d = dp[{fullSet ^ 1, i}].first + haversine(cities[i].latitude, cities[i].longitude, cities[0].latitude, cities[0].longitude);
        if (d < minTour) {
            minTour = d;
            lastCity = i;
        }
    }

    // Reconstruct the optimal path from the dp table
    int current = lastCity;
    int mask = fullSet ^ 1;
    path = {0};
    QVector<int> reversePath;
    while (current != 0) {
        reversePath.append(current);
        int temp = current;
        current = dp[{mask, current}].second;
        mask ^= (1 << temp);
    }

    // Reverse the path to get it in the correct order
    std::reverse(reversePath.begin(), reversePath.end());
    path.append(reversePath);

    return minTour;
}
