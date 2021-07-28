#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include "command.h"

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
    void on_sourceAdd_clicked();
    void on_includeButton_clicked();
    void on_libPathButton_clicked();
    void on_compileButton_clicked();

    void on_sourceClear_clicked();

private:
    Ui::MainWindow *ui;
    Command command;
};
#endif // MAINWINDOW_H
