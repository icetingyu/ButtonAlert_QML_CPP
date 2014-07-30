/*
 * Copyright (c) 2014, Simon HSU @ Taiwan BlackBerry Developer Group
 * 
 * 2014-07-30 Version 1.0
 * This is a sample about create a button, click and show a dialog.
 * I did this because some developers asked me about how to do this all in C++
 * 
 * In this sample you can learn three kinds of creating button and showing dialog
 * The Button is already created in QML
 * 
 * 1. Pure C++:
 *  - Find the button defined in QML and connect onClick Signal, show dialog in C++
 * 
 * 2. Hybrid:
 *  - Put the onClick Signal in QML, show dialog in C++
 *  
 * 3. Pure QML:
 *  - Do all the things in QML
 * 
 */

import bb.cascades 1.0
import bb.system 1.0

Page {
    Container {
        Label {
            // Localized text with the dynamic translation and locale updates support
            text: qsTr("ButtonAlert") + Retranslate.onLocaleOrLanguageChanged
            textStyle.base: SystemDefaults.TextStyles.BigText
            horizontalAlignment: HorizontalAlignment.Center
        }

        Container {
            topPadding: 20
            leftPadding: 20
            rightPadding: 20
            bottomPadding: 20
            Label {
                text: qsTr("Click signal in C++ and Show Dialog in C++")
            }
            Button {
                id: btn
                objectName: "button"
                text: qsTr("Pure C++")
            }
        }

        Container {
            topPadding: 20
            leftPadding: 20
            rightPadding: 20
            bottomPadding: 20
            Label {
                text: qsTr("Click Button in QML and Show Dialog in C++")
            }
            Button {
                id: btn2
                text: qsTr("BtnQML & Dialog C++")

                onClicked: {
                    _app.showDialog()
                }
            }
        }
        
        Container {
            topPadding: 20
            leftPadding: 20
            rightPadding: 20
            bottomPadding: 20
            Label {
                text: qsTr("Click Button in QML and Show Dialog in QML")
            }
            Button {
                id: btn3
                text: qsTr("Pure QML")
                
                onClicked: {
                    dialog.show();
                }
            }
        }
    }
    attachedObjects: [
        SystemDialog {
            id: dialog
            title: qsTr("Dialog Title")
            body: qsTr("Dialog Body")

        }
    ]
}
