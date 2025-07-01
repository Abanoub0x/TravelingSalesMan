#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsLineItem>
#include <QTreeWidgetItem>
#include <cmath>
#include <limits>
#include <algorithm>
#include <QList>
#include <QDebug>
#include <QRegularExpression>
#include <QPen>
#include <QTimer>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QDir>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "Current working directory:" << QDir::currentPath();
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("border: 2px solid white;");

    // Add Egypt map background
    addEgyptMapBackground();

    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->btnAddCity, &QPushButton::clicked, this, &MainWindow::onAddCityClicked);
    connect(ui->btnDeleteDrawings, &QPushButton::clicked, this, &MainWindow::onDeleteDrawings);
    connect(ui->btnResetTable, &QPushButton::clicked, this, &MainWindow::resetToInitialState);
    resetToInitialState();
}


MainWindow::~MainWindow()
{
    delete ui;
}





QPointF MainWindow::toPointF(double lat, double lon) {
    // Egypt's geographical bounds
    double minLat = 22.0, maxLat = 32.0;
    double minLon = 25.0, maxLon = 36.0;

    // Egypt area in the image (excluding borders)
    double x0 = 32.0, y0 = 8.0; // top-left corner of Egypt in the image
    double imgWidth = 784.0, imgHeight = 736.0;

    // Map lat/lon to image pixel coordinates
    double x = x0 + (lon - minLon) / (maxLon - minLon) * imgWidth;
    double y = y0 + (maxLat - lat) / (maxLat - minLat) * imgHeight;

    return QPointF(x, y);
}






void MainWindow::onAddCityClicked() {
    QString name = ui->inputName->text();
    QString latStr = ui->inputLat->text();
    QString lonStr = ui->inputLon->text();

    QRegularExpression latRegex("[^0-9\\.\\-]");
    latStr.remove(latRegex);
    QRegularExpression lonRegex("[^0-9\\.\\-]");
    lonStr.remove(lonRegex);

    bool latOk, lonOk;
    double lat = latStr.toDouble(&latOk);
    double lon = lonStr.toDouble(&lonOk);

    if (!latOk || !lonOk || name.isEmpty()) {
        qDebug() << "Invalid input!";
        return;
    }

    // Add city to the tree widget
    QTreeWidgetItem* cityItem = new QTreeWidgetItem();
    cityItem->setText(0, name);
    cityItem->setText(1, QString::number(lat));
    cityItem->setText(2, QString::number(lon));
    ui->tableCities->addTopLevelItem(cityItem);

    // Assign a color to the city
    static const QColor colors[] = {
        Qt::blue, Qt::red, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkBlue, Qt::darkGreen, Qt::darkRed
    };
    int colorIndex = ui->tableCities->topLevelItemCount() - 1; // index of the newly added city
    if (colorIndex >= 10) colorIndex = 9;  // limit to a maximum of 10 colors

    QColor cityColor = colors[colorIndex];

    QPointF point = toPointF(lat, lon);
    scene->addEllipse(point.x() - 2.5, point.y() - 2.5, 5, 5, QPen(cityColor), QBrush(cityColor)); // small node with unique color
    // Add city name label
    QGraphicsTextItem* label = scene->addText(name);
    QColor labelColor = cityColor;
    // Use black for bright colors for better visibility
    if (labelColor == Qt::yellow || labelColor == Qt::cyan || labelColor == Qt::green || labelColor == Qt::gray) {
        labelColor = Qt::black;
    }
    label->setDefaultTextColor(labelColor);
    label->setPos(point.x() + 7, point.y() - 7); // Offset label from point
}








