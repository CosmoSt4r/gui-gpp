#include "templateswindow.h"
#include "ui_templateswindow.h"

void
TemplatesWindow::fillCommandInfo()
{
    std::string files = "";
    for (const std::string& file : command->sourceFiles)
        files += file + '\n';
    ui->sourceTextEdit->setPlainText(QString::fromStdString(files));

    files = "";
    for (const std::string& file : command->libraries)
        files += file + '\n';
    ui->dependenciesLineEdit->setText(QString::fromStdString(files));

    ui->includeLineEdit->setText(QString::fromStdString(command->includePath));
    ui->librariesLineEdit->setText(QString::fromStdString(command->libPath));
    ui->outputLineEdit->setText(QString::fromStdString(command->outputPath));

    ui->optimLineEdit->setText(QString::fromStdString(command->optimization));
    ui->stdLineEdit->setText(QString::fromStdString(command->standard));

    ui->outNameLineEdit->setText(QString::fromStdString(command->outputName));
}

TemplatesWindow::TemplatesWindow(QWidget *parent,
                                 Command* command, std::vector<Command>* commandTemplates) :
    QMainWindow(parent),
    ui(new Ui::TemplatesWindow)
{
    this->command = command;
    this->commandTemplates = commandTemplates;

    ui->setupUi(this);
    fillCommandInfo();
}

TemplatesWindow::~TemplatesWindow()
{
    delete ui;
}

void TemplatesWindow::on_cancelButton_clicked()
{
    this->~TemplatesWindow();
}

