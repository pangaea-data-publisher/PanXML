/* CreateePicXml.cpp          */
/* 2010-01-10                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-01-10

int MainWindow::CreateSimpleEPicXml( const QString& s_XmlSchema, const QStringList& sl_FilenameList,
                                     const QString& s_PublicationAuthors, const QString& s_PublicationDate, const QString& s_PublicationTitle,
                                     const QString& s_PublicationPages, const QString& s_Publisher, const QString& s_PublicationPlace, const QString& s_RelatedPublicationAuthors,
                                     const QString& s_RelatedPublicationDate, const QString& s_RelatedPublicationTitle, const QString& s_RelatedPublicationSource )
{
    QString         s_Pages                     = "";

    QString         tab                         = "\t";

    QDateTime       DateTime                    = QDateTime::currentDateTime();

// **********************************************************************************************

    QFileInfo fi( sl_FilenameList.at( 0 ) );

    QFile fout( fi.absolutePath() + "/documentation_batch_" + DateTime.toString( "yyyy-MM-dd" ) + ".xml" );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout ); tout.setCodec( "UTF-8" );

// **********************************************************************************************

    tout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    tout << "<!-- created with PanXML (doi:10.1594/PANGAEA.746153) on " << DateTime.toString( "yyyy-MM-dd" ) << " -->" << endl;
    tout << "<reports-documentations xsi:noNamespaceSchemaLocation=\"" << s_XmlSchema << "\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl;

    tout << tab << "<reports-documentation>" << endl;

    tout << tab << tab << "<authors>" << endl;

    int i_NumberOfAuthors = s_PublicationAuthors.count( "//" ) + 1;

    for ( int j=0; j<i_NumberOfAuthors; j++ )
    {
        tout << tab << tab << tab << "<author>" << endl;
        tout << tab << tab << tab << tab << buildTextEntry( "family", s_PublicationAuthors.section( "//", j, j ).section( ", ", 0, 0 ) ) << endl;
        tout << tab << tab << tab << tab << buildTextEntry( "given", s_PublicationAuthors.section( "//", j, j ).section( ", ", 1, 1 ) ) << endl;
        tout << tab << tab << tab << "</author>" << endl;
    }

    tout << tab << tab << "</authors>" << endl;

    tout << tab << tab << "<files>" << endl;

    for ( int j=0; j<sl_FilenameList.count(); j++ )
    {
        fi.setFile( sl_FilenameList.at( j ) );
        tout << tab << tab << tab << buildTextEntry( "file", fi.completeBaseName() + "." + fi.suffix() ) << endl;
    }

    tout << tab << tab << "</files>" << endl;

    tout << tab << tab << buildTextEntry( "title", s_PublicationTitle ) << endl;

    if ( s_PublicationDate.length() > 4 )
    {
        tout << tab << tab << buildTextEntry( "date", s_PublicationDate ) << endl;
    }
    else
    {
        if ( s_PublicationDate.length() < 4 )
            tout << tab << tab << buildTextEntry( "date", tr( "" ) ) << endl;
        else
            tout << tab << tab << buildTextEntry( "date", s_PublicationDate + tr( "-01-01" ) ) << endl;
    }

    tout << tab << tab << buildTextEntry( "publisher", s_Publisher ) << endl;
    tout << tab << tab << buildTextEntry( "place_of_pub", s_PublicationPlace ) << endl;

    if ( s_Pages.toInt() > 0 )
    {
        tout << tab << tab << buildTextEntry( "pagerange", QString( "1-%1" ).arg( s_PublicationPages.toInt() ) ) << endl;
        tout << tab << tab << buildIntegerEntry( "pages", s_PublicationPages.toInt() ) << endl;
    }

    if ( s_RelatedPublicationAuthors.isEmpty() == false )
    {
        tout << tab << tab << "<relatedPublication>" << endl;

        tout << tab << tab << tab << "<authors>" << endl;

        int i_NumberOfAuthors = s_RelatedPublicationAuthors.count( "//" ) + 1;

        for ( int j=0; j<i_NumberOfAuthors; j++ )
        {
            tout << tab << tab << tab << tab << "<author>" << endl;
            tout << tab << tab << tab << tab << tab << buildTextEntry( "family", s_RelatedPublicationAuthors.section( "//", j, j ).section( ", ", 0, 0 ) ) << endl;
            tout << tab << tab << tab << tab << tab << buildTextEntry( "given", s_RelatedPublicationAuthors.section( "//", j, j ).section( ", ", 1, 1 ) ) << endl;
            tout << tab << tab << tab << tab << "</author>" << endl;
        }

        tout << tab << tab << tab << "</authors>" << endl;

        if ( s_RelatedPublicationDate.length() > 4 )
        {
            tout << tab << tab << buildTextEntry( "date", s_RelatedPublicationDate ) << endl;
        }
        else
        {
            if ( s_RelatedPublicationDate.length() < 4 )
                tout << tab << tab << buildTextEntry( "date", tr( "" ) ) << endl;
            else
                tout << tab << tab << buildTextEntry( "date", s_RelatedPublicationDate + tr( "-01-01" ) ) << endl;
        }

        tout << tab << tab << tab << buildTextEntry( "title", s_RelatedPublicationTitle ) << endl;
        tout << tab << tab << tab << buildTextEntry( "source", s_RelatedPublicationSource ) << endl;

        tout << tab << tab << "</relatedPublication>" << endl;
    }

    tout << tab << "</reports-documentation>" << endl;
    tout << "</reports-documentations>" << endl;

    fout.close();

// **********************************************************************************************

    return( NOERROR );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-01-10

void MainWindow::doCreateSimpleEPicXml()
{
    int         i				  = 0;
    int         n                 = 0;
    int         err				  = 0;
    int         stopProgress      = 0;

    QDateTime   DateTime          = QDateTime::currentDateTime();
    QString     s_PublicationDate = DateTime.toString( "yyyy-MM-dd" );

// **********************************************************************************************

    if ( doCreateSimpleEPicXmlDialog( gs_PublicationAuthors, s_PublicationDate, gs_PublicationTitle,
                                      gs_PublicationPages, gs_Publisher, gs_PublicationPlace, gs_RelatedPublicationAuthors,
                                      gs_RelatedPublicationDate, gs_RelatedPublicationTitle, gs_RelatedPublicationSource ) == QDialog::Rejected )
    {
              err = CHOOSEABORTED;
    }
    else
    {
        if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
        {
            initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Creating XML files..." ) );

            while ( ( i < gsl_FilenameList.count() ) && ( err == NOERROR ) && ( stopProgress != APPBREAK ) )
            {
                err          = CreateSimpleEPicXml( tr( "documentation_batch.xsd" ), gsl_FilenameList, gs_PublicationAuthors, s_PublicationDate, gs_PublicationTitle,
                                                    gs_PublicationPages, gs_Publisher, gs_PublicationPlace, gs_RelatedPublicationAuthors, gs_RelatedPublicationDate,
                                                    gs_RelatedPublicationTitle, gs_RelatedPublicationSource );

                stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
            }

            resetFileProgress( gsl_FilenameList.count() );
        }
        else
        {
            err = CHOOSEABORTED;
        }
    }

// ******************************************************************************************************

//  downloadXsdFile( gs_XmlPath, tr( "documentation_batch.xsd" ) );

    gi_ActionNumber = 1;

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Creating XML files was canceled" ), false, false );

    if ( ( gsl_FilenameList.count() > 0 ) && ( err == NOERROR ) && ( stopProgress != APPBREAK ) )
    {
        QFileInfo fi( gsl_FilenameList.at( 0 ) );

        QString s_XmlFile = fi.absolutePath() + "/documentation_batch_" + DateTime.toString( "yyyy-MM-dd" ) + ".xml";

        if ( n == 1 )
            QMessageBox::information( this, getApplicationName( true ), tr( "ePic XML file has been written to\n" ) + QDir::toNativeSeparators( s_XmlFile ) );

        if ( n > 1 )
            QMessageBox::information( this, getApplicationName( true ), QString( "%1 ePic XML files have been written to\n%2" ).arg( n ).arg( QDir::toNativeSeparators( s_XmlFile ) ) );
    }

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-14

int MainWindow::CreateEPicXml( const QString& s_XmlPath, const QString& s_XmlSchema, const QString& InputStr )
{
    int             Authors                     = 0;
    int             Title                       = 1;
    int             PublicationDate             = 2;
    int             Pages                       = 3;
    int             Publisher                   = 4;
    int             PublicationPlace            = 5;
    int             RelatedPublicationAuthor    = 6;
    int             RelatedPublicationDate      = 7;
    int             RelatedPublicationTitel     = 8;
    int             RelatedPublicationSource    = 9;
    int             Files                       = 10;

    QString         s_FilenameOut           = "";

    QString         tab                     = "\t";

    QDateTime       DateTime                = QDateTime::currentDateTime();

// **********************************************************************************************

    s_FilenameOut   = "documentation_batch_" + DateTime.toString( "yyyy-MM-dd" ) + ".xml";

    QFile fout( s_XmlPath + "/" + s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout ); tout.setCodec( "UTF-8" );

// **********************************************************************************************

    tout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    tout << "<!-- created with PanXML (doi:10.1594/PANGAEA.746153) on " << DateTime.toString( "yyyy-MM-dd" ) << " -->" << endl;
    tout << "<reports-documentations xsi:noNamespaceSchemaLocation=\"" << s_XmlSchema << "\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl;

    tout << tab << "<reports-documentation>" << endl;

    tout << tab << tab << "<authors>" << endl;

    int i_NumberOfAuthors = InputStr.section( "\t", Authors, Authors ).count( "//" ) + 1;

    for ( int j=0; j<i_NumberOfAuthors; j++ )
    {
        tout << tab << tab << tab << "<author>" << endl;
        tout << tab << tab << tab << tab << buildTextEntry( "family", InputStr.section( "\t", Authors, Authors ).section( "//", j, j ).section( ", ", 0, 0 ) ) << endl;
        tout << tab << tab << tab << tab << buildTextEntry( "given", InputStr.section( "\t", Authors, Authors ).section( "//", j, j ).section( ", ", 1, 1 ) ) << endl;
        tout << tab << tab << tab << "</author>" << endl;
    }

    tout << tab << tab << "</authors>" << endl;

    tout << tab << tab << "<files>" << endl;

    int i_NumberOfFiles = InputStr.section( "\t", Files, Files ).count( "//" ) + 1;

    for ( int j=0; j<i_NumberOfFiles; j++ )
        tout << tab << tab << tab << buildTextEntry( "file", InputStr.section( "\t", Files, Files ).section( "//", j, j ) ) << endl;

    tout << tab << tab << "</files>" << endl;

    tout << tab << tab << buildTextEntry( "title", InputStr.section( "\t", Title, Title ) ) << endl;

    if ( InputStr.section( "\t", PublicationDate, PublicationDate ).length() > 4 )
        tout << tab << tab << buildTextEntry( "date", InputStr.section( "\t", PublicationDate, PublicationDate ) ) << endl;
    else
        tout << tab << tab << buildTextEntry( "date", InputStr.section( "\t", PublicationDate, PublicationDate ) + "-01-01" ) << endl;

    tout << tab << tab << buildTextEntry( "publisher", InputStr.section( "\t", Publisher, Publisher ) ) << endl;
    tout << tab << tab << buildTextEntry( "place_of_pub", InputStr.section( "\t", PublicationPlace, PublicationPlace ) ) << endl;

    if ( InputStr.section( "\t", Pages, Pages ).toInt() > 0 )
    {
        tout << tab << tab << buildTextEntry( "pagerange", QString( "1-%1" ).arg( InputStr.section( "\t", Pages, Pages ).toInt() ) ) << endl;
        tout << tab << tab << buildIntegerEntry( "pages", InputStr.section( "\t", Pages, Pages ).toInt() ) << endl;
    }

    if ( InputStr.section( "\t", RelatedPublicationAuthor, RelatedPublicationAuthor ).isEmpty() == false )
    {
        tout << tab << tab << "<relatedPublication>" << endl;

        tout << tab << tab << tab << "<authors>" << endl;

        int i_NumberOfAuthors = InputStr.section( "\t", RelatedPublicationAuthor, RelatedPublicationAuthor ).count( "//" ) + 1;

        for ( int j=0; j<i_NumberOfAuthors; j++ )
        {
            tout << tab << tab << tab << tab << "<author>" << endl;
            tout << tab << tab << tab << tab << tab << buildTextEntry( "family", InputStr.section( "\t", RelatedPublicationAuthor, RelatedPublicationAuthor ).section( "//", j, j ).section( ", ", 0, 0 ) ) << endl;
            tout << tab << tab << tab << tab << tab << buildTextEntry( "given", InputStr.section( "\t", RelatedPublicationAuthor, RelatedPublicationAuthor ).section( "//", j, j ).section( ", ", 1, 1 ) ) << endl;
            tout << tab << tab << tab << tab << "</author>" << endl;
        }

        tout << tab << tab << tab << "</authors>" << endl;

        if ( InputStr.section( "\t", RelatedPublicationDate, RelatedPublicationDate ).length() > 4 )
            tout << tab << tab << tab << buildTextEntry( "date", InputStr.section( "\t", RelatedPublicationDate, RelatedPublicationDate ) ) << endl;
        else
            tout << tab << tab << tab << buildTextEntry( "date", InputStr.section( "\t", RelatedPublicationDate, RelatedPublicationDate ) + "-01-01" ) << endl;

        tout << tab << tab << tab << buildTextEntry( "title", InputStr.section( "\t", RelatedPublicationTitel, RelatedPublicationTitel ) ) << endl;
        tout << tab << tab << tab << buildTextEntry( "source", InputStr.section( "\t", RelatedPublicationSource, RelatedPublicationSource ) ) << endl;

        tout << tab << tab << "</relatedPublication>" << endl;
    }

    tout << tab << "</reports-documentation>" << endl;
    tout << "</reports-documentations>" << endl;

    fout.close();

// **********************************************************************************************

    return( NOERROR );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-12

void MainWindow::doCreateEPicXml()
{
    int         i				= 0;
    int         j               = 1;
    int         n               = 0;
    int         err				= 0;
    int         stopProgress	= 0;

    QString     s_FilenameIn    = "";
    QString     s_FilenameOut   = "";

    QStringList sl_Input;

// **********************************************************************************************

    if ( doSetOptionsDialog() == QDialog::Rejected )
    {
         err = CHOOSEABORTED;
    }
    else
    {
        if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
        {
            initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Creating XML files..." ) );

            while ( ( i < gsl_FilenameList.count() ) && ( err == NOERROR ) && ( stopProgress != APPBREAK ) )
            {
                if ( buildFilename( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList.at( i ), s_FilenameIn, s_FilenameOut ) == true )
                {
                    if ( readFile( s_FilenameIn, sl_Input, gi_Codec ) > 1 )
                    {
                        initProgress( gsl_FilenameList.count(), s_FilenameIn, tr( "Creating files..." ), sl_Input.count() ); j = 1;

                        while ( ( j<sl_Input.count() ) && ( stopProgress != APPBREAK ) )
                        {
                            err          = CreateEPicXml( gs_XmlPath, tr( "documentation_batch.xsd" ), sl_Input.at( j ) );

                            stopProgress = incProgress( gsl_FilenameList.count(), ++j );
                        }

                        resetProgress( sl_Input.count() );

                        n += j - 1;
                    }

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
    }

// ******************************************************************************************************

    downloadXsdFile( gs_XmlPath, tr( "documentation_batch.xsd" ) );

    gi_ActionNumber = 1;

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Creating XML files was canceled" ), false, false );

    if ( n == 1 )
        QMessageBox::information( this, getApplicationName( true ), tr( "ePic XML file has been written to\n" ) + QDir::toNativeSeparators( gs_XmlPath ) );

    if ( n > 1 )
        QMessageBox::information( this, getApplicationName( true ), QString( "%1 ePic XML files have been written to\n%2" ).arg( n ).arg( QDir::toNativeSeparators( gs_XmlPath ) ) );

    onError( err );
}

