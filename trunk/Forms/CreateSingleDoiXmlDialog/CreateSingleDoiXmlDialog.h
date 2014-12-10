#ifndef CREATESINGLEDOIXMLDIALOG_H
#define CREATESINGLEDOIXMLDIALOG_H

#include <QDialog>

#include "ui_createsingledoixmldialog.h"

class CreateSingleDoiXmlDialog : public QDialog, public Ui::CreateSingleDoiXmlDialog
{
Q_OBJECT

public:
    CreateSingleDoiXmlDialog( QWidget *parent = 0 );
    QString getDocumentDir();

private slots:
    void browseDirDialog();
    void setExample();
    void clearDialog();
};

#endif
