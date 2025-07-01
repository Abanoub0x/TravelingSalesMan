/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBoxAlgo;
    QPushButton *btnStart;
    QPushButton *btnReset;
    QPushButton *btnAddCity;
    QTreeWidget *tableCities;
    QLineEdit *inputName;
    QLineEdit *inputLat;
    QLineEdit *inputLon;
    QLabel *labelDistance;
    QGraphicsView *graphicsView;
    QPushButton *btnDeleteDrawings;
    QPushButton *btnResetTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1502, 756);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        comboBoxAlgo = new QComboBox(centralwidget);
        comboBoxAlgo->addItem(QString());
        comboBoxAlgo->addItem(QString());
        comboBoxAlgo->addItem(QString());
        comboBoxAlgo->setObjectName("comboBoxAlgo");
        comboBoxAlgo->setGeometry(QRect(10, 20, 82, 28));
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");
        btnStart->setGeometry(QRect(10, 70, 83, 29));
        btnReset = new QPushButton(centralwidget);
        btnReset->setObjectName("btnReset");
        btnReset->setGeometry(QRect(10, 120, 83, 29));
        btnAddCity = new QPushButton(centralwidget);
        btnAddCity->setObjectName("btnAddCity");
        btnAddCity->setGeometry(QRect(10, 170, 83, 29));
        tableCities = new QTreeWidget(centralwidget);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        new QTreeWidgetItem(tableCities);
        tableCities->setObjectName("tableCities");
        tableCities->setGeometry(QRect(100, 10, 381, 192));
        inputName = new QLineEdit(centralwidget);
        inputName->setObjectName("inputName");
        inputName->setGeometry(QRect(500, 50, 113, 28));
        inputLat = new QLineEdit(centralwidget);
        inputLat->setObjectName("inputLat");
        inputLat->setGeometry(QRect(500, 100, 113, 28));
        inputLon = new QLineEdit(centralwidget);
        inputLon->setObjectName("inputLon");
        inputLon->setGeometry(QRect(500, 150, 113, 28));
        labelDistance = new QLabel(centralwidget);
        labelDistance->setObjectName("labelDistance");
        labelDistance->setGeometry(QRect(10, 300, 151, 20));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(680, 30, 671, 621));
        graphicsView->setMinimumSize(QSize(671, 0));
        btnDeleteDrawings = new QPushButton(centralwidget);
        btnDeleteDrawings->setObjectName("btnDeleteDrawings");
        btnDeleteDrawings->setGeometry(QRect(10, 220, 121, 29));
        btnResetTable = new QPushButton(centralwidget);
        btnResetTable->setObjectName("btnResetTable");
        btnResetTable->setGeometry(QRect(10, 260, 121, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1502, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBoxAlgo->setItemText(0, QCoreApplication::translate("MainWindow", "Brute Force", nullptr));
        comboBoxAlgo->setItemText(1, QCoreApplication::translate("MainWindow", "Greedy", nullptr));
        comboBoxAlgo->setItemText(2, QCoreApplication::translate("MainWindow", "Dynamic Programming", nullptr));

        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        btnAddCity->setText(QCoreApplication::translate("MainWindow", "Add City", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tableCities->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Longitude", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Latitude", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "City Name", nullptr));

        const bool __sortingEnabled = tableCities->isSortingEnabled();
        tableCities->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = tableCities->topLevelItem(0);
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("MainWindow", "31.2357", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("MainWindow", "30.0444", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Cairo", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = tableCities->topLevelItem(1);
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("MainWindow", "29.9187", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("MainWindow", "31.2001", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("MainWindow", "Alexandria", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = tableCities->topLevelItem(2);
        ___qtreewidgetitem3->setText(2, QCoreApplication::translate("MainWindow", "31.2089", nullptr));
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("MainWindow", "30.0131", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("MainWindow", "Giza", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = tableCities->topLevelItem(3);
        ___qtreewidgetitem4->setText(2, QCoreApplication::translate("MainWindow", "32.6396", nullptr));
        ___qtreewidgetitem4->setText(1, QCoreApplication::translate("MainWindow", "25.6872", nullptr));
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("MainWindow", "Luxor", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = tableCities->topLevelItem(4);
        ___qtreewidgetitem5->setText(2, QCoreApplication::translate("MainWindow", "32.8998", nullptr));
        ___qtreewidgetitem5->setText(1, QCoreApplication::translate("MainWindow", "24.0889", nullptr));
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("MainWindow", "Aswan", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = tableCities->topLevelItem(5);
        ___qtreewidgetitem6->setText(2, QCoreApplication::translate("MainWindow", "34.2399", nullptr));
        ___qtreewidgetitem6->setText(1, QCoreApplication::translate("MainWindow", "27.9158", nullptr));
        ___qtreewidgetitem6->setText(0, QCoreApplication::translate("MainWindow", "Sharm El-Sheikh", nullptr));
        QTreeWidgetItem *___qtreewidgetitem7 = tableCities->topLevelItem(6);
        ___qtreewidgetitem7->setText(2, QCoreApplication::translate("MainWindow", "33.8116", nullptr));
        ___qtreewidgetitem7->setText(1, QCoreApplication::translate("MainWindow", "27.2579", nullptr));
        ___qtreewidgetitem7->setText(0, QCoreApplication::translate("MainWindow", "Hurghada", nullptr));
        QTreeWidgetItem *___qtreewidgetitem8 = tableCities->topLevelItem(7);
        ___qtreewidgetitem8->setText(2, QCoreApplication::translate("MainWindow", "32.5484", nullptr));
        ___qtreewidgetitem8->setText(1, QCoreApplication::translate("MainWindow", "29.9730", nullptr));
        ___qtreewidgetitem8->setText(0, QCoreApplication::translate("MainWindow", "Suez", nullptr));
        QTreeWidgetItem *___qtreewidgetitem9 = tableCities->topLevelItem(8);
        ___qtreewidgetitem9->setText(2, QCoreApplication::translate("MainWindow", "32.2885", nullptr));
        ___qtreewidgetitem9->setText(1, QCoreApplication::translate("MainWindow", "31.2561", nullptr));
        ___qtreewidgetitem9->setText(0, QCoreApplication::translate("MainWindow", "Port Said", nullptr));
        QTreeWidgetItem *___qtreewidgetitem10 = tableCities->topLevelItem(9);
        ___qtreewidgetitem10->setText(2, QCoreApplication::translate("MainWindow", "32.2682", nullptr));
        ___qtreewidgetitem10->setText(1, QCoreApplication::translate("MainWindow", "30.5898", nullptr));
        ___qtreewidgetitem10->setText(0, QCoreApplication::translate("MainWindow", "Ismailia", nullptr));
        tableCities->setSortingEnabled(__sortingEnabled);

        inputName->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        inputLat->setText(QCoreApplication::translate("MainWindow", "Latitude", nullptr));
        inputLon->setText(QCoreApplication::translate("MainWindow", "Longitude", nullptr));
        labelDistance->setText(QCoreApplication::translate("MainWindow", "Total Distance", nullptr));
        btnDeleteDrawings->setText(QCoreApplication::translate("MainWindow", "Delete Drawings", nullptr));
        btnResetTable->setText(QCoreApplication::translate("MainWindow", "Reset Table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
