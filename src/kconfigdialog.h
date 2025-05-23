/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2003 Benjamin C Meyer <ben+kdelibs at meyerhome dot net>
    SPDX-FileCopyrightText: 2003 Waldo Bastian <bastian@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KCONFIGDIALOG_H
#define KCONFIGDIALOG_H

#include <KPageDialog>
#include <memory>

#include "kconfigwidgets_export.h"

class KConfig;
class KCoreConfigSkeleton;
class KConfigDialogManager;

/*!
 * \class KConfigDialog
 * \inmodule KConfigWidgets
 *
 * \brief Standard KDE configuration dialog class.
 *
 * The KConfigDialog class provides an easy and uniform means of displaying
 * a settings dialog using KPageDialog, KConfigDialogManager and a
 * KConfigSkeleton derived settings class.
 *
 * KConfigDialog handles the enabling and disabling of buttons, creation
 * of the dialog, and deletion of the widgets.  Because of
 * KConfigDialogManager, this class also manages: restoring
 * the settings, resetting them to the default values, and saving them. This
 * requires that the names of the widgets corresponding to configuration entries
 * have to have the same name plus an additional "kcfg_" prefix. For example the
 * widget named "kcfg_MyOption" would be associated with the configuration entry
 * "MyOption".
 *
 * Here is an example usage of KConfigDialog:
 *
 * \code
 * void KCoolApp::showSettings(){
 *     if (KConfigDialog::showDialog(QStringLiteral("settings"))) {
 *       return;
 *     }
 *     KConfigDialog *dialog = new KConfigDialog(this, QStringLiteral("settings"), MySettings::self());
 *     dialog->setFaceType(KPageDialog::List);
 *     dialog->addPage(new General(0, "General"), i18n("General"));
 *     dialog->addPage(new Appearance(0, "Style"), i18n("Appearance"));
 *     connect(dialog, &KConfigDialog::settingsChanged, mainWidget, &Bar::loadSettings);
 *     connect(dialog, &KConfigDialog::settingsChanged, this, &Foo::loadSettings);
 *     dialog->show();
 * }
 * \endcode
 *
 * Other than the above code, each class that has settings in the dialog should
 * have a loadSettings() type slot to read settings and perform any
 * necessary changes.
 *
 * For dialog appearance options (like buttons, default button, ...) please see
 * KPageDialog.
 *
 * \sa KConfigSkeleton
 */
class KCONFIGWIDGETS_EXPORT KConfigDialog : public KPageDialog
{
    Q_OBJECT

Q_SIGNALS:
    /*!
     * A widget in the dialog was modified.
     */
    void widgetModified();

    /*!
     * One or more of the settings have been permanently changed such as if
     * the user clicked on the Apply or Ok button.
     *
     * \a dialogName the name of the dialog.
     */
    void settingsChanged(const QString &dialogName);

public:
    /*!
     * \a parent The parent of this object. Even though the class
     * deletes itself the parent should be set so the dialog can be centered
     * with the application on the screen.
     *
     * \a name The name of this object. The name is used in determining if
     * there can be more than one dialog at a time.  Use names such as:
     * "Font Settings" or "Color Settings" and not just "Settings" in
     * applications where there is more than one dialog.
     *
     * \a config Config object containing settings.
     */
    KConfigDialog(QWidget *parent, const QString &name, KCoreConfigSkeleton *config);

    /*!
     * Deconstructor, removes name from the list of open dialogs.
     * \sa exists()
     */
    ~KConfigDialog() override;

    /*!
     * Adds page to the dialog and to KConfigDialogManager. When an
     * application is done adding pages show() should be called to
     * display the dialog.
     *
     * \a page Pointer to the page that is to be added to the dialog.
     * This object is reparented.
     *
     * \a itemName Name of the page.
     *
     * \a pixmapName Name of the icon that should be used, if needed, when
     *        displaying the page. The string may either be the name of a themed
     *        icon (e.g. "document-save"), which the internal icon loader will be
     *        used to retrieve, or an absolute path to the pixmap on disk.
     *
     * \a header Header text use in the list modes. Ignored in Tabbed
     *        mode. If empty, the itemName text is used when needed.
     *
     * \a manage Whether KConfigDialogManager should manage the page or not.
     *
     * Returns the KPageWidgetItem associated with the page.
     */
    KPageWidgetItem *
    addPage(QWidget *page, const QString &itemName, const QString &pixmapName = QString(), const QString &header = QString(), bool manage = true);

