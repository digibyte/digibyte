/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QLabel *sizeWarningLabel;
    QRadioButton *dataDirDefault;
    QRadioButton *dataDirCustom;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *dataDirectory;
    QPushButton *ellipsisButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *freeSpace;
    QSpacerItem *verticalSpacer_2;
    QLabel *errorMessage;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName(QString::fromUtf8("Intro"));
        Intro->resize(674, 363);
        verticalLayout = new QVBoxLayout(Intro);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(Intro);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel { font-style:italic; }"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        label_4 = new QLabel(Intro);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        verticalLayout->addWidget(label_4);

        sizeWarningLabel = new QLabel(Intro);
        sizeWarningLabel->setObjectName(QString::fromUtf8("sizeWarningLabel"));
        sizeWarningLabel->setWordWrap(true);

        verticalLayout->addWidget(sizeWarningLabel);

        dataDirDefault = new QRadioButton(Intro);
        dataDirDefault->setObjectName(QString::fromUtf8("dataDirDefault"));

        verticalLayout->addWidget(dataDirDefault);

        dataDirCustom = new QRadioButton(Intro);
        dataDirCustom->setObjectName(QString::fromUtf8("dataDirCustom"));

        verticalLayout->addWidget(dataDirCustom);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        dataDirectory = new QLineEdit(Intro);
        dataDirectory->setObjectName(QString::fromUtf8("dataDirectory"));

        horizontalLayout_2->addWidget(dataDirectory);

        ellipsisButton = new QPushButton(Intro);
        ellipsisButton->setObjectName(QString::fromUtf8("ellipsisButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ellipsisButton->sizePolicy().hasHeightForWidth());
        ellipsisButton->setSizePolicy(sizePolicy);
        ellipsisButton->setMaximumSize(QSize(30, 16777215));
        ellipsisButton->setText(QString::fromUtf8("\342\200\246"));
        ellipsisButton->setAutoDefault(false);

        horizontalLayout_2->addWidget(ellipsisButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        freeSpace = new QLabel(Intro);
        freeSpace->setObjectName(QString::fromUtf8("freeSpace"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(freeSpace->sizePolicy().hasHeightForWidth());
        freeSpace->setSizePolicy(sizePolicy1);
        freeSpace->setWordWrap(true);

        verticalLayout_2->addWidget(freeSpace);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        errorMessage = new QLabel(Intro);
        errorMessage->setObjectName(QString::fromUtf8("errorMessage"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(errorMessage->sizePolicy().hasHeightForWidth());
        errorMessage->setSizePolicy(sizePolicy2);
        errorMessage->setTextFormat(Qt::RichText);
        errorMessage->setWordWrap(true);

        verticalLayout_2->addWidget(errorMessage);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(Intro);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Intro);
        QObject::connect(buttonBox, SIGNAL(accepted()), Intro, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Intro, SLOT(reject()));

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QDialog *Intro)
    {
        Intro->setWindowTitle(QApplication::translate("Intro", "Welcome", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Intro", "Welcome to Bitcoin Core.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Intro", "As this is the first time the program is launched, you can choose where Bitcoin Core will store its data.", 0, QApplication::UnicodeUTF8));
        sizeWarningLabel->setText(QApplication::translate("Intro", "Bitcoin Core will download and store a copy of the Bitcoin block chain. At least %1GB of data will be stored in this directory, and it will grow over time. The wallet will also be stored in this directory.", 0, QApplication::UnicodeUTF8));
        dataDirDefault->setText(QApplication::translate("Intro", "Use the default data directory", 0, QApplication::UnicodeUTF8));
        dataDirCustom->setText(QApplication::translate("Intro", "Use a custom data directory:", 0, QApplication::UnicodeUTF8));
        freeSpace->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H
