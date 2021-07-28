#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sourceButton_clicked()
{
    QFileDialog dialog;
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList filters;
    filters.push_back("*.cpp");
    filters.push_back("*.c");
    dialog.setNameFilters(filters);

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    QString filePaths = "";
    for (int i = 0; i < fileNames.size(); ++i)
    {
        filePaths += fileNames[i] + " ";
    }

    MainWindow::command.setSourceFiles(filePaths.toStdString());
    QString x = QString::fromStdString(MainWindow::command.getSourceFiles());
    ui->sourceLineEdit->setText(x);

}

