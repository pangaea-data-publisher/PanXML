// ***********************************************************************************************
// *                                                                                             *
// * CreateSingleDoiXmlDialog.cpp - Create a DOI XML file from dialog input                      *
// *                                                                                             *
// * Dr. Rainer Sieger - 2010-10-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtWidgets>

#include "Application.h"
#include "CreateSingleDoiXmlDialog.h"

CreateSingleDoiXmlDialog::CreateSingleDoiXmlDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(browseDir_pushButton, SIGNAL( clicked() ), this, SLOT( browseDirDialog() ) );
    connect(New_pushButton, SIGNAL( clicked() ), this, SLOT( clearDialog() ) );
    connect(Example_pushButton, SIGNAL( clicked() ), this, SLOT( setExample() ) );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void CreateSingleDoiXmlDialog::setExample()
{
    this->DOI_lineEdit->setText( "auto");

    this->Authors_lineEdit->setText( "Grobe, Hannes; Fuetterer, Dieter" );
    this->Title_lineEdit->setText( "Zur Fragmentierung benthischer Foraminiferen in der Kieler Bucht (Westliche Ostsee)" );
    this->Date_lineEdit->setText( "1981" );
    this->Volume_lineEdit->setText( "33" );
    this->Issue_lineEdit->setText( "1" );
    this->FirstPage_lineEdit->setText( "85" );
    this->LastPage_lineEdit->setText( "96" );
    this->Language_comboBox->setCurrentIndex( 1 );
    this->Description_textEdit->setText( "Early diagenetic ultrastructural alterations of benthic foraminifers of the genera Elphidium and Ophthalmina from the shallow water sediments of the Kiel Bight were investigated by scanning electron microscopy. Pure solution patterns were deduced from supplementary experiments. Several carbonate destroying processes can be specified by ultrastructural patterns of the shell surfaces. Based on these patterns three zones are established, each showing different mechanisms of shell fragmentation: 1) zone of abrasion, 2) zone of disintegration, 3) zone of corrosion. This zonation depends on the water depth and is caused primarily by water agitation and by under saturation of the bottom water with respect to carbonate." );
    this->Discipline_comboBox->setCurrentIndex( 5 );
    this->Type_comboBox->setCurrentIndex( 6 );

    this->ProceedingsTitle_lineEdit->setText( "MEYNIANA" );
    this->ProceedingsPublisher_lineEdit->setText( "Institute for Geosciences, Christian Albrechts University, Kiel" );
    this->ProceedingsContributor_lineEdit->setText( "University of Kiel" );
    this->PublicationPlace_lineEdit->setText( "Kiel, Germany" );
    this->ProceedingsIdentifier_lineEdit->setText( "ISSN 0076-7689" );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void CreateSingleDoiXmlDialog::clearDialog()
{
    this->DOI_lineEdit->setText( "auto");

    this->Authors_lineEdit->setText( "" );
    this->Title_lineEdit->setText( "" );
    this->Date_lineEdit->setText( "" );
    this->Volume_lineEdit->setText( "" );
    this->Issue_lineEdit->setText( "" );
    this->FirstPage_lineEdit->setText( "" );
    this->LastPage_lineEdit->setText( "" );
    this->Language_comboBox->setCurrentIndex( 1 );
    this->Description_textEdit->setText( "" );
    this->Discipline_comboBox->setCurrentIndex( 5 );
    this->Type_comboBox->setCurrentIndex( 6 );

    this->ProceedingsTitle_lineEdit->setText( "" );
    this->ProceedingsPublisher_lineEdit->setText( "" );
    this->ProceedingsContributor_lineEdit->setText( "" );
    this->PublicationPlace_lineEdit->setText( "" );
    this->ProceedingsIdentifier_lineEdit->setText( "" );
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void CreateSingleDoiXmlDialog::browseDirDialog()
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

QString CreateSingleDoiXmlDialog::getDocumentDir()
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

int MainWindow::doCreateSingleDoiXmlDialog()
{
    int i_DialogResult = QDialog::Rejected;

    QValidator *page = new QIntValidator( 0, 9999, this );

// ***********************************************************************************************************************

    CreateSingleDoiXmlDialog dialog( this );

    dialog.FirstPage_lineEdit->setValidator( page );
    dialog.LastPage_lineEdit->setValidator( page );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );
    dialog.New_pushButton->setWhatsThis( "Clear dialog" );
    dialog.browseDir_pushButton->setWhatsThis( "Browse for the output directory" );

// ***********************************************************************************************************************

    dialog.DirLineEdit->setText( QDir::toNativeSeparators( gs_XmlPath ) );

    dialog.DOI_lineEdit->setText( gs_DOI );

    dialog.Authors_lineEdit->setText( gs_Authors );
    dialog.Title_lineEdit->setText( gs_Title );
    dialog.Date_lineEdit->setText( gs_Date );
    dialog.Volume_lineEdit->setText( gs_Volume );
    dialog.Issue_lineEdit->setText( gs_Issue );
    dialog.FirstPage_lineEdit->setText( gs_FirstPage );
    dialog.LastPage_lineEdit->setText( gs_LastPage );
    dialog.Language_comboBox->setCurrentIndex( gi_Language );
    dialog.Description_textEdit->setText( gs_Description );
    dialog.Discipline_comboBox->setCurrentIndex( gi_Discipline );
    dialog.Type_comboBox->setCurrentIndex( gi_Type );

    dialog.ProceedingsTitle_lineEdit->setText( gs_ProceedingsTitle );
    dialog.ProceedingsPublisher_lineEdit->setText( gs_ProceedingsPublisher );
    dialog.ProceedingsContributor_lineEdit->setText( gs_ProceedingsContributor );
    dialog.PublicationPlace_lineEdit->setText( gs_ProceedingsPublicationPlace );
    dialog.ProceedingsIdentifier_lineEdit->setText( gs_ProceedingsIdentifier );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    if ( dialog.exec() == QDialog::Accepted )
    {
        gs_XmlPath                      = dialog.DirLineEdit->text();

        gs_DOI                          = dialog.DOI_lineEdit->text();

        gs_Authors                      = dialog.Authors_lineEdit->text();
        gs_Title                        = dialog.Title_lineEdit->text();
        gs_Date                         = dialog.Date_lineEdit->text();
        gs_Volume                       = dialog.Volume_lineEdit->text();
        gs_Issue                        = dialog.Issue_lineEdit->text();
        gs_FirstPage                    = dialog.FirstPage_lineEdit->text();
        gs_LastPage                     = dialog.LastPage_lineEdit->text();
        gi_Language                     = dialog.Language_comboBox->currentIndex();
        gs_Description                  = dialog.Description_textEdit->toPlainText();
        gi_Discipline                   = dialog.Discipline_comboBox->currentIndex();
        gi_Type                         = dialog.Type_comboBox->currentIndex();

        gs_ProceedingsTitle             = dialog.ProceedingsTitle_lineEdit->text();
        gs_ProceedingsPublisher         = dialog.ProceedingsPublisher_lineEdit->text();
        gs_ProceedingsContributor       = dialog.ProceedingsContributor_lineEdit->text();
        gs_ProceedingsPublicationPlace  = dialog.PublicationPlace_lineEdit->text();
        gs_ProceedingsIdentifier        = dialog.ProceedingsIdentifier_lineEdit->text();

        i_DialogResult                  = QDialog::Accepted;
    }

    posDialog  = dialog.pos();
    sizeDoiXmlDialog = dialog.size();

    if ( i_DialogResult == QDialog::Accepted )
    {
        QString s_Authors   = gs_Authors;
        QString InputStr    = buildDoi( gs_DOI, gs_ProceedingsTitle, gs_Date, gs_Volume, gs_FirstPage );

        s_Authors.replace( "; ", "//" );
        s_Authors.replace( ";", "//" );

        InputStr.append( "\t" + s_Authors + "\t" + gs_Title + "\t" + gs_Date + "\t" + gs_Volume );
        InputStr.append( "\t" + gs_Issue + "\t" + gs_FirstPage + "\t" + gs_LastPage + "\t" );

        switch ( gi_Language )
        {
        case 0: // de
            InputStr.append( "de" );
            break;
        case 1: // en
            InputStr.append( "en" );
            break;
        case 2: // es
            InputStr.append( "es" );
            break;
        case 3: // fr
            InputStr.append( "fr" );
            break;
        case 4: // ru
            InputStr.append( "ru" );
            break;
        default:
            InputStr.append( "en" );
            break;
        }

        InputStr.append( "\t" + gs_Description + "\t" );

        switch ( gi_Discipline )
        {
        default:
            InputStr.append( "500 Science" );
            break;
        case 1:
            InputStr.append( "510 Mathematics" );
            break;
        case 2:
            InputStr.append( "520 Astronomy" );
            break;
        case 3:
            InputStr.append( "530 Physics" );
            break;
        case 4:
            InputStr.append( "540 Chemistry" );
            break;
        case 5:
            InputStr.append( "550 Earth sciences and geology" );
            break;
        case 6:
            InputStr.append( "560 Fossils and prehistoric life" );
            break;
        case 7:
            InputStr.append( "570 Life sciences; biology" );
            break;
        case 8:
            InputStr.append( "580 Plants (Botany)" );
            break;
        case 9:
            InputStr.append( "590 Animals (Zoology)" );
            break;
        }

        InputStr.append( "\t\t" );

        switch ( gi_Type )
        {
        case 0:
             InputStr.append( "Book chapter" );
             break;
        case 1:
             InputStr.append( "Book preface" );
             break;
        case 2:
             InputStr.append( "Conference abstract" );
             break;
        case 3:
             InputStr.append( "Conference paper" );
             break;
        case 4:
             InputStr.append( "Conference poster" );
             break;
        case 5:
             InputStr.append( "Conference talk" );
             break;
        case 6:
             InputStr.append( "Journal article" );
             break;
        case 7:
             InputStr.append( "Journal comment" );
             break;
        case 8:
             InputStr.append( "Journal letter" );
             break;
        case 9:
             InputStr.append( "Journal review" );
             break;
        case 10:
             InputStr.append( "Lecture notes" );
             break;
        case 11:
             InputStr.append( "Newspaper article" );
             break;
        case 12:
             InputStr.append( "Report" );
             break;
        case 13:
             InputStr.append( "Report chapter" );
             break;
        }

        InputStr.append( "\t\t\tapplication/pdf" );
        InputStr.append( "\t" + gs_ProceedingsTitle + "\t" + gs_ProceedingsPublisher + "\t" + gs_ProceedingsContributor );
        InputStr.append( "\t" + gs_ProceedingsPublicationPlace + "\t" + gs_ProceedingsIdentifier );

        CreateDoiXml( gs_XmlPath, tr( "article-doi_v3.2.xsd" ), InputStr );

        downloadXsdFile( gs_XmlPath, tr( "article-doi_v3.2.xsd" ) );

        QMessageBox::information( this, getApplicationName( true ), tr( "DOI XML file has been written to\n" ) + QDir::toNativeSeparators( gs_XmlPath ) );

    }

    return( i_DialogResult );
}
