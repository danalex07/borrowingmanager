#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString("%1/database.db").arg(QApplication::applicationDirPath()));

    if(db.open()) qDebug()<<"database open";
    else qDebug()<<"database not open";

    borrowModel = new QSqlTableModel(this,db);
    borrowModel->setTable("borrow");
    borrowModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    borrowModel->select();


    borrowModel->setHeaderData(1, Qt::Horizontal, tr("Device"));
    borrowModel->setHeaderData(2, Qt::Horizontal, tr("Quantity"));
    borrowModel->setHeaderData(3, Qt::Horizontal, tr("Name"));
    borrowModel->setHeaderData(4, Qt::Horizontal, tr("Out Description"));
    borrowModel->setHeaderData(5, Qt::Horizontal, tr("Date Out"));
    borrowModel->setHeaderData(6, Qt::Horizontal, tr("State"));
    borrowModel->setHeaderData(7, Qt::Horizontal, tr("Date In"));
    borrowModel->setHeaderData(8, Qt::Horizontal, tr("Description In"));

    ui->tableView->setModel(borrowModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->hideColumn(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}
