#include "templateswindow.h"
#include "ui_templateswindow.h"

TemplatesWindow::TemplatesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TemplatesWindow)
{
    ui->setupUi(this);
}

TemplatesWindow::~TemplatesWindow()
{
    delete ui;
}
