#ifndef TEMPLATESWINDOW_H
#define TEMPLATESWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "command.h"

namespace Ui {
class TemplatesWindow;
}

void readTemplates(std::vector<Command>& templates, const std::string& filename);

class TemplatesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplatesWindow(QWidget *parent,
                             Command* command, std::vector<Command>* commandTemplates);
    ~TemplatesWindow();

    Command* command;
    std::vector<Command>* commandTemplates;
private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::TemplatesWindow *ui;

    void fillCommandInfo();
};

#endif // TEMPLATESWINDOW_H
