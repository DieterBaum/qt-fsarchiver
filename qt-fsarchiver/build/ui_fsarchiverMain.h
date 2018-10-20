/********************************************************************************
** Form generated from reading UI file 'fsarchiverMain.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FSARCHIVERMAIN_H
#define UI_FSARCHIVERMAIN_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPfad_fuer_die_Sicherung_festlegen;
    QAction *action_partition_save;
    QAction *action_partition_restore;
    QAction *action_Einstellungen;
    QAction *action_Information;
    QAction *action_mbr_save;
    QAction *action_mbr_restore;
    QAction *action_dir_restore;
    QAction *action_dir_save;
    QAction *action_Beenden;
    QAction *action_partition_save_net;
    QAction *action_partition_restore_net;
    QAction *breakProcess;
    QAction *action_CloneDrive;
    QAction *action_CloneDrive_net;
    QAction *actionClone_HD;
    QAction *action_Save_directories_on_network;
    QAction *action_Restore_directories_from_network;
    QWidget *centralwidget;
    QLabel *label_Partition;
    QLabel *label_folder;
    QPushButton *pushButton_save;
    QPushButton *pushButton_end;
    QListWidget *listWidget;
    QTreeView *treeView;
    QPushButton *pushButton_partition;
    QPushButton *pushButton_folder;
    QLineEdit *lineEdit_DateiName;
    QPushButton *pushButton_restore;
    QLabel *label_4;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_8;
    QLineEdit *SekundeElapsed;
    QLineEdit *MinuteRemaining;
    QLineEdit *SekundeRemaining;
    QLabel *label_6;
    QLabel *label_9;
    QLineEdit *AnzahlsaveFile;
    QLineEdit *AnzahlgesicherteFile;
    QLineEdit *MinuteElapsed;
    QProgressBar *progressBar;
    QFrame *frame_2;
    QComboBox *cmb_zip;
    QLabel *label_11;
    QComboBox *cmb_kerne;
    QLabel *label;
    QCheckBox *chk_Beschreibung;
    QLineEdit *lineKey;
    QCheckBox *chk_overwrite;
    QCheckBox *chk_split;
    QCheckBox *chk_key;
    QCheckBox *chk_pbr;
    QComboBox *cmb_GB;
    QLabel *label_12;
    QComboBox *cmb_zstd;
    QGroupBox *groupBox;
    QRadioButton *rdBt_saveFsArchiv;
    QRadioButton *rdBt_restoreFsArchiv;
    QCheckBox *chk_hidden;
    QPushButton *pushButton_zstd;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuAktionen;
    QMenu *menu_Einstellungen;
    QMenu *menuInformation;
    QMenu *menu_Beenden;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(770, 710);
        actionPfad_fuer_die_Sicherung_festlegen = new QAction(MainWindow);
        actionPfad_fuer_die_Sicherung_festlegen->setObjectName(QStringLiteral("actionPfad_fuer_die_Sicherung_festlegen"));
        action_partition_save = new QAction(MainWindow);
        action_partition_save->setObjectName(QStringLiteral("action_partition_save"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/src/images/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_partition_save->setIcon(icon);
        action_partition_restore = new QAction(MainWindow);
        action_partition_restore->setObjectName(QStringLiteral("action_partition_restore"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/src/images/book_previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_partition_restore->setIcon(icon1);
        action_Einstellungen = new QAction(MainWindow);
        action_Einstellungen->setObjectName(QStringLiteral("action_Einstellungen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/src/images/einstellung.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Einstellungen->setIcon(icon2);
        action_Information = new QAction(MainWindow);
        action_Information->setObjectName(QStringLiteral("action_Information"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/src/images/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Information->setIcon(icon3);
        action_mbr_save = new QAction(MainWindow);
        action_mbr_save->setObjectName(QStringLiteral("action_mbr_save"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/src/images/mbr_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_mbr_save->setIcon(icon4);
        action_mbr_restore = new QAction(MainWindow);
        action_mbr_restore->setObjectName(QStringLiteral("action_mbr_restore"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/src/images/mbr_restore.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_mbr_restore->setIcon(icon5);
        action_dir_restore = new QAction(MainWindow);
        action_dir_restore->setObjectName(QStringLiteral("action_dir_restore"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/src/images/folder_back.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_dir_restore->setIcon(icon6);
        action_dir_save = new QAction(MainWindow);
        action_dir_save->setObjectName(QStringLiteral("action_dir_save"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/src/images/folder_go.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_dir_save->setIcon(icon7);
        action_Beenden = new QAction(MainWindow);
        action_Beenden->setObjectName(QStringLiteral("action_Beenden"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/src/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Beenden->setIcon(icon8);
        action_partition_save_net = new QAction(MainWindow);
        action_partition_save_net->setObjectName(QStringLiteral("action_partition_save_net"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/src/images/applications-internet.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_partition_save_net->setIcon(icon9);
        action_partition_restore_net = new QAction(MainWindow);
        action_partition_restore_net->setObjectName(QStringLiteral("action_partition_restore_net"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/src/images/applications-internet-ein.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_partition_restore_net->setIcon(icon10);
        breakProcess = new QAction(MainWindow);
        breakProcess->setObjectName(QStringLiteral("breakProcess"));
        breakProcess->setIcon(icon8);
        action_CloneDrive = new QAction(MainWindow);
        action_CloneDrive->setObjectName(QStringLiteral("action_CloneDrive"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/src/images/clone1.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_CloneDrive->setIcon(icon11);
        action_CloneDrive_net = new QAction(MainWindow);
        action_CloneDrive_net->setObjectName(QStringLiteral("action_CloneDrive_net"));
        actionClone_HD = new QAction(MainWindow);
        actionClone_HD->setObjectName(QStringLiteral("actionClone_HD"));
        actionClone_HD->setIcon(icon11);
        action_Save_directories_on_network = new QAction(MainWindow);
        action_Save_directories_on_network->setObjectName(QStringLiteral("action_Save_directories_on_network"));
        action_Restore_directories_from_network = new QAction(MainWindow);
        action_Restore_directories_from_network->setObjectName(QStringLiteral("action_Restore_directories_from_network"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_Partition = new QLabel(centralwidget);
        label_Partition->setObjectName(QStringLiteral("label_Partition"));
        label_Partition->setGeometry(QRect(370, 10, 371, 18));
        label_Partition->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label_folder = new QLabel(centralwidget);
        label_folder->setObjectName(QStringLiteral("label_folder"));
        label_folder->setGeometry(QRect(370, 165, 371, 18));
        label_folder->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        pushButton_save = new QPushButton(centralwidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(10, 335, 351, 41));
        pushButton_end = new QPushButton(centralwidget);
        pushButton_end->setObjectName(QStringLiteral("pushButton_end"));
        pushButton_end->setGeometry(QRect(10, 418, 351, 41));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(370, 30, 380, 131));
        QFont font;
        font.setFamily(QStringLiteral("Courier 10 Pitch"));
        listWidget->setFont(font);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(370, 185, 380, 240));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        treeView->setFont(font1);
        treeView->header()->setDefaultSectionSize(400);
        pushButton_partition = new QPushButton(centralwidget);
        pushButton_partition->setObjectName(QStringLiteral("pushButton_partition"));
        pushButton_partition->setGeometry(QRect(120, 430, 20, 20));
        pushButton_partition->setMinimumSize(QSize(20, 0));
        pushButton_folder = new QPushButton(centralwidget);
        pushButton_folder->setObjectName(QStringLiteral("pushButton_folder"));
        pushButton_folder->setGeometry(QRect(190, 430, 20, 20));
        lineEdit_DateiName = new QLineEdit(centralwidget);
        lineEdit_DateiName->setObjectName(QStringLiteral("lineEdit_DateiName"));
        lineEdit_DateiName->setGeometry(QRect(10, 303, 351, 26));
        pushButton_restore = new QPushButton(centralwidget);
        pushButton_restore->setObjectName(QStringLiteral("pushButton_restore"));
        pushButton_restore->setGeometry(QRect(10, 376, 351, 41));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 283, 291, 18));
        label_4->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 460, 741, 153));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_10 = new QLabel(frame);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 2, 6, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 4, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setLocale(QLocale(QLocale::German, QLocale::Germany));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 6, 1, 1);

        SekundeElapsed = new QLineEdit(frame);
        SekundeElapsed->setObjectName(QStringLiteral("SekundeElapsed"));
        SekundeElapsed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(SekundeElapsed, 0, 5, 1, 1);

        MinuteRemaining = new QLineEdit(frame);
        MinuteRemaining->setObjectName(QStringLiteral("MinuteRemaining"));
        MinuteRemaining->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(MinuteRemaining, 2, 3, 1, 1);

        SekundeRemaining = new QLineEdit(frame);
        SekundeRemaining->setObjectName(QStringLiteral("SekundeRemaining"));
        SekundeRemaining->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(SekundeRemaining, 2, 5, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 2, 4, 1, 1);

        AnzahlsaveFile = new QLineEdit(frame);
        AnzahlsaveFile->setObjectName(QStringLiteral("AnzahlsaveFile"));
        AnzahlsaveFile->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(AnzahlsaveFile, 0, 1, 1, 1);

        AnzahlgesicherteFile = new QLineEdit(frame);
        AnzahlgesicherteFile->setObjectName(QStringLiteral("AnzahlgesicherteFile"));
        AnzahlgesicherteFile->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(AnzahlgesicherteFile, 2, 1, 1, 1);

        MinuteElapsed = new QLineEdit(frame);
        MinuteElapsed->setObjectName(QStringLiteral("MinuteElapsed"));
        MinuteElapsed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(MinuteElapsed, 0, 3, 1, 1);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximum(100);
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 4, 0, 1, 7);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 60, 351, 220));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Plain);
        cmb_zip = new QComboBox(frame_2);
        cmb_zip->setObjectName(QStringLiteral("cmb_zip"));
        cmb_zip->setGeometry(QRect(110, 185, 161, 27));
        label_11 = new QLabel(frame_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 137, 290, 41));
        label_11->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        cmb_kerne = new QComboBox(frame_2);
        cmb_kerne->setObjectName(QStringLiteral("cmb_kerne"));
        cmb_kerne->setGeometry(QRect(300, 145, 45, 27));
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 175, 161, 41));
        chk_Beschreibung = new QCheckBox(frame_2);
        chk_Beschreibung->setObjectName(QStringLiteral("chk_Beschreibung"));
        chk_Beschreibung->setGeometry(QRect(0, 0, 331, 23));
        lineKey = new QLineEdit(frame_2);
        lineKey->setObjectName(QStringLiteral("lineKey"));
        lineKey->setGeometry(QRect(225, 58, 121, 26));
        chk_overwrite = new QCheckBox(frame_2);
        chk_overwrite->setObjectName(QStringLiteral("chk_overwrite"));
        chk_overwrite->setGeometry(QRect(0, 28, 341, 23));
        chk_split = new QCheckBox(frame_2);
        chk_split->setObjectName(QStringLiteral("chk_split"));
        chk_split->setGeometry(QRect(0, 88, 251, 23));
        chk_key = new QCheckBox(frame_2);
        chk_key->setObjectName(QStringLiteral("chk_key"));
        chk_key->setGeometry(QRect(0, 51, 221, 35));
        chk_pbr = new QCheckBox(frame_2);
        chk_pbr->setObjectName(QStringLiteral("chk_pbr"));
        chk_pbr->setGeometry(QRect(0, 114, 261, 22));
        cmb_GB = new QComboBox(frame_2);
        cmb_GB->setObjectName(QStringLiteral("cmb_GB"));
        cmb_GB->setGeometry(QRect(260, 90, 51, 27));
        label_12 = new QLabel(frame_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(318, 95, 21, 17));
        cmb_zstd = new QComboBox(frame_2);
        cmb_zstd->setObjectName(QStringLiteral("cmb_zstd"));
        cmb_zstd->setGeometry(QRect(300, 185, 45, 27));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 362, 71));
        groupBox->setSizeIncrement(QSize(10, 10));
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        rdBt_saveFsArchiv = new QRadioButton(groupBox);
        rdBt_saveFsArchiv->setObjectName(QStringLiteral("rdBt_saveFsArchiv"));
        rdBt_saveFsArchiv->setGeometry(QRect(0, 20, 165, 40));
        rdBt_restoreFsArchiv = new QRadioButton(groupBox);
        rdBt_restoreFsArchiv->setObjectName(QStringLiteral("rdBt_restoreFsArchiv"));
        rdBt_restoreFsArchiv->setGeometry(QRect(165, 20, 195, 40));
        chk_hidden = new QCheckBox(centralwidget);
        chk_hidden->setObjectName(QStringLiteral("chk_hidden"));
        chk_hidden->setGeometry(QRect(370, 430, 361, 22));
        pushButton_zstd = new QPushButton(centralwidget);
        pushButton_zstd->setObjectName(QStringLiteral("pushButton_zstd"));
        pushButton_zstd->setGeometry(QRect(230, 430, 21, 20));
        MainWindow->setCentralWidget(centralwidget);
        pushButton_zstd->raise();
        pushButton_partition->raise();
        pushButton_folder->raise();
        label_Partition->raise();
        label_folder->raise();
        pushButton_save->raise();
        pushButton_end->raise();
        listWidget->raise();
        treeView->raise();
        lineEdit_DateiName->raise();
        pushButton_restore->raise();
        label_4->raise();
        frame->raise();
        frame_2->raise();
        groupBox->raise();
        chk_hidden->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setOrientation(Qt::Horizontal);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 25));
        menuAktionen = new QMenu(menuBar);
        menuAktionen->setObjectName(QStringLiteral("menuAktionen"));
        menu_Einstellungen = new QMenu(menuBar);
        menu_Einstellungen->setObjectName(QStringLiteral("menu_Einstellungen"));
        menuInformation = new QMenu(menuBar);
        menuInformation->setObjectName(QStringLiteral("menuInformation"));
        menu_Beenden = new QMenu(menuBar);
        menu_Beenden->setObjectName(QStringLiteral("menu_Beenden"));
        MainWindow->setMenuBar(menuBar);

        toolBar->addAction(action_partition_save);
        toolBar->addAction(action_partition_restore);
        toolBar->addAction(action_mbr_save);
        toolBar->addAction(action_mbr_restore);
        toolBar->addAction(action_dir_save);
        toolBar->addAction(action_dir_restore);
        toolBar->addAction(action_partition_save_net);
        toolBar->addAction(action_partition_restore_net);
        toolBar->addAction(action_CloneDrive);
        menuBar->addAction(menuAktionen->menuAction());
        menuBar->addAction(menu_Einstellungen->menuAction());
        menuBar->addAction(menuInformation->menuAction());
        menuBar->addAction(menu_Beenden->menuAction());
        menuAktionen->addSeparator();
        menuAktionen->addAction(action_partition_save);
        menuAktionen->addAction(action_partition_restore);
        menuAktionen->addSeparator();
        menuAktionen->addAction(action_partition_save_net);
        menuAktionen->addAction(action_partition_restore_net);
        menuAktionen->addAction(action_mbr_save);
        menuAktionen->addAction(action_mbr_restore);
        menuAktionen->addSeparator();
        menuAktionen->addAction(action_dir_save);
        menuAktionen->addAction(action_dir_restore);
        menuAktionen->addSeparator();
        menuAktionen->addAction(actionClone_HD);
        menu_Einstellungen->addAction(action_Einstellungen);
        menuInformation->addAction(action_Information);
        menu_Beenden->addAction(action_Beenden);

        retranslateUi(MainWindow);
        QObject::connect(listWidget, SIGNAL(clicked(QModelIndex)), pushButton_partition, SLOT(click()));
        QObject::connect(treeView, SIGNAL(clicked(QModelIndex)), pushButton_folder, SLOT(click()));
        QObject::connect(cmb_zip, SIGNAL(activated(QString)), pushButton_zstd, SLOT(click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Save/restore partition ", Q_NULLPTR));
        actionPfad_fuer_die_Sicherung_festlegen->setText(QApplication::translate("MainWindow", "Basic Settings", Q_NULLPTR));
        action_partition_save->setText(QApplication::translate("MainWindow", "&Backup partition", Q_NULLPTR));
        action_partition_restore->setText(QApplication::translate("MainWindow", "&Restore partition", Q_NULLPTR));
        action_Einstellungen->setText(QApplication::translate("MainWindow", "&Basic Settings", Q_NULLPTR));
        action_Information->setText(QApplication::translate("MainWindow", "&Information fsarchiver", Q_NULLPTR));
        action_mbr_save->setText(QApplication::translate("MainWindow", "Save &MBR/GPT", Q_NULLPTR));
        action_mbr_restore->setText(QApplication::translate("MainWindow", "R&estore MBR/GPT", Q_NULLPTR));
        action_dir_restore->setText(QApplication::translate("MainWindow", "Rest&ore directory ", Q_NULLPTR));
        action_dir_save->setText(QApplication::translate("MainWindow", "Save &directory ", Q_NULLPTR));
        action_Beenden->setText(QApplication::translate("MainWindow", "&Exit program", Q_NULLPTR));
        action_partition_save_net->setText(QApplication::translate("MainWindow", "&Save a partition/directorie on network", Q_NULLPTR));
        action_partition_restore_net->setText(QApplication::translate("MainWindow", "Restore &a partition/directorie on network", Q_NULLPTR));
        breakProcess->setText(QApplication::translate("MainWindow", "breakprocess", Q_NULLPTR));
        action_CloneDrive->setText(QApplication::translate("MainWindow", "Clone Drive HD-Image save/restore ", Q_NULLPTR));
        action_CloneDrive_net->setText(QApplication::translate("MainWindow", "HD-Image save/restore on network", Q_NULLPTR));
        actionClone_HD->setText(QApplication::translate("MainWindow", "&Clone HD, HD-Image built and restore", Q_NULLPTR));
        action_Save_directories_on_network->setText(QApplication::translate("MainWindow", "Save directories on network", Q_NULLPTR));
        action_Restore_directories_from_network->setText(QApplication::translate("MainWindow", "Restore directories from network", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Partition->setToolTip(QApplication::translate("MainWindow", "Select the partition to be backed up or restored.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Partition->setText(QApplication::translate("MainWindow", "Existing partitions:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_folder->setToolTip(QApplication::translate("MainWindow", "Directory in which the partition is backed up or from the recovery file is removed.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_folder->setText(QApplication::translate("MainWindow", "Backup directory:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_save->setToolTip(QApplication::translate("MainWindow", "Start the backup of a partition.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_save->setText(QApplication::translate("MainWindow", "Stored partitions", Q_NULLPTR));
        pushButton_end->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        pushButton_partition->setText(QApplication::translate("MainWindow", "S", Q_NULLPTR));
        pushButton_folder->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_restore->setToolTip(QApplication::translate("MainWindow", "Start restore a partition.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_restore->setText(QApplication::translate("MainWindow", "Partition restore", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Name the backup file:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "seconds", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "minutes", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "elapsed time:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "On the number saved\n"
"Files/directories:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "already saved \n"
"files/directories:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "seconds", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "remaining time:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "minutes", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Number of processors\n"
"cores for to be used fsarchiver:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Compression\n"
"setting:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_Beschreibung->setToolTip(QApplication::translate("MainWindow", "Notes to the backup is written to a file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_Beschreibung->setText(QApplication::translate("MainWindow", "Notes to  the backup", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_overwrite->setToolTip(QApplication::translate("MainWindow", "Same backup files are overwritten without prior consultation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_overwrite->setText(QApplication::translate("MainWindow", "available backup overwrite", Q_NULLPTR));
        chk_split->setText(QApplication::translate("MainWindow", "Stock Split on size:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_key->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        chk_key->setText(QApplication::translate("MainWindow", "Encrypt \n"
"backup key", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_pbr->setToolTip(QApplication::translate("MainWindow", "PBR is first block of any bootable partition", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_pbr->setText(QApplication::translate("MainWindow", "Save PBR", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "GB", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Proposed action:", Q_NULLPTR));
        rdBt_saveFsArchiv->setText(QApplication::translate("MainWindow", "&Partition save \n"
"with fsarchiver", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        rdBt_restoreFsArchiv->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        rdBt_restoreFsArchiv->setText(QApplication::translate("MainWindow", "Restore partition\n"
"with fsarchi&ver", Q_NULLPTR));
        chk_hidden->setText(QApplication::translate("MainWindow", "Show hidden directories and files", Q_NULLPTR));
        pushButton_zstd->setText(QApplication::translate("MainWindow", "z", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        menuAktionen->setTitle(QApplication::translate("MainWindow", "&Actions", Q_NULLPTR));
        menu_Einstellungen->setTitle(QApplication::translate("MainWindow", "Se&ttings", Q_NULLPTR));
        menuInformation->setTitle(QApplication::translate("MainWindow", "&Information", Q_NULLPTR));
        menu_Beenden->setTitle(QApplication::translate("MainWindow", "&Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FSARCHIVERMAIN_H
