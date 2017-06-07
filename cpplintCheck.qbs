import qbs 1.0

import QtcPlugin

QtcPlugin {
    name: "cpplintCheck"

    Depends { name: "Core" }

    files: [ "cpplintplugin.cpp" ]
}
