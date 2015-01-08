/* CreateDoiXml.cpp           */
/* 2010-10-12                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-14

int MainWindow::CreateDoiXml( const QString& s_XmlPath, const QString& s_XmlSchema, const QString& InputStr )
{
    int             DOI                     = 0;
    int             Authors                 = 1;
    int             Title                   = 2;
    int             PublicationDate         = 3;
    int             ProceedingsVolume       = 4;
    int             ProceedingsIssue        = 5;
    int             firstPage               = 6;
    int             lastPage                = 7;
    int             Language                = 8;
    int             Description             = 9;
    int             Discipline              = 10;
    int             ResourceIdentifiers     = 11;
    int             ResourceType            = 12;
    int             RelatedIdentifiers      = 13;
    int             RelationType            = 14;
    int             Format                  = 15;
    int             ProceedingsTitle        = 16;
    int             ProceedingsPublisher    = 17;
    int             ProceedingsContributor  = 18;
    int             PublicationPlace        = 19;
    int             ProceedingsIdentifier   = 20;

    QString         s_FilenameOut           = "";
    QString         s_DOI                   = "";

    QString         tab                     = "\t";

    QDateTime       DateTime                = QDateTime::currentDateTime();

// **********************************************************************************************

    s_DOI           = buildDoi( InputStr.section( "\t", DOI, DOI ), InputStr.section( "\t", ProceedingsTitle, ProceedingsTitle ), InputStr.section( "\t", PublicationDate , PublicationDate ),  InputStr.section( "\t", ProceedingsVolume, ProceedingsVolume ),  InputStr.section( "\t", firstPage, firstPage ) );
    s_FilenameOut   = s_DOI.section( "/", 1, 1 ) + ".xml";

    QFile fout( s_XmlPath + "/" + s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout ); tout.setCodec( "UTF-8" );

    DateTime = QDateTime::currentDateTime();

// **********************************************************************************************

    tout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    tout << "<!-- created with PanXML (doi:10.1594/PANGAEA.746153) on " << DateTime.toString( "yyyy-MM-dd" ) << " -->" << endl;
    tout << "<resource xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"" << s_XmlSchema << "\">" << endl;

    tout << tab << buildTextEntry( "issueDate", DateTime.toString( "yyyy-MM-dd" ) ) << endl;
    tout << tab << buildIntegerEntry( "issueNumber", 1 ) << endl;
    tout << tab << buildTextEntry( "DOI", s_DOI ) << endl;
    tout << tab << buildTextEntry( "title", InputStr.section( "\t", Title, Title ) ) << endl;

    int i_NumberOfAuthors = InputStr.section( "\t", Authors, Authors ).count( "//" ) + 1;

    for ( int j=0; j<i_NumberOfAuthors; j++ )
        tout << tab << buildTextEntry( "creator", InputStr.section( "\t", Authors, Authors ).section( "//", j, j ) ) << endl;

    tout << tab << "<proceedingsInfo>" << endl;
    tout << tab << tab << buildTextEntry( "title", InputStr.section( "\t", ProceedingsTitle, ProceedingsTitle ) ) << endl;
    tout << tab << tab << buildTextEntry( "publisher", InputStr.section( "\t", ProceedingsPublisher, ProceedingsPublisher ) ) << endl;

    if ( InputStr.section( "\t", ProceedingsContributor, ProceedingsContributor ).isEmpty() == false )
        tout << tab << tab << buildTextEntry( "contributor", InputStr.section( "\t", ProceedingsContributor, ProceedingsContributor ) ) << endl;

    if ( InputStr.section( "\t", ProceedingsIdentifier, ProceedingsIdentifier ).isEmpty() == false )
        tout << tab << tab << buildIdentifierEntry( "identifier", InputStr.section( "\t", ProceedingsIdentifier, ProceedingsIdentifier ) ) << endl;

    if ( InputStr.section( "\t", ProceedingsVolume, ProceedingsVolume ).isEmpty() == false )
        tout << tab << tab << buildTextEntry( "volume", InputStr.section( "\t", ProceedingsVolume, ProceedingsVolume ) ) << endl;

    if ( InputStr.section( "\t", ProceedingsIssue, ProceedingsIssue ).isEmpty() == false )
        tout << tab << tab << buildTextEntry( "issue", InputStr.section( "\t", ProceedingsIssue, ProceedingsIssue ) ) << endl;

    tout << tab << "</proceedingsInfo>" << endl;

    tout << tab << buildIntegerAttributeEntry( "size", "type", "Pages", calcNumOfPages( InputStr.section( "\t", firstPage, firstPage ), InputStr.section( "\t", lastPage, lastPage ) ) ) << endl;
    tout << tab << buildIntegerEntry( "firstPage", InputStr.section( "\t", firstPage, firstPage ).toInt() ) << endl;
    tout << tab << buildIntegerEntry( "lastPage", InputStr.section( "\t", lastPage, lastPage ).toInt() ) << endl;

    if ( InputStr.section( "\t", PublicationDate, PublicationDate ).length() > 4 )
        tout << tab << buildTextEntry( "publicationDate", InputStr.section( "\t", PublicationDate, PublicationDate ) ) << endl;
    else
        tout << tab << buildTextEntry( "publicationDate", InputStr.section( "\t", PublicationDate, PublicationDate ) + "-01-01" ) << endl;

    tout << tab << buildTextEntry( "publicationPlace", InputStr.section( "\t", PublicationPlace, PublicationPlace ) ) << endl;

    if ( InputStr.section( "\t", Language, Language ).isEmpty() == false )
        tout << tab << buildTextEntry( "language", InputStr.section( "\t", Language, Language ) ) << endl;

    tout << tab << buildTextEntry( "description", InputStr.section( "\t", Description, Description ) ) << endl;

    if ( InputStr.section( "\t", ResourceIdentifiers, ResourceIdentifiers ).isEmpty() == false )
    {
        tout << tab << "<resourceIdentifiers>" << endl;
        tout << tab << tab << buildIdentifierEntry( "resourceIdentifier", InputStr.section( "\t", ResourceIdentifiers, ResourceIdentifiers ) ) << endl;
        tout << tab << "</resourceIdentifiers>" << endl;
    }

    tout << tab << buildTextEntry( "discipline", InputStr.section( "\t", Discipline, Discipline ) ) << endl;
    tout << tab << buildTextEntry( "resourceType", InputStr.section( "\t", ResourceType, ResourceType ) ) << endl;
    tout << tab << buildTextEntry( "format", InputStr.section( "\t", Format, Format ) ) << endl;

    if ( InputStr.section( "\t", RelatedIdentifiers, RelatedIdentifiers ).isEmpty() == false )
    {
        tout << tab << "<relatedIdentifiers>" << endl;
        tout << tab << tab << buildIdentifierEntry( "relatedIdentifier", InputStr.section( "\t", RelatedIdentifiers, RelatedIdentifiers ) ) << endl;
        tout << tab << tab << buildTextEntry( "relationType", InputStr.section( "\t", RelationType, RelationType ) ) << endl;
        tout << tab << "</relatedIdentifiers>" << endl;
    }

    tout << "</resource>" << endl;

    fout.close();

// **********************************************************************************************

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

QString MainWindow::buildDoi( const QString& InputStr, const QString& s_ProceedingsTitle, const QString& s_PublicationDate, const QString& s_Volume, const QString& s_FirstPage )
{
    QString s_DOI = "10.2312/";

    if ( InputStr.toLower() == "auto" )
    {
        if ( s_ProceedingsTitle.isEmpty() == false )
            s_DOI.append( s_ProceedingsTitle.toLower() );
        else
            s_DOI.append( "pangaea" );

        if ( s_PublicationDate.isEmpty() == false )
            s_DOI.append( "." + s_PublicationDate.section( "-", 0, 0 ) ) ;

        if ( s_Volume.isEmpty() == false )
            s_DOI.append( "." + s_Volume );

        if ( s_FirstPage.isEmpty() == false )
            s_DOI.append( "." + s_FirstPage );
    }
    else
    {
        if ( InputStr.startsWith( "10.2312/" ) == true )
            s_DOI = InputStr;
        else
            s_DOI.append( InputStr );
    }

    if ( s_DOI == "10.2312/pangaea" )
        s_DOI = "pangaea/DOI is not given";

    return( s_DOI );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

int MainWindow::calcNumOfPages( const QString& s_firstPage, const QString& s_lastPage )
{
    int i_FirstPage  = 0;
    int i_LastPage   = 0;
    int i_NumOfPages = 0;

    if ( s_firstPage.isEmpty() == false )
        i_FirstPage = s_firstPage.toInt();

    if ( s_lastPage.isEmpty() == false )
        i_LastPage = s_lastPage.toInt();
    else
        i_LastPage = i_FirstPage;

    if ( i_LastPage >= i_FirstPage )
        i_NumOfPages = i_LastPage - i_FirstPage + 1;

    return( i_NumOfPages );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-24

QString MainWindow::escapeChar( const QString& EntryStr )
{
    QString OutStr = EntryStr;

    if ( ( OutStr.startsWith( "\"") ) == true )
        OutStr = OutStr.right( OutStr.length() - 1 );

    if ( ( OutStr.endsWith( "\"") ) == true )
        OutStr = OutStr.left( OutStr.length() - 1 );

    OutStr.replace( "&", "&amp;" );
    OutStr.replace( "<", "&lt;" );
    OutStr.replace( ">", "&gt;" );
    OutStr.replace( "'", "&apos;" );
    OutStr.replace( "\"\"", "&quot;" );
    OutStr.replace( "\"", "&quot;" );
    OutStr.replace( "@", "" );

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

QString MainWindow::buildTextEntry( const QString& s_Tag, const QString& EntryStr, const bool b_emptyElement )
{
    QString OutStr  = "";

    if ( EntryStr.isEmpty() == false )
    {
        OutStr = "<" + s_Tag + ">" + escapeChar( EntryStr ) + "</" + s_Tag + ">";
    }
    else
    {
        if ( b_emptyElement == true )
            OutStr = "<" + s_Tag + " />";
        else
            OutStr = "<" + s_Tag + "></" + s_Tag + ">";
    }

    OutStr.replace( "@", "-" );

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

QString MainWindow::buildTextAttributeEntry( const QString& s_Tag, const QString& s_AttributeName, const QString& s_AttributeValue, const QString& EntryStr )
{
    QString OutStr  = "";

    if ( EntryStr.isEmpty() == false )
    {
        OutStr = "<" + s_Tag + " " + s_AttributeName + "=\"" + s_AttributeValue + "\">" + escapeChar( EntryStr ) + "</" + s_Tag + ">";
    }
    else
    {
        OutStr = "<" + s_Tag + "></" + s_Tag + ">";
    }

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-24

QString MainWindow::buildIntegerEntry( const QString& s_Tag, const int i_Value )
{
    QString OutStr  = "";

    if ( i_Value != -999 )
        OutStr = "<" + s_Tag + ">" + QString( "%1" ).arg( i_Value ) + "</" + s_Tag + ">";
    else
        OutStr = "<" + s_Tag + "></" + s_Tag + ">";

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-24

QString MainWindow::buildIntegerAttributeEntry( const QString& s_Tag, const QString& s_AttributeName, const QString& s_AttributeValue, const int i_Value )
{
    QString OutStr  = "";

    if ( i_Value != -999 )
        OutStr = "<" + s_Tag + " " + s_AttributeName + "=\"" + s_AttributeValue + "\">" + QString( "%1" ).arg( i_Value ) + "</" + s_Tag + ">";
    else
        OutStr = "<" + s_Tag + "></" + s_Tag + ">";

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-24

QString MainWindow::buildIdentifierEntry( const QString& s_Tag, const QString& EntryStr )
{
    QString s_Identifier = "";

    if ( EntryStr.contains( "doi:" ) == true )
        return(  "<" + s_Tag + " type=\"DOI\">" + EntryStr.section( "doi:", 1, 1 ) + "</" + s_Tag + ">" );

    if ( EntryStr.contains( "hdl:" ) == true )
        return(  "<" + s_Tag + " type=\"Handle\">" + EntryStr.section( "hdl:", 1, 1 ) + "</" + s_Tag + ">" );

    if ( EntryStr.contains( " " ) == true )
        return(  "<" + s_Tag + " type=\"" + EntryStr.section( " ", 0, 0 ).toUpper() + "\">" + EntryStr.section( " ", 1, 1 ) + "</" + s_Tag + ">" );

    return( s_Identifier );
}

// ******************************************************************************************************
// download xsd file

void MainWindow::downloadXsdFile( const QString& s_Path, const QString& s_XmlSchema )
{
    QFile outfile( s_Path + "/" + s_XmlSchema );

    if ( outfile.exists() == true )
        outfile.remove();

    if ( outfile.open( QIODevice::WriteOnly | QIODevice::Text ) == true )
    {
        webfile m_webfile;

        m_webfile.setUrl( QLatin1String( "http://www.pangaea.de/curator/files/" ) + s_XmlSchema );

        if ( m_webfile.open() == true )
        {
            char    buffer[1024];
            qint64  nSize = 0;

            while ( ( nSize = m_webfile.read( buffer, sizeof( buffer ) ) ) > 0 )
                outfile.write( buffer, nSize );

            m_webfile.close();
        }

        outfile.close();
    }
}

// ******************************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-12

void MainWindow::doCreateDoiXml()
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

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        if ( doSetOptionsDialog() == QDialog::Accepted )
        {
            initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Creating XML files..." ) );

            while ( ( i < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
            {
                if ( buildFilename( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList.at( i ), s_FilenameIn, s_FilenameOut ) == true )
                {
                    if ( readFile( s_FilenameIn, sl_Input, gi_Codec ) > 1 )
                    {
                        initProgress( gsl_FilenameList.count(), s_FilenameIn, tr( "Creating files..." ), sl_Input.count() ); j = 1;

                        while ( ( j<sl_Input.count() ) && ( stopProgress != _APPBREAK_ ) )
                        {
                            err          = CreateDoiXml( gs_XmlPath, tr( "article-doi_v3.2.xsd" ), sl_Input.at( j ) );

                            stopProgress = incProgress( gsl_FilenameList.count(), ++j );
                        }

                        resetProgress( sl_Input.count() );

                        n += j - 1;
                    }

                    stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
                }
                else
                {
                    err = _FILENOTEXISTS_;
                }
            }

            resetFileProgress( gsl_FilenameList.count() );
        }
        else
        {
            err = _CHOOSEABORTED_;
        }
    }

// ******************************************************************************************************

    downloadXsdFile( gs_XmlPath, "article-doi_v3.2.xsd" );

    gi_ActionNumber = 1;

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Creating XML files was canceled" ), false, false );

// ******************************************************************************************************

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
        err = checkXmlFolder( gs_XmlPath, n );

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) && ( n == 1 ) )
        QMessageBox::information( this, getApplicationName( true ), tr( "DOI XML file has been written to\n" ) + QDir::toNativeSeparators( gs_XmlPath ) );

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) && ( n > 1 ) )
        QMessageBox::information( this, getApplicationName( true ), QString( "%1 DOI XML files have been written to\n%2" ).arg( n ).arg( QDir::toNativeSeparators( gs_XmlPath ) ) );

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2014-11-19

int MainWindow::checkXmlFolder( const QString& s_XmlPath, const int n )
{
    bool        b_hasXsd = false;

    QStringList sl_FilenameList;
    QStringList sl_baseNames;

// **********************************************************************************************

    listDir( sl_FilenameList, s_XmlPath, false );

    if ( sl_FilenameList.count() != 2*n+1 )
    {
        QMessageBox::critical( this, getApplicationName( true ), tr( "Number of files is wrong" ) );
        return( -60 );
    }
    else
    {
        for ( int i=0; i<2*n+1; i++ )
        {
            QFileInfo fi( sl_FilenameList.at( i ) );

            if ( fi.fileName() != "article-doi_v3.2.xsd" )
                sl_baseNames.append( fi.completeBaseName() );
            else
                b_hasXsd = true;
        }

        if ( b_hasXsd == false )
        {
            QMessageBox::critical( this, getApplicationName( true ), tr( "File article-doi_v3.2.xsd is missing" ) );
            return( -60 );
        }

        for ( int i=0; i<2*n; i++ )
        {
            if ( sl_baseNames.count( sl_baseNames.at( i ) ) != 2 )
            {
                QMessageBox::critical( this, getApplicationName( true ), tr( "File name is wrong. Please check\n\n  " ).append( sl_baseNames.at( i ) ).append( tr( ".*" ) ) );
                return( -60 );
            }
        }
    }

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-12

void MainWindow::doCreateDoiXmlTemplate()
{
    int err = 0;

    QFileInfo	fi;

// *********************************************************************************************

    fi.setFile( gs_Path );

    if ( fi.exists() == false )
        gs_Path = getDocumentDir();

    QString s_Filename         = gs_Path + "/" + "ReferenceListTemplate.txt";
    QString s_FilenameTemplate = QFileDialog::getSaveFileName( this, tr( "Save Template" ), s_Filename, tr( "Text (*.txt)" ), 0, QFileDialog::DontUseNativeDialog );

    if ( s_FilenameTemplate.isEmpty() == true )
    {
        err = _CHOOSEABORTED_;
    }
    else
    {
        fi.setFile( s_FilenameTemplate );
        gs_Path = fi.absolutePath();

        QFile fout( s_FilenameTemplate );

        if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        {
            err = -20;
        }
        else
        {
            QTextStream tout( &fout );

            tout << "DOI\tAuthors\tTitle\tPublicationDate\tVolume\tIssue\tFirst page\tLast page\tLanguage\tDescription\tDiscipline\t";
            tout << "ResourceIdentifier\tResourceType\tRelatedIdentifier\tRelationType\tFormat\tProceedingsTitle\t";
            tout << "ProceedingsPublisher\tProceedingsContributor\tPublicationPlace\tProceedingsIdentifier" << endl;

            tout << "10.2312/your.doi.suffix\tSurname1, Firstname1//Surname2, Firstname2//...\tTitle of article\t2010\t34\t4\t10\t23\t";
            tout << "en\ta short description of the content\t550 Earth sciences and geology\tdoi:other_DOI_or_Handle\tJournal article\t";
            tout << "doi:DOI_or_Handle_of_a_related_resource\tisNewVersionOf\tapplication/pdf\tReports on Polar and Marine Research\t";
            tout << "Alfred Wegener Institute for Polar and Marine Research\t\tBremerhaven, Germany\teISSN 1866-3192" << endl;

            fout.close();

            downloadXsdFile( gs_Path, tr( "article-doi_v3.2.xsd" ) );

            QMessageBox::information( this, getApplicationName( true ), tr( "Reference list template file has been written to\n" ) + QDir::toNativeSeparators( s_FilenameTemplate ) );
        }
    }

    onError( err );
}
