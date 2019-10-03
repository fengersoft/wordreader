#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "resultwindow.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    ResultWindow* resultWindow;
private slots:
    void on_btnOpen_clicked();

    void on_btnAnaly_clicked();

private:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
