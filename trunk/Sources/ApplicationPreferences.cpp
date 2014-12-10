/****************************************************************
**
** Preferences
** 2008-12-01, Dr. Rainer Sieger
** last change: 2009-12-01
**
****************************************************************/

#include "Application.h"

/*! @brief Sichern der Programmeinstellungen */

void MainWindow::savePreferences()
{
    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    settings.beginGroup( "GeneralSettings" );
    settings.setValue( "NumOfProgramStarts", gi_NumOfProgramStarts );

    settings.setValue( "WindowX", x() );
    settings.setValue( "WindowY", y() );
    settings.setValue( "WindowHeight", height() );
    settings.setValue( "WindowWidth", width() );

    settings.setValue( "DialogX", posDialog.x() );
    settings.setValue( "DialogY", posDialog.y() );
    settings.setValue( "DialogHeight", sizeDialog.height() );
    settings.setValue( "DialogWidth", sizeDialog.width() );
    settings.setValue( "XmlDialogHeight", sizeDoiXmlDialog.height() );
    settings.setValue( "XmlDialogWidth", sizeDoiXmlDialog.width() );

    settings.setValue( "Path", gs_Path );
    settings.setValue( "XmlPath", gs_XmlPath );
    settings.setValue( "Codec", gi_Codec );
    settings.endGroup();

    // DOI Dialog
    settings.beginGroup( "Dialog" );
    settings.setValue( "Language", gi_Language );
    settings.setValue( "Discipline", gi_Discipline );
    settings.setValue( "Type", gi_Type );
    settings.setValue( "DOI", gs_DOI );
    settings.setValue( "Authors", gs_Authors );
    settings.setValue( "Title", gs_Title );
    settings.setValue( "Date", gs_Date );
    settings.setValue( "Volume", gs_Volume );
    settings.setValue( "Issue", gs_Issue );
    settings.setValue( "FirstPage", gs_FirstPage );
    settings.setValue( "LastPage", gs_LastPage );
    settings.setValue( "Description", gs_Description );
    settings.setValue( "ProceedingsTitle", gs_ProceedingsTitle );
    settings.setValue( "ProceedingsPublisher", gs_ProceedingsPublisher );
    settings.setValue( "ProceedingsContributor", gs_ProceedingsContributor );
    settings.setValue( "ProceedingsPublisher", gs_ProceedingsPublisher );
    settings.setValue( "ProceedingsIdentifier", gs_ProceedingsIdentifier );
    settings.setValue( "PublicationAuthors", gs_PublicationAuthors );
    settings.setValue( "PublicationDate", gs_PublicationDate );
    settings.setValue( "PublicationTitle", gs_PublicationTitle );
    settings.setValue( "PublicationPages", gs_PublicationPages );
    settings.setValue( "Publisher", gs_Publisher );
    settings.setValue( "PublicationPlace", gs_PublicationPlace );
    settings.setValue( "RelatedPublicationAuthors", gs_RelatedPublicationAuthors );
    settings.setValue( "RelatedPublicationDate", gs_RelatedPublicationDate );
    settings.setValue( "RelatedPublicationTitle", gs_RelatedPublicationTitle );
    settings.setValue( "RelatedPublicationSource", gs_RelatedPublicationSource );
    settings.endGroup();

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 21.11.2007

/*! @brief Laden der Programmeinstellungen */

void MainWindow::loadPreferences()
{
    #if defined(Q_OS_LINUX)
        gi_Codec                = _UTF8_; // UTF-8
        gi_EOL                  = _UNIX_;
    #endif

    #if defined(Q_OS_MAC)
        gi_Codec                = _APPLEROMAN_; // Mac Roman
        gi_EOL                  = _UNIX_;
    #endif

    #if defined(Q_OS_WIN)
        gi_Codec                = _LATIN1_; // Latin-1 = ISO 8859-1
        gi_EOL                  = _WIN_;
    #endif

    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    settings.beginGroup( "GeneralSettings" );
    gi_NumOfProgramStarts = settings.value( "NumOfProgramStarts", 0 ).toInt();

    posWindow.setX( settings.value( "WindowX", 100 ).toInt() );
    posWindow.setY( settings.value( "WindowY", 100 ).toInt() );
    sizeWindow.setHeight( settings.value( "WindowHeight", 250 ).toInt() );
    sizeWindow.setWidth( settings.value( "WindowWidth", 600 ).toInt() );

    posDialog.setX( settings.value( "DialogX", 110 ).toInt() );
    posDialog.setY( settings.value( "DialogY", 110 ).toInt() );
    sizeDialog.setHeight( settings.value( "DialogHeight", 100 ).toInt() );
    sizeDialog.setWidth( settings.value( "DialogWidth", 100 ).toInt() );
    sizeDoiXmlDialog.setHeight( settings.value( "XmlDialogHeight", 100 ).toInt() );
    sizeDoiXmlDialog.setWidth( settings.value( "XmlDialogWidth", 100 ).toInt() );

    gs_Path    = settings.value( "Path", getDocumentDir() ).toString();
    gs_XmlPath = settings.value( "XmlPath", getDocumentDir() ).toString();
    gi_Codec   = settings.value( "Codec", gi_Codec ).toInt();
    settings.endGroup();

    // DOI Dialog
    settings.beginGroup( "Dialog" );
    gi_Language                  = settings.value( "Language", 0 ).toInt();
    gi_Discipline                = settings.value( "Discipline", 0 ).toInt();
    gi_Type                      = settings.value( "Type", 0 ).toInt();
    gs_DOI                       = settings.value( "DOI", "auto" ).toString();
    gs_Authors                   = settings.value( "Authors", "" ).toString();
    gs_Title                     = settings.value( "Title", "" ).toString();
    gs_Date                      = settings.value( "Date", "" ).toString();
    gs_Volume                    = settings.value( "Volume", "" ).toString();
    gs_Issue                     = settings.value( "Issue", "" ).toString();
    gs_FirstPage                 = settings.value( "FirstPage", "" ).toString();
    gs_LastPage                  = settings.value( "LastPage", "" ).toString();
    gs_Description               = settings.value( "Description", "" ).toString();
    gs_ProceedingsTitle          = settings.value( "ProceedingsTitle", "" ).toString();
    gs_ProceedingsPublisher      = settings.value( "ProceedingsPublisher", "" ).toString();
    gs_ProceedingsContributor    = settings.value( "ProceedingsContributor", "" ).toString();
    gs_ProceedingsPublisher      = settings.value( "ProceedingsPublisher", "" ).toString();
    gs_ProceedingsIdentifier     = settings.value( "ProceedingsIdentifier", "" ).toString();
    gs_PublicationAuthors        = settings.value( "PublicationAuthors", "Grobe, Hannes" ).toString();
    gs_PublicationDate           = settings.value( "PublicationDate", "2011-01-11" ).toString();
    gs_PublicationTitle          = settings.value( "PublicationTitle", "PANGAEA Logo files" ).toString();
    gs_PublicationPages          = settings.value( "PublicationPages", "" ).toString();
    gs_Publisher                 = settings.value( "Publisher", "Alfred Wegener Institute Bremerhaven" ).toString();
    gs_PublicationPlace          = settings.value( "PublicationPlace", "Bremerhaven" ).toString();
    gs_RelatedPublicationAuthors = settings.value( "RelatedPublicationAuthors", "Grobe, Hannes//Sieger, Rainer" ).toString();
    gs_RelatedPublicationDate    = settings.value( "RelatedPublicationDate", "2005" ).toString();
    gs_RelatedPublicationTitle   = settings.value( "RelatedPublicationTitle", "PANGAEA Logo" ).toString();
    gs_RelatedPublicationSource  = settings.value( "RelatedPublicationSource", "PANGAEA, Bremerhaven, Germany" ).toString();
    settings.endGroup();

    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Ermitteln des Dateinamens fuer die Programmeinstellungen.
*   @return Name der Datei fuer die Programmeinstellungen. Dateiname ist gleich "_ERROR_",
*   wenn Betriebssystem ungleich Windows, Mac OS oder Unix ist.
*/

QString MainWindow::getPreferenceFilename()
{
    QString s_PrefFilename = "";

    #if defined(Q_OS_LINUX)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/.config/" ) + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".conf" );
    #endif

    #if defined(Q_OS_MAC)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/Library/Preferences/" ) + QCoreApplication::organizationDomain().section( ".", 1, 1 ) + "." + QCoreApplication::organizationDomain().section( ".", 0, 0 ) + "." + QCoreApplication::applicationName() + QLatin1String( ".plist" );
    #endif

    #if defined(Q_OS_WIN)
        if ( QCoreApplication::applicationName().toLower().endsWith( "portable" ) )
        {
            s_PrefFilename = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
        else
        {
            QSettings cfg( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName() );
            s_PrefFilename = QFileInfo( cfg.fileName() ).absolutePath() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
    #endif

    return( s_PrefFilename );
}
