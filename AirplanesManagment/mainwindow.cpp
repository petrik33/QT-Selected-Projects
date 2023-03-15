#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filePath = "C:\\Qt\\Projects\\AirplanesManagment\\save.json";

    ui->tableWidgetFlights->setColumnCount(FLIGHT::PASSENGERS);
    ui->tableWidgetFlights->setEditTriggers(QTableWidget::NoEditTriggers);
    QStringList tableHeaders = FlightEnumClass::FLIGHT_ENUM_NAMES;
    tableHeaders.removeLast();
    ui->tableWidgetFlights->setHorizontalHeaderLabels(tableHeaders);
    ui->tableWidgetFlights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetFlights->verticalHeader()->setVisible(false);

    setWindowTitle("Flights Manager");

    ui->listWidgetPassengers->setWindowTitle("Passengers");

    flightsNum = 0;
    readFlights();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this, "Save", "Would you like to save files before exiting?",
                          QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        saveFlights();
    }
}

bool MainWindow::readFlights()
{
    Clear();
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,"Error","Couldn't open save file.");
        return false;
    }

    QByteArray saveData = saveFile.readAll();

    QJsonDocument saveDoc(QJsonDocument::fromJson(saveData));

//    QJsonObject json = saveDoc.object();
    if(!saveDoc.isArray())
    {
        QMessageBox::warning(this,"Error","Opened file may be corrupted.");
        return false;
    }

    if(saveDoc.isEmpty())
    {
        QMessageBox::warning(this,"Warning","File is empty.");
        return false;
    }

//    QJsonArray flightsArray = json["flights"].toArray();
    QJsonArray flightsArray = saveDoc.array();
    int flightsNum = flightsArray.size();
    for(int i = 0; i < flightsNum; i++)
    {
        QJsonObject flightObj = flightsArray[i].toObject();
        FlightData* pFlight = nullptr;
        pFlight = new FlightData(flightObj);
        if(pFlight != nullptr)
        {
            addFlight(*pFlight);
        }
    }

    return true;
}

bool MainWindow::saveFlights()
{
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this,"Error","Couldn't open save file.");
        return false;
    }

    QJsonArray flightsArray;
    for(int i = 0; i < flightsNum; i++)
    {
        FlightData* pFlight = flights[i];
        QJsonObject flightJSON;
        pFlight->save(flightJSON);
        flightsArray.append(flightJSON);
    }

    saveFile.write(QJsonDocument(flightsArray).toJson());

    return true;

}

void MainWindow::Clear()
{
    ui->tableWidgetFlights->clear();
    ui->tableWidgetFlights->setRowCount(0);
    ui->listWidgetPassengers->clear();
    ui->leditPassport->clear();
    flights.clear();
    flightsNum = 0;
    QStringList tableHeaders = FlightEnumClass::FLIGHT_ENUM_NAMES;
    tableHeaders.removeLast();
    ui->tableWidgetFlights->setHorizontalHeaderLabels(tableHeaders);
}

void MainWindow::addFlight(FlightData& flight)
{
    ui->tableWidgetFlights->setRowCount(++flightsNum);
    flights.push_back(&flight);
    QTableWidgetItem* number = new QTableWidgetItem(flight._number);
    number->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* destination = new QTableWidgetItem(flight._destination);
    destination->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* departure = new QTableWidgetItem(flight._departure.toString(dateFormat));
    departure->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* arrival = new QTableWidgetItem(flight._arrival.toString(dateFormat));
    arrival->setTextAlignment(Qt::AlignCenter);

    ui->tableWidgetFlights->setItem(flightsNum-1,int(FLIGHT::NUMBER),number);
    ui->tableWidgetFlights->setItem(flightsNum-1,int(FLIGHT::DESTINATION),destination);
    ui->tableWidgetFlights->setItem(flightsNum-1,int(FLIGHT::DEPARTURE),departure);
    ui->tableWidgetFlights->setItem(flightsNum-1,int(FLIGHT::ARRIVAL),arrival);
//    ui->tableWidgetFlights->setItem(flightsNum-1,0,number);
//    ui->tableWidgetFlights->setItem(flightsNum-1,1,destination);
//    ui->tableWidgetFlights->setItem(flightsNum-1,2,departure);
//    ui->tableWidgetFlights->setItem(flightsNum-1,3,arrival);
    //add passengers
}


void MainWindow::on_tableWidgetFlights_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if(current == nullptr)
    {
        ui->listWidgetPassengers->clear();
        return;
    }
    if(previous == nullptr || current->row()!=previous->row())
    {
        ui->listWidgetPassengers->clear();
        FlightData* flightSelected = flights[current->row()];
        int passengersNum = flightSelected->_passengers.size();
        for(int i = 0; i < passengersNum;i++)
        {
            Person* p = flightSelected->_passengers[i];
            new QListWidgetItem(p->_name,ui->listWidgetPassengers);
        }
    }

    //Debug: instantiate the flight to use passengers data
}

void MainWindow::on_pushBottonAddNewFlight_clicked()
{
    FlightDialog dlog(this);
    if(dlog.exec() == QDialog::Accepted)
    {
        FlightData* flight = dlog.flightFromDialog();
        if(flight != nullptr)
        {
            addFlight(*flight);
        }
    }
}

void MainWindow::on_pushButtonAddPassenger_clicked()
{
    int flightID = ui->tableWidgetFlights->currentRow();
    if(flightID >= 0 && flightID < flightsNum)
    {
        PassengerDialog dlog(this);
        if(dlog.exec() == QDialog::Accepted)
        {
            Person* person = dlog.personFromDialog();
            if(person != nullptr)
            {
                flights[flightID]->_passengers.push_back(person);
                new QListWidgetItem(person->_name,ui->listWidgetPassengers);
            }
        }
    }
}

//void MainWindow::on_listWidgetPassengers_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
//{
//    if(current != nullptr)
//    {

//    }
//}

void MainWindow::on_listWidgetPassengers_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
        FlightData* flightSelected = flights[ui->tableWidgetFlights->currentRow()];
        Person* selectedP = flightSelected->_passengers[currentRow];
        ui->leditPassport->setText(selectedP->_docID);
    }
    else
    {
        ui->leditPassport->clear();
    }
//    int passengersNum =
//    if(currentRow >= 0 && currentRow < flightSelected->_passengers.size())
//    {

//    }

}

void MainWindow::on_pushButtonRemovePassenger_clicked()
{
    int currentID = ui->listWidgetPassengers->currentRow();
    if(currentID >= 0)
    {
        QListWidgetItem* item = ui->listWidgetPassengers->currentItem();
        delete item;
        FlightData* flightSelected = flights[ui->tableWidgetFlights->currentRow()];
        flightSelected->_passengers.remove(currentID);
        ui->leditPassport->clear();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(saveFlights())
    {
        QMessageBox::information(this,"Saved","Flights data has been saved successfuly.");
    }
}

void MainWindow::on_actionClear_triggered()
{
    Clear();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionChoose_triggered()
{
    if(QMessageBox::question(this, "Test", "Would you like to save file before choosing different one?",
                          QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        saveFlights();
    }

    QString fileChosen = QFileDialog::getOpenFileName(this,"Choose file",
                                                      "C:\\Qt\\Projects\\AirplanesManagment","*.json");
    if(!fileChosen.isEmpty()) filePath = fileChosen;
    readFlights();
}
