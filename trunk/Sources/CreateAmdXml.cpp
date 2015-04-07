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
    int             i                       = 0;

    QString         tab                     = "\t";

    QStringList     sl_OutStr;

    QDateTime       DateTime                = QDateTime::currentDateTime();

// **********************************************************************************************

    QFile fout( s_XmlPath + "/" + InputStr.section( "\t", 0, 0 ) + ".xml" );

    if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        return( -20 );

    QTextStream tout( &fout ); tout.setCodec( "UTF-8" );

    DateTime = QDateTime::currentDateTime();

// **********************************************************************************************

    sl_OutStr.append( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" );
    sl_OutStr.append( "<!-- created with PanXML (doi:10.1594/PANGAEA.746153) on " + DateTime.toString( "yyyy-MM-dd" ) + " -->" );
    sl_OutStr.append( "<DIF xmlns=\"http://gcmd.gsfc.nasa.gov/Aboutus/xml/dif/\"" );
    sl_OutStr.append( tab + "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" );
    sl_OutStr.append( tab + "xsi:schemaLocation=\"http://gcmd.gsfc.nasa.gov/Aboutus/xml/dif/ http://gcmd.nasa.gov/Aboutus/xml/dif/" + s_XmlSchema + "\">"  );

    sl_OutStr.append( tab + buildTextEntry( "Entry_ID", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Entry_Title", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<Data_Set_Citation>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Creator", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Editor", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Title", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Series_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Release_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Release_Place", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_Publisher", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Version", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Issue_Identification", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Data_Presentation_Form", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Other_Citation_Details", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Dataset_DOI", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Online_Resource", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Data_Set_Citation>" );
    sl_OutStr.append( tab + "<Personnel>" ); // PI
    sl_OutStr.append( tab + tab + buildTextEntry( "Role", "INVESTIGATOR", 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "First_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Middle_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Last_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildEmailEntry( "Email", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + buildPhoneEntry( "Phone", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + buildPhoneEntry( "Fax", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + "<Contact_Address>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Address", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "City", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Province_or_State", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Postal_Code", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Country", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "</Contact_Address>" );
    sl_OutStr.append( tab + "</Personnel>" );
    sl_OutStr.append( tab + "<Personnel>" ); // DIF Author
    sl_OutStr.append( tab + tab + buildTextEntry( "Role", "DIF AUTHOR", 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "First_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Middle_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Last_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildEmailEntry( "Email", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + buildPhoneEntry( "Phone", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + buildPhoneEntry( "Fax", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + "<Contact_Address>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Address", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "City", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Province_or_State", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Postal_Code", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Country", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "</Contact_Address>" );
    sl_OutStr.append( tab + "</Personnel>" );
    sl_OutStr.append( tab + "<Discipline>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Discipline_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Subdiscipline", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Detailed_Subdiscipline", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Discipline>" );
    sl_OutStr.append( tab + "<Parameters>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Category", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Topic", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Term", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Variable_Level_1", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Variable_Level_2", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Variable_Level_3", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Detailed_Variable", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Parameters>" );
    sl_OutStr.append( tab + buildTextEntry( "ISO_Topic_Category", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Keyword", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<Sensor_Name>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Short_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Long_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Sensor_Name>" );
    sl_OutStr.append( tab + "<Source_Name>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Short_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Long_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Source_Name>" );
    sl_OutStr.append( tab + "<Temporal_Coverage>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Start_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Stop_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Temporal_Coverage>" );
    sl_OutStr.append( tab + "<Paleo_Temporal_Coverage>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Paleo_Start_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Paleo_Stop_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "<Chronostratigraphic_Unit>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Eon", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Era", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Period", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Epoch", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Stage", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Detailed_Classification", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "</Chronostratigraphic_Unit>" );
    sl_OutStr.append( tab + "</Paleo_Temporal_Coverage>" );
    sl_OutStr.append( tab + buildTextEntry( "Data_Set_Progress", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<Spatial_Coverage>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Southernmost_Latitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Northernmost_Latitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Westernmost_Longitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Easternmost_Longitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Minimum_Altitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Maximum_Altitude", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Minimum_Depth", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Maximum_Depth", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Spatial_Coverage>" );
    sl_OutStr.append( tab + "<Location>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Location_Category", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Location_Type", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Location_Subregion1", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Location_Subregion2", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Location_Subregion3", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Detailed_Location", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Location>" );
    sl_OutStr.append( tab + "<Data_Resolution>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Latitude_Resolution", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Longitude_Resolution", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Horizontal_Resolution_Range", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Vertical_Resolution", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Vertical_Resolution_Range", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Temporal_Resolution", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Temporal_Resolution_Range", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Data_Resolution>" );
    sl_OutStr.append( tab + "<Project>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Short_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Long_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Project>" );
    sl_OutStr.append( tab + buildTextEntry( "Quality", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Access_Constraints", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Use_Constraints", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Data_Set_Language", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Originating_Center", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<Data_Center>" );
    sl_OutStr.append( tab + tab + "<Data_Center_Name>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Short_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Long_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "</Data_Center_Name>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Data_Center_URL", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Data_Set_ID", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "<Personnel>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Role", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "First_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Middle_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Last_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildEmailEntry( "Email", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildPhoneEntry( "Phone", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildPhoneEntry( "Fax", InputStr.section( "\t", i, i ) ) ); i++;
    sl_OutStr.append( tab + tab + tab + "<Contact_Address>" );
    sl_OutStr.append( tab + tab + tab + tab + buildTextEntry( "Address", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + tab + buildTextEntry( "City", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + tab + buildTextEntry( "Province_or_State", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + tab + buildTextEntry( "Postal_Code", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + tab + buildTextEntry( "Country", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + "</Contact_Address>" );
    sl_OutStr.append( tab + tab + "</Personnel>" );
    sl_OutStr.append( tab + "</Data_Center>" );
    sl_OutStr.append( tab + "<Distribution>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Distribution_Media", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Distribution_Size", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Distribution_Format", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Fees", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Distribution>" );
    sl_OutStr.append( tab + "<Multimedia_Sample>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "File", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "URL", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Format", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Caption", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Description", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Multimedia_Sample>" );
    sl_OutStr.append( tab + "<Reference>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Author", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Publication_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Title", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Series", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Edition", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Volume", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Issue", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Report_Number", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Publication_Place", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Publisher", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Pages", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "ISBN", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "DOI", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Online_Resource", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Other_Reference_Details", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Reference>" );
    sl_OutStr.append( tab + "<Summary>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Abstract", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Purpose", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Summary>" );
    sl_OutStr.append( tab + "<Related_URL>" );
    sl_OutStr.append( tab + tab + "<URL_Content_Type>" );
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Type", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + tab + buildTextEntry( "Subtype", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + "</URL_Content_Type>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "URL", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Description", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Related_URL>" );
    sl_OutStr.append( tab + buildTextEntry( "Parent_DIF", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<IDN_Node>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Short_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Long_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</IDN_Node>" );
    sl_OutStr.append( tab + buildTextEntry( "Originating_Metadata_Node", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Metadata_Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "<Extended_Metadata>" );
    sl_OutStr.append( tab + tab + buildTextEntry( "Group", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Name", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + tab + buildTextEntry( "Value", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + "</Extended_Metadata>" );
    sl_OutStr.append( tab + buildTextEntry( "Metadata_Version", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "DIF_Creation_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Last_DIF_Revision_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "DIF_Revision_History", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Future_DIF_Review_Date", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( tab + buildTextEntry( "Private", InputStr.section( "\t", i, i ), 0 ) ); i++;
    sl_OutStr.append( "</DIF>" );

    for ( int i=0; i<sl_OutStr.count(); i++ )
    {
        if ( sl_OutStr.at( i ).contains( "<EMPTY>" ) == false )
            tout << sl_OutStr.at( i ) << endl;
    }

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

            tout << "Entry\tEntry\t";

            for ( int i=1; i<=13; i++ )
                tout << "Dataset Citation\t";

            for ( int i=1; i<=12; i++ )
                tout << "PI\t";

            for ( int i=1; i<=12; i++ )
                tout << "DIF Author\t";

            for ( int i=1; i<=3; i++ )
                tout << "Discipline\t";

            for ( int i=1; i<=7; i++ )
                tout << "Parameters\t";

            tout << "\t\t";

            tout << "Instrument (Sensor Name)\tInstrument (Sensor Name)\t";
            tout << "Platform (Source Name)\tPlatform (Source Name)\t";
            tout << "Temporal Coverage\tTemporal Coverage\t";

            for ( int i=1; i<=8; i++ )
                tout << "Paleo Temporal Coverage\t";

            tout << "\t";

            for ( int i=1; i<=8; i++ )
                tout << "Spatial Coverage\t";

            for ( int i=1; i<=6; i++ )
                tout << "Location\t";

            for ( int i=1; i<=7; i++ )
                tout << "Data Resolution\t";

            tout << "Project\tProject\t\t\t\t\t\t";

            for ( int i=1; i<=4; i++ )
                tout << "Data Center\t";

            for ( int i=1; i<=12; i++ )
                tout << "Data Center Personnel\t";

            for ( int i=1; i<=4; i++ )
                tout << "Distribution\t";

            for ( int i=1; i<=5; i++ )
                tout << "Multimedia Sample\t";

            for ( int i=1; i<=15; i++ )
                tout << "Reference\t";

            tout << "Summary\tSummary\t";

            for ( int i=1; i<=4; i++ )
                tout << "Related_URL\t";

            tout << "\tIDN Node\tIDN Node\t\t\t";

            tout << "Extended Metadata\tExtended Metadata\tExtended Metadata" << endl;

            tout << "Entry ID\tEntry Title\tDataset Creator\tDataset Editor\tDataset Title\tDataset Series Name\t";
            tout << "Dataset Release Date\tDataset Release Place\tDataset Publisher\tVersion\tIssue Identification\t";
            tout << "Data Presentation Form\tOther Citation Details\tDataset DOI\tOnline Resource\t";
            tout << "Role\tFirst Name\tMiddle Name\tLast Name\tEmail\tPhone\tFax\tAddress\tCity\tProvince or State\tPostal Code\tCountry\t"; // PI
            tout << "Role\tFirst Name\tMiddle Name\tLast Name\tEmail\tPhone\tFax\tAddress\tCity\tProvince or State\tPostal Code\tCountry\t"; // Editor
            tout << "Discipline Name\tSubdiscipline\tDetailed Subdiscipline\tCategory\tTopic\tTerm\tVariable Level 1\t";
            tout << "Variable Level 2\tVariable Level 3\tDetailed Variable\tISO Topic Category\tKeyword\tShort Name\t";
            tout << "Long Name\tShort Name\tLong Name\tStart Date\tStop Date\tPaleo Start Date\tPaleo Stop Date\tEon\tEra\t";
            tout << "Period\tEpoch\tStage\tDetailed Classification\tData Set Progress\tSouthernmost Latitude\tNorthernmost Latitude\t";
            tout << "Westernmost Longitude\tEasternmost Longitude\tMinimum Altitude\tMaximum Altitude\tMinimum Depth\tMaximum Depth\t";
            tout << "Location Category\tLocation Type\tLocation Subregion1\tLocation Subregion2\tLocation Subregion3\tDetailed Location\t";
            tout << "Latitude Resolution\tLongitude Resolution\tHorizontal Resolution Range\tVertical Resolution\tVertical Resolution Range\t";
            tout << "Temporal Resolution\tTemporal Resolution Range\tShort Name\tLong Name\tQuality\tAccess Constraints\tUse Constraints\t";
            tout << "Data Set Language\tOriginating Center\tShort Name\tLong Name\tData Center URL\tData Set ID\tRole\tFirst Name\tMiddle Name\t";
            tout << "Last Name\tEmail\tPhone\tFax\tAddress\tCity\tProvince or State\tPostal Code\tCountry\tDistribution Media\tDistribution Size\t";
            tout << "Distribution Format\tFees\tFile\tURL\tFormat\tCaption\tDescription\tAuthor\tPublication Date\tTitle\tSeries\tEdition\tVolume\t";
            tout << "Issue\tReport Number\tPublication Place\tPublisher\tPages\tISBN\tDOI\tOnline Resource\tOther Reference Details\tAbstract\t";
            tout << "Purpose\tType\tSubtype\tURL\tDescription\tParent DIF\tShort Name\tLong Name\tOriginating Metadata Node\tMetadata Name\tGroup\t";
            tout << "Name\tValue\tMetadata Version\tDIF Creation Date\tLast DIF Revision Date\tDIF Revision History\tFuture DIF Review Date\tPrivate" << endl;

            fout.close();

            downloadXsdFile( gs_Path, tr( "dif_v9.8.4.xsd" ) );

            QMessageBox::information( this, getApplicationName( true ), tr( "Dataset list template file has been written to\n" ) + QDir::toNativeSeparators( s_FilenameTemplate ) );
        }
    }

    onError( err );
}
