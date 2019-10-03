#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QMap>
#include <QStandardItemModel>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
using namespace QtCharts;

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ResultWindow(QWidget* parent = nullptr);
    ~ResultWindow();
    QStandardItemModel* model;
    void updateData(QMap<QString, int>& map, QList<int>& list);
    QChartView* chartView;
    void resizeEvent(QResizeEvent* event);

private:
    Ui::ResultWindow* ui;
};

#endif // RESULTWINDOW_H
