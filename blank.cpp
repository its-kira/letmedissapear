#include <iostream>
#include <Windows.h>
#include <string>
#include <regex>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtGui/QDesktopWidget>

using namespace std;

class MainWindow : public QWidget {
public:
    MainWindow() {
        setWindowTitle("Privacy Tools");

        // Create buttons for each task
        QPushButton* clearChromeCookiesButton = new QPushButton("Clear Chrome Cookies");
        connect(clearChromeCookiesButton, &QPushButton::clicked, [this] {
            clearChromeCookies();
        });

        QPushButton* clearBraveCookiesButton = new QPushButton("Clear Brave Cookies");
        connect(clearBraveCookiesButton, &QPushButton::clicked, [this] {
            clearBraveCookies();
        });

        QPushButton* clearFirefoxCookiesButton = new QPushButton("Clear Firefox Cookies");
        connect(clearFirefoxCookiesButton, &QPushButton::clicked, [this] {
            clearFirefoxCookies();
        });

        QPushButton* clearSafariCookiesButton = new QPushButton("Clear Safari Cookies");
        connect(clearSafariCookiesButton, &QPushButton::clicked, [this] {
            clearSafariCookies();
        });

        QPushButton* clearTrackersButton = new QPushButton("Clear Trackers");
        connect(clearTrackersButton, &QPushButton::clicked, [this] {
            clearTrackers();
        });

        QPushButton* clearTempFilesButton = new QPushButton("Clear Temp Files");
        connect(clearTempFilesButton, &QPushButton::clicked, [this] {
            clearTempFiles();
        });

        QPushButton* changeMacAddressButton = new QPushButton("Change MAC Address");
        connect(changeMacAddressButton, &QPushButton::clicked, [this] {
            changeMacAddress();
        });

        // Create labels for each button
        QLabel* clearChromeCookiesLabel = new QLabel("Clears cookies from Chrome");
        QLabel* clearBraveCookiesLabel = new QLabel("Clears cookies from Brave");
        QLabel* clearFirefoxCookiesLabel = new QLabel("Clears cookies from Firefox");
        QLabel* clearSafariCookiesLabel = new QLabel("Clears cookies from Safari");
        QLabel* clearTrackersLabel = new QLabel("Clears all trackers stored on the system");
        QLabel* clearTempFilesLabel = new QLabel("Clears all temporary files on the system");
        QLabel* changeMacAddressLabel = new QLabel("Changes the MAC address of the network adapter");

        // Layout the buttons and labels
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(clearChromeCookiesButton);
        layout->addWidget(clearChromeCookiesLabel);
        layout->addWidget(clearBraveCookiesButton);
        layout->addWidget(clearBraveCookiesLabel);
        layout->addWidget(clearFirefoxCookiesButton);
        layout->addWidget(clearFirefoxCookiesLabel);
        layout->addWidget(clearSafariCookiesButton);
        layout->addWidget(clearSafariCookiesLabel);
        layout->addWidget(clearTrackersButton);
        layout->addWidget(clearTrackersLabel);
        layout->addWidget(clearTempFilesButton);
        layout->addWidget(clearTempFilesLabel);
        layout->addWidget(changeMacAddressButton);
        layout->addWidget(changeMacAddressLabel);

        setLayout(layout);

        // Center the window on the desktop
        QDesktopWidget* desktop = QApplication::desktop();
        QRect screen = desktop->availableGeometry();
        setGeometry((screen.width() - width()) / 2, (screen.height() - height()) / 2, width(), height());
    }

   // Function to clear cookies from Chrome
void clearChromeCookies() {
    system("RunDll32.exe Inetcpl.cpl,ClearMyTracksByProcess 8");
}

// Function to clear cookies from Brave
void clearBraveCookies() {
    string command = "brave://settings/privacy";
    system(command.c_str());

    cout << "Opening Brave settings..." << endl;
    system("start brave://settings/privacy");

    cout << "Clearing cookies..." << endl;
    system("RunDll32.exe Inetcpl.cpl,ClearMyTracksByProcess 8");
}

// Function to clear cookies from Firefox
void clearFirefoxCookies() {
    system("firefox -privacy");
}

// Function to clear cookies from Safari
void clearSafariCookies() {
    system("open -a Safari Preferences");

    cout << "Clearing cookies..." << endl;
    system("RunDll32.exe Inetcpl.cpl,ClearMyTracksByProcess 8");
}

// Function to clear all trackers
void clearTrackers() {
    string command = "cmd /c \"for /f \"delims=\" %%a in ('REG QUERY \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Group Policy\\History\" /v Run\") do del /q \"%%a\"";
    system(command.c_str());

    cout << "Clearing all trackers..." << endl;
    system("RunDll32.exe Inetcpl.cpl,ClearMyTracksByProcess 8");
}

// Function to clear all temp files on the system
void clearTempFiles() {
    string command = "del /Q /F /S %TEMP% /A:H /AH";
    system(command.c_str());
}

// Function to change the MAC address
void changeMacAddress() {
#ifdef _WIN32
    // On Windows, use the netsh command to change the MAC address
    string command = "netsh interface ip set address name=\"Ethernet\" static 00-11-22-33-44-55";
    system(command.c_str());
#elif __APPLE__
    // On Mac, use the ifconfig command to change the MAC address
    string command = "sudo ifconfig en0 ether 00:11:22:33:44:55";
    system(command.c_str());
#endif
}
