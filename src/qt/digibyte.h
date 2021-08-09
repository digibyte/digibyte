// Copyright (c) 2011-2020 The DigiByte Core developers
// Copyright (c) 2013-2021 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_QT_DIGIBYTE_H
#define DIGIBYTE_QT_DIGIBYTE_H

#if defined(HAVE_CONFIG_H)
#include <config/digibyte-config.h>
#endif

#include <interfaces/node.h>
#include <qt/initexecutor.h>

#include <assert.h>
#include <memory>
#include <optional>

#include <QApplication>

class DigiByteGUI;
class ClientModel;
class NetworkStyle;
class OptionsModel;
class PaymentServer;
class PlatformStyle;
class SplashScreen;
class WalletController;
class WalletModel;


/** Main DigiByte application object */
class DigiByteApplication: public QApplication
{
    Q_OBJECT
public:
    explicit DigiByteApplication();
    ~DigiByteApplication();

#ifdef ENABLE_WALLET
    /// Create payment server
    void createPaymentServer();
#endif
    /// parameter interaction/setup based on rules
    void parameterSetup();
    /// Create options model
    void createOptionsModel(bool resetSettings);
    /// Initialize prune setting
    void InitPruneSetting(int64_t prune_MiB);
    /// Create main window
    void createWindow(const NetworkStyle *networkStyle);
    /// Create splash screen
    void createSplashScreen(const NetworkStyle *networkStyle);
    /// Basic initialization, before starting initialization/shutdown thread. Return true on success.
    bool baseInitialize();

    /// Request core initialization
    void requestInitialize();
    /// Request core shutdown
    void requestShutdown();

    /// Get process return value
    int getReturnValue() const { return returnValue; }

    /// Get window identifier of QMainWindow (DigiByteGUI)
    WId getMainWinId() const;

    /// Setup platform style
    void setupPlatformStyle();

    interfaces::Node& node() const { assert(m_node); return *m_node; }
    void setNode(interfaces::Node& node);

public Q_SLOTS:
    void initializeResult(bool success, interfaces::BlockAndHeaderTipInfo tip_info);
    void shutdownResult();
    /// Handle runaway exceptions. Shows a message box with the problem and quits the program.
    void handleRunawayException(const QString &message);

    /**
     * A helper function that shows a message box
     * with details about a non-fatal exception.
     */
    void handleNonFatalException(const QString& message);

Q_SIGNALS:
    void requestedInitialize();
    void requestedShutdown();
    void splashFinished();
    void windowShown(DigiByteGUI* window);

private:
    std::optional<InitExecutor> m_executor;
    OptionsModel *optionsModel;
    ClientModel *clientModel;
    DigiByteGUI *window;
    QTimer *pollShutdownTimer;
#ifdef ENABLE_WALLET
    PaymentServer* paymentServer{nullptr};
    WalletController* m_wallet_controller{nullptr};
#endif
    int returnValue;
    const PlatformStyle *platformStyle;
    std::unique_ptr<QWidget> shutdownWindow;
    SplashScreen* m_splash = nullptr;
    interfaces::Node* m_node = nullptr;

    void startThread();
};

int GuiMain(int argc, char* argv[]);

#endif // DIGIBYTE_QT_DIGIBYTE_H