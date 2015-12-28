// ***********************************************************************************************
// *                                                                                             *
// * createMenu.cpp - creates application menus                                                  *
// *                                                                                             *
// * Dr. Rainer Sieger - 2008-05-18                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Erstellen der Menue-Aktionen. */

void MainWindow::createActions()
{
// File menu
    newWindowAction = new QAction(tr("&New window"), this);
    newWindowAction->setShortcut(tr("Ctrl+N"));
    connect(newWindowAction, SIGNAL(triggered()), this, SLOT(newWindow()));

    openFileAction = new QAction(tr("&Open..."), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(chooseFiles()));

    openFolderAction = new QAction(tr("Select &Folder..."), this);
    openFolderAction->setShortcut(tr("Ctrl+F"));
    connect(openFolderAction, SIGNAL(triggered()), this, SLOT(chooseFolder()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    hideWindowAction = new QAction(tr("&Close window"), this);
    hideWindowAction->setShortcut(tr("Ctrl+W"));
    connect(hideWindowAction, SIGNAL(triggered()), this, SLOT(hideWindow()));

    exitAction = new QAction(tr("&Quit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //AMD
    createAmdXmlAction = new QAction(tr("Dataset list -> XML files for AMD registration"), this);
    connect(createAmdXmlAction, SIGNAL(triggered()), this, SLOT(doCreateAmdXml()));

    // TIB
    createDoiXmlAction = new QAction(tr("Reference list -> XML files for DOI registration"), this);
    connect(createDoiXmlAction, SIGNAL(triggered()), this, SLOT(doCreateDoiXml()));

    createSingleDoiXmlDialogAction = new QAction(tr("Create XML file for DOI registration..."), this);
    connect(createSingleDoiXmlDialogAction, SIGNAL(triggered()), this, SLOT(doCreateSingleDoiXmlDialog()));

/*
    // ePIC
    createEPicXmlAction = new QAction(tr("Reference list -> XML file for ePIC batch upload"), this);
    connect(createEPicXmlAction, SIGNAL(triggered()), this, SLOT(doCreateEPicXml()));

    createSimpleEPicXmlAction = new QAction(tr("Create simple XML file for ePIC batch upload..."), this);
    connect(createSimpleEPicXmlAction, SIGNAL(triggered()), this, SLOT(doCreateSimpleEPicXml()));
*/

    // Templates
    createAmdXmlTemplateAction = new QAction(tr("Create dataset list as template"), this);
    connect(createAmdXmlTemplateAction, SIGNAL(triggered()), this, SLOT(doCreateAmdXmlTemplate()));

    createDoiXmlTemplateAction = new QAction(tr("Create reference list as template"), this);
    connect(createDoiXmlTemplateAction, SIGNAL(triggered()), this, SLOT(doCreateDoiXmlTemplate()));

    // Help menu
    aboutAction = new QAction(tr("&About ") + getApplicationName( true ), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    showHelpAction = new QAction(getApplicationName( true ) + tr(" &Help"), this);
    showHelpAction->setShortcut(tr("F1"));
    connect(showHelpAction, SIGNAL(triggered()), this, SLOT(displayHelp()));

#if defined(Q_OS_WIN)
    newWindowAction->setStatusTip(tr("Create a new file"));
    openFileAction->setStatusTip(tr("Choose an existing file"));
    openFolderAction->setStatusTip(tr("Choose an existing folder"));
    saveAction->setStatusTip(tr("Save the document to disk"));
    saveAsAction->setStatusTip(tr("Save the document under a new name"));
    exitAction->setStatusTip(tr("Exit the application"));

    createSingleDoiXmlDialogAction->setStatusTip(tr("create a single DOI XML file with a dialog"));
    createDoiXmlAction->setStatusTip(tr("create many DOI XML files with a list of references"));
    createDoiXmlTemplateAction->setStatusTip(tr("create a reference list as template"));

    aboutAction->setStatusTip(tr("Show the application's About box"));
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    showHelpAction->setStatusTip(tr("Show the application's help"));
#endif

}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Verbindet Menues mit Aktionen. */

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->addAction( openFileAction );
    fileMenu->addAction( openFolderAction );
    fileMenu->addSeparator();

#if defined(Q_OS_LINUX)
    fileMenu->addAction( exitAction );
#endif

#if defined(Q_OS_MAC)
    fileMenu->addAction( newWindowAction );
    newWindowAction->setEnabled( false );
    fileMenu->addAction( hideWindowAction );
#endif

#if defined(Q_OS_WIN)
    fileMenu->addAction( hideWindowAction );
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );
#endif

// **********************************************************************************************

    toolMenu = menuBar()->addMenu( tr( "Tools" ) );
    toolMenu->addAction( createAmdXmlAction );
    toolMenu->addAction( createDoiXmlAction );
    toolMenu->addSeparator();
    toolMenu->addAction( createAmdXmlTemplateAction );
    toolMenu->addAction( createDoiXmlTemplateAction );
//  toolMenu->addAction( createSingleDoiXmlDialogAction );
//  toolMenu->addAction( createSimpleEPicXmlAction );
//  toolMenu->addAction( createEPicXmlAction );
//  toolMenu->addSeparator();

// **********************************************************************************************

    helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
    helpMenu->addSeparator();
    helpMenu->addAction( showHelpAction );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::enableMenuItems( const QStringList sl_FilenameList )
{
    bool b_containsBinaryFile = containsBinaryFile( sl_FilenameList );

// **********************************************************************************************

    QList<QAction*> toolMenuActions = toolMenu->actions();

    if ( b_containsBinaryFile == false )
    {
        for ( int i=0; i<toolMenuActions.count(); ++i )
            toolMenuActions.at( i )->setEnabled( true );
    }
    else
    {
        for ( int i=0; i<toolMenuActions.count(); ++i )
            toolMenuActions.at( i )->setEnabled( false );
    }
}
