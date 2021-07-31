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


void TemplatesWindow::on_saveButton_clicked()
{
    command->templateName = ui->tempNameLineEdit->text().toStdString();

    for (Command &temp : *commandTemplates)
    {
        if (temp.templateName == command->templateName)
        {
            QMessageBox msgBox;
            QString message = "Template with name '" + QString::fromStdString(temp.templateName)
                    + "' already exists.";
            msgBox.setText(message);
            msgBox.setInformativeText("Do you want to save it anyway?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();

            switch(ret)
            {
            case QMessageBox::Save:
                temp = *command;
                this->~TemplatesWindow();
                return;
            case QMessageBox::Cancel:
                return;
            }
        }
    }

    commandTemplates->push_back(*command);
    this->~TemplatesWindow();
}