void MainWindow::onStartClicked() {


    int cityCount = ui->tableCities->topLevelItemCount();
    QString algorithm = ui->comboBoxAlgo->currentText();

    // Safety checks
    if (cityCount < 2) {
        QMessageBox::warning(this, "Error", "Need at least 2 cities");
        return;
    }


    // Add null check for algorithm
    if (algorithm.isEmpty()) {
        QMessageBox::warning(this, "Error", "No algorithm selected");
        return;
    }

    QVector<QPointF> cities;
    for (int i = 0; i < cityCount; ++i) {
        QTreeWidgetItem* item = ui->tableCities->topLevelItem(i);
        if (!item) continue;  // Skip if item is null
        bool latOk, lonOk;
        double lat = item->text(1).toDouble(&latOk);
        double lon = item->text(2).toDouble(&lonOk);
        if (latOk && lonOk) {
            cities.append(toPointF(lat, lon));
        }
    }

    // Check if we got valid cities
    if (cities.size() < 2) {
        QMessageBox::warning(this, "Error", "Not valid city coordinates");
        return;
    }


    // Determine which algorithm to use
    QString selectedAlgorithm = ui->comboBoxAlgo->currentText();
    QVector<QPointF> tspPath;

    if (selectedAlgorithm == "Greedy") {
        tspPath = runGreedyAlgorithm(cities);
    } else if (selectedAlgorithm == "Dynamic Programming") {
        tspPath = runDynamicProgramming(cities);
    } else if (selectedAlgorithm == "Brute Force") {
        tspPath = runBruteForce(cities);
    }

    if (tspPath.isEmpty()) {
        qDebug() << "Error: TSP path is empty!";
        return;
    }

    // Clear existing drawings
    clearLines();


    for (int i = 0; i < ui->tableCities->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = ui->tableCities->topLevelItem(i);
        double lat = item->text(1).toDouble();
        double lon = item->text(2).toDouble();

        static const QColor colors[] = {
            Qt::blue, Qt::red, Qt::green, Qt::yellow, Qt::cyan,
            Qt::magenta, Qt::gray, Qt::darkBlue, Qt::darkGreen, Qt::darkRed
        };
        QColor cityColor = colors[i % 10];

        QPointF point = toPointF(lat, lon);
        scene->addEllipse(point.x() - 3, point.y() - 3, 6, 6,
                          QPen(cityColor), QBrush(cityColor));
        // Add city name label
        QGraphicsTextItem* label = scene->addText(item->text(0));
        QColor labelColor = cityColor;
        // Use black for bright colors for better visibility
        if (labelColor == Qt::yellow || labelColor == Qt::cyan || labelColor == Qt::green || labelColor == Qt::gray) {
            labelColor = Qt::black;
        }
        label->setDefaultTextColor(labelColor);
        label->setPos(point.x() + 7, point.y() - 7); // Offset label from point
    }

    // Animate the path
    animatePath(tspPath);
}









void MainWindow::onResetClicked()
{

    QTreeWidgetItem* selectedItem = ui->tableCities->currentItem();
    if (selectedItem) {
        int row = ui->tableCities->indexOfTopLevelItem(selectedItem);
        ui->tableCities->takeTopLevelItem(row);
        delete selectedItem;

        scene->clear();
        for (int i = 0; i < ui->tableCities->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = ui->tableCities->topLevelItem(i);
            QString name = item->text(0);
            double lat = item->text(1).toDouble();
            double lon = item->text(2).toDouble();

            static const QColor colors[] = {
                Qt::blue, Qt::red, Qt::green, Qt::yellow, Qt::cyan,
                Qt::magenta, Qt::gray, Qt::darkBlue, Qt::darkGreen, Qt::darkRed
            };
            QColor cityColor = colors[i % 10];

            QPointF point = toPointF(lat, lon);
            scene->addEllipse(point.x() - 2.5, point.y() - 2.5, 5, 5,
                              QPen(cityColor), QBrush(cityColor));
            // Add city name label
            QGraphicsTextItem* label = scene->addText(name);
            QColor labelColor = cityColor;
            // Use black for bright colors for better visibility
            if (labelColor == Qt::yellow || labelColor == Qt::cyan || labelColor == Qt::green || labelColor == Qt::gray) {
                labelColor = Qt::black;
            }
            label->setDefaultTextColor(labelColor);
            label->setPos(point.x() + 7, point.y() - 7); // Offset label from point
        }
    }
}








