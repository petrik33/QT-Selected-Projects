#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMenu>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>
#include <QComboBox>
#include <QCloseEvent>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include <book.h>
#include <addbookdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:

    void onLoad();
    void saveBooks();
    void onExit();
    void onSaveAs();
    void readBooks();
    void onAddBook();
    void onRemoveBook();
    void onAddAuthor();
    void onRemoveAuthor();
    void clear();
    void onTableItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
protected:
    void addBook(Book& book);
    void closeEvent(QCloseEvent* event) override;
private:
    QTableWidget* table;
    QListWidget* list;
    Ui::MainWindow *ui;
    QVector<Book*> books;
    QString filePath = "C:\\Qt\\Projects\\MVC_PatternLab\\Data.json";

};
#endif // MAINWINDOW_H
