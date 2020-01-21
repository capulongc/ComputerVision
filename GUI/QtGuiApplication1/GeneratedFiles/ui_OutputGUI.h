/********************************************************************************
** Form generated from reading UI file 'OutputGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTPUTGUI_H
#define UI_OUTPUTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutputGUI
{
public:
    QLabel *tirePhoto;
    QLabel *detectPhoto;
    QLabel *decisionText;

    void setupUi(QWidget *OutputGUI)
    {
        if (OutputGUI->objectName().isEmpty())
            OutputGUI->setObjectName(QStringLiteral("OutputGUI"));
        OutputGUI->resize(1700, 1000);
        tirePhoto = new QLabel(OutputGUI);
        tirePhoto->setObjectName(QStringLiteral("tirePhoto"));
        tirePhoto->setGeometry(QRect(25, 20, 800, 800));
        detectPhoto = new QLabel(OutputGUI);
        detectPhoto->setObjectName(QStringLiteral("detectPhoto"));
        detectPhoto->setGeometry(QRect(850, 20, 800, 800));
        decisionText = new QLabel(OutputGUI);
        decisionText->setObjectName(QStringLiteral("decisionText"));
        decisionText->setGeometry(QRect(280, 850, 1151, 101));
        QFont font;
        font.setPointSize(18);
        decisionText->setFont(font);
        decisionText->setFocusPolicy(Qt::NoFocus);
        decisionText->setAlignment(Qt::AlignCenter);

        retranslateUi(OutputGUI);

        QMetaObject::connectSlotsByName(OutputGUI);
    } // setupUi

    void retranslateUi(QWidget *OutputGUI)
    {
        OutputGUI->setWindowTitle(QApplication::translate("OutputGUI", "OutputGUI", Q_NULLPTR));
        tirePhoto->setText(QString());
        detectPhoto->setText(QString());
        decisionText->setText(QApplication::translate("OutputGUI", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OutputGUI: public Ui_OutputGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTPUTGUI_H
