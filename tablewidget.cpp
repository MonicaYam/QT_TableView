#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QMessageBox> //display error
#include <QFile>     //get file
#include <QFileInfo> //get file info
#include <QList>
#include <QPalette>

//What is this program?
//read file and show the contents with table view.

// NOTE:
//alternatingRowColors is true in tablewidget.ui to use two colours for table view.
//
// NOTE (file rules):
// A file that uses a comma to separate values
// First line will use as header
// if user put only file name, this program go to check
// C:\Users\username\Documents\QTProjects\build-QTTableView-Desktop_Qt_6_2_3_MSVC2019_64bit-Debug
TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    setWindowTitle("TableView");
    connect(ui->read, SIGNAL(clicked()), this,
            SLOT(readClicked()));

}

TableWidget::~TableWidget()
{
    delete ui;
}

//Get file info and Read file line by line
void TableWidget::readTextFileLine(QString& filePath){
    int rowCount,lineCount = 0;
    //one element has one line of file
    QList<QString> fileContent;
    QStringList headerNameList;
    QFile file(filePath);

    fileContent.clear();
    headerNameList.clear();

    //Check file
    if (! file.open(QIODevice::ReadOnly)) {
        QFileInfo fileInfo(filePath);
        QString errStr = "file(" + fileInfo.absoluteFilePath() + ") Open Error:" + file.errorString();

        QMessageBox::warning(this, "Open Error", errStr);
        qDebug() << errStr;
        return;
    }

    //input file
    QTextStream in(&file);

    //read line until the EOF
    while (! in.atEnd()) {
        //read line
        QString line = in.readLine();

        //check empty line and if it is empty line, do nothing.
        if(line.size()>0){
            //if lineCount is 0, it is header info
            if(lineCount == 0){
                headerNameList = line.split(",");
            }else{
                // add the content of line at the end of list
                fileContent.append(line);
            }

            //count line number
            ++lineCount;
        }
    }

    //close file
    file.close();

    rowCount = lineCount - 1;

    //Set header and row and items in table view
    setHeader(headerNameList);
    setRow(rowCount);
    setTableColor();
    setItems(rowCount, fileContent);

}

//Set header in table
void TableWidget::setHeader(const QStringList& headerName){
    ui->tableWidget->setColumnCount(headerName.count());
    ui->tableWidget->setHorizontalHeaderLabels(headerName);

}

//Set row in the table
void TableWidget::setRow(const int& rowCount){
    ui->tableWidget->setRowCount(rowCount);
}

//Set table's bg colors and font color
void TableWidget::setTableColor(){
    QPalette p = ui->tableWidget->palette();
    //Change bg colors
    p.setColor(QPalette::Base,  QColor(255,139,148));
    p.setColor(QPalette::AlternateBase,  QColor(255,170,165));
    //Change font color
    p.setColor(QPalette::Text, QColor(255,255,255));

    //set these color on table
    ui->tableWidget->setPalette(p);
}

//Set all items in table view
void TableWidget::setItems(const int& rowCount, const QList<QString>& fileContent){
    QStringList itemList;
    bool is_ok; // to check some strings are num or not.

    //set items in table view
    for(int i=0; i< rowCount; ++i){
        itemList = fileContent[i].split(",");

        for(int k=0; k < itemList.count(); ++k){
            QTableWidgetItem *item = ui->tableWidget->item(i,k);
            //if item is not existing, then create
            if(!item){
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(i,k, item);
            }

            if(itemList[k].toDouble(&is_ok)){
                //if it is number
                item->setTextAlignment(Qt::AlignRight);
            }else{
                //if it is string
                item->setTextAlignment(Qt::AlignLeft);
            }
            item->setText(itemList[k]);
        }
    }
}
void TableWidget::readClicked()
{
    QString filePath = ui->filePathForm->text();
    readTextFileLine(filePath);
}

