/********************************************************************************
** Form generated from reading UI file 'clone_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLONE_DIALOG_H
#define UI_CLONE_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clone_dialog
{
public:
    QTreeView *treeView_clone;
    QLabel *lbl_hd;
    QListWidget *listWidget_exist;
    QListWidget *listWidget_clone;
    QLabel *label_3;
    QCommandLinkButton *commandLinkButton;
    QCommandLinkButton *commandLinkButton_2;
    QFrame *frame_2;
    QLabel *label_8;
    QLineEdit *SekundeElapsed;
    QLabel *label_7;
    QLineEdit *MinuteElapsed;
    QLabel *label_5;
    QLabel *label_10;
    QLineEdit *SekundeRemaining;
    QLabel *label_9;
    QLineEdit *MinuteRemaining;
    QLabel *label_6;
    QProgressBar *progressBar;
    QLineEdit *savedBytes;
    QLabel *lbl_save;
    QLabel *lbl_hd_size;
    QLabel *label_11;
    QLineEdit *HourElapsed;
    QLabel *label_12;
    QLineEdit *HourRemaining;
    QLabel *label;
    QLineEdit *bytes_sec;
    QLabel *lbl_B_sec;
    QPushButton *pushButton_folder;
    QLabel *label_folder;
    QFrame *frame;
    QRadioButton *rdbt_image_restore;
    QRadioButton *rdbt_clone;
    QGroupBox *groupBox;
    QRadioButton *rdbt_image_save;
    QRadioButton *rdbt_partition_save;
    QRadioButton *rdbt_partition_restore;
    QCheckBox *chk_zip;
    QPushButton *pushButton_partition;
    QPushButton *bt_save;
    QPushButton *bt_end;
    QCommandLinkButton *commandLinkButton_3;
    QCommandLinkButton *commandLinkButton_4;
    QCommandLinkButton *commandLinkButton_5;
    QListWidget *listWidget;

    void setupUi(QWidget *clone_dialog)
    {
        if (clone_dialog->objectName().isEmpty())
            clone_dialog->setObjectName(QStringLiteral("clone_dialog"));
        clone_dialog->resize(752, 607);
        treeView_clone = new QTreeView(clone_dialog);
        treeView_clone->setObjectName(QStringLiteral("treeView_clone"));
        treeView_clone->setGeometry(QRect(410, 170, 321, 231));
        treeView_clone->header()->setDefaultSectionSize(400);
        lbl_hd = new QLabel(clone_dialog);
        lbl_hd->setObjectName(QStringLiteral("lbl_hd"));
        lbl_hd->setGeometry(QRect(20, 150, 351, 18));
        listWidget_exist = new QListWidget(clone_dialog);
        listWidget_exist->setObjectName(QStringLiteral("listWidget_exist"));
        listWidget_exist->setGeometry(QRect(20, 170, 168, 231));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setBold(true);
        font.setWeight(75);
        listWidget_exist->setFont(font);
        listWidget_clone = new QListWidget(clone_dialog);
        listWidget_clone->setObjectName(QStringLiteral("listWidget_clone"));
        listWidget_clone->setGeometry(QRect(220, 170, 168, 231));
        listWidget_clone->setFont(font);
        label_3 = new QLabel(clone_dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 150, 171, 18));
        commandLinkButton = new QCommandLinkButton(clone_dialog);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(190, 210, 31, 41));
        commandLinkButton_2 = new QCommandLinkButton(clone_dialog);
        commandLinkButton_2->setObjectName(QStringLiteral("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(190, 170, 31, 41));
        frame_2 = new QFrame(clone_dialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(20, 420, 471, 161));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(397, 5, 71, 34));
        SekundeElapsed = new QLineEdit(frame_2);
        SekundeElapsed->setObjectName(QStringLiteral("SekundeElapsed"));
        SekundeElapsed->setGeometry(QRect(360, 10, 30, 27));
        SekundeElapsed->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(295, 10, 61, 30));
        MinuteElapsed = new QLineEdit(frame_2);
        MinuteElapsed->setObjectName(QStringLiteral("MinuteElapsed"));
        MinuteElapsed->setGeometry(QRect(260, 10, 30, 27));
        MinuteElapsed->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 135, 34));
        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(397, 35, 71, 34));
        SekundeRemaining = new QLineEdit(frame_2);
        SekundeRemaining->setObjectName(QStringLiteral("SekundeRemaining"));
        SekundeRemaining->setGeometry(QRect(360, 40, 30, 27));
        SekundeRemaining->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(295, 37, 61, 30));
        MinuteRemaining = new QLineEdit(frame_2);
        MinuteRemaining->setObjectName(QStringLiteral("MinuteRemaining"));
        MinuteRemaining->setGeometry(QRect(260, 40, 30, 27));
        MinuteRemaining->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 40, 135, 31));
        label_6->setWordWrap(true);
        progressBar = new QProgressBar(frame_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 125, 441, 25));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        savedBytes = new QLineEdit(frame_2);
        savedBytes->setObjectName(QStringLiteral("savedBytes"));
        savedBytes->setGeometry(QRect(377, 85, 51, 27));
        savedBytes->setAlignment(Qt::AlignCenter);
        lbl_save = new QLabel(frame_2);
        lbl_save->setObjectName(QStringLiteral("lbl_save"));
        lbl_save->setGeometry(QRect(265, 78, 105, 41));
        lbl_save->setWordWrap(true);
        lbl_hd_size = new QLabel(frame_2);
        lbl_hd_size->setObjectName(QStringLiteral("lbl_hd_size"));
        lbl_hd_size->setGeometry(QRect(430, 90, 31, 17));
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(183, 15, 75, 20));
        HourElapsed = new QLineEdit(frame_2);
        HourElapsed->setObjectName(QStringLiteral("HourElapsed"));
        HourElapsed->setGeometry(QRect(150, 10, 30, 27));
        HourElapsed->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(183, 45, 75, 20));
        HourRemaining = new QLineEdit(frame_2);
        HourRemaining->setObjectName(QStringLiteral("HourRemaining"));
        HourRemaining->setGeometry(QRect(150, 40, 30, 27));
        HourRemaining->setAlignment(Qt::AlignCenter);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 80, 131, 41));
        label->setWordWrap(true);
        bytes_sec = new QLineEdit(frame_2);
        bytes_sec->setObjectName(QStringLiteral("bytes_sec"));
        bytes_sec->setGeometry(QRect(150, 85, 51, 27));
        lbl_B_sec = new QLabel(frame_2);
        lbl_B_sec->setObjectName(QStringLiteral("lbl_B_sec"));
        lbl_B_sec->setGeometry(QRect(205, 90, 51, 17));
        pushButton_folder = new QPushButton(clone_dialog);
        pushButton_folder->setObjectName(QStringLiteral("pushButton_folder"));
        pushButton_folder->setGeometry(QRect(550, 540, 16, 21));
        label_folder = new QLabel(clone_dialog);
        label_folder->setObjectName(QStringLiteral("label_folder"));
        label_folder->setGeometry(QRect(410, 150, 171, 18));
        label_folder->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        frame = new QFrame(clone_dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 10, 711, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        rdbt_image_restore = new QRadioButton(frame);
        rdbt_image_restore->setObjectName(QStringLiteral("rdbt_image_restore"));
        rdbt_image_restore->setGeometry(QRect(390, 30, 301, 25));
        rdbt_clone = new QRadioButton(frame);
        rdbt_clone->setObjectName(QStringLiteral("rdbt_clone"));
        rdbt_clone->setGeometry(QRect(390, 90, 161, 25));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 221, 31));
        groupBox->setSizeIncrement(QSize(10, 10));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        rdbt_image_save = new QRadioButton(frame);
        rdbt_image_save->setObjectName(QStringLiteral("rdbt_image_save"));
        rdbt_image_save->setGeometry(QRect(20, 30, 251, 25));
        rdbt_partition_save = new QRadioButton(frame);
        rdbt_partition_save->setObjectName(QStringLiteral("rdbt_partition_save"));
        rdbt_partition_save->setGeometry(QRect(20, 60, 301, 25));
        rdbt_partition_restore = new QRadioButton(frame);
        rdbt_partition_restore->setObjectName(QStringLiteral("rdbt_partition_restore"));
        rdbt_partition_restore->setGeometry(QRect(390, 60, 301, 25));
        chk_zip = new QCheckBox(frame);
        chk_zip->setObjectName(QStringLiteral("chk_zip"));
        chk_zip->setGeometry(QRect(20, 90, 391, 25));
        pushButton_partition = new QPushButton(clone_dialog);
        pushButton_partition->setObjectName(QStringLiteral("pushButton_partition"));
        pushButton_partition->setGeometry(QRect(520, 430, 31, 27));
        bt_save = new QPushButton(clone_dialog);
        bt_save->setObjectName(QStringLiteral("bt_save"));
        bt_save->setGeometry(QRect(500, 420, 231, 71));
        bt_end = new QPushButton(clone_dialog);
        bt_end->setObjectName(QStringLiteral("bt_end"));
        bt_end->setGeometry(QRect(500, 510, 231, 71));
        commandLinkButton_3 = new QCommandLinkButton(clone_dialog);
        commandLinkButton_3->setObjectName(QStringLiteral("commandLinkButton_3"));
        commandLinkButton_3->setGeometry(QRect(190, 250, 31, 41));
        commandLinkButton_4 = new QCommandLinkButton(clone_dialog);
        commandLinkButton_4->setObjectName(QStringLiteral("commandLinkButton_4"));
        commandLinkButton_4->setGeometry(QRect(190, 290, 31, 41));
        commandLinkButton_5 = new QCommandLinkButton(clone_dialog);
        commandLinkButton_5->setObjectName(QStringLiteral("commandLinkButton_5"));
        commandLinkButton_5->setGeometry(QRect(190, 330, 31, 41));
        listWidget = new QListWidget(clone_dialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 170, 371, 231));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier 10 Pitch"));
        font1.setBold(false);
        font1.setWeight(50);
        listWidget->setFont(font1);
        pushButton_folder->raise();
        treeView_clone->raise();
        lbl_hd->raise();
        listWidget_exist->raise();
        listWidget_clone->raise();
        label_3->raise();
        commandLinkButton->raise();
        commandLinkButton_2->raise();
        frame_2->raise();
        label_folder->raise();
        frame->raise();
        pushButton_partition->raise();
        bt_save->raise();
        bt_end->raise();
        commandLinkButton_3->raise();
        commandLinkButton_4->raise();
        commandLinkButton_5->raise();
        listWidget->raise();

        retranslateUi(clone_dialog);
        QObject::connect(treeView_clone, SIGNAL(clicked(QModelIndex)), pushButton_folder, SLOT(click()));
        QObject::connect(listWidget, SIGNAL(clicked(QModelIndex)), pushButton_partition, SLOT(click()));

        QMetaObject::connectSlotsByName(clone_dialog);
    } // setupUi

    void retranslateUi(QWidget *clone_dialog)
    {
        clone_dialog->setWindowTitle(QApplication::translate("clone_dialog", "Clone hard drive", Q_NULLPTR));
        lbl_hd->setText(QApplication::translate("clone_dialog", "Exist harddrive:", Q_NULLPTR));
        label_3->setText(QApplication::translate("clone_dialog", "New harddrive:", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("clone_dialog", "CommandLinkButton", Q_NULLPTR));
        commandLinkButton_2->setText(QApplication::translate("clone_dialog", "CommandLinkButton", Q_NULLPTR));
        label_8->setText(QApplication::translate("clone_dialog", "seconds", Q_NULLPTR));
        label_7->setText(QApplication::translate("clone_dialog", "minutes", Q_NULLPTR));
        label_5->setText(QApplication::translate("clone_dialog", "elapsed time:", Q_NULLPTR));
        label_10->setText(QApplication::translate("clone_dialog", "seconds", Q_NULLPTR));
        label_9->setText(QApplication::translate("clone_dialog", "minutes", Q_NULLPTR));
        label_6->setText(QApplication::translate("clone_dialog", "remaining time:", Q_NULLPTR));
        lbl_save->setText(QApplication::translate("clone_dialog", "already saved:", Q_NULLPTR));
        lbl_hd_size->setText(QApplication::translate("clone_dialog", "MB", Q_NULLPTR));
        label_11->setText(QApplication::translate("clone_dialog", "hours", Q_NULLPTR));
        label_12->setText(QApplication::translate("clone_dialog", "hours", Q_NULLPTR));
        label->setText(QApplication::translate("clone_dialog", "Transmission speed:", Q_NULLPTR));
        lbl_B_sec->setText(QApplication::translate("clone_dialog", "MB/sec", Q_NULLPTR));
        pushButton_folder->setText(QApplication::translate("clone_dialog", "f", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_folder->setToolTip(QApplication::translate("clone_dialog", "Directory in which the image is written", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_folder->setText(QApplication::translate("clone_dialog", "Backup directory:", Q_NULLPTR));
        rdbt_image_restore->setText(QApplication::translate("clone_dialog", "&Image of a hard disk write back", Q_NULLPTR));
        rdbt_clone->setText(QApplication::translate("clone_dialog", "&Clone hard disk", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("clone_dialog", "Proposed action:", Q_NULLPTR));
        rdbt_image_save->setText(QApplication::translate("clone_dialog", "Image of a &hard disk to create", Q_NULLPTR));
        rdbt_partition_save->setText(QApplication::translate("clone_dialog", "Image of a partition &to create", Q_NULLPTR));
        rdbt_partition_restore->setText(QApplication::translate("clone_dialog", "Image of a &partition write back", Q_NULLPTR));
        chk_zip->setText(QApplication::translate("clone_dialog", "Use gzip", Q_NULLPTR));
        pushButton_partition->setText(QApplication::translate("clone_dialog", "p", Q_NULLPTR));
        bt_save->setText(QApplication::translate("clone_dialog", "Save/Restore", Q_NULLPTR));
        bt_end->setText(QApplication::translate("clone_dialog", "Exit", Q_NULLPTR));
        commandLinkButton_3->setText(QApplication::translate("clone_dialog", "CommandLinkButton", Q_NULLPTR));
        commandLinkButton_4->setText(QApplication::translate("clone_dialog", "CommandLinkButton", Q_NULLPTR));
        commandLinkButton_5->setText(QApplication::translate("clone_dialog", "CommandLinkButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class clone_dialog: public Ui_clone_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLONE_DIALOG_H
