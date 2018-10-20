/********************************************************************************
** Form generated from reading UI file 'treeview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEVIEW_H
#define UI_TREEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_treeview_dialog
{
public:
    QFrame *frame;
    QPushButton *cmd_cancel;
    QPushButton *cmd_save;
    QTreeView *treeView;
    QLabel *label;
    QPushButton *pushButton_treeview;

    void setupUi(QDialog *treeview_dialog)
    {
        if (treeview_dialog->objectName().isEmpty())
            treeview_dialog->setObjectName(QStringLiteral("treeview_dialog"));
        treeview_dialog->resize(473, 415);
        frame = new QFrame(treeview_dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 451, 391));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        cmd_cancel = new QPushButton(frame);
        cmd_cancel->setObjectName(QStringLiteral("cmd_cancel"));
        cmd_cancel->setGeometry(QRect(10, 350, 423, 27));
        cmd_cancel->setAutoDefault(false);
        cmd_cancel->setFlat(false);
        cmd_save = new QPushButton(frame);
        cmd_save->setObjectName(QStringLiteral("cmd_save"));
        cmd_save->setGeometry(QRect(10, 320, 423, 27));
        cmd_save->setAutoDefault(false);
        treeView = new QTreeView(frame);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 40, 421, 271));
        treeView->header()->setDefaultSectionSize(400);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 411, 17));
        pushButton_treeview = new QPushButton(frame);
        pushButton_treeview->setObjectName(QStringLiteral("pushButton_treeview"));
        pushButton_treeview->setGeometry(QRect(50, 320, 31, 16));
        cmd_cancel->raise();
        treeView->raise();
        label->raise();
        pushButton_treeview->raise();
        cmd_save->raise();
        QWidget::setTabOrder(cmd_cancel, cmd_save);

        retranslateUi(treeview_dialog);
        QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), pushButton_treeview, SLOT(click()));

        cmd_save->setDefault(true);


        QMetaObject::connectSlotsByName(treeview_dialog);
    } // setupUi

    void retranslateUi(QDialog *treeview_dialog)
    {
        treeview_dialog->setWindowTitle(QApplication::translate("treeview_dialog", "Select restore file", Q_NULLPTR));
        cmd_cancel->setText(QApplication::translate("treeview_dialog", "Cancel", Q_NULLPTR));
        cmd_save->setText(QApplication::translate("treeview_dialog", "Next", Q_NULLPTR));
        label->setText(QApplication::translate("treeview_dialog", "Existing restore files:", Q_NULLPTR));
        pushButton_treeview->setText(QApplication::translate("treeview_dialog", "a", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class treeview_dialog: public Ui_treeview_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEVIEW_H
