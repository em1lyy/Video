#include <iostream>
#include "mainwindow.h"
#include "video-common-dbus.h"
#include <QApplication>
#include <QIcon>
#include <QString>
#include <QLockFile>
#include <QDir>
#include <QtDBus/QtDBus>
#include <QMessageBox>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(":/" + locale);
    a.installTranslator(&translator);
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, QObject::tr("Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`").toStdString().c_str());
        QMessageBox::critical(NULL, "Video", QObject::tr("Cannot connect to the D-Bus session bus.\nTo start it, run:\n\teval `dbus-launch --auto-syntax`"), QMessageBox::Ok);
        return 1;
    }
    QString tmpDir = QDir::tempPath();
    QLockFile lockFile(tmpDir + "/jagudev-video.lock");
    if (lockFile.tryLock(50))
    {
        if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
            fprintf(stderr, "%s\n",
                    qPrintable(QDBusConnection::sessionBus().lastError().message()));
            QMessageBox::critical(NULL, "Video", QObject::tr("Could not register service to D-Bus session bus."), QMessageBox::Ok);
            exit(1);
        }
        if (argc == 2)
        {
            std::string path(argv[1]);
            MainWindow *w = new MainWindow(0, path);
            w->setWindowIcon(QIcon::fromTheme("video"));
            QDBusConnection::sessionBus().registerObject("/", w, QDBusConnection::ExportAllSlots);
            w->show();
        }
        else if (argc >= 2)
        {
            std::cout << "ARGUMENT LENGTH MUST BE 0 OR 1!\n EXITING!" << endl;
            return 1;
        }
        else
        {
            MainWindow *w = new MainWindow(0, "");
            w->setWindowIcon(QIcon::fromTheme("video"));
            QDBusConnection::sessionBus().registerObject("/", w, QDBusConnection::ExportAllSlots);
            w->show();
        }
    }
    else
    {
        if (argc == 2)
        {
            QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::sessionBus());
            if (iface.isValid()) {
                iface.call("loadVideoFromFileAndPlayIt", argv[1]);
            } else {
                QMessageBox::critical(NULL, "Video", QObject::tr("Interface invalid."), QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::critical(NULL, "Video", QObject::tr("An instance of Video is already running!"), QMessageBox::Ok);
        }
        return 0;
    }
    return a.exec();
}
