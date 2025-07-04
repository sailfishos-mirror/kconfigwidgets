add_library(KF6ConfigWidgets)
add_library(KF6::ConfigWidgets ALIAS KF6ConfigWidgets)

set_target_properties(KF6ConfigWidgets PROPERTIES
    VERSION     ${KCONFIGWIDGETS_VERSION}
    SOVERSION   ${KCONFIGWIDGETS_SOVERSION}
    EXPORT_NAME ConfigWidgets
)

target_sources(KF6ConfigWidgets PRIVATE
  kcodecaction.cpp
  kcolorschememenu.cpp
  kcommandbar.cpp
  kcommandbarmodel_p.cpp
  kconfigdialog.cpp
  kconfigviewstatesaver.cpp
  kconfigdialogmanager.cpp
  khelpclient.cpp
  khamburgermenu.cpp
  khamburgermenuhelpers.cpp
  klanguagebutton.cpp
  klanguagename.cpp
  kopenaction.cpp
  krecentfilesaction.cpp
  kstandardaction.cpp
  kstylemanager.cpp

  kcodecaction.h
  kcommandbar.h
  kcommandbarmodel_p.h
  kconfigdialog.h
  kconfigviewstatesaver.h
  kconfigdialogmanager.h
  khelpclient.h
  khamburgermenu.h
  khamburgermenuhelpers_p.h
  klanguagebutton.h
  klanguagename.h
  kopenaction_p.h
  krecentfilesaction.h
  kstandardaction.h
  kstylemanager.h
)

ecm_qt_declare_logging_category(KF6ConfigWidgets
    HEADER kconfigwidgets_debug.h
    IDENTIFIER KCONFIG_WIDGETS_LOG
    CATEGORY_NAME kf.configwidgets
    OLD_CATEGORY_NAMES kf5.kconfigwidgets
    DESCRIPTION "KConfigWidgets"
    EXPORT KCONFIGWIDGETS
)

ecm_generate_export_header(KF6ConfigWidgets
    BASE_NAME KConfigWidgets
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    USE_VERSION_HEADER
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_include_directories(KF6ConfigWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KConfigWidgets>")

target_link_libraries(KF6ConfigWidgets
  PUBLIC
    KF6::WidgetsAddons # For K*Action, KPage*, KViewStateSerializer, KAcceleratorManager, K*GuiItem
    KF6::ConfigGui # KStandardAction uses KStandardShortcut
    KF6::ColorScheme
  PRIVATE
    Qt6::GuiPrivate # KStyleManager::initStyle
    KF6::CoreAddons # KAboutData, KFuzzymatcher
    KF6::GuiAddons # KColorScheme uses KColorUtils
    KF6::I18n # For action and widget texts
    KF6::Codecs # KCodecActions uses KCharsets, KEncodingProber
)

if (HAVE_DBUS)
    target_link_libraries(KF6ConfigWidgets
        PRIVATE
        Qt::DBus # KRecentFilesAction to send call to ActivityManager
    )
    target_compile_definitions(KF6ConfigWidgets PRIVATE -DHAVE_QTDBUS=1)
else()
    target_compile_definitions(KF6ConfigWidgets PRIVATE -DHAVE_QTDBUS=0)
endif()

ecm_generate_headers(KConfigWidgets_HEADERS
  HEADER_NAMES
  KCodecAction
  KColorSchemeMenu
  KCommandBar
  KConfigDialog
  KConfigViewStateSaver
  KConfigDialogManager
  KHamburgerMenu
  KHelpClient
  KLanguageButton
  KLanguageName
  KRecentFilesAction
  KViewStateMaintainer
  KStandardAction
  KStyleManager

  REQUIRED_HEADERS KConfigWidgets_HEADERS
)

install(TARGETS KF6ConfigWidgets EXPORT KF6ConfigWidgetsTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kconfigwidgets_export.h
  ${KConfigWidgets_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KConfigWidgets COMPONENT Devel
)

install( FILES entry.desktop  DESTINATION  ${KDE_INSTALL_LOCALEDIR}/en_US RENAME kf6_entry.desktop )

file(GLOB lang_dirs "language_files/*")
foreach(lang_dir ${lang_dirs})
   get_filename_component(lang ${lang_dir} NAME)
   install( FILES language_files/${lang}/kf6_entry.desktop DESTINATION ${KDE_INSTALL_LOCALEDIR}/${lang} )
endforeach()

ecm_qt_install_logging_categories(
    EXPORT KCONFIGWIDGETS
    FILE kconfigwidgets.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

ecm_generate_qdoc(KF6ConfigWidgets kconfigwidgets.qdocconf)
