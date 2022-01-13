#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int series_def;
    int events;

private slots:
    void BeginDef();
    int getRandomNumber(int min, int max);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
