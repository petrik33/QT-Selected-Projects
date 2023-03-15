#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu* fileMenu = new QMenu("File");
    QAction* actSave = new QAction("Save");
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveBooks()));
    QAction* actSaveAs = new QAction("Save as...");
    connect(actSaveAs,SIGNAL(triggered()),this,SLOT(onSaveAs()));
    QAction* actLoad = new QAction("Load...");
    connect(actLoad,SIGNAL(triggered()),this,SLOT(onLoad()));
    QAction* actClear = new QAction("Clear");
    connect(actClear,SIGNAL(triggered()),this,SLOT(clear()));
    QAction* actExit = new QAction("Exit");
    connect(actExit,SIGNAL(triggered()),this,SLOT(onExit()));

    fileMenu->addAction(actSave);
    fileMenu->addAction(actSaveAs);
    fileMenu->addAction(actLoad);
    fileMenu->addAction(actClear);
    fileMenu->addSeparator();
    fileMenu->addAction(actExit);

    menuBar()->addMenu(fileMenu);

    QHBoxLayout* mainLayout = new QHBoxLayout();

    QWidget* w = new QWidget();
    setCentralWidget(w);
    w->setLayout(mainLayout);

    QVBoxLayout* tableLayout = new QVBoxLayout();

    table = new QTableWidget();

    table->setRowCount(0);
    table->setColumnCount(4);

    const QStringList labels = {"Number","Name","Year","Pages"};
    table->setHorizontalHeaderLabels(labels);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);

    connect(table,SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
            this,SLOT(onTableItemChanged(QTableWidgetItem*, QTableWidgetItem*)));


    QHBoxLayout* tableBtnsLayout = new QHBoxLayout();
    QPushButton* btnAddBook = new QPushButton("+");
    connect(btnAddBook,SIGNAL(clicked()),this,SLOT(onAddBook()));
    QPushButton* btnRemoveBook = new QPushButton("-");
    connect(btnAddBook,SIGNAL(clicked()),this,SLOT(onRemoveBook()));
    tableBtnsLayout->addWidget(btnAddBook);
    tableBtnsLayout->addWidget(btnRemoveBook);

    tableLayout->addWidget(table);
    tableLayout->addLayout(tableBtnsLayout);

    QVBoxLayout* listLayout = new QVBoxLayout();

    list = new QListWidget();

    QHBoxLayout* listBtnsLayout = new QHBoxLayout();
    QPushButton* btnAddList = new QPushButton("+");
    connect(btnAddList,SIGNAL(clicked()),this,SLOT(onAddAuthor()));
    QPushButton* btnRemoveList = new QPushButton("-");
    connect(btnRemoveList,SIGNAL(clicked()),this,SLOT(onRemoveAuthor()));
    listBtnsLayout->addWidget(btnAddList);
    listBtnsLayout->addWidget(btnRemoveList);

    listLayout->addWidget(list);
    listLayout->addLayout(listBtnsLayout);

    mainLayout->addLayout(tableLayout);
    mainLayout->addLayout(listLayout);

    resize(800,800);
    setMinimumSize(800,800);

    table->setMinimumWidth(500);
    list->setMaximumWidth(450);

    setWindowTitle("Library");

    readBooks();

}

MainWindow::~MainWindow()
{

}

void MainWindow::onLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Load Data",qApp->applicationDirPath(),"*.json");
    if(!fileName.isEmpty())
    {
        filePath = fileName;
        readBooks();
    }
}

void MainWindow::saveBooks()
{
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this,"Error","Couldn't open save file.");
        return;
    }

    QJsonArray booksArray;
    for(int i = 0; i < books.size(); i++)
    {
        Book* book = books[i];
        QJsonObject bookJSON;
        book->save(bookJSON);
        booksArray.append(bookJSON);
    }

    saveFile.write(QJsonDocument(booksArray).toJson());
}

void MainWindow::onExit()
{
    QApplication::quit();
}

void MainWindow::onSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save Data",qApp->applicationDirPath(),"*.json");
    if(!fileName.isEmpty())
    {
        filePath = fileName;
        saveBooks();
    }
}

void MainWindow::readBooks()
{
    clear();
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,"Error","Couldn't open save file.");
        return;
    }

    QByteArray saveData = saveFile.readAll();

    QJsonDocument saveDoc(QJsonDocument::fromJson(saveData));

    if(!saveDoc.isArray())
    {
        QMessageBox::warning(this,"Error","Opened file may be corrupted.");
        return;
    }

    if(saveDoc.isEmpty())
    {
        QMessageBox::warning(this,"Warning","File is empty.");
        return;
    }

    QJsonArray booksArray = saveDoc.array();
    int booksNum = booksArray.size();
    for(int i = 0; i < booksNum; i++)
    {
        QJsonObject bookObj = booksArray[i].toObject();
        Book* book = nullptr;
        book = new Book(bookObj);
        if(book != nullptr)
        {
            addBook(*book);
        }
    }
}

void MainWindow::onAddBook()
{
    AddBookDialog d;
    if(d.exec() == QDialog::Accepted)
    {
        int number = d.lnEdtNumber->text().toInt();
        QString name = d.lnEdtName->text();
        int year = d.lnEdtYear->text().toInt();
        int pages = d.lnEdtPages->text().toInt();
        Book* book = new Book(number,name,year,pages);
        addBook(*book);
    }
}

void MainWindow::onRemoveBook()
{
    int currentID = table->currentRow();
    if(currentID >= 0){
        books.remove(currentID);
        table->removeRow(currentID);
        list->clear();
    }
}

void MainWindow::onAddAuthor()
{
    int currentID = table->currentRow();
    if(currentID >= 0){
        QString author = QInputDialog::getText(this,"Author","Full Name");
        if(!author.isEmpty())
        {
            list->addItem(author);
            books[currentID]->authors.push_back(author);
        }
    }

}

void MainWindow::onRemoveAuthor()
{
    int currentAuthorID = list->currentRow();
    if(currentAuthorID >= 0)
    {
        int currentID = table->currentRow();
        QListWidgetItem* item = list->currentItem();
        delete item;
        books[currentID]->authors.removeAt(currentAuthorID);
    }
}

void MainWindow::clear()
{
    books.clear();
    table->setRowCount(0);
    list->clear();
}

void MainWindow::onTableItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if(current == nullptr)
    {
        list->clear();
        return;
    }
    if(previous == nullptr || current->row()!=previous->row())
    {
        list->clear();
        Book* bookSelected = books[current->row()];
        int authorsNum = bookSelected->authors.size();
        for(int i = 0; i < authorsNum;i++)
        {
            new QListWidgetItem(bookSelected->authors[i],list);
        }
    }
}

void MainWindow::addBook(Book& book)
{
    int booksNum = books.size();
    table->setRowCount(++booksNum);
    books.push_back(&book);
    QTableWidgetItem* number = new QTableWidgetItem(QString::number(book.number));
    number->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* name = new QTableWidgetItem(book.name);
    name->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* year = new QTableWidgetItem(QString::number(book.year));
    year->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem* pages = new QTableWidgetItem(QString::number(book.pages));
    pages->setTextAlignment(Qt::AlignCenter);

    table->setItem(booksNum-1,0,number);
    table->setItem(booksNum-1,1,name);
    table->setItem(booksNum-1,2,year);
    table->setItem(booksNum-1,3,pages);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this, "Save", "Would you like to save files before exiting?",
                          QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        saveBooks();
    }
    QWidget::closeEvent(event);
}

