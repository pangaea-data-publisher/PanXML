/* Application.h              */
/* 2013-05-15                 */
/* Dr. Rainer Sieger          */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QTextEdit>
#include <QTextCodec>
#include <QTextStream>
#include <QStringListModel>
#include <QListView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QProcess>
#include <QTimer>
#include <QMimeData>
#include <QDesktopServices>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>
#include <QStatusBar>
#include <QSettings>

#include "Globals.h"
#include "Webfile.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QAction;
class QLabel;
class QProgressDialog;
class QProgressBar;
class QTimer;
class QDateTime;
class QUrl;
class QTextEdit;
class QStringListModel;
class QListView;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_CLASSINFO( "author", "Rainer Sieger" )
    Q_CLASSINFO( "url", "http://www.pangaea.de" )

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    int			gi_ActionNumber;                 //!< Die ActionNumber wird bei jedem angewandenten Tool um 1 erhoeht.
    int         gi_Codec;                        //!< Welches Codec benutzt die Inputdatei?
    int         gi_EOL;                          //!< End-of-Line Zeichen fr die Outputdateien
    int         gi_Extension;                    //! Dateierweiterung fr Ausgabedateien
    int         gi_NumOfProgramStarts;           //!< Anzahl der Programmstarts

    QStringList gsl_FilenameList;                //!< Liste aller Dateinamen incl. Pfad.

    QString		gs_FilenameFormat;               //!< Bestimmt in die Form des automatisch erzeugten neuen Dateinamens. \%a = aktuelle Actionnumber, \%N = Dateiname.
    QString		gs_Path;                         //!< Der zuletzt verwendete Pfad.
    QString     gs_XmlPath;                      //!< Ablagepfad fuer die XML Dateien.
    QString     gs_Version;                      //!< Aktuelle Version des Programms.

    int         gi_Language;
    int         gi_Discipline;
    int         gi_Type;

    QString     gs_DOI;
    QString     gs_Authors;
    QString     gs_Title;
    QString     gs_Date;
    QString     gs_Volume;
    QString     gs_Issue;
    QString     gs_FirstPage;
    QString     gs_LastPage;
    QString     gs_Description;
    QString     gs_ProceedingsTitle;
    QString     gs_ProceedingsPublisher;
    QString     gs_ProceedingsContributor;
    QString     gs_ProceedingsPublicationPlace;
    QString     gs_ProceedingsIdentifier;

    QString     gs_PublicationAuthors;
    QString     gs_PublicationDate;
    QString     gs_PublicationTitle;
    QString     gs_PublicationPages;
    QString     gs_Publisher;
    QString     gs_PublicationPlace;
    QString     gs_RelatedPublicationAuthors;
    QString     gs_RelatedPublicationDate;
    QString     gs_RelatedPublicationTitle;
    QString     gs_RelatedPublicationSource;

    int CreateAmdXml( const QString& XmlPath, const QString& XmlSchema, const QString& Input );
    int CreateDoiXml( const QString& XmlPath, const QString& XmlSchema, const QString& Input );
    int CreateEPicXml( const QString& XmlPath, const QString& XmlSchema, const QString& Input );

    int CreateSimpleEPicXml( const QString& XmlSchema, const QStringList& FilenameList,
                             const QString& PublicationAuthors, const QString& PublicationDate, const QString& PublicationTitle,
                             const QString& PublicationPages, const QString& Publisher, const QString& PublicationPlace, const QString& RelatedPublicationAuthors,
                             const QString& RelatedPublicationDate, const QString& RelatedPublicationTitle, const QString& RelatedPublicationSource );

    QString escapeChar( const QString& EntryStr );

    QString buildTextEntry( const QString& Tag = "Tag", const QString& EntryStr = "", const int emptyElement = 2 );
    QString buildTextAttributeEntry( const QString& Tag = "Tag", const QString& AttributeName = "AttributeName", const QString& AttributeValue = "AttributeValue", const QString& EntryStr = "" );
    QString buildIdentifierEntry( const QString& s_Tag = "", const QString& EntryStr = "" );
    QString buildIntegerEntry( const QString& Tag = "Tag", const int = -999 );
    QString buildIntegerAttributeEntry( const QString& Tag = "Tag", const QString& AttributeName = "AttributeName", const QString& AttributeValue = "AttributeValue", const int = -999 );
    QString buildDoi( const QString& InputStr, const QString& s_ProceedingsTitle = "", const QString& s_PublicationDate = "", const QString& s_Volume = "", const QString& s_FirstPage = "" );
    QString buildEmailEntry( const QString& Tag = "Tag", const QString& EntryStr = "" );
    QString buildPhoneEntry( const QString& Tag = "Tag", const QString& EntryStr = "" );

    int calcNumOfPages( const QString& firstPage = "0", const QString& lastPage = "0" );
    int checkXmlFolder( const QString& XmlPath, const int n );

    void downloadXsdFile( const QString& s_Path, const QString& s_XmlSchema );

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
    void closeEvent( QCloseEvent *event );
    void onError( const int err );

