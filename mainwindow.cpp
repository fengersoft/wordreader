#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    resultWindow = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path == "") {
        return;
    }
    ui->edtPath->setText(path);
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream stm(&file);
    QString info = stm.readAll();
    ui->mmoInfo->setPlainText(info);
    file.close();
}

void MainWindow::on_btnAnaly_clicked()
{

    QString info = ui->mmoInfo->toPlainText();
    double m = info.length() + 1;
    ui->pb->setRange(0, 100);
    ui->pb->setValue(0);
    info = info.replace("\n", "");
    info = info.replace("\r", "");
    info = info.replace("\t", "");
    info = info.replace(" ", "");
    info = info.replace("，", "");
    info = info.replace("。", "");
    info = info.replace("、", "");
    info = info.replace("：", "");
    info = info.replace("？", "");
    info = info.replace("！", "");
    info = info.replace("”", "");
    info = info.replace("“", "");
    info = info.replace("　", "");
    QMap<QString, int> map;
    int n, s;
    while (info.length() > 2) {
        if (info.length() >= 10) {
            n = 10;
        } else {
            n = info.length();
        }
        bool find = false;
        for (int i = n; i >= 2; i--) {
            QString temp = info.left(i);
            if (map.value(temp, -1) == -1) {
                map.insert(temp, 1);
            } else {
                int v = map.value(temp);
                v++;
                map[temp] = v;
            }
        }

        info = info.mid(1);

        QApplication::processEvents();
        double d = info.length() / m;
        d = 1 - d;
        int w = d * 100;
        ui->pb->setValue(w);
    }
    ui->pb->setRange(1, 100);
    QList<int> list;
    QMap<QString, int>::iterator it = map.begin();
    for (; it != map.end(); it++) {
        list.append(it.value());
    }
    qSort(list.begin(), list.end());
    for (int i = list.count() - 1; i >= 0; i--) {
        if (list.at(i) < 5) {
            list.removeAt(i);
        }
    }

    if (resultWindow != nullptr) {
        delete resultWindow;
        resultWindow = nullptr;
    }
    resultWindow = new ResultWindow(this);
    resultWindow->updateData(map, list);
    resultWindow->show();
}
