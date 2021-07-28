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
MainWindow::on_sourceAdd_clicked()
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

    std::vector<std::string> vecFileNames;
    for (const QString& file : fileNames)
        vecFileNames.push_back(file.toStdString());

    MainWindow::command.addSourceFiles(vecFileNames);
    QString sourceFileNames = QString::fromStdString(MainWindow::command.getSourceFiles());
    ui->sourceFilesLabel->setText(sourceFileNames);
}


void
MainWindow::on_includeButton_clicked()
{
    QString path = getDirectoryPath();

    MainWindow::command.setIncludePath(path.toStdString());
    ui->includeLineEdit->setText(path);
}


void
MainWindow::on_libPathButton_clicked()
{
    QString path = getDirectoryPath();

    MainWindow::command.setLibPath(path.toStdString());
    ui->libPathLineEdit->setText(path);
}


void
MainWindow::parseForm()
{
    MainWindow::command.setIncludePath(ui->includeLineEdit->text().toStdString());
    MainWindow::command.setLibPath(ui->libPathLineEdit->text().toStdString());
    MainWindow::command.setLibraries(ui->libsLineEdit->text().toStdString());
    MainWindow::command.setOptimization(ui->optimComboBox->currentText().toStdString());
    MainWindow::command.setStandard(ui->stdComboBox->currentText().toStdString());
    MainWindow::command.setOutputName(ui->outputNameLineEdit->text().toStdString());
}


void
MainWindow::on_compileButton_clicked()
{
    if (MainWindow::command.getSourceFiles() == "")
        ui->cmdLineEdit->setText("Specify source files");
    else
    {
        parseForm();
        QString cmd = QString::fromStdString(MainWindow::command.get());
        ui->cmdLineEdit->setText(cmd);
    }
}


void MainWindow::on_sourceClear_clicked()
{
    MainWindow::command.clearSourceFiles();
    ui->sourceFilesLabel->clear();
}


void MainWindow::on_copyButton_clicked()
{
    ui->cmdLineEdit->selectAll();
    ui->cmdLineEdit->copy();
}


void MainWindow::on_outPathButton_clicked()
{
    QString path = getDirectoryPath() + "/";

    MainWindow::command.setOutputPath(path.toStdString());
    ui->outPathLineEdit->setText(path);
}

