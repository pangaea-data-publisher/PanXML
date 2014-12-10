/* 2008-07-23                 */
/* Dr. Rainer Sieger          */

#include <QtGui>

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

int MainWindow::DeleteDoubleLines( const QString& s_FilenameIn, const QString& s_FilenameOut, const int i_NumOfFiles )
{
    int         i               = 0;
    int         n               = 0;

    int			i_stopProgress	= 0;

    QStringList sl_Input;

// **********************************************************************************************
// open output file

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text) == FALSE )
        return( -20 );

    QTextStream tout( &fout );

// **********************************************************************************************
// read file

    setWaitCursor();

    n = readFile( s_FilenameIn, sl_Input );

// **********************************************************************************************

    initProgress( i_NumOfFiles, s_FilenameIn, tr( "Deleting double lines..." ), sl_Input.count() );

// **********************************************************************************************

    tout << sl_Input.at( i++ ) << endl;

    while ( ( i<sl_Input.count() ) && ( i_stopProgress != APPBREAK ) )
    {
        if ( sl_Input.at( i ) != sl_Input.at( i-1) )
            tout << sl_Input.at( i ) << endl;

        i_stopProgress = incProgress( i_NumOfFiles, ++i );
    }

    fout.close();

    resetProgress( i_NumOfFiles );
    setNormalCursor();

    if ( i_stopProgress == APPBREAK )
        return( APPBREAK );

    return( NOERROR );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-04-07

void MainWindow::doDeleteDoubleLines()
{
    int         i				= 0;
    int         err				= 0;
    int         stopProgress	= 0;

    QString s_FilenameIn    = "";
    QString s_FilenameOut   = "";

// **********************************************************************************************

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gsl_FilenameList ) == TRUE )
    {
        initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Deleting double lines..." ) );

        while ( ( i < gsl_FilenameList.count() ) && ( err == NOERROR ) && ( stopProgress != APPBREAK ) )
        {
            if ( buildFilename( gi_ActionNumber, gs_FilenameFormat, gsl_FilenameList.at( i ), s_FilenameIn, s_FilenameOut ) == TRUE )
            {
                err = DeleteDoubleLines( s_FilenameIn, s_FilenameOut, gsl_FilenameList.count() );

                stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
            }
            else
            {
                err = FILENOTEXISTS;
            }
        }

        resetFileProgress( gsl_FilenameList.count() );
    }
    else
    {
        err = CHOOSEABORTED;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gsl_FilenameList, tr( "Done" ), tr( "Deleting double lines was canceled" ) );

    onError( err );
}

