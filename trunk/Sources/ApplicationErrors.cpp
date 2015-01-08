/* ApplicationErrors.cpp      */
/* 2008-03-27                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! Errorhandling */

void MainWindow::onError( const int err )
{
    switch ( err )
    {
    case _APPBREAK_:  // Progress aborted
        break;
    case _ERROR_:     // Error
        break;
    case _NOERROR_:   // No error
        break;
    case _CHOOSEABORTED_: // Choose aborted
        break;
    case _FILENOTEXISTS_: // File not exists
        QMessageBox::information( this, getApplicationName( true ), tr( "Import file not exists." ) );
        break;
    case -3: // Progress aborted
        break;
    case -10:
        QMessageBox::information( this, getApplicationName( true ), tr( "Can't open import file.\nPossible locked by another application." ) );
        break;
    case -20:
        QMessageBox::information( this, getApplicationName( true ), tr( "Can't create export file.\nFile is already open." ) );
        break ;
    case -30:
        QMessageBox::information( this, getApplicationName( true ), tr( "Converter was canceled" ) );
        break ;
    case -40:
        QMessageBox::information( this, getApplicationName( true ), tr( "Wrong format" ) );
        break ;
    case -50:
        QMessageBox::information( this, getApplicationName( true ), tr( "Only one file selected" ) );
        break ;
    case -60:
        break;
    default :
        QMessageBox::information( this, getApplicationName( true ), tr( "Unknown error.\nPlease contact rsieger@pangaea.de" ) );
        break ;
    }
}