signals:
    void finishedBuildFilelist( bool );

private slots:
    int  chooseFile();
    int  chooseFiles();
    int  chooseFolder( const QString &Folder = "" );
    int  saveFile();
    int  saveFileAs();
    void hideWindow();
    void newWindow();
    void displayHelp();
    void about();
    void clearStatusMessage();

    int doSetOptionsDialog();
    int doCreateSingleDoiXmlDialog();

    void doCreateAmdXml();
    void doCreateAmdXmlTemplate();

    void doCreateDoiXml();
    void doCreateDoiXmlTemplate();

private:
    QStringList expandCommandline();
    QStringList renameFiles( const QStringList Filename, const QString &searchStr, const QString &replaceStr );
    bool buildFilename( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QString &Filename, QString &FilenameIn, QString &FilenameOut );
    bool existsFirstFile( const int ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList );
    bool isEmptyLine( const QString &String );
    int NumOfSections( const QString &String );
    int buildFileList( QStringList &FilenameList, const QString &Filename, const bool extractZipFile = true );
    int calcFileSizeClass( const QString &FilenameIn, const int NumOfFiles, const int lowerLimit = 100, const int upperLimit = 1000 );
    int copyStringList( const QStringList InStringList, QStringList &OutStringList, const QString &s_Pattern = "*" );
    int emptyDir( const QString &Dir );
    int extractZipFile( const QString &Filename, const bool createNewDir = false, const bool delZipFile = false );
    int incFileProgress( const int NumOfFiles, const int FileNumber );
    int incProgress( const int NumOfFiles, const int Step );
    int readFile( const QString &FilenameIn, QStringList &Input, const int Codec = -1, const int NumOfFiles = 0, const qint64 Bytes = 0 );
    int removeFile( const QString &Filename );
    int downloadFile( const QString &Url, const QString &absoluteFilePath );
    unsigned int incProgress( const int NumOfFiles, const unsigned int filesize, const unsigned int length, const QString &InputStr );
    void appendItem( QStringList &List, const QString &Item, const QString &SS = "", const QString &RS = "" );
    void clearFilenameList( int &ActionNumber, QStringList &FilenameList );
    void clearList( QStringList& List );
    void clearMessage();
    void createActions();
    void createMenus();
    void createStatusBar();
    void endTool( const int err, const int stopProgress, int &ActionNumber, const QString &FilenameFormat, const int Extension, QStringList &FilenameList, const QString &doneMessage = "Done", const QString &canceledMessage = "Converter was canceled", const bool clearList = false, const bool incActionNumber = true );
    void initFileProgress( const int NumOfFiles, const QString &FilenameIn, const QString &MessageText );
    void initProgress( const int NumOfFiles, const QString &Filename, const QString &MessageText, const int totalNumberOfSteps );
    void initProgress( const int totalNumberOfSteps );
    void listDir( QStringList &Filename, const QString &Directory, const bool extractZipFile = true );
    void loadPreferences();
    void resetFileProgress( const int NumOfFiles );
    void resetProgress( const int NumOfFiles = 0 );
    void savePreferences();
    void setNormalCursor();
    void setStatusBar( const QString &Message = "", const int seconds = 0 );
    void setStatusBarFileInProgress( const QString &Filename, const QString &Message = "", const int i_seconds = 0 );
    void setWTitle( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList &sl_FilenameList );
    void setWaitCursor();
    void showFilenameList( const int ActionNumber, const QString &FilenameFormat, const int Extension, const QStringList FilenameList );
    void showList( const QStringList List );
    void showMessage( const QString &Message, QStringList &MessageList );
    void wait( const int msec );

    QString getApplicationName( const bool replaceUnderline = false );
    QString getDocumentDir();
    QString getDataLocation();
    QString getPreferenceFilename();
    QString getVersion();
    QString setEOLChar( const int EOL );
    QString setExtension( const int Extension );

    QMenu	*fileMenu;
    QMenu   *toolMenu;
    QMenu	*helpMenu;

    QAction *newWindowAction;
    QAction *openFileAction;
    QAction *openFolderAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *hideWindowAction;
    QAction *exitAction;

    QAction *createAmdXmlAction;
    QAction *createAmdXmlTemplateAction;
    QAction *createDoiXmlAction;
    QAction *createDoiXmlTemplateAction;
    QAction *createSingleDoiXmlDialogAction;

    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showHelpAction;

    QProgressDialog *ProgressDialog;
    QProgressDialog *FileProgressDialog;
    QProgressBar    *ProgressBar;
    QLabel			*StatusMessage;

    QStringListModel	*Model;
    QListView			*ListView;
    QTextEdit			*textViewer;

    QPoint	posWindow;              //!< Position des Programmfensters.
    QSize	sizeWindow;             //!< Groesse des Programmfensters.

    QPoint	posDialog;              //!< Position der Dialoge.
    QSize	sizeDialog;             //!< Groesse der Dialoge.
    QSize   sizeDoiXmlDialog;       //!> Groesse des DOI XML Dialogs.
};

#endif
