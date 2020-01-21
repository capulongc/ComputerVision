/********************************************************************************
** Form generated from reading UI file 'GUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QWidget *centralWidget;
    QPushButton *exitButton;
    QPushButton *startButton;
    QPushButton *folderButton;
    QLabel *projectTitle;
    QLabel *locationLabel;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->resize(1250, 850);
        centralWidget = new QWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(850, 600, 370, 150));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setEnabled(false);
        startButton->setGeometry(QRect(30, 600, 370, 150));
        folderButton = new QPushButton(centralWidget);
        folderButton->setObjectName(QStringLiteral("folderButton"));
        folderButton->setGeometry(QRect(440, 600, 370, 150));
        projectTitle = new QLabel(centralWidget);
        projectTitle->setObjectName(QStringLiteral("projectTitle"));
        projectTitle->setGeometry(QRect(70, 30, 1121, 241));
        QFont font;
        font.setFamily(QStringLiteral("Yu Gothic"));
        font.setPointSize(30);
        font.setBold(true);
        font.setWeight(75);
        projectTitle->setFont(font);
        projectTitle->setAlignment(Qt::AlignCenter);
        locationLabel = new QLabel(centralWidget);
        locationLabel->setObjectName(QStringLiteral("locationLabel"));
        locationLabel->setGeometry(QRect(40, 330, 1151, 61));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        locationLabel->setFont(font1);
        locationLabel->setAlignment(Qt::AlignCenter);
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(250, 480, 701, 71));
        QtGuiApplication1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1250, 47));
        QtGuiApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication1Class->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication1Class);

        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "QtGuiApplication1", Q_NULLPTR));
        exitButton->setText(QApplication::translate("QtGuiApplication1Class", "Exit", Q_NULLPTR));
        startButton->setText(QApplication::translate("QtGuiApplication1Class", "Start", Q_NULLPTR));
        folderButton->setText(QApplication::translate("QtGuiApplication1Class", "Select Folder", Q_NULLPTR));
        projectTitle->setText(QApplication::translate("QtGuiApplication1Class", "<html><head/><body><p>Image Scanner</p><p><br/></p></body></html>", Q_NULLPTR));
        locationLabel->setText(QApplication::translate("QtGuiApplication1Class", "Photo Folder Loaction : <None>", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("QtGuiApplication1Class", "Face Recognition", Q_NULLPTR)
         << QApplication::translate("QtGuiApplication1Class", "Tire Detection", Q_NULLPTR)
         << QApplication::translate("QtGuiApplication1Class", "Shape Detection", Q_NULLPTR)
         << QApplication::translate("QtGuiApplication1Class", "Color Detection", Q_NULLPTR)
         << QApplication::translate("QtGuiApplication1Class", "License Plate Reader", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
