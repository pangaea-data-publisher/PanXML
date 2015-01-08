#ifndef CREATESIMPLEEPICXMLDIALOG_H
#define CREATESIMPLEEPICXMLDIALOG_H

#include <QDialog>

#include "ui_createsimpleepicxmldialog.h"

class CreateSimpleEPicXmlDialog : public QDialog, public Ui::CreateSimpleEPicXmlDialog
{
Q_OBJECT

public:
    CreateSimpleEPicXmlDialog(QWidget *parent = 0);

private slots:
    void Clear();
};

#endif // CREATESIMPLEEPICXMLDIALOG_H
