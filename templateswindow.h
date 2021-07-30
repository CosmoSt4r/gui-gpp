#ifndef TEMPLATESWINDOW_H
#define TEMPLATESWINDOW_H

#include <QMainWindow>

namespace Ui {
class TemplatesWindow;
}

class TemplatesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TemplatesWindow(QWidget *parent = nullptr);
    ~TemplatesWindow();

private:
    Ui::TemplatesWindow *ui;
};

#endif // TEMPLATESWINDOW_H
