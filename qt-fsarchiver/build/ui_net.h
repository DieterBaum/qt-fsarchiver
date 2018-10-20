/********************************************************************************
** Form generated from reading UI file 'net.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NET_H
#define UI_NET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Net
{
public:
    QLabel *label_2;
    QLabel *label_folder;
    QPushButton *pushButton_partition;
    QLabel *label_Partition;
    QGroupBox *groupBox;
    QRadioButton *rdBt_saveFsArchiv;
    QRadioButton *rdBt_restoreFsArchiv;
    QListWidget *listWidget;
    QPushButton *pushButton_folder_free;
    QPushButton *pushButton_save;
    QLineEdit *lineEdit_DateiName;
    QPushButton *bt_net_art;
    QLineEdit *txt_rechner_net;
    QLabel *label_4;
    QPushButton *pushButton_end;
    QPushButton *pushButton_restore;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_3;
    QLineEdit *AnzahlsaveFile;
    QLabel *label_6;
    QLineEdit *AnzahlgesicherteFile;
    QLineEdit *MinuteElapsed;
    QLabel *label_8;
    QLineEdit *SekundeElapsed;
    QLabel *label_7;
    QLineEdit *MinuteRemaining;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *SekundeRemaining;
    QLabel *label_11;
    QProgressBar *progressBar;
    QLabel *label_folder_free;
    QListWidget *listWidget_free_folder;
    QLineEdit *restore_file_name_txt;
    QFrame *frame_2;
    QComboBox *cmb_zip;
    QLabel *label_12;
    QComboBox *cmb_kerne;
    QLabel *label;
    QCheckBox *chk_Beschreibung;
    QLineEdit *lineKey;
    QCheckBox *chk_overwrite;
    QCheckBox *chk_split;
    QCheckBox *chk_key;
    QCheckBox *chk_pbr;
    QCheckBox *chk_path;
    QComboBox *cmb_zstd_net;
    QComboBox *cmb_Net;
    QLabel *label_13;
    QPushButton *bt_toParent;
    QPushButton *bt_treeWiget;
    QTreeWidget *treeWidget;
    QCheckBox *chk_hidden;
    QTreeView *treeView_dir;
    QGroupBox *groupBox_2;
    QRadioButton *rdBt_showPartition;
    QRadioButton *rdBt_showDirectories;
    QPushButton *pushButton_zstd_net;

    void setupUi(QDialog *Dialog_Net)
    {
        if (Dialog_Net->objectName().isEmpty())
            Dialog_Net->setObjectName(QStringLiteral("Dialog_Net"));
        Dialog_Net->resize(777, 671);
        label_2 = new QLabel(Dialog_Net);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(385, 450, 351, 21));
        label_folder = new QLabel(Dialog_Net);
        label_folder->setObjectName(QStringLiteral("label_folder"));
        label_folder->setGeometry(QRect(385, 405, 371, 18));
        pushButton_partition = new QPushButton(Dialog_Net);
        pushButton_partition->setObjectName(QStringLiteral("pushButton_partition"));
        pushButton_partition->setGeometry(QRect(150, 420, 20, 20));
        pushButton_partition->setMinimumSize(QSize(20, 0));
        label_Partition = new QLabel(Dialog_Net);
        label_Partition->setObjectName(QStringLiteral("label_Partition"));
        label_Partition->setGeometry(QRect(390, 55, 361, 18));
        groupBox = new QGroupBox(Dialog_Net);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 360, 71));
        groupBox->setSizeIncrement(QSize(10, 10));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        rdBt_saveFsArchiv = new QRadioButton(groupBox);
        rdBt_saveFsArchiv->setObjectName(QStringLiteral("rdBt_saveFsArchiv"));
        rdBt_saveFsArchiv->setGeometry(QRect(0, 20, 161, 40));
        rdBt_restoreFsArchiv = new QRadioButton(groupBox);
        rdBt_restoreFsArchiv->setObjectName(QStringLiteral("rdBt_restoreFsArchiv"));
        rdBt_restoreFsArchiv->setGeometry(QRect(170, 20, 181, 40));
        rdBt_restoreFsArchiv->raise();
        rdBt_saveFsArchiv->raise();
        listWidget = new QListWidget(Dialog_Net);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(390, 80, 371, 151));
        QFont font;
        font.setFamily(QStringLiteral("Courier 10 Pitch"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        listWidget->setFont(font);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButton_folder_free = new QPushButton(Dialog_Net);
        pushButton_folder_free->setObjectName(QStringLiteral("pushButton_folder_free"));
        pushButton_folder_free->setGeometry(QRect(230, 420, 21, 21));
        pushButton_save = new QPushButton(Dialog_Net);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(20, 370, 351, 41));
        lineEdit_DateiName = new QLineEdit(Dialog_Net);
        lineEdit_DateiName->setObjectName(QStringLiteral("lineEdit_DateiName"));
        lineEdit_DateiName->setGeometry(QRect(20, 340, 351, 26));
        bt_net_art = new QPushButton(Dialog_Net);
        bt_net_art->setObjectName(QStringLiteral("bt_net_art"));
        bt_net_art->setGeometry(QRect(190, 420, 21, 20));
        txt_rechner_net = new QLineEdit(Dialog_Net);
        txt_rechner_net->setObjectName(QStringLiteral("txt_rechner_net"));
        txt_rechner_net->setGeometry(QRect(385, 470, 371, 27));
        label_4 = new QLabel(Dialog_Net);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 320, 291, 18));
        pushButton_end = new QPushButton(Dialog_Net);
        pushButton_end->setObjectName(QStringLiteral("pushButton_end"));
        pushButton_end->setGeometry(QRect(20, 458, 351, 41));
        pushButton_restore = new QPushButton(Dialog_Net);
        pushButton_restore->setObjectName(QStringLiteral("pushButton_restore"));
        pushButton_restore->setGeometry(QRect(20, 415, 351, 41));
        frame = new QFrame(Dialog_Net);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 500, 741, 153));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setLocale(QLocale(QLocale::German, QLocale::Germany));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        AnzahlsaveFile = new QLineEdit(frame);
        AnzahlsaveFile->setObjectName(QStringLiteral("AnzahlsaveFile"));
        AnzahlsaveFile->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(AnzahlsaveFile, 0, 1, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        AnzahlgesicherteFile = new QLineEdit(frame);
        AnzahlgesicherteFile->setObjectName(QStringLiteral("AnzahlgesicherteFile"));
        AnzahlgesicherteFile->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(AnzahlgesicherteFile, 1, 1, 1, 1);

        MinuteElapsed = new QLineEdit(frame);
        MinuteElapsed->setObjectName(QStringLiteral("MinuteElapsed"));
        MinuteElapsed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(MinuteElapsed, 0, 3, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 6, 1, 1);

        SekundeElapsed = new QLineEdit(frame);
        SekundeElapsed->setObjectName(QStringLiteral("SekundeElapsed"));
        SekundeElapsed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(SekundeElapsed, 0, 5, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        MinuteRemaining = new QLineEdit(frame);
        MinuteRemaining->setObjectName(QStringLiteral("MinuteRemaining"));
        MinuteRemaining->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(MinuteRemaining, 1, 3, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 1, 4, 1, 1);

        SekundeRemaining = new QLineEdit(frame);
        SekundeRemaining->setObjectName(QStringLiteral("SekundeRemaining"));
        SekundeRemaining->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(SekundeRemaining, 1, 5, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 1, 6, 1, 1);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 3, 0, 1, 7);

        label_folder_free = new QLabel(Dialog_Net);
        label_folder_free->setObjectName(QStringLiteral("label_folder_free"));
        label_folder_free->setGeometry(QRect(390, 280, 261, 17));
        listWidget_free_folder = new QListWidget(Dialog_Net);
        listWidget_free_folder->setObjectName(QStringLiteral("listWidget_free_folder"));
        listWidget_free_folder->setGeometry(QRect(390, 300, 351, 101));
        restore_file_name_txt = new QLineEdit(Dialog_Net);
        restore_file_name_txt->setObjectName(QStringLiteral("restore_file_name_txt"));
        restore_file_name_txt->setGeometry(QRect(385, 425, 371, 27));
        frame_2 = new QFrame(Dialog_Net);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(20, 80, 351, 235));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        cmb_zip = new QComboBox(frame_2);
        cmb_zip->setObjectName(QStringLiteral("cmb_zip"));
        cmb_zip->setGeometry(QRect(102, 200, 161, 27));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 160, 271, 41));
        label_12->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        cmb_kerne = new QComboBox(frame_2);
        cmb_kerne->setObjectName(QStringLiteral("cmb_kerne"));
        cmb_kerne->setGeometry(QRect(290, 168, 51, 27));
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 193, 161, 41));
        chk_Beschreibung = new QCheckBox(frame_2);
        chk_Beschreibung->setObjectName(QStringLiteral("chk_Beschreibung"));
        chk_Beschreibung->setGeometry(QRect(0, 0, 331, 23));
        lineKey = new QLineEdit(frame_2);
        lineKey->setObjectName(QStringLiteral("lineKey"));
        lineKey->setGeometry(QRect(220, 58, 121, 26));
        chk_overwrite = new QCheckBox(frame_2);
        chk_overwrite->setObjectName(QStringLiteral("chk_overwrite"));
        chk_overwrite->setGeometry(QRect(0, 28, 341, 23));
        chk_split = new QCheckBox(frame_2);
        chk_split->setObjectName(QStringLiteral("chk_split"));
        chk_split->setGeometry(QRect(0, 88, 251, 23));
        chk_key = new QCheckBox(frame_2);
        chk_key->setObjectName(QStringLiteral("chk_key"));
        chk_key->setGeometry(QRect(0, 48, 221, 41));
        chk_pbr = new QCheckBox(frame_2);
        chk_pbr->setObjectName(QStringLiteral("chk_pbr"));
        chk_pbr->setGeometry(QRect(0, 114, 261, 22));
        chk_path = new QCheckBox(frame_2);
        chk_path->setObjectName(QStringLiteral("chk_path"));
        chk_path->setGeometry(QRect(0, 140, 351, 22));
        cmb_zstd_net = new QComboBox(frame_2);
        cmb_zstd_net->setObjectName(QStringLiteral("cmb_zstd_net"));
        cmb_zstd_net->setGeometry(QRect(290, 200, 51, 27));
        cmb_Net = new QComboBox(Dialog_Net);
        cmb_Net->setObjectName(QStringLiteral("cmb_Net"));
        cmb_Net->setGeometry(QRect(560, 240, 201, 27));
        label_13 = new QLabel(Dialog_Net);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(390, 235, 151, 41));
        label_13->setWordWrap(true);
        bt_toParent = new QPushButton(Dialog_Net);
        bt_toParent->setObjectName(QStringLiteral("bt_toParent"));
        bt_toParent->setGeometry(QRect(730, 270, 31, 27));
        QIcon icon;
        icon.addFile(QStringLiteral(":/src/images/cdtoparent.png"), QSize(), QIcon::Normal, QIcon::Off);
        bt_toParent->setIcon(icon);
        bt_treeWiget = new QPushButton(Dialog_Net);
        bt_treeWiget->setObjectName(QStringLiteral("bt_treeWiget"));
        bt_treeWiget->setGeometry(QRect(40, 380, 21, 27));
        treeWidget = new QTreeWidget(Dialog_Net);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(390, 300, 371, 101));
        chk_hidden = new QCheckBox(Dialog_Net);
        chk_hidden->setObjectName(QStringLiteral("chk_hidden"));
        chk_hidden->setGeometry(QRect(390, 32, 351, 22));
        treeView_dir = new QTreeView(Dialog_Net);
        treeView_dir->setObjectName(QStringLiteral("treeView_dir"));
        treeView_dir->setGeometry(QRect(390, 80, 371, 151));
        treeView_dir->setFont(font);
        treeView_dir->header()->setDefaultSectionSize(400);
        groupBox_2 = new QGroupBox(Dialog_Net);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(390, 10, 371, 25));
        rdBt_showPartition = new QRadioButton(groupBox_2);
        rdBt_showPartition->setObjectName(QStringLiteral("rdBt_showPartition"));
        rdBt_showPartition->setGeometry(QRect(0, 0, 191, 22));
        rdBt_showDirectories = new QRadioButton(groupBox_2);
        rdBt_showDirectories->setObjectName(QStringLiteral("rdBt_showDirectories"));
        rdBt_showDirectories->setGeometry(QRect(190, 0, 191, 22));
        pushButton_zstd_net = new QPushButton(Dialog_Net);
        pushButton_zstd_net->setObjectName(QStringLiteral("pushButton_zstd_net"));
        pushButton_zstd_net->setGeometry(QRect(210, 460, 21, 27));
        pushButton_zstd_net->raise();
        bt_treeWiget->raise();
        label_2->raise();
        label_folder->raise();
        pushButton_partition->raise();
        label_Partition->raise();
        groupBox->raise();
        listWidget->raise();
        pushButton_folder_free->raise();
        pushButton_save->raise();
        lineEdit_DateiName->raise();
        bt_net_art->raise();
        txt_rechner_net->raise();
        label_4->raise();
        pushButton_end->raise();
        pushButton_restore->raise();
        frame->raise();
        label_folder_free->raise();
        listWidget_free_folder->raise();
        restore_file_name_txt->raise();
        frame_2->raise();
        cmb_Net->raise();
        label_13->raise();
        bt_toParent->raise();
        treeWidget->raise();
        chk_hidden->raise();
        treeView_dir->raise();
        groupBox_2->raise();

        retranslateUi(Dialog_Net);
        QObject::connect(listWidget, SIGNAL(clicked(QModelIndex)), pushButton_partition, SLOT(click()));
        QObject::connect(listWidget_free_folder, SIGNAL(clicked(QModelIndex)), pushButton_folder_free, SLOT(click()));
        QObject::connect(cmb_Net, SIGNAL(activated(int)), bt_net_art, SLOT(click()));
        QObject::connect(treeWidget, SIGNAL(clicked(QModelIndex)), bt_treeWiget, SLOT(click()));
        QObject::connect(cmb_zip, SIGNAL(activated(QString)), pushButton_zstd_net, SLOT(click()));

        QMetaObject::connectSlotsByName(Dialog_Net);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Net)
    {
        Dialog_Net->setWindowTitle(QApplication::translate("Dialog_Net", "Backup/restore partition over network", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog_Net", "Network computer  name:", Q_NULLPTR));
        label_folder->setText(QApplication::translate("Dialog_Net", "Restore file name:", Q_NULLPTR));
        pushButton_partition->setText(QApplication::translate("Dialog_Net", "S", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Partition->setToolTip(QApplication::translate("Dialog_Net", "Select the partition to be backed up or restored.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Partition->setText(QApplication::translate("Dialog_Net", "Existing partitions/directories:", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog_Net", "Proposed action:", Q_NULLPTR));
        rdBt_saveFsArchiv->setText(QApplication::translate("Dialog_Net", "Save par&tition\n"
" or directory", Q_NULLPTR));
        rdBt_restoreFsArchiv->setText(QApplication::translate("Dialog_Net", "&Restore partition \n"
" or directory", Q_NULLPTR));
        pushButton_folder_free->setText(QApplication::translate("Dialog_Net", "n", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_save->setToolTip(QApplication::translate("Dialog_Net", "Start the backup of a partition.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_save->setText(QApplication::translate("Dialog_Net", "Save partition/directorie", Q_NULLPTR));
        bt_net_art->setText(QString());
        label_4->setText(QApplication::translate("Dialog_Net", "Name the backup file:", Q_NULLPTR));
        pushButton_end->setText(QApplication::translate("Dialog_Net", "Exit", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_restore->setToolTip(QApplication::translate("Dialog_Net", "Start restore a partition.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_restore->setText(QApplication::translate("Dialog_Net", "Partition/directorie restore", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog_Net", "elapsed time:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog_Net", "On the number saved\n"
"Files/directories:", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog_Net", "already saved \n"
"files/directories:", Q_NULLPTR));
        label_8->setText(QApplication::translate("Dialog_Net", "seconds", Q_NULLPTR));
        label_7->setText(QApplication::translate("Dialog_Net", "minutes", Q_NULLPTR));
        label_9->setText(QApplication::translate("Dialog_Net", "remaining time", Q_NULLPTR));
        label_10->setText(QApplication::translate("Dialog_Net", "minutes", Q_NULLPTR));
        label_11->setText(QApplication::translate("Dialog_Net", "seconds", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_folder_free->setToolTip(QApplication::translate("Dialog_Net", "Directory in which the partition is backed up or from the recovery file is removed.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_folder_free->setText(QApplication::translate("Dialog_Net", "Please select the folder.", Q_NULLPTR));
        label_12->setText(QApplication::translate("Dialog_Net", "Number of processors\n"
"cores for to be used fsarchiver:", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog_Net", "Compression\n"
"setting:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_Beschreibung->setToolTip(QApplication::translate("Dialog_Net", "Notes to the backup is written to a file.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_Beschreibung->setText(QApplication::translate("Dialog_Net", "Notes to  the backup", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_overwrite->setToolTip(QApplication::translate("Dialog_Net", "Same backup files are overwritten without prior consultation.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_overwrite->setText(QApplication::translate("Dialog_Net", "available backup overwrite", Q_NULLPTR));
        chk_split->setText(QApplication::translate("Dialog_Net", "Stock Split on DVD size", Q_NULLPTR));
        chk_key->setText(QApplication::translate("Dialog_Net", "Encrypt \n"
"backup key", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_pbr->setToolTip(QApplication::translate("Dialog_Net", "PBR is first block of any bootable partition.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_pbr->setText(QApplication::translate("Dialog_Net", "Save PBR", Q_NULLPTR));
        chk_path->setText(QApplication::translate("Dialog_Net", "Backup restore to the Origin", Q_NULLPTR));
        label_13->setText(QApplication::translate("Dialog_Net", "Protocoll for network\n"
"transmission:", Q_NULLPTR));
        bt_toParent->setText(QString());
        bt_treeWiget->setText(QString());
        chk_hidden->setText(QApplication::translate("Dialog_Net", "Show hidden directories and files", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        rdBt_showPartition->setText(QApplication::translate("Dialog_Net", "Show &partitions", Q_NULLPTR));
        rdBt_showDirectories->setText(QApplication::translate("Dialog_Net", "Show &directories", Q_NULLPTR));
        pushButton_zstd_net->setText(QApplication::translate("Dialog_Net", "z", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Net: public Ui_Dialog_Net {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NET_H
