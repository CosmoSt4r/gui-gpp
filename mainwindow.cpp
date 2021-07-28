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

QString
getDirectoryPath()
{
    QFileDialog dialog;
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::Directory);

    QString path;
    path = dialog.getExistingDirectory();

    return path;
}

void
MainWindow::on_sourceButton_clicked()
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
    QString sourceFileNames = QString::fromStdString(MainWindow::command.getSourceFiles());
    ui->sourceLineEdit->setText(sourceFileNames);
}

void
MainWindow::on_includeButton_clicked()
{
    QString path = getDirectoryPath();

    MainWindow::command.setIncludePath(path.toStdString());
    ui->includeLineEdit->setText(path);
}


void MainWindow::on_libPathButton_clicked()
{
    QString path = getDirectoryPath();

    MainWindow::command.setLibPath(path.toStdString());
    ui->libPathLineEdit->setText(path);
}