QVector<QPointF> MainWindow::runBruteForce(const QVector<QPointF>& cities) {
    // Vector to store the final shortest path
    QVector<QPointF> path;

    // Get the number of cities
    int n = cities.size();

    // Create a vector with indices 0 to n-1 representing each city
    QVector<int> permutation(n);
    std::iota(permutation.begin(), permutation.end(), 0);  // Fill with 0, 1, 2, ..., n-1

    // Initialize the minimum distance with the largest possible double value
    double minDistance = std::numeric_limits<double>::max();

    // To store the permutation (city order) that gives the shortest path
    QVector<int> bestPermutation;

    try {
        // Try all possible permutations of city orders
        do {
            // Variable to store the total distance for the current permutation
            double totalDistance = 0;

            // Calculate distance from city i to city i+1 for all cities in the permutation
            for (int i = 0; i < n - 1; ++i) {
                totalDistance += calculateDistance(cities[permutation[i]],
                                                   cities[permutation[i + 1]]);  // Add distance between consecutive cities
            }

            // Add the distance to return from the last city to the first one (complete the cycle)
            totalDistance += calculateDistance(cities[permutation[n - 1]],
                                               cities[permutation[0]]);  // Complete the loop

            // If this total distance is shorter than the previous best, update best
            if (totalDistance < minDistance) {
                minDistance = totalDistance;            // Update minimum distance
                bestPermutation = permutation;          // Store this permutation as the best
            }

            // Every few iterations, process UI events to keep the interface responsive
            if (permutation[0] % 5 == 0) {
                QCoreApplication::processEvents();      // Allow UI updates
            }

        } while (std::next_permutation(permutation.begin(), permutation.end()));  // Try next permutation
    }
    catch (const std::bad_alloc&) {
        // Catch memory allocation errors (in case of huge input)
        qWarning() << "Memory allocation failed in brute force";  // Print error to debug console
        return path;  // Return empty path if error occurs
    }

    // Construct the final path using the best permutation
    for (int idx : bestPermutation) {
        path.append(cities[idx]);  // Append each city in the best order
    }

    // Return to the starting city to complete the tour
    path.append(cities[bestPermutation[0]]);  // Add starting city at the end

    // Return the path with the shortest distance
    return path;
}








QVector<QPointF> MainWindow::runGreedyAlgorithm(const QVector<QPointF>& cities) {

    // Vector to hold the resulting path
    QVector<QPointF> path;

    // If there are fewer than 2 cities, return an empty path
    if (cities.size() < 2) return path;

    // Boolean array to track which cities have been visited
    QVector<bool> visited(cities.size(), false);

    // Start from the first city (index 0)
    path.append(cities[0]);    // Add the first city to the path
    visited[0] = true;         // Mark the first city as visited

    // Repeat until all cities are added to the path
    for (int i = 1; i < cities.size(); ++i) {

        // Initialize the minimum distance and index of the next city
        double minDistance = std::numeric_limits<double>::max();
        int nextCityIndex = -1;

        // Get the current city (the last one added to the path)
        const QPointF& currentCity = path.last();

        // Loop through all cities to find the nearest unvisited city
        for (int j = 0; j < cities.size(); ++j) {
            if (!visited[j]) { // Only consider unvisited cities
                // Calculate the distance to this city
                double distance = calculateDistance(currentCity, cities[j]);

                // If this distance is the smallest so far, remember it
                if (distance < minDistance) {
                    minDistance = distance;
                    nextCityIndex = j;  // Update the index of the closest city
                }
            }
        }

        // If a valid next city was found, add it to the path
        if (nextCityIndex >= 0) {
            visited[nextCityIndex] = true;                   // Mark the city as visited
            path.append(cities[nextCityIndex]);              // Add it to the path
        }
    }

    // Return the final path (not a closed loop)
    return path;
}











