/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_setting_dialog
{
public:
    QFrame *frame;
    QLabel *label;
    QComboBox *cmb_Kerne;
    QLabel *label_2;
    QComboBox *cmb_zip;
    QLabel *label_3;
    QComboBox *cmb_language;
    QCheckBox *chk_file;
    QCheckBox *chk_tip;
    QCheckBox *chk_folder;
    QCheckBox *chk_key;
    QCheckBox *chk_split;
    QCheckBox *chk_password;
    QCheckBox *chk_datesave;
    QPushButton *cmd_save;
    QPushButton *cmd_cancel;
    QCheckBox *chk_pbr;
    QComboBox *cmb_network;
    QLabel *label_4;
    QCheckBox *chk_ssh;
    QCheckBox *chk_sshfs;
    QCheckBox *chk_prg;
    QCheckBox *chk_hidden;
    QComboBox *cmb_zstd;
    QLabel *label_5;
    QPushButton *cmd_zstd;
    QLabel *label_6;
    QComboBox *cmb_sleep;

    void setupUi(QDialog *setting_dialog)
    {
        if (setting_dialog->objectName().isEmpty())
            setting_dialog->setObjectName(QStringLiteral("setting_dialog"));
        setting_dialog->resize(473, 643);
        frame = new QFrame(setting_dialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 451, 611));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 17, 225, 51));
        cmb_Kerne = new QComboBox(frame);
        cmb_Kerne->setObjectName(QStringLiteral("cmb_Kerne"));
        cmb_Kerne->setGeometry(QRect(241, 30, 200, 27));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 73, 225, 34));
        cmb_zip = new QComboBox(frame);
        cmb_zip->setObjectName(QStringLiteral("cmb_zip"));
        cmb_zip->setGeometry(QRect(241, 73, 200, 27));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 145, 225, 27));
        cmb_language = new QComboBox(frame);
        cmb_language->setObjectName(QStringLiteral("cmb_language"));
        cmb_language->setGeometry(QRect(240, 145, 200, 27));
        chk_file = new QCheckBox(frame);
        chk_file->setObjectName(QStringLiteral("chk_file"));
        chk_file->setGeometry(QRect(10, 185, 441, 39));
        chk_tip = new QCheckBox(frame);
        chk_tip->setObjectName(QStringLiteral("chk_tip"));
        chk_tip->setGeometry(QRect(10, 210, 441, 39));
        chk_folder = new QCheckBox(frame);
        chk_folder->setObjectName(QStringLiteral("chk_folder"));
        chk_folder->setGeometry(QRect(10, 260, 441, 39));
        chk_key = new QCheckBox(frame);
        chk_key->setObjectName(QStringLiteral("chk_key"));
        chk_key->setGeometry(QRect(10, 235, 441, 39));
        chk_split = new QCheckBox(frame);
        chk_split->setObjectName(QStringLiteral("chk_split"));
        chk_split->setGeometry(QRect(10, 310, 441, 39));
        chk_password = new QCheckBox(frame);
        chk_password->setObjectName(QStringLiteral("chk_password"));
        chk_password->setGeometry(QRect(10, 335, 441, 39));
        chk_datesave = new QCheckBox(frame);
        chk_datesave->setObjectName(QStringLiteral("chk_datesave"));
        chk_datesave->setGeometry(QRect(10, 360, 441, 39));
        cmd_save = new QPushButton(frame);
        cmd_save->setObjectName(QStringLiteral("cmd_save"));
        cmd_save->setGeometry(QRect(10, 540, 431, 27));
        cmd_cancel = new QPushButton(frame);
        cmd_cancel->setObjectName(QStringLiteral("cmd_cancel"));
        cmd_cancel->setGeometry(QRect(10, 570, 431, 27));
        chk_pbr = new QCheckBox(frame);
        chk_pbr->setObjectName(QStringLiteral("chk_pbr"));
        chk_pbr->setGeometry(QRect(10, 288, 441, 39));
        cmb_network = new QComboBox(frame);
        cmb_network->setObjectName(QStringLiteral("cmb_network"));
        cmb_network->setGeometry(QRect(240, 390, 200, 27));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 390, 225, 27));
        chk_ssh = new QCheckBox(frame);
        chk_ssh->setObjectName(QStringLiteral("chk_ssh"));
        chk_ssh->setGeometry(QRect(10, 415, 441, 39));
        chk_sshfs = new QCheckBox(frame);
        chk_sshfs->setObjectName(QStringLiteral("chk_sshfs"));
        chk_sshfs->setGeometry(QRect(10, 440, 441, 39));
        chk_prg = new QCheckBox(frame);
        chk_prg->setObjectName(QStringLiteral("chk_prg"));
        chk_prg->setGeometry(QRect(10, 465, 441, 39));
        chk_hidden = new QCheckBox(frame);
        chk_hidden->setObjectName(QStringLiteral("chk_hidden"));
        chk_hidden->setGeometry(QRect(10, 368310, 401, 22));
        cmb_zstd = new QComboBox(frame);
        cmb_zstd->setObjectName(QStringLiteral("cmb_zstd"));
        cmb_zstd->setGeometry(QRect(370, 110, 71, 27));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 108, 321, 30));
        cmd_zstd = new QPushButton(frame);
        cmd_zstd->setObjectName(QStringLiteral("cmd_zstd"));
        cmd_zstd->setGeometry(QRect(150, 570, 20, 20));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(15, 496, 351, 41));
        label_6->setWordWrap(true);
        cmb_sleep = new QComboBox(frame);
        cmb_sleep->setObjectName(QStringLiteral("cmb_sleep"));
        cmb_sleep->setGeometry(QRect(384, 500, 51, 27));
        cmd_zstd->raise();
        label->raise();
        cmb_Kerne->raise();
        label_2->raise();
        cmb_zip->raise();
        label_3->raise();
        cmb_language->raise();
        chk_file->raise();
        chk_tip->raise();
        chk_folder->raise();
        chk_key->raise();
        chk_split->raise();
        chk_password->raise();
        chk_datesave->raise();
        cmd_save->raise();
        cmd_cancel->raise();
        chk_pbr->raise();
        cmb_network->raise();
        label_4->raise();
        chk_ssh->raise();
        chk_sshfs->raise();
        chk_prg->raise();
        chk_hidden->raise();
        cmb_zstd->raise();
        label_5->raise();
        label_6->raise();
        cmb_sleep->raise();
        QWidget::setTabOrder(cmb_Kerne, cmb_zip);
        QWidget::setTabOrder(cmb_zip, cmb_language);
        QWidget::setTabOrder(cmb_language, chk_file);
        QWidget::setTabOrder(chk_file, chk_tip);
        QWidget::setTabOrder(chk_tip, chk_key);
        QWidget::setTabOrder(chk_key, chk_folder);
        QWidget::setTabOrder(chk_folder, chk_split);
        QWidget::setTabOrder(chk_split, chk_password);
        QWidget::setTabOrder(chk_password, chk_datesave);
        QWidget::setTabOrder(chk_datesave, cmd_save);
        QWidget::setTabOrder(cmd_save, cmd_cancel);

        retranslateUi(setting_dialog);
        QObject::connect(cmb_zip, SIGNAL(activated(QString)), cmd_zstd, SLOT(click()));

        QMetaObject::connectSlotsByName(setting_dialog);
    } // setupUi

    void retranslateUi(QDialog *setting_dialog)
    {
        setting_dialog->setWindowTitle(QApplication::translate("setting_dialog", "Basic settings", Q_NULLPTR));
        label->setText(QApplication::translate("setting_dialog", "Number of processors\n"
"cores, for fsarchiver\n"
"should be used:", Q_NULLPTR));
        label_2->setText(QApplication::translate("setting_dialog", "Standard\n"
"compression:", Q_NULLPTR));
        label_3->setText(QApplication::translate("setting_dialog", "Language:", Q_NULLPTR));
        chk_file->setText(QApplication::translate("setting_dialog", "Existing files by default override", Q_NULLPTR));
        chk_tip->setText(QApplication::translate("setting_dialog", "Backup note enable by default", Q_NULLPTR));
        chk_folder->setText(QApplication::translate("setting_dialog", "Directories by default write \n"
"back to the original location", Q_NULLPTR));
        chk_key->setText(QApplication::translate("setting_dialog", "Enable encryption by default", Q_NULLPTR));
        chk_split->setText(QApplication::translate("setting_dialog", "Archive file size divided on DVD", Q_NULLPTR));
        chk_password->setText(QApplication::translate("setting_dialog", "Show passwords", Q_NULLPTR));
        chk_datesave->setText(QApplication::translate("setting_dialog", "Network input data save", Q_NULLPTR));
        cmd_save->setText(QApplication::translate("setting_dialog", "Save Settings", Q_NULLPTR));
        cmd_cancel->setText(QApplication::translate("setting_dialog", "Exit", Q_NULLPTR));
        chk_pbr->setText(QApplication::translate("setting_dialog", "Safe PBR by default", Q_NULLPTR));
        label_4->setText(QApplication::translate("setting_dialog", "Network protocol:", Q_NULLPTR));
        chk_ssh->setText(QApplication::translate("setting_dialog", "Show Note for accessing network computer", Q_NULLPTR));
        chk_sshfs->setText(QApplication::translate("setting_dialog", "Show  Note to mount the network computer", Q_NULLPTR));
        chk_prg->setText(QApplication::translate("setting_dialog", "Show  Note about the programm qt5-fsarchiver", Q_NULLPTR));
        chk_hidden->setText(QApplication::translate("setting_dialog", "Show hidden directories and files", Q_NULLPTR));
        label_5->setText(QApplication::translate("setting_dialog", "zstd level   1: very fast   22:highest compression", Q_NULLPTR));
        cmd_zstd->setText(QApplication::translate("setting_dialog", "z", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_6->setToolTip(QApplication::translate("setting_dialog", "If the program does not work correctly, you can \n"
"slow down the evaluation time. As standard, the \n"
"evaluation time set with factor 5 * 10 msec\n"
"You can set the factor between 1 and 20.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("setting_dialog", "Selection of the evaluation time \n"
"from the terminal program. ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class setting_dialog: public Ui_setting_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
