/* CreateAmdXML.cpp           */
/* 2015-04-03                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-14

int MainWindow::CreateAmdXml( const QString& s_XmlPath, const QString& s_XmlSchema, const QString& InputStr )
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
    tout << "<DIF xmlns=\"http://gcmd.gsfc.nasa.gov/Aboutus/xml/dif/\"" << endl;
    tout << tab << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
    tout << tab << "xsi:schemaLocation=\"http://gcmd.gsfc.nasa.gov/Aboutus/xml/dif/ http://gcmd.nasa.gov/Aboutus/xml/dif/" << s_XmlSchema << "\">" << endl;

    tout << tab << "<Entry_ID></Entry_ID>" << endl;
    tout << tab << "<Entry_Title></Entry_Title>" << endl;
    tout << tab << "<Data_Set_Citation>" << endl;
    tout << tab << tab << "<Dataset_Creator></Dataset_Creator>" << endl;
    tout << tab << tab << "<Dataset_Editor></Dataset_Editor>" << endl;
    tout << tab << tab << "<Dataset_Title></Dataset_Title>" << endl;
    tout << tab << tab << "<Dataset_Series_Name></Dataset_Series_Name>" << endl;
    tout << tab << tab << "<Dataset_Release_Date></Dataset_Release_Date>" << endl;
    tout << tab << tab << "<Dataset_Release_Place></Dataset_Release_Place>" << endl;
    tout << tab << tab << "<Dataset_Publisher></Dataset_Publisher>" << endl;
    tout << tab << tab << "<Version></Version>" << endl;
    tout << tab << tab << "<Issue_Identification></Issue_Identification>" << endl;
    tout << tab << tab << "<Data_Presentation_Form></Data_Presentation_Form>" << endl;
    tout << tab << tab << "<Other_Citation_Details></Other_Citation_Details>" << endl;
    tout << tab << tab << "<Dataset_DOI></Dataset_DOI>" << endl;
    tout << tab << tab << "<Online_Resource></Online_Resource>" << endl;
    tout << tab << "</Data_Set_Citation>" << endl;
    tout << tab << "<Personnel>" << endl;
    tout << tab << tab << "<Role></Role>" << endl;
    tout << tab << tab << "<First_Name></First_Name>" << endl;
    tout << tab << tab << "<Middle_Name></Middle_Name>" << endl;
    tout << tab << tab << "<Last_Name></Last_Name>" << endl;
    tout << tab << tab << "<Email></Email>" << endl;
    tout << tab << tab << "<Phone></Phone>" << endl;
    tout << tab << tab << "<Fax></Fax>" << endl;
    tout << tab << tab << "<Contact_Address>" << endl;
    tout << tab << tab << tab << "<Address></Address>" << endl;
    tout << tab << tab << tab << "<City></City>" << endl;
    tout << tab << tab << tab << "<Province_or_State></Province_or_State>" << endl;
    tout << tab << tab << tab << "<Postal_Code></Postal_Code>" << endl;
    tout << tab << tab << tab << "<Country></Country>" << endl;
    tout << tab << tab << "</Contact_Address>" << endl;
    tout << tab << "</Personnel>" << endl;
    tout << tab << "<Discipline>" << endl;
    tout << tab << tab << "<Discipline_Name></Discipline_Name>" << endl;
    tout << tab << tab << "<Subdiscipline></Subdiscipline>" << endl;
    tout << tab << tab << "<Detailed_Subdiscipline></Detailed_Subdiscipline>" << endl;
    tout << tab << "</Discipline>" << endl;
    tout << tab << "<Parameters>" << endl;
    tout << tab << tab << "<Category></Category>" << endl;
    tout << tab << tab << "<Topic></Topic>" << endl;
    tout << tab << tab << "<Term></Term>" << endl;
    tout << tab << tab << "<Variable_Level_1></Variable_Level_1>" << endl;
    tout << tab << tab << "<Variable_Level_2></Variable_Level_2>" << endl;
    tout << tab << tab << "<Variable_Level_3></Variable_Level_3>" << endl;
    tout << tab << tab << "<Detailed_Variable></Detailed_Variable>" << endl;
    tout << tab << "</Parameters>" << endl;
    tout << tab << "<ISO_Topic_Category></ISO_Topic_Category>" << endl;
    tout << tab << "<Keyword></Keyword>" << endl;
    tout << tab << "<Sensor_Name>" << endl;
    tout << tab << tab << "<Short_Name></Short_Name>" << endl;
    tout << tab << tab << "<Long_Name></Long_Name>" << endl;
    tout << tab << "</Sensor_Name>" << endl;
    tout << tab << "<Source_Name>" << endl;
    tout << tab << tab << "<Short_Name></Short_Name>" << endl;
    tout << tab << tab << "<Long_Name></Long_Name>" << endl;
    tout << tab << "</Source_Name>" << endl;
    tout << tab << "<Temporal_Coverage>" << endl;
    tout << tab << tab << "<Start_Date></Start_Date>" << endl;
    tout << tab << tab << "<Stop_Date></Stop_Date>" << endl;
    tout << tab << "</Temporal_Coverage>" << endl;
    tout << tab << "<Paleo_Temporal_Coverage>" << endl;
    tout << tab << tab << "<Paleo_Start_Date></Paleo_Start_Date>" << endl;
    tout << tab << tab << "<Paleo_Stop_Date></Paleo_Stop_Date>" << endl;
    tout << tab << tab << "<Chronostratigraphic_Unit>" << endl;
    tout << tab << tab << tab << "<Eon></Eon>" << endl;
    tout << tab << tab << tab << "<Era></Era>" << endl;
    tout << tab << tab << tab << "<Period></Period>" << endl;
    tout << tab << tab << tab << "<Epoch></Epoch>" << endl;
    tout << tab << tab << tab << "<Stage></Stage>" << endl;
    tout << tab << tab << tab << "<Detailed_Classification></Detailed_Classification>" << endl;
    tout << tab << tab << "</Chronostratigraphic_Unit>" << endl;
    tout << tab << "</Paleo_Temporal_Coverage>" << endl;
    tout << tab << "<Data_Set_Progress></Data_Set_Progress>" << endl;
    tout << tab << "<Spatial_Coverage>" << endl;
    tout << tab << tab << "<Southernmost_Latitude></Southernmost_Latitude>" << endl;
    tout << tab << tab << "<Northernmost_Latitude></Northernmost_Latitude>" << endl;
    tout << tab << tab << "<Westernmost_Longitude></Westernmost_Longitude>" << endl;
    tout << tab << tab << "<Easternmost_Longitude></Easternmost_Longitude>" << endl;
    tout << tab << tab << "<Minimum_Altitude></Minimum_Altitude>" << endl;
    tout << tab << tab << "<Maximum_Altitude></Maximum_Altitude>" << endl;
    tout << tab << tab << "<Minimum_Depth></Minimum_Depth>" << endl;
    tout << tab << tab << "<Maximum_Depth></Maximum_Depth>" << endl;
    tout << tab << "</Spatial_Coverage>" << endl;
    tout << tab << "<Location>" << endl;
    tout << tab << tab << "<Location_Category></Location_Category>" << endl;
    tout << tab << tab << "<Location_Type></Location_Type>" << endl;
    tout << tab << tab << "<Location_Subregion1></Location_Subregion1>" << endl;
    tout << tab << tab << "<Location_Subregion2></Location_Subregion2>" << endl;
    tout << tab << tab << "<Location_Subregion3></Location_Subregion3>" << endl;
    tout << tab << tab << "<Detailed_Location></Detailed_Location>" << endl;
    tout << tab << "</Location>" << endl;
    tout << tab << "<Data_Resolution>" << endl;
    tout << tab << tab << "<Latitude_Resolution></Latitude_Resolution>" << endl;
    tout << tab << tab << "<Longitude_Resolution></Longitude_Resolution>" << endl;
    tout << tab << tab << "<Horizontal_Resolution_Range></Horizontal_Resolution_Range>" << endl;
    tout << tab << tab << "<Vertical_Resolution></Vertical_Resolution>" << endl;
    tout << tab << tab << "<Vertical_Resolution_Range></Vertical_Resolution_Range>" << endl;
    tout << tab << tab << "<Temporal_Resolution></Temporal_Resolution>" << endl;
    tout << tab << tab << "<Temporal_Resolution_Range></Temporal_Resolution_Range>" << endl;
    tout << tab << "</Data_Resolution>" << endl;
    tout << tab << "<Project>" << endl;
    tout << tab << tab << "<Short_Name></Short_Name>" << endl;
    tout << tab << tab << "<Long_Name></Long_Name>" << endl;
    tout << tab << "</Project>" << endl;
    tout << tab << "<Quality></Quality>" << endl;
    tout << tab << "<Access_Constraints></Access_Constraints>" << endl;
    tout << tab << "<Use_Constraints></Use_Constraints>" << endl;
    tout << tab << "<Data_Set_Language></Data_Set_Language>" << endl;
    tout << tab << "<Originating_Center></Originating_Center>" << endl;
    tout << tab << "<Data_Center>" << endl;
    tout << tab << tab << "<Data_Center_Name>" << endl;
    tout << tab << tab << tab << "<Short_Name></Short_Name>" << endl;
    tout << tab << tab << tab << "<Long_Name></Long_Name>" << endl;
    tout << tab << tab << "</Data_Center_Name>" << endl;
    tout << tab << tab << "<Data_Center_URL></Data_Center_URL>" << endl;
    tout << tab << tab << "<Data_Set_ID></Data_Set_ID>" << endl;
    tout << tab << tab << "<Personnel>" << endl;
    tout << tab << tab << tab << "<Role></Role>" << endl;
    tout << tab << tab << tab << "<First_Name></First_Name>" << endl;
    tout << tab << tab << tab << "<Middle_Name></Middle_Name>" << endl;
    tout << tab << tab << tab << "<Last_Name></Last_Name>" << endl;
    tout << tab << tab << tab << "<Email></Email>" << endl;
    tout << tab << tab << tab << "<Phone></Phone>" << endl;
    tout << tab << tab << tab << "<Fax></Fax>" << endl;
    tout << tab << tab << tab << "<Contact_Address>" << endl;
    tout << tab << tab << tab << tab << "<Address></Address>" << endl;
    tout << tab << tab << tab << tab << "<City></City>" << endl;
    tout << tab << tab << tab << tab << "<Province_or_State></Province_or_State>" << endl;
    tout << tab << tab << tab << tab << "<Postal_Code></Postal_Code>" << endl;
    tout << tab << tab << tab << tab << "<Country></Country>" << endl;
    tout << tab << tab << tab << "</Contact_Address>" << endl;
    tout << tab << tab << "</Personnel>" << endl;
    tout << tab << "</Data_Center>" << endl;
    tout << tab << "<Distribution>" << endl;
    tout << tab << tab << "<Distribution_Media></Distribution_Media>" << endl;
    tout << tab << tab << "<Distribution_Size></Distribution_Size>" << endl;
    tout << tab << tab << "<Distribution_Format></Distribution_Format>" << endl;
    tout << tab << tab << "<Fees></Fees>" << endl;
    tout << tab << "</Distribution>" << endl;
    tout << tab << "<Multimedia_Sample>" << endl;
    tout << tab << tab << "<File></File>" << endl;
    tout << tab << tab << "<URL></URL>" << endl;
    tout << tab << tab << "<Format></Format>" << endl;
    tout << tab << tab << "<Caption></Caption>" << endl;
    tout << tab << tab << "<Description></Description>" << endl;
    tout << tab << "</Multimedia_Sample>" << endl;
    tout << tab << "<Reference>" << endl;
    tout << tab << tab << "<Author></Author>" << endl;
    tout << tab << tab << "<Publication_Date></Publication_Date>" << endl;
    tout << tab << tab << "<Title></Title>" << endl;
    tout << tab << tab << "<Series></Series>" << endl;
    tout << tab << tab << "<Edition></Edition>" << endl;
    tout << tab << tab << "<Volume></Volume>" << endl;
    tout << tab << tab << "<Issue></Issue>" << endl;
    tout << tab << tab << "<Report_Number></Report_Number>" << endl;
    tout << tab << tab << "<Publication_Place></Publication_Place>" << endl;
    tout << tab << tab << "<Publisher></Publisher>" << endl;
    tout << tab << tab << "<Pages></Pages>" << endl;
    tout << tab << tab << "<ISBN></ISBN>" << endl;
    tout << tab << tab << "<DOI></DOI>" << endl;
    tout << tab << tab << "<Online_Resource></Online_Resource>" << endl;
    tout << tab << tab << "<Other_Reference_Details></Other_Reference_Details>" << endl;
    tout << tab << "</Reference>" << endl;
    tout << tab << "<Summary>" << endl;
    tout << tab << tab << "<Abstract></Abstract>" << endl;
    tout << tab << tab << "<Purpose></Purpose>" << endl;
    tout << tab << "</Summary>" << endl;
    tout << tab << "<Related_URL>" << endl;
    tout << tab << tab << "<URL_Content_Type>" << endl;
    tout << tab << tab << tab << "<Type></Type>" << endl;
    tout << tab << tab << tab << "<Subtype></Subtype>" << endl;
    tout << tab << tab << "</URL_Content_Type>" << endl;
    tout << tab << tab << "<URL></URL>" << endl;
    tout << tab << tab << "<Description></Description>" << endl;
    tout << tab << "</Related_URL>" << endl;
    tout << tab << "<Parent_DIF></Parent_DIF>" << endl;
    tout << tab << "<IDN_Node>" << endl;
    tout << tab << tab << "<Short_Name></Short_Name>" << endl;
    tout << tab << tab << "<Long_Name></Long_Name>" << endl;
    tout << tab << "</IDN_Node>" << endl;
    tout << tab << "<Originating_Metadata_Node></Originating_Metadata_Node>" << endl;
    tout << tab << "<Metadata_Name></Metadata_Name>" << endl;
    tout << tab << "<Extended_Metadata>" << endl;
    tout << tab << tab << "<Group></Group>" << endl;
    tout << tab << tab << "<Name></Name>" << endl;
    tout << tab << tab << "<Value></Value>" << endl;
    tout << tab << "</Extended_Metadata>" << endl;
    tout << tab << "<Metadata_Version></Metadata_Version>" << endl;
    tout << tab << "<DIF_Creation_Date></DIF_Creation_Date>" << endl;
    tout << tab << "<Last_DIF_Revision_Date></Last_DIF_Revision_Date>" << endl;
    tout << tab << "<DIF_Revision_History></DIF_Revision_History>" << endl;
    tout << tab << "<Future_DIF_Review_Date></Future_DIF_Review_Date>" << endl;
    tout << tab << "<Private></Private>" << endl;
    tout << "</DIF>" << endl;

    fout.close();

// **********************************************************************************************

    return( _NOERROR_ );
}

// ******************************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-12

void MainWindow::doCreateAmdXml()
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
                        initProgress( gsl_FilenameList.count(), s_FilenameIn, tr( "Creating files..." ), sl_Input.count() );

                        j = 2;

                        while ( ( j<sl_Input.count() ) && ( stopProgress != _APPBREAK_ ) )
                        {
                            err          = CreateAmdXml( gs_XmlPath, tr( "dif_v9.8.4.xsd" ), sl_Input.at( j ) );

                            stopProgress = incProgress( gsl_FilenameList.count(), ++j );
                        }

                        resetProgress( sl_Input.count() );

                        n += j - 2;
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

    downloadXsdFile( gs_XmlPath, "dif_v9.8.4.xsd" );

    gi_ActionNumber = 1;

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Creating XML files was canceled" ), false, false );

// ******************************************************************************************************

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) && ( n == 1 ) )
        QMessageBox::information( this, getApplicationName( true ), tr( "AMD XML file has been written to\n" ) + QDir::toNativeSeparators( gs_XmlPath ) );

    if ( ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) && ( n > 1 ) )
        QMessageBox::information( this, getApplicationName( true ), QString( "%1 AMD XML files have been written to\n%2" ).arg( n ).arg( QDir::toNativeSeparators( gs_XmlPath ) ) );

    onError( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-10-12

void MainWindow::doCreateAmdXmlTemplate()
{
    int err = 0;

    QFileInfo	fi;

// *********************************************************************************************

    fi.setFile( gs_Path );

    if ( fi.exists() == false )
        gs_Path = getDocumentDir();

    QString s_Filename         = gs_Path + "/" + "DatasetListTemplate.txt";
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

            tout << "Entry\tEntry\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tData_Set_Citation\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tPersonnel\tDiscipline\tDiscipline\tDiscipline\tParameters\tParameters\tParameters\tParameters\tParameters\tParameters\tParameters\tParameters\t\t\tSensor_Name\tSensor_Name\tSource_Name\tSource_Name\tTemporal_Coverage\tTemporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\tPaleo_Temporal_Coverage\t\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tSpatial_Coverage\tLocation\tLocation\tLocation\tLocation\tLocation\tLocation\tData_Resolution\tData_Resolution\tData_Resolution\tData_Resolution\tData_Resolution\tData_Resolution\tData_Resolution\tProject\tProject\t\t\t\t\t\tData_Center\tData_Center\tData_Center\tData_Center\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tData_Center_Personnel\tDistribution\tDistribution\tDistribution\tDistribution\tMultimedia_Sample\tMultimedia_Sample\tMultimedia_Sample\tMultimedia_Sample\tMultimedia_Sample\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tReference\tSummary\tSummary\tRelated_URL\tRelated_URL\tRelated_URL\tRelated_URL\t\tIDN_Node\tIDN_Node\t\t\tExtended_Metadata\tExtended_Metadata\tExtended_Metadata" << endl;
            tout << "Entry_ID\tEntry_Title\tDataset_Creator\tDataset_Editor\tDataset_Title\tDataset_Series_Name\tDataset_Release_Date\tDataset_Release_Place\tDataset_Publisher\tVersion\tIssue_Identification\tData_Presentation_Form\tOther_Citation_Details\tDataset_DOI\tOnline_Resource\tRole\tFirst_Name\tMiddle_Name\tLast_Name\tEmail\tPhone\tFax\tAddress\tCity\tProvince_or_State\tPostal_Code\tCountry\tDiscipline_Name\tSubdiscipline\tDetailed_Subdiscipline\tParameters\tCategory\tTopic\tTerm\tVariable_Level_1\tVariable_Level_2\tVariable_Level_3\tDetailed_Variable\tISO_Topic_Category\tKeyword\tShort_Name\tLong_Name\tShort_Name\tLong_Name\tStart_Date\tStop_Date\tPaleo_Start_Date\tPaleo_Stop_Date\tEon\tEra\tPeriod\tEpoch\tStage\tDetailed_Classification\tData_Set_Progress\tSouthernmost_Latitude\tNorthernmost_Latitude\tWesternmost_Longitude\tEasternmost_Longitude\tMinimum_Altitude\tMaximum_Altitude\tMinimum_Depth\tMaximum_Depth\tLocation_Category\tLocation_Type\tLocation_Subregion1\tLocation_Subregion2\tLocation_Subregion3\tDetailed_Location\tLatitude_Resolution\tLongitude_Resolution\tHorizontal_Resolution_Range\tVertical_Resolution\tVertical_Resolution_Range\tTemporal_Resolution\tTemporal_Resolution_Range\tShort_Name\tLong_Name\tQuality\tAccess_Constraints\tUse_Constraints\tData_Set_Language\tOriginating_Center\tShort_Name\tLong_Name\tData_Center_URL\tData_Set_ID\tRole\tFirst_Name\tMiddle_Name\tLast_Name\tEmail\tPhone\tFax\tContact_Address\tAddress\tCity\tProvince_or_State\tPostal_Code\tCountry\tDistribution_Media\tDistribution_Size\tDistribution_Format\tFees\tFile\tURL\tFormat\tCaption\tDescription\tAuthor\tPublication_Date\tTitle\tSeries\tEdition\tVolume\tIssue\tReport_Number\tPublication_Place\tPublisher\tPages\tISBN\tDOI\tOnline_Resource\tOther_Reference_Details\tAbstract\tPurpose\tType\tSubtype\tURL\tDescription\tParent_DIF\tShort_Name\tLong_Name\tOriginating_Metadata_Node\tMetadata_Name\tGroup\tName\tValue\tMetadata_Version\tDIF_Creation_Date\tLast_DIF_Revision_Date\tDIF_Revision_History\tFuture_DIF_Review_Date\tPrivate" << endl;

            fout.close();

            downloadXsdFile( gs_Path, tr( "dif_v9.8.4.xsd" ) );

            QMessageBox::information( this, getApplicationName( true ), tr( "Dataset list template file has been written to\n" ) + QDir::toNativeSeparators( s_FilenameTemplate ) );
        }
    }

    onError( err );
}
