//---------------------------------------------------------------------
//----mainwindow.cpp
//----skeleton was autogenerated by qt Creator
//----contains functions for the UI
//----------------------------------------------------------------------

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY
#endif

#ifndef __MAIN_CLASSES
#include "main_classes.h"
#define __MAIN_CLASSES
#endif




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addEntryButton_clicked()
{
    QString qTmpDesc, qTmpCurr, qTmpVal;
    std::string tmpDesc,tmpCurr,tmpVal;
    float tmpFVal;

    //get input text from the Desc, Curr, and Val widgets
    qTmpDesc = ui->qInDesc->displayText();
    qTmpCurr = ui->qInCurr->displayText();
    qTmpVal = ui->qInVal->displayText();


    ui->qLogOut->setReadOnly(true);
    ui->qLogOut->setText(QString("the following expenditure entry had been stored\n")+
                            qTmpCurr + qTmpVal + QString(" ") + qTmpDesc);


    //convert to std string
    tmpDesc = qTmpDesc.toStdString();
    tmpCurr = qTmpCurr.toStdString();
    tmpVal = qTmpVal.toStdString();

    //ideally perform the error checking of the input, but that would be done later~~~
    tmpFVal = atof(tmpVal.c_str());
    Ev1.addEntry(tmpCurr,tmpFVal,tmpDesc);
}

void MainWindow::on_printAllButton_clicked()
{
    QString tmpQString;
    ui->qLogOut->setReadOnly(true);
    ui->qLogOut->setText(QString(""));

    //get expenditure as QString and output to LogOut
    for(int i=0; i<Ev1.getSize(); ++i){
        //tmpQString = QString::fromStdString(Ev1.getExpenditure(i));
        tmpQString = QString::fromUtf8(Ev1.getExpenditure(i).c_str());
        ui->qLogOut->append(tmpQString);
    }

}


//Load a csv file to the database
void MainWindow::on_actionLoad_triggered()
{   
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                tr("csv Files (*.csv);"));

    const char* fName = fileName.toStdString().c_str();
    Ev1.loadVctr(fName);

}

//save current database to a CSV file
void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                tr("csv Files (*.csv);"));

     const char* fName = fileName.toStdString().c_str();
     Ev1.exportVctr(fName);
}


//interface for the printVctr Range function
void MainWindow::on_printEntriesButton_clicked()
{
    QString qTmpStartDate, qTmpEndDate, qTmpViewMode;
    std::string tmpStartDate, tmpEndDate, tmpViewMode;

    if(Ev1.getSize()>0){
        qTmpStartDate = ui->qStartDate->displayText();
        qTmpEndDate = ui->qEndDate->displayText();
        qTmpViewMode = ui->qViewModeBox->currentText();

        tmpStartDate = qTmpStartDate.toStdString();
        tmpEndDate = qTmpEndDate.toStdString();
        tmpViewMode = qTmpViewMode.toStdString();

        dateMode_t tmpDateMode = perEntry;

       if(!tmpViewMode.compare("perEntry")) tmpDateMode = perEntry;
       if(!tmpViewMode.compare("perDay")) tmpDateMode = perDay;
       if(!tmpViewMode.compare("perMonth")) tmpDateMode = perMonth;
       if(!tmpViewMode.compare("perYear")) tmpDateMode = perYear;


       string tmpData = Ev1.printVctrRange(tmpStartDate,tmpEndDate,tmpDateMode);

       QString qTmpData = QString::fromStdString(tmpData);

       ui->qOutput->setReadOnly(true);
       ui->qOutput->setText(qTmpData);
    }

    else  ui->qOutput->setText(QString("the database is empty"));



}

void MainWindow::on_deleteEntryButton_clicked()
{
    QString tmpQString;
    ui->qLogOut->setReadOnly(true);

    if(Ev1.getSize()>0){
        tmpQString = QString::fromUtf8(Ev1.getExpenditure(Ev1.getSize()-1).c_str());
        Ev1.dropEntry();
        ui->qLogOut->setText(QString("the following expenditure entry had been deleted\n")+
                tmpQString);
    }

    else ui->qLogOut->setText(QString("the database is currently empty"));

}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}
