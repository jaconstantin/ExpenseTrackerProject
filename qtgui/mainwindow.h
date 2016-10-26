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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addEntryButton_clicked();

    void on_printAllButton_clicked();

    void on_actionLoad_triggered();

    void on_actionSave_triggered();

    void on_printEntriesButton_clicked();

    void on_deleteEntryButton_clicked();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