QVector<QPointF> MainWindow::runDynamicProgramming(const QVector<QPointF>& cities) {

    // If there are fewer than 2 cities, no tour is possible
    if (cities.size() < 2) return QVector<QPointF>();

    int n = cities.size();  // Number of cities

    // Create a 2D vector to store distances between all pairs of cities
    QVector<QVector<double>> dist(n, QVector<double>(n));

    // Precompute Euclidean distances between each pair of cities
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = calculateDistance(cities[i], cities[j]);
        }
    }

    // dp[mask][i]: the shortest distance to reach set 'mask' of cities ending at city 'i'
    QVector<QVector<double>> dp(1 << n, QVector<double>(n, std::numeric_limits<double>::max()));

    // Starting condition: at city 0 with only city 0 visited
    dp[1][0] = 0;

    // Fill the DP table
    for (int mask = 1; mask < (1 << n); ++mask) {      // Iterate through all subsets of visited cities
        for (int u = 0; u < n; ++u) {                   // Last city in the path
            if ((mask & (1 << u)) == 0) continue;       // Skip if city 'u' is not in the mask
            for (int v = 0; v < n; ++v) {               // Try to go to every other city 'v'
                if (mask & (1 << v)) continue;          // Skip if city 'v' is already visited
                // Update the shortest path to the new mask ending at city 'v'
                dp[mask | (1 << v)][v] = std::min(
                    dp[mask | (1 << v)][v],
                    dp[mask][u] + dist[u][v]
                    );
            }
        }
    }

    // Reconstruct the shortest path from the DP table
    int mask = (1 << n) - 1;  // All cities visited
    int last = 0;

    // Find the city 'last' which gives the minimum cost ending path
    for (int i = 1; i < n; ++i) {
        if (dp[mask][i] < dp[mask][last]) {
            last = i;
        }
    }

    QVector<QPointF> path;
    path.append(cities[last]);     // Start from the last city in the path
    mask ^= (1 << last);           // Remove 'last' from the visited set

    // Backtrack to find the full path
    while (mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // Check if city 'i' is in the current mask
                double newCost = dp[mask][i] + dist[i][last];
                // If this was the path taken to reach 'last', it means 'i' is the previous city
                if (dp[mask | (1 << last)][last] == newCost) {
                    path.prepend(cities[i]); // Add city 'i' to the path
                    mask ^= (1 << i);        // Remove 'i' from the visited set
                    last = i;                // Move backward in the path
                    break;
                }
            }
        }
    }

    return path;  // Return the ordered list of cities in the optimal path
}










double MainWindow::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371;
    double lat1Rad = qDegreesToRadians(lat1);
    double lon1Rad = qDegreesToRadians(lon1);
    double lat2Rad = qDegreesToRadians(lat2);
    double lon2Rad = qDegreesToRadians(lon2);
    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1Rad) * cos(lat2Rad) * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}




double MainWindow::calculateTotalDistance(const QList<QTreeWidgetItem*>& path) {
    double total = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        total += haversine(
            path[i]->text(1).toDouble(), path[i]->text(2).toDouble(),
            path[i + 1]->text(1).toDouble(), path[i + 1]->text(2).toDouble()
            );
    }
    return total;
}








void MainWindow::onDeleteDrawings() {
    clearLines();
    ui->labelDistance->clear();
    // Cities (nodes) remain on screen
}







void MainWindow::clearLines() {
    if (!scene) return;  // Check if scene exists

    for (QGraphicsLineItem* line : lines) {
        if (line) {  // Check for null pointer
            if (scene->items().contains(line)) {  // Check if item is in scene
                scene->removeItem(line);
            }
            delete line;
            line = nullptr;  // Good practice
        }
    }
    lines.clear();
}