    /*!
     * Adds page to the dialog that is managed by a custom KConfigDialogManager.
     * This is useful for dialogs that contain settings spread over more than
     * one configuration file and thus have/need more than one KConfigSkeleton.
     * When an application is done adding pages show() should be called to
     * display the dialog.
     *
     * \a page Pointer to the page that is to be added to the dialog.
     * This object is reparented.
     *
     * \a config Config object containing corresponding settings.
     *
     * \a itemName Name of the page.
     *
     * \a pixmapName Name of the icon that should be used, if needed, when
     *        displaying the page. The string may either be the name of a themed
     *        icon (e.g. "document-save"), which the internal icon loader will be
     *        used to retrieve, or an absolute path to the pixmap on disk.
     *
     * \a header Header text use in the list modes. Ignored in Tabbed
     *        mode. If empty, the itemName text is used when needed.
     *
     * Returns the KPageWidgetItem associated with the page.
     */
    KPageWidgetItem *
    addPage(QWidget *page, KCoreConfigSkeleton *config, const QString &itemName, const QString &pixmapName = QString(), const QString &header = QString());

    /*!
     * See if a dialog with the name 'name' already exists.
     *
     * \sa showDialog()
     *
     * \a name Dialog name to look for.
     *
     * Returns pointer to widget or \c nullptr if it does not exist.
     */
    static KConfigDialog *exists(const QString &name);

    /*!
     * Attempts to show the dialog with the name 'name'.
     *
     * \sa exists()
     *
     * \a name The name of the dialog to show.
     *
     * Returns \c true if the dialog 'name' exists and was shown.
     */
    static bool showDialog(const QString &name);

protected Q_SLOTS:
    /*!
     * Update the settings from the dialog.
     *
     * Virtual function for custom additions.
     *
     * Example use: User clicks Ok or Apply button in a configure dialog.
     */
    virtual void updateSettings();

    /*!
     * Update the dialog based on the settings.
     *
     * Virtual function for custom additions.
     *
     * Example use: Initialisation of dialog.
     *
     * Example use: User clicks Reset button in a configure dialog.
     */
    virtual void updateWidgets();

    /*!
     * Update the dialog based on the default settings.
     *
     * Virtual function for custom additions.
     *
     * Example use: User clicks Defaults button in a configure dialog.
     */
    virtual void updateWidgetsDefault();

    /*!
     * Updates the Apply and Default buttons.
     *
     * Connect to this slot if you implement your own hasChanged()
     * or isDefault() methods for widgets not managed by KConfig.
     *
     * \since 4.3
     */
    void updateButtons();

    /*!
     * Some setting was changed. Emit the signal with the dialogs name.
     *
     * Connect to this slot if there are widgets not managed by KConfig.
     *
     * \since 4.3
     */
    void settingsChangedSlot();

    /*!
     * Sets the help path and topic.
     *
     * The HTML file will be found using the X-DocPath entry in the application's desktop file.
     * It can be either a relative path, or a website URL.
     *
     * \a anchor This has to be a defined anchor in your
     *                    docbook sources or website. If empty the main index
     *                    is loaded.
     *
     * \a appname This allows you to specify the .desktop file to get the help path from.
     *                    If empty the QCoreApplication::applicationName() is used.
     */
    void setHelp(const QString &anchor, const QString &appname = QString());

    /*!
     * Displays help for this config dialog.
     * \since 5.0
     */
    virtual void showHelp();

protected:
    /*!
     * Returns whether the current state of the dialog is
     * different from the current configuration.
     *
     * Virtual function for custom additions.
     */
    virtual bool hasChanged();

    /*!
     * Returns whether the current state of the dialog is
     * the same as the default configuration.
     */
    virtual bool isDefault();

    void showEvent(QShowEvent *e) override;

private Q_SLOTS:
    KCONFIGWIDGETS_NO_EXPORT void onPageRemoved(KPageWidgetItem *item);

private:
    friend class KConfigDialogPrivate;
    std::unique_ptr<class KConfigDialogPrivate> const d;

    Q_DISABLE_COPY(KConfigDialog)
};

#endif // KCONFIGDIALOG_H
