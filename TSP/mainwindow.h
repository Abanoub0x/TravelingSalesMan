#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTreeWidgetItem>
#include <QGraphicsPathItem>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void onAddCityClicked();
    void onStartClicked();
    void onResetClicked();
    void onDeleteDrawings();
    void clearLines();



private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;



    QList<QGraphicsLineItem*> lines; // To keep track of all drawn lines
    QPointF toPointF(double lat, double lon);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    double calculateDistance(const QPointF& p1, const QPointF& p2);
    double calculateTotalDistance(const QList<QTreeWidgetItem*>& path);
    void resetToInitialState();
    void animatePath(const QVector<QPointF>& path);
    QVector<QPointF> runGreedyAlgorithm(const QVector<QPointF>& cities);
    QVector<QPointF> runDynamicProgramming(const QVector<QPointF>& cities);
    QVector<QPointF> runBruteForce(const QVector<QPointF>& cities);
    void drawCity(const QString& name, double lat, double lon, const QColor& color);
    void addEgyptMapBackground();
};

#endif // MAINWINDOW_H
