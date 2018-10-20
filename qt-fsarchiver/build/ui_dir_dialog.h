/********************************************************************************
** Form generated from reading UI file 'dir_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIR_DIALOG_H
#define UI_DIR_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dir_dialog
{
public:
    QPushButton *bt_end;
    QPushButton *bt_save;
    QTreeView *treeView_dir;
    QLabel *label;
    QTreeView *treeView_path;
    QLabel *label_2;
    QFrame *frame;
    QLabel *label_4;
    QLineEdit *AnzahlsaveFile;
    QLabel *label_5;
    QLineEdit *AnzahlgesicherteFile;
    QProgressBar *progressBar;
    QLabel *label_6;
    QLineEdit *MinuteElapsed;
    QLabel *label_7;
    QLineEdit *SekundeElapsed;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *MinuteRemaining;
    QLineEdit *SekundeRemaining;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *cmb_kerne;
    QLabel *label_12;
    QFrame *frame_2;
    QLabel *label_3;
    QComboBox *cmb_zip;
    QCheckBox *chk_key;
    QLineEdit *lineKey;
    QCheckBox *chk_overwrite;
    QCheckBox *chk_path;
    QComboBox *cmb_zstd_dir;
    QCheckBox *chk_hidden;
    QPushButton *pushButton_zstd_dir;

    void setupUi(QWidget *dir_dialog)
    {
        if (dir_dialog->objectName().isEmpty())
            dir_dialog->setObjectName(QStringLiteral("dir_dialog"));
        dir_dialog->resize(714, 654);
        bt_end = new QPushButton(dir_dialog);
        bt_end->setObjectName(QStringLiteral("bt_end"));
        bt_end->setGeometry(QRect(375, 458, 321, 41));
        bt_save = new QPushButton(dir_dialog);
        bt_save->setObjectName(QStringLiteral("bt_save"));
        bt_save->setGeometry(QRect(375, 415, 321, 41));
        treeView_dir = new QTreeView(dir_dialog);
        treeView_dir->setObjectName(QStringLiteral("treeView_dir"));
        treeView_dir->setGeometry(QRect(20, 52, 331, 301));
        treeView_dir->header()->setDefaultSectionSize(400);
        label = new QLabel(dir_dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 25, 311, 18));
        treeView_path = new QTreeView(dir_dialog);
        treeView_path->setObjectName(QStringLiteral("treeView_path"));
        treeView_path->setGeometry(QRect(370, 52, 325, 301));
        treeView_path->header()->setDefaultSectionSize(400);
        label_2 = new QLabel(dir_dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(370, 25, 291, 18));
        frame = new QFrame(dir_dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 500, 711, 131));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(15, 6, 181, 41));
        AnzahlsaveFile = new QLineEdit(frame);
        AnzahlsaveFile->setObjectName(QStringLiteral("AnzahlsaveFile"));
        AnzahlsaveFile->setGeometry(QRect(200, 20, 71, 24));
        AnzahlsaveFile->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 50, 171, 41));
        AnzahlgesicherteFile = new QLineEdit(frame);
        AnzahlgesicherteFile->setObjectName(QStringLiteral("AnzahlgesicherteFile"));
        AnzahlgesicherteFile->setGeometry(QRect(200, 60, 71, 25));
        AnzahlgesicherteFile->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 100, 671, 23));
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 20, 131, 18));
        MinuteElapsed = new QLineEdit(frame);
        MinuteElapsed->setObjectName(QStringLiteral("MinuteElapsed"));
        MinuteElapsed->setGeometry(QRect(440, 20, 41, 26));
        MinuteElapsed->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(490, 25, 71, 18));
        SekundeElapsed = new QLineEdit(frame);
        SekundeElapsed->setObjectName(QStringLiteral("SekundeElapsed"));
        SekundeElapsed->setGeometry(QRect(560, 20, 41, 26));
        SekundeElapsed->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(610, 25, 71, 18));
        label_9 = new QLabel(frame);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(300, 52, 141, 41));
        MinuteRemaining = new QLineEdit(frame);
        MinuteRemaining->setObjectName(QStringLiteral("MinuteRemaining"));
        MinuteRemaining->setGeometry(QRect(440, 60, 41, 26));
        MinuteRemaining->setAlignment(Qt::AlignCenter);
        SekundeRemaining = new QLineEdit(frame);
        SekundeRemaining->setObjectName(QStringLiteral("SekundeRemaining"));
        SekundeRemaining->setGeometry(QRect(560, 60, 41, 26));
        SekundeRemaining->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(frame);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(490, 65, 71, 18));
        label_11 = new QLabel(frame);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(610, 65, 71, 18));
        cmb_kerne = new QComboBox(dir_dialog);
        cmb_kerne->setObjectName(QStringLiteral("cmb_kerne"));
        cmb_kerne->setGeometry(QRect(634, 355, 61, 27));
        label_12 = new QLabel(dir_dialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(370, 350, 251, 41));
        frame_2 = new QFrame(dir_dialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(20, 360, 331, 141));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 0, 191, 31));
        cmb_zip = new QComboBox(frame_2);
        cmb_zip->setObjectName(QStringLiteral("cmb_zip"));
        cmb_zip->setGeometry(QRect(150, 0, 131, 27));
        chk_key = new QCheckBox(frame_2);
        chk_key->setObjectName(QStringLiteral("chk_key"));
        chk_key->setGeometry(QRect(0, 30, 200, 41));
        lineKey = new QLineEdit(frame_2);
        lineKey->setObjectName(QStringLiteral("lineKey"));
        lineKey->setGeometry(QRect(200, 40, 131, 26));
        chk_overwrite = new QCheckBox(frame_2);
        chk_overwrite->setObjectName(QStringLiteral("chk_overwrite"));
        chk_overwrite->setGeometry(QRect(0, 75, 330, 23));
        chk_path = new QCheckBox(frame_2);
        chk_path->setObjectName(QStringLiteral("chk_path"));
        chk_path->setGeometry(QRect(0, 105, 321, 31));
        cmb_zstd_dir = new QComboBox(frame_2);
        cmb_zstd_dir->setObjectName(QStringLiteral("cmb_zstd_dir"));
        cmb_zstd_dir->setGeometry(QRect(294, 0, 35, 27));
        chk_hidden = new QCheckBox(dir_dialog);
        chk_hidden->setObjectName(QStringLiteral("chk_hidden"));
        chk_hidden->setGeometry(QRect(370, 390, 321, 22));
        pushButton_zstd_dir = new QPushButton(dir_dialog);
        pushButton_zstd_dir->setObjectName(QStringLiteral("pushButton_zstd_dir"));
        pushButton_zstd_dir->setGeometry(QRect(510, 462, 21, 27));
        pushButton_zstd_dir->raise();
        bt_end->raise();
        bt_save->raise();
        treeView_dir->raise();
        label->raise();
        treeView_path->raise();
        label_2->raise();
        frame->raise();
        cmb_kerne->raise();
        label_12->raise();
        frame_2->raise();
        chk_hidden->raise();

        retranslateUi(dir_dialog);
        QObject::connect(cmb_zip, SIGNAL(activated(QString)), pushButton_zstd_dir, SLOT(click()));

        QMetaObject::connectSlotsByName(dir_dialog);
    } // setupUi

    void retranslateUi(QWidget *dir_dialog)
    {
        dir_dialog->setWindowTitle(QApplication::translate("dir_dialog", "Save/restore directory", Q_NULLPTR));
        bt_end->setText(QApplication::translate("dir_dialog", "Exit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        bt_save->setToolTip(QApplication::translate("dir_dialog", "Start the backup or the restore of a folder.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        bt_save->setText(QApplication::translate("dir_dialog", "Save/restore directory", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("dir_dialog", "Select the folder to be backed up or restored.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("dir_dialog", "Saved directory", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("dir_dialog", "Directory in which the folder is backed up or from the recovery file is removed.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("dir_dialog", "Location (path) of backup:", Q_NULLPTR));
        label_4->setText(QApplication::translate("dir_dialog", "On the number of\n"
"captive Files/directories:", Q_NULLPTR));
        label_5->setText(QApplication::translate("dir_dialog", "Already backed\n"
"Files/directories:", Q_NULLPTR));
        label_6->setText(QApplication::translate("dir_dialog", "elapsed time:", Q_NULLPTR));
        label_7->setText(QApplication::translate("dir_dialog", "minutes", Q_NULLPTR));
        label_8->setText(QApplication::translate("dir_dialog", "seconds", Q_NULLPTR));
        label_9->setText(QApplication::translate("dir_dialog", "remaining  time:", Q_NULLPTR));
        label_10->setText(QApplication::translate("dir_dialog", "minutes", Q_NULLPTR));
        label_11->setText(QApplication::translate("dir_dialog", "seconds", Q_NULLPTR));
        label_12->setText(QApplication::translate("dir_dialog", "Number of processor cores\n"
"for to be used fsarchiver:", Q_NULLPTR));
        label_3->setText(QApplication::translate("dir_dialog", "Compression setting:", Q_NULLPTR));
        chk_key->setText(QApplication::translate("dir_dialog", "Encrypt\n"
"backup key", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_overwrite->setToolTip(QApplication::translate("dir_dialog", "Same backup files are overwritten without prior consultation.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_overwrite->setText(QApplication::translate("dir_dialog", "Overwrite existing backup", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_path->setToolTip(QApplication::translate("dir_dialog", "The directory will be written back to the original path", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_path->setText(QApplication::translate("dir_dialog", "Backup restore to the Origin", Q_NULLPTR));
        chk_hidden->setText(QApplication::translate("dir_dialog", "show hidden directories/files", Q_NULLPTR));
        pushButton_zstd_dir->setText(QApplication::translate("dir_dialog", "z", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dir_dialog: public Ui_dir_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIR_DIALOG_H
