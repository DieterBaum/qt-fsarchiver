/********************************************************************************
** Form generated from reading UI file 'net_ein.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NET_EIN_H
#define UI_NET_EIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Eingabe_Net
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *chk_datesave;
    QLineEdit *txt_key;
    QLineEdit *txt_user;
    QPushButton *pushButton_go;
    QListWidget *listWidget_net;
    QLabel *label;
    QPushButton *pushButton_net;
    QCheckBox *chk_password;
    QPushButton *pushButton_end;

    void setupUi(QDialog *Eingabe_Net)
    {
        if (Eingabe_Net->objectName().isEmpty())
            Eingabe_Net->setObjectName(QStringLiteral("Eingabe_Net"));
        Eingabe_Net->resize(353, 383);
        label_2 = new QLabel(Eingabe_Net);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 190, 141, 17));
        label_3 = new QLabel(Eingabe_Net);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 230, 141, 17));
        chk_datesave = new QCheckBox(Eingabe_Net);
        chk_datesave->setObjectName(QStringLiteral("chk_datesave"));
        chk_datesave->setGeometry(QRect(190, 260, 141, 41));
        txt_key = new QLineEdit(Eingabe_Net);
        txt_key->setObjectName(QStringLiteral("txt_key"));
        txt_key->setGeometry(QRect(170, 230, 151, 27));
        txt_key->setEchoMode(QLineEdit::Password);
        txt_user = new QLineEdit(Eingabe_Net);
        txt_user->setObjectName(QStringLiteral("txt_user"));
        txt_user->setGeometry(QRect(170, 190, 151, 27));
        txt_user->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_go = new QPushButton(Eingabe_Net);
        pushButton_go->setObjectName(QStringLiteral("pushButton_go"));
        pushButton_go->setGeometry(QRect(180, 310, 141, 41));
        listWidget_net = new QListWidget(Eingabe_Net);
        listWidget_net->setObjectName(QStringLiteral("listWidget_net"));
        listWidget_net->setGeometry(QRect(20, 40, 301, 131));
        label = new QLabel(Eingabe_Net);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 15, 311, 20));
        pushButton_net = new QPushButton(Eingabe_Net);
        pushButton_net->setObjectName(QStringLiteral("pushButton_net"));
        pushButton_net->setGeometry(QRect(230, 320, 21, 16));
        chk_password = new QCheckBox(Eingabe_Net);
        chk_password->setObjectName(QStringLiteral("chk_password"));
        chk_password->setGeometry(QRect(10, 260, 161, 41));
        pushButton_end = new QPushButton(Eingabe_Net);
        pushButton_end->setObjectName(QStringLiteral("pushButton_end"));
        pushButton_end->setGeometry(QRect(20, 310, 141, 41));
        pushButton_net->raise();
        label_2->raise();
        label_3->raise();
        chk_datesave->raise();
        txt_key->raise();
        txt_user->raise();
        pushButton_go->raise();
        listWidget_net->raise();
        label->raise();
        chk_password->raise();
        pushButton_end->raise();
        QWidget::setTabOrder(listWidget_net, txt_user);
        QWidget::setTabOrder(txt_user, txt_key);
        QWidget::setTabOrder(txt_key, pushButton_go);
        QWidget::setTabOrder(pushButton_go, pushButton_end);
        QWidget::setTabOrder(pushButton_end, pushButton_net);
        QWidget::setTabOrder(pushButton_net, chk_password);
        QWidget::setTabOrder(chk_password, chk_datesave);

        retranslateUi(Eingabe_Net);
        QObject::connect(listWidget_net, SIGNAL(clicked(QModelIndex)), pushButton_net, SLOT(click()));

        QMetaObject::connectSlotsByName(Eingabe_Net);
    } // setupUi

    void retranslateUi(QDialog *Eingabe_Net)
    {
        Eingabe_Net->setWindowTitle(QApplication::translate("Eingabe_Net", "Data network", Q_NULLPTR));
        label_2->setText(QApplication::translate("Eingabe_Net", "Username:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Eingabe_Net", "Password:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chk_datesave->setToolTip(QApplication::translate("Eingabe_Net", "Username and password are stored.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chk_datesave->setText(QApplication::translate("Eingabe_Net", "Save data", Q_NULLPTR));
        pushButton_go->setText(QApplication::translate("Eingabe_Net", "Next", Q_NULLPTR));
        label->setText(QApplication::translate("Eingabe_Net", "Achievable network computer:", Q_NULLPTR));
        pushButton_net->setText(QApplication::translate("Eingabe_Net", "n", Q_NULLPTR));
        chk_password->setText(QApplication::translate("Eingabe_Net", "Show Password", Q_NULLPTR));
        pushButton_end->setText(QApplication::translate("Eingabe_Net", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Eingabe_Net: public Ui_Eingabe_Net {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NET_EIN_H
