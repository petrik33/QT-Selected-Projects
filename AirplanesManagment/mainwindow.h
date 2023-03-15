#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <flightenumclass.h>
#include <QDebug>
#include <QDateTime>
#include <flightdata.h>
#include <QVector>
#include <flightdialog.h>
#include <passengerdialog.h>
#include <QMessageBox>
#include <QFileDialog>
#include <airplanesunitest.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_tableWidgetFlights_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

    void on_pushBottonAddNewFlight_clicked();

    void on_pushButtonAddPassenger_clicked();

//    void on_listWidgetPassengers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidgetPassengers_currentRowChanged(int currentRow);

    void on_pushButtonRemovePassenger_clicked();

    void on_actionSave_triggered();

    void on_actionClear_triggered();

    void on_actionExit_triggered();

    void on_actionChoose_triggered();

private:
    Ui::MainWindow *ui;
    QString filePath;
    bool readFlights();
    bool saveFlights();
    void Clear();
    void addFlight(FlightData& flight);
    QVector <FlightData*> flights;
    int flightsNum;

friend class AirplanesUniTest;
};
#endif // MAINWINDOW_H
