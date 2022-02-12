#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TableWidget; }
QT_END_NAMESPACE

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

private slots:
    void readClicked();

private:
    Ui::TableWidget *ui;
    void setHeader(const QStringList&);
    void setRow(const int&);
    void setTableColor();
    void setItems(const int&, const QList<QString>&);
    void readTextFileLine(QString&);
};
#endif // TABLEWIDGET_H
