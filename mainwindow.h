#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QProcess>

#include "command.h"
#include "templateswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void parseForm();

    void on_sourceAdd_clicked();
    void on_includeButton_clicked();
    void on_libPathButton_clicked();
    void on_compileButton_clicked();
    void on_sourceClear_clicked();
    void on_copyButton_clicked();
    void on_outPathButton_clicked();
    void on_compileRunButton_clicked();

    void on_actionManage_triggered();

private:
    Ui::MainWindow *ui;
    Command command;
    std::vector<Command> commandTemplates;
    TemplatesWindow* templatesWindow;
};
#endif // MAINWINDOW_H
