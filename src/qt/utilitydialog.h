<<<<<<< HEAD
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
=======
// Copyright (c) 2011-2020 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_QT_UTILITYDIALOG_H
#define DIGIBYTE_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QWidget>

<<<<<<< HEAD
class DigiByteGUI;

namespace interfaces {
    class Node;
}
=======
QT_BEGIN_NAMESPACE
class QMainWindow;
QT_END_NAMESPACE
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget *parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static QWidget *showShutdownWindow(DigiByteGUI *window);
=======
    explicit ShutdownWindow(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::Widget);
    static QWidget* showShutdownWindow(QMainWindow* window);
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // DIGIBYTE_QT_UTILITYDIALOG_H
