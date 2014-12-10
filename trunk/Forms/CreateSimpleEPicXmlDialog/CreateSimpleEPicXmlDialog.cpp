// ***********************************************************************************************
// *                                                                                             *
// * CreateSimpleEPicXmlDialog.cpp - Create a XML file from dialog input                         *
// *                                                                                             *
// * Dr. Rainer Sieger - 2012-01-11                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"
#include "CreateSimpleEPicXmlDialog.h"

CreateSimpleEPicXmlDialog::CreateSimpleEPicXmlDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(Clear_pushButton, SIGNAL( clicked() ), this, SLOT( Clear() ) );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void CreateSimpleEPicXmlDialog::Clear()
{
    this->PublicationAuthors_plainTextEdit->setPlainText( tr( "" ) );
    this->PublicationDate_lineEdit->setText( tr( "" ) );
    this->PublicationTitle_plainTextEdit->setPlainText( tr( "" ) );
    this->PublicationPages_lineEdit->setText( tr( "" ) );
    this->Publisher_lineEdit->setText( tr( "" ) );
    this->Place_lineEdit->setText( tr( "" ) );

    this->RelatedPublicationAuthors_plainTextEdit->setPlainText( tr( "" ) );
    this->RelatedPublicationDate_lineEdit->setText( tr( "" ) );
    this->RelatedPublicationTitle_plainTextEdit->setPlainText( tr( "" ) );
    this->RelatedPublicationSource_plainTextEdit->setPlainText( tr( "" ) );

    this->PublicationAuthors_plainTextEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

int MainWindow::doCreateSimpleEPicXmlDialog( QString& s_PublicationAuthors, QString& s_PublicationDate, QString& s_PublicationTitle,
                                             QString& s_PublicationPages, QString& s_Publisher, QString& s_PublicationPlace, QString& s_RelatedPublicationAuthors,
                                             QString& s_RelatedPublicationDate, QString& s_RelatedPublicationTitle, QString& s_RelatedPublicationSource )
{
    int i_DialogResult = QDialog::Rejected;

    QValidator *page = new QIntValidator( 0, 9999, this );

// ***********************************************************************************************************************

    CreateSimpleEPicXmlDialog *dialog = new CreateSimpleEPicXmlDialog();

    dialog->PublicationPages_lineEdit->setValidator( page );

    dialog->OK_pushButton->setWhatsThis( "Close dialog" );
    dialog->Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog->PublicationAuthors_plainTextEdit->setPlainText( s_PublicationAuthors );
    dialog->PublicationDate_lineEdit->setText( s_PublicationDate );
    dialog->PublicationTitle_plainTextEdit->setPlainText( s_PublicationTitle );
    dialog->PublicationPages_lineEdit->setText( s_PublicationPages );
    dialog->Publisher_lineEdit->setText( s_Publisher );
    dialog->Place_lineEdit->setText( s_PublicationPlace );

    dialog->RelatedPublicationAuthors_plainTextEdit->setPlainText( s_RelatedPublicationAuthors );
    dialog->RelatedPublicationDate_lineEdit->setText( s_RelatedPublicationDate );
    dialog->RelatedPublicationTitle_plainTextEdit->setPlainText( s_RelatedPublicationTitle );
    dialog->RelatedPublicationSource_plainTextEdit->setPlainText( s_RelatedPublicationSource );

    dialog->PublicationAuthors_plainTextEdit->setFocus();

    dialog->move( posDialog );
    dialog->resize( dialog->sizeHint() );

// ******************************************************************************************************

    if ( dialog->exec() == QDialog::Accepted )
    {
        s_PublicationAuthors		= dialog->PublicationAuthors_plainTextEdit->toPlainText();
        s_PublicationDate			= dialog->PublicationDate_lineEdit->text();
        s_PublicationTitle          = dialog->PublicationTitle_plainTextEdit->toPlainText();
        s_PublicationPages          = dialog->PublicationPages_lineEdit->text();
        s_Publisher                 = dialog->Publisher_lineEdit->text();
        s_PublicationPlace          = dialog->Place_lineEdit->text();

        s_RelatedPublicationAuthors = dialog->RelatedPublicationAuthors_plainTextEdit->toPlainText();
        s_RelatedPublicationDate    = dialog->RelatedPublicationDate_lineEdit->text();
        s_RelatedPublicationTitle   = dialog->RelatedPublicationTitle_plainTextEdit->toPlainText();
        s_RelatedPublicationSource  = dialog->RelatedPublicationSource_plainTextEdit->toPlainText();

        i_DialogResult              = QDialog::Accepted;
    }

    posDialog  = dialog->pos();

    delete dialog;

    return( i_DialogResult );
}

