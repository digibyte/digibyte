/********************************************************************************
** Form generated from reading UI file 'receiverequestdialog.ui'
**
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEREQUESTDIALOG_H
#define UI_RECEIVEREQUESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include "receiverequestdialog.h"

QT_BEGIN_NAMESPACE

class Ui_ReceiveRequestDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QRImageWidget *lblQRCode;
    QTextEdit *outUri;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCopyURI;
    QPushButton *btnCopyAddress;
    QPushButton *btnSaveAs;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ReceiveRequestDialog)
    {
        if (ReceiveRequestDialog->objectName().isEmpty())
            ReceiveRequestDialog->setObjectName(QString::fromUtf8("ReceiveRequestDialog"));
        ReceiveRequestDialog->resize(487, 597);
        verticalLayout_3 = new QVBoxLayout(ReceiveRequestDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lblQRCode = new QRImageWidget(ReceiveRequestDialog);
        lblQRCode->setObjectName(QString::fromUtf8("lblQRCode"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblQRCode->sizePolicy().hasHeightForWidth());
        lblQRCode->setSizePolicy(sizePolicy);
        lblQRCode->setMinimumSize(QSize(300, 300));
        lblQRCode->setTextFormat(Qt::PlainText);
        lblQRCode->setAlignment(Qt::AlignCenter);
        lblQRCode->setWordWrap(true);

        verticalLayout_3->addWidget(lblQRCode);

        outUri = new QTextEdit(ReceiveRequestDialog);
        outUri->setObjectName(QString::fromUtf8("outUri"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(outUri->sizePolicy().hasHeightForWidth());
        outUri->setSizePolicy(sizePolicy1);
        outUri->setMinimumSize(QSize(0, 50));
        outUri->setFrameShape(QFrame::NoFrame);
        outUri->setFrameShadow(QFrame::Plain);
        outUri->setTabChangesFocus(true);
        outUri->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_3->addWidget(outUri);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCopyURI = new QPushButton(ReceiveRequestDialog);
        btnCopyURI->setObjectName(QString::fromUtf8("btnCopyURI"));

        horizontalLayout->addWidget(btnCopyURI);

        btnCopyAddress = new QPushButton(ReceiveRequestDialog);
        btnCopyAddress->setObjectName(QString::fromUtf8("btnCopyAddress"));

        horizontalLayout->addWidget(btnCopyAddress);

        btnSaveAs = new QPushButton(ReceiveRequestDialog);
        btnSaveAs->setObjectName(QString::fromUtf8("btnSaveAs"));

        horizontalLayout->addWidget(btnSaveAs);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(ReceiveRequestDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(ReceiveRequestDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), ReceiveRequestDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), ReceiveRequestDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(ReceiveRequestDialog);
    } // setupUi

    void retranslateUi(QDialog *ReceiveRequestDialog)
    {
#ifndef QT_NO_TOOLTIP
        lblQRCode->setToolTip(QApplication::translate("ReceiveRequestDialog", "QR Code", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnCopyURI->setText(QApplication::translate("ReceiveRequestDialog", "Copy &URI", 0, QApplication::UnicodeUTF8));
        btnCopyAddress->setText(QApplication::translate("ReceiveRequestDialog", "Copy &Address", 0, QApplication::UnicodeUTF8));
        btnSaveAs->setText(QApplication::translate("ReceiveRequestDialog", "&Save Image...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ReceiveRequestDialog);
    } // retranslateUi

};

namespace Ui {
    class ReceiveRequestDialog: public Ui_ReceiveRequestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEREQUESTDIALOG_H
