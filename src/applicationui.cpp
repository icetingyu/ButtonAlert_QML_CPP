/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <QObject>
#include <bb/cascades/AbstractPane>
#include <bb/system/SystemDialog>
#include <bb/system/SystemListDialog>
#include <bb/system/SystemProgressDialog>
#include <bb/system/SystemPrompt>
#include <bb/system/SystemCredentialsPrompt>
#include <bb/system/SystemToast>
#include <bb/system/SystemProgressToast>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiInputField>
#include <bb/system/SystemUiError>
#include <bb/system/SystemUiInputMode>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiPosition>
#include <bb/system/SystemUiProgressState>
#include <bb/system/SystemUiResult>
#include <bb/system/SystemUiReturnKeyAction>

using namespace bb::system;
using namespace bb::cascades;

ApplicationUI::ApplicationUI() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    qml->setContextProperty("_app", this);
    bool connectResult;
    Q_UNUSED(connectResult);
    QObject *newButton = root->findChild<QObject*>("button");
    connectResult = connect(newButton, SIGNAL(clicked()), this, SLOT(showDialog()));
    Q_ASSERT(connectResult);
    // Set created root object as the application scene
    Application::instance()->setScene(root);



}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("ButtonAlert_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

// A public function to display a SystemDialog in your UI
void ApplicationUI::showDialog()
{

    // Set up the SystemDialog with a title and some body text.
    // Label the two standard buttons with specific text.
    // Add a custom button as well.

    SystemDialog *dialog = new SystemDialog("Save as",
                                            "Discard changes",
                                            "Cancel");

    dialog->setTitle("Save changes");

    dialog->setBody("Save your changes and close the document?");

    dialog->setEmoticonsEnabled(true);

    // Connect the finished() signal to the onDialogFinished() slot.
    // The slot will check the SystemUiResult to see which
    // button was tapped.

    bool success = connect(dialog,
         SIGNAL(finished(bb::system::SystemUiResult::Type)),
         this,
         SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));

    if (success) {
        // Signal was successfully connected.
        // Now show the dialog box in your UI.

        dialog->show();
    } else {
        // Failed to connect to signal.
        // This is not normal in most cases and can be a critical
        // situation for your app! Make sure you know exactly why
        // this has happened. Add some code to recover from the
        // lost connection below this line.
        dialog->deleteLater();
    }
}

void ApplicationUI::onDialogFinished(bb::system::SystemUiResult::Type)
{
    qDebug() << "Dialog Finished";
}
