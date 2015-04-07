// ***********************************************************************************************
// *                                                                                             *
// * SetOptionsDialog.cpp - Sets program options                                                 *
// *                                                                                             *
// * Dr. Rainer Sieger - 2010-10-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtWidgets>

#include "Application.h"
#include "SetOptionsDialog.h"

SetOptionsDialog::SetOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(browseDir_pushButton, SIGNAL( clicked() ), this, SLOT( browseDirDialog() ) );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void SetOptionsDialog::browseDirDialog()
{
    QString	sd_Path 	= "";
    QString s_Path 		= this->DirLineEdit->text();
    QString s_PathStart	= getDocumentDir();

// ***********************************************************************************************************************

    s_PathStart.replace( "//", "/" );

    if ( s_Path.isEmpty() == false )
        s_PathStart = s_Path;

    sd_Path = QFileDialog::getExistingDirectory( this,  tr( "Choose a folder for the output files" ), s_PathStart, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    if ( sd_Path.isEmpty() == false )
        s_Path = sd_Path;

    this->DirLineEdit->setText( QDir::toNativeSeparators( s_Path ) );

    DirLineEdit->setFocus();
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

QString SetOptionsDialog::getDocumentDir()
{
    #if defined(Q_OS_LINUX)
        return( QDir::homePath() );
    #endif

    #if defined(Q_OS_MAC)
        return( QDir::homePath() );
    #endif

    #if defined(Q_OS_WIN)
        return( QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) );
    #endif
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

int MainWindow::doSetOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

// ***********************************************************************************************************************

    SetOptionsDialog dialog( this );

    dialog.setCodecComboBox->setCurrentIndex( gi_Codec );
    dialog.DirLineEdit->setText( QDir::toNativeSeparators( gs_XmlPath ) );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );
    dialog.browseDir_pushButton->setWhatsThis( "Browse for the output directory" );

    dialog.move( posDialog );
    dialog.resize( sizeDialog );
    dialog.show();

// ******************************************************************************************************

    if ( dialog.exec() == QDialog::Accepted )
    {
        gi_Codec    	= dialog.setCodecComboBox->currentIndex();
        gs_XmlPath      = QDir::toNativeSeparators( dialog.DirLineEdit->text() );
        i_DialogResult  = QDialog::Accepted;
    }

    posDialog  = dialog.pos();
    sizeDialog = dialog.size();

    return( i_DialogResult );
}
