#include "resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->lvData->setModel(model);
    //    ui->lvData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->lvData->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    ui->lvData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lvData->verticalHeader()->setHidden(true);
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::updateData(QMap<QString, int>& map, QList<int>& list)
{
    int m = 0;
    int w = -1;
    QMap<int, int> tmpMap;
    model->clear();
    for (int i = list.count() - 1; i >= 0; i--) {
        int n = list.at(i);
        if (w == n) {
            continue;
        }
        if (n > 1) {
            QList<QString> names = map.keys(n);
            for (int j = 0; j < names.count(); j++) {
                m++;
                QList<QStandardItem*> items;
                QStandardItem* item1 = new QStandardItem();
                item1->setText(QString("%1").arg(m));
                items << item1;
                QStandardItem* item2 = new QStandardItem();
                item2->setText(names.at(j));
                items << item2;
                QStandardItem* item3 = new QStandardItem();
                item3->setText(QString("%1").arg(n));
                items << item3;
                model->appendRow(items);
                w = n;
                if (m == 100) {
                    QStringList labels;
                    labels << "序号"
                           << "关键词"
                           << "出现次数";
                    model->setHorizontalHeaderLabels(labels);
                    return;
                }
            }
        }
    }

    QStringList labels;
    labels << "序号"
           << "关键词"
           << "出现次数";
    model->setHorizontalHeaderLabels(labels);
}

void ResultWindow::resizeEvent(QResizeEvent* event)
{
}
