#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QtMath>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QListWidget>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSaveLog();
    void onRead();
    void onCountClicked();
    void onReadButtonGroupClicked(int id);
    void onFunctionChanged(int);
    QString countFunction(double value);
    QString readNumberFromFile();

private:
    QLineEdit* lnEdtInput{};
    QLineEdit* lnEdtResult{};
    QLabel* lblResult{};
    QPushButton* pshBtnCount{};
    QListWidget* lstVwCountHistory{};
    QButtonGroup* btnGrpReadFromFile{};
    QComboBox* cmbBxFunctions{};

    enum TFunctions{
        ASIN,
        ACOS,
        ATAN,
        ACATAN
    };

    bool readFile;
    QString filePath;
    QStringList history;
    TFunctions funcChosen = ASIN;
};
#endif // MAINWINDOW_H
