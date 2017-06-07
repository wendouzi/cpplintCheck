#include "cpplintplugin.h"

#include "Constants.h"

#include <app/app_version.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/id.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/findplaceholder.h>
#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/helpmanager.h>
#include <coreplugin/minisplitter.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/rightpane.h>
#include <coreplugin/sidebar.h>
#include <extensionsystem/pluginmanager.h>
#include <coreplugin/find/findplugin.h>
#include <texteditor/texteditorconstants.h>
#include <utils/hostosinfo.h>
#include <utils/styledbar.h>

#include <cppeditor/cppeditor.h>
#include <texteditor/texteditorconstants.h>
#include <cpptools/cpptoolsconstants.h>
#include <cppeditor/cppeditorconstants.h>

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/project.h>
#include <projectexplorer/taskhub.h>
#include <projectexplorer/buildmanager.h>
#include <projectexplorer/session.h>

#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QTimer>
#include <QTranslator>
#include <qplugin.h>
#include <QRegExp>
#include <QString>
#include <QAction>
#include <QComboBox>
#include <QDesktopServices>
#include <QMenu>
#include <QShortcut>
#include <QStackedLayout>
#include <QSplitter>
#include <QIcon>
#include <QLatin1String>
#include <iostream>

using namespace Core;

#define IMAGEPATH ":/help/images/"

namespace cpplintCheck {

cpplintCheckPlugin::cpplintCheckPlugin() {

}
cpplintCheckPlugin::~cpplintCheckPlugin() {
}

bool cpplintCheckPlugin::initialize(const QStringList &arguments, QString *errorString){

    //Context context(CppEditor::Constants::C_CPPEDITOR);
    Context context(Core::Constants::C_GLOBAL);

    QAction * checkNodeAction = new QAction(tr("Scan with cppcheck"), this);
    Command* checkNodeCmd = ActionManager::registerAction(checkNodeAction, Constants::ACTION_CHECK_NODE_ID,
                                                          Context(Core::Constants::C_EDIT_MODE));
    connect(checkNodeAction, SIGNAL(triggered()), this, SLOT(checkCurrentNode()));

#define ADD_TO_MENU(COMMAND, CONTAINER_ID) {ActionContainer *menu = ActionManager::actionContainer(CONTAINER_ID);if (menu != NULL) {menu->addAction(COMMAND);}}
    ADD_TO_MENU (checkNodeCmd, ProjectExplorer::Constants::M_FILECONTEXT);
    ADD_TO_MENU (checkNodeCmd, ProjectExplorer::Constants::M_FOLDERCONTEXT);
    ADD_TO_MENU (checkNodeCmd, ProjectExplorer::Constants::M_PROJECTCONTEXT);
    ADD_TO_MENU (checkNodeCmd, ProjectExplorer::Constants::M_SUBPROJECTCONTEXT);
#undef ADD_TO_MENU

    QAction *checkProjectAction = new QAction(tr("cpplint Check current project"), this);
    Core::Command *checkProjectCmd = ActionManager::registerAction(
                checkProjectAction, Constants::ACTION_CHECK_PROJECT_ID,
                context);
    checkProjectCmd->setDefaultKeySequence (QKeySequence(tr("Alt+C,Ctrl+A")));
    connect(checkProjectAction, SIGNAL(triggered()), this, SLOT(checkActiveProject()));

    QAction *checkDocumentAction = new QAction(tr("cpplint Check current document"), this);
    Command *checkDocumentCmd = ActionManager::registerAction(
                                  checkDocumentAction, Constants::ACTION_CHECK_DOCUMENT_ID,
                                  context);
    checkDocumentCmd->setDefaultKeySequence (QKeySequence (tr ("Alt+C,Ctrl+D")));
    connect(checkDocumentAction, SIGNAL(triggered()), this, SLOT(checkCurrentDocument()));

    ActionContainer *contextMenu = ActionManager::createMenu(CppEditor::Constants::M_CONTEXT);
    ActionContainer *cppToolsMenu = ActionManager::actionContainer(CppTools::Constants::M_TOOLS_CPP);

    contextMenu->addAction(checkDocumentCmd);
    contextMenu->addAction(checkProjectCmd);
    cppToolsMenu->addAction(checkDocumentCmd);
    cppToolsMenu->addAction(checkProjectCmd);
}
void cpplintCheckPlugin::extensionsInitialized() {
}
bool cpplintCheckPlugin::delayedInitialize() {
    return false;
}

ExtensionSystem::IPlugin::ShutdownFlag cpplintCheckPlugin::aboutToShutdown() {
    return SynchronousShutdown;
}

QObject *cpplintCheckPlugin::remoteCommand(const QStringList & /* options */, const QStringList & /* arguments */) {
    return 0;
}

void cpplintCheckPlugin::checkActiveProject () {

}

//! Check currently open document.
void cpplintCheckPlugin::checkCurrentDocument () {

}

//! Check current ProjectExplorer's node.
void cpplintCheckPlugin::checkCurrentNode () {

}

}
