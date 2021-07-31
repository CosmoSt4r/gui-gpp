#include "mainwindow.h"
#include "templateswindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readTemplates(commandTemplates, "templates.txt");
    updateTemplatesList();
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

    MainWindow::command.includePath = path.toStdString();
    ui->includeLineEdit->setText(path);
}


void
MainWindow::on_libPathButton_clicked()
{
    QString path = getDirectoryPath();

    MainWindow::command.libPath = path.toStdString();
    ui->libPathLineEdit->setText(path);
}


void
MainWindow::parseForm()
{
    MainWindow::command.includePath = ui->includeLineEdit->text().toStdString();
    MainWindow::command.libPath = ui->libPathLineEdit->text().toStdString();
    MainWindow::command.setLibraries(ui->libsLineEdit->text().toStdString());
    MainWindow::command.optimization = ui->optimComboBox->currentText().toStdString();
    MainWindow::command.standard = ui->stdComboBox->currentText().toStdString();
    MainWindow::command.outputName = ui->outputNameLineEdit->text().toStdString();
    MainWindow::command.outputPath = ui->outPathLineEdit->text().toStdString();
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

        QProcess process;
        process.start(cmd);
        process.waitForFinished(-1);

        ui->outputPlainText->clear();
        ui->outputPlainText->appendPlainText(process.readAllStandardError());
        ui->outputPlainText->appendPlainText(process.readAllStandardOutput());
    }
}


void
MainWindow::on_compileRunButton_clicked()
{
    on_compileButton_clicked();

    QString filepath = QString::fromStdString(MainWindow::command.getFilePath());
    if (QFileInfo::exists(filepath) && QFileInfo(filepath).isFile())
        system( ("start " + filepath.toStdString()).c_str() );
}


void
MainWindow::on_sourceClear_clicked()
{
    MainWindow::command.clearSourceFiles();
    ui->sourceFilesLabel->clear();
}


void
MainWindow::on_copyButton_clicked()
{
    ui->cmdLineEdit->selectAll();
    ui->cmdLineEdit->copy();
}


void
MainWindow::on_outPathButton_clicked()
{
    QString path = getDirectoryPath() + "/";

    MainWindow::command.outputPath = path.toStdString();
    ui->outPathLineEdit->setText(path);
}


void
MainWindow::updateTemplatesList()
{
    ui->templatesList->clear();
    for (const Command& command: commandTemplates)
        ui->templatesList->addItem(QString::fromStdString(command.templateName));
}


void
MainWindow::on_saveTempButton_clicked()
{
    parseForm();
    templatesWindow = new TemplatesWindow(this, &command, &commandTemplates);
    templatesWindow->show();
    updateTemplatesList();
}

void MainWindow::on_templatesRButton_clicked(bool checked)
{ ui->templatesList->setVisible(checked); }


void MainWindow::on_outputRButton_toggled(bool checked)
{ ui->outputPlainText->setVisible(checked); }


void MainWindow::on_templatesList_currentRowChanged(int currentRow)
{
    command = commandTemplates[currentRow];

    ui->sourceFilesLabel->setText(QString::fromStdString(command.getSourceFiles()));
    ui->includeLineEdit->setText(QString::fromStdString(command.includePath));
    ui->libPathLineEdit->setText(QString::fromStdString(command.libPath));
    ui->outPathLineEdit->setText(QString::fromStdString(command.outputPath));
    ui->outputNameLineEdit->setText(QString::fromStdString(command.outputName));

    QString libraries = "";
    for (const std::string& lib : command.libraries)
        libraries += QString::fromStdString(lib) + " ";
    ui->libsLineEdit->setText(libraries);

    ui->optimComboBox->setCurrentText(QString::fromStdString(command.optimization));
    ui->stdComboBox->setCurrentText(QString::fromStdString(command.standard));
}
