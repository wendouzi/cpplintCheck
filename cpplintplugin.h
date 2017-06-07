#ifndef CPPLINTPLUGIN_H
#define CPPLINTPLUGIN_H

#include <coreplugin/editormanager/ieditorfactory.h>

#include <extensionsystem/iplugin.h>
#include <QMap>
#include <QStringList>
#include <QtPlugin>
#include <QAction>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QMenu;
class QToolButton;
class QUrl;
QT_END_NAMESPACE

namespace Core {
class IMode;
class MiniSplitter;
class SideBar;
class SideBarItem;
}   // Core

namespace Utils { class StyledBar; }


namespace cpplintCheck {

class CentralWidget;
class DocSettingsPage;
class ExternalHelpWindow;
class FilterSettingsPage;
class GeneralSettingsPage;
class HelpMode;
class HelpViewer;
class LocalHelpManager;
class OpenPagesManager;
class SearchWidget;

class cpplintCheckPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "cpplintCheck.json")
public:
    cpplintCheckPlugin();
    ~cpplintCheckPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorString);
    virtual void extensionsInitialized();
    virtual bool delayedInitialize();
    virtual ShutdownFlag aboutToShutdown();
    virtual QObject *remoteCommand(const QStringList & /* options */, const QStringList & /* arguments */);
private slots:
  // General checking.
  //! Check active project.
  void checkActiveProject ();
  //! Check currently open document.
  void checkCurrentDocument ();
  //! Check current ProjectExplorer's node.
  void checkCurrentNode ();

};

}
#endif // CPPLINTPLUGIN_H
