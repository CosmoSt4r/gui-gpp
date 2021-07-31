#include "templateswindow.h"
#include "ui_templateswindow.h"
#include "fstream"

void
saveTemplates(const std::vector<Command>& commands, const std::string& filename)
{
    std::ofstream file(filename);

    for (const Command& command : commands){

        file << command.templateName + "\n";

        for (const std::string& source : command.sourceFiles)
        { file << source + " "; }

        file << "\n" + command.includePath + "\n" + command.libPath +
                "\n" + command.outputPath + " \n" + command.outputName + "\n";

        for (const std::string& lib : command.libraries)
        { file << lib + " "; }

        file << "\n" + command.optimization + "\n" + command.standard + "\n";
    }

    file.close();
}

void
readTemplates(std::vector<Command>& templates, const std::string& filename)
{
    std::ifstream file(filename);

    templates.clear();
    Command command;
    std::string line;

    while (!file.eof())
    {
        std::getline(file, line);
        command.templateName = line;

        std::getline(file, line);
        command.sourceFiles = stringSplit(line);

        std::getline(file, line);
        command.includePath = line;
        std::getline(file, line);
        command.libPath = line;
        std::getline(file, line);
        command.outputPath = line;
        std::getline(file, line);
        command.outputName = line;

        std::getline(file, line);
        command.libraries = stringSplit(line);

        std::getline(file, line);
        command.optimization = line;
        std::getline(file, line);
        command.standard = line;

        templates.push_back(command);
        command = Command();
    }
    file.close();
}

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
    saveTemplates(*commandTemplates, "templates.txt");
    readTemplates(*commandTemplates, "templates.txt");
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