void MainWindow::animatePath(const QVector<QPointF>& path) {
    if (path.size() < 2) return;

    // Clear only the lines, preserving city nodes
    clearLines();
    ui->labelDistance->clear();

    // Calculate total distance first
    double totalDistance = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        totalDistance += calculateDistance(path[i], path[i+1]);
    }
    if (path.size() > 2) {  // Only complete loop if more than 2 points
        totalDistance += calculateDistance(path.last(), path.first());
    }
    ui->labelDistance->setText(QString("Total Distance: %1 km").arg(totalDistance, 0, 'f', 2));

    // Use smart pointers for safer memory management
    std::shared_ptr<int> index(new int(0));
    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (*index > path.size()) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Draw closing segment only if we have enough points
        if (*index == path.size() && path.size() > 2) {
            QGraphicsLineItem* line = scene->addLine(
                QLineF(path.last(), path.first()),
                QPen(Qt::red, 2)
                );
            lines.append(line);
            (*index)++;
            return;
        }

        if (*index < path.size() - 1) {
            QGraphicsLineItem* line = scene->addLine(
                QLineF(path[*index], path[*index + 1]),
                QPen(Qt::red, 2)
                );
            lines.append(line);
        }

        (*index)++;
    });

    timer->start(700);
}








double MainWindow::calculateDistance(const QPointF& p1, const QPointF& p2) {
    // Use more numerically stable calculation for large distances
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    return std::hypot(dx, dy); // More stable than sqrt(dx*dx + dy*dy)
}









void MainWindow::resetToInitialState()
{
    // Clear everything
    ui->tableCities->clear();
    scene->clear();
    lines.clear();
    ui->labelDistance->clear();

    // Add Egypt map background again
    addEgyptMapBackground();

    // Define default cities with colors
    struct City {
        QString name;
        double lat;
        double lon;
        QColor color;
    };

    QVector<City> defaultCities = {
        {"Cairo", 29.8, 31.8, Qt::blue},
        {"Alexandria", 30.7, 29.9553, Qt::red},
        {"Giza", 29.3, 31.7, Qt::green},
        {"Luxor", 24.8, 33.5, Qt::yellow},
        {"Aswan", 23.7, 33.5, Qt::cyan},
        {"Sharm El-Sheikh", 27.6, 35.1, Qt::magenta},
        {"Hurghada", 26.8, 34.3, Qt::gray},
        {"Suez", 29.8, 33.3, Qt::darkBlue},
        {"Port Said", 31.4, 32.3, Qt::darkGreen},
        {"Ismailia", 30.5898, 32.2682, Qt::darkRed}
    };

    // Repopulate table and scene
    for (const auto& city : defaultCities) {
        // Add to table
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, city.name);
        item->setText(1, QString::number(city.lat));
        item->setText(2, QString::number(city.lon));
        ui->tableCities->addTopLevelItem(item);

        // Add to scene
        QPointF point = toPointF(city.lat, city.lon);
        scene->addEllipse(point.x()-3, point.y()-3, 6, 6,
                          QPen(city.color), QBrush(city.color));
        // Add city name label
        QGraphicsTextItem* label = scene->addText(city.name);
        QColor labelColor = city.color;
        // Use black for bright colors for better visibility
        if (labelColor == Qt::yellow || labelColor == Qt::cyan || labelColor == Qt::green || labelColor == Qt::gray) {
            labelColor = Qt::black;
        }
        label->setDefaultTextColor(labelColor);
        label->setPos(point.x() + 7, point.y() - 7); // Offset label from point
    }
}

void MainWindow::addEgyptMapBackground() {
    // Remove any previous background
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->data(0) == "egypt_map") {
            scene->removeItem(item);
            delete item;
        }
    }
    QPixmap mapPixmap("Egypt_Map.png"); // Now loads from the project source directory
    if (mapPixmap.isNull()) {
        qDebug() << "Failed to load Egypt_Map.png!";
    } else {
        qDebug() << "Loaded Egypt_Map.png successfully.";
        QGraphicsPixmapItem* mapItem = scene->addPixmap(mapPixmap);
        mapItem->setPos(0, 0); // Top-left at (0,0)
        mapItem->setScale(1.0); // No scaling
        mapItem->setZValue(-100);
        mapItem->setData(0, "egypt_map");
        // Set the scene rect to the image size
        scene->setSceneRect(0, 0, mapPixmap.width(), mapPixmap.height());
        // Fit the view to the scene
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}
