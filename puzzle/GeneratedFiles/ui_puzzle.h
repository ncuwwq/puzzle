/********************************************************************************
** Form generated from reading UI file 'puzzle.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUZZLE_H
#define UI_PUZZLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_puzzleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *puzzleClass)
    {
        if (puzzleClass->objectName().isEmpty())
            puzzleClass->setObjectName(QString::fromUtf8("puzzleClass"));
        puzzleClass->resize(600, 400);
        menuBar = new QMenuBar(puzzleClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        puzzleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(puzzleClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        puzzleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(puzzleClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        puzzleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(puzzleClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        puzzleClass->setStatusBar(statusBar);

        retranslateUi(puzzleClass);

        QMetaObject::connectSlotsByName(puzzleClass);
    } // setupUi

    void retranslateUi(QMainWindow *puzzleClass)
    {
        puzzleClass->setWindowTitle(QApplication::translate("puzzleClass", "puzzle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class puzzleClass: public Ui_puzzleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUZZLE_H
