/* BuildXmlEntry.cpp          */
/* 2010-10-12                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

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
    OutStr.replace( "@", "-" );

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

QString MainWindow::buildTextEntry(const QString& s_Tag, const QString& EntryStr, const int i_emptyElement )
{
    QString OutStr  = "<EMPTY>";

    if ( EntryStr.isEmpty() == false )
    {
        OutStr = "<" + s_Tag + ">" + escapeChar( EntryStr ) + "</" + s_Tag + ">";
    }
    else
    {
        switch ( i_emptyElement )
        {
        case 1:
            OutStr = "<" + s_Tag + " />";
            break;
        case 2:
            OutStr = "<" + s_Tag + "></" + s_Tag + ">";
            break;
        default:
            break;
        }
    }

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2015-04-03

QString MainWindow::buildEmailEntry( const QString& s_Tag, const QString& EntryStr )
{
    QString OutStr  = "<EMPTY>";

    if ( EntryStr.isEmpty() == false )
        OutStr = "<" + s_Tag + ">" + EntryStr + "</" + s_Tag + ">";

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2015-04-03

QString MainWindow::buildPhoneEntry( const QString& s_Tag, const QString& EntryStr )
{
    QString OutStr  = "<EMPTY>";

    if ( EntryStr.isEmpty() == false )
    {
        OutStr = "<" + s_Tag + ">" + EntryStr + "</" + s_Tag + ">";

        OutStr.replace( "  ", " " );
        OutStr.replace( " ", "-" );
    }

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-23

QString MainWindow::buildTextAttributeEntry( const QString& s_Tag, const QString& s_AttributeName, const QString& s_AttributeValue, const QString& EntryStr )
{
    QString OutStr  = "<EMPTY>";

    if ( EntryStr.isEmpty() == false )
        OutStr = "<" + s_Tag + " " + s_AttributeName + "=\"" + s_AttributeValue + "\">" + escapeChar( EntryStr ) + "</" + s_Tag + ">";
    else
        OutStr = "<" + s_Tag + "></" + s_Tag + ">";

    return( OutStr );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-24

QString MainWindow::buildIntegerEntry( const QString& s_Tag, const int i_Value )
{
    QString OutStr  = "<EMPTY>";

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
    QString OutStr  = "<EMPTY>";

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

// **********************************************************************************************
// **********************************************************************************************
// ******************************************************************************************************
// download xsd file

void MainWindow::downloadXsdFile( const QString& s_Path, const QString& s_XmlSchema )
{
    QString s_FilenameLocal = s_Path + "/" + s_XmlSchema;

    QFile outfile( s_FilenameLocal );

    if ( outfile.exists() == true )
        outfile.remove();

    downloadFile( QLatin1String( "https://pangaea.de/curator/files/" ) + s_XmlSchema, s_FilenameLocal );
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

