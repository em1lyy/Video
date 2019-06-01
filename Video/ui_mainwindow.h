/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QVideoWidget>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *bgWidget;
    QVideoWidget *videoWidget;
    QPushButton *fullscreenButton;
    QPushButton *playPauseButton;
    QSlider *positionSlider;
    QSlider *volumeSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(854, 480);
        MainWindow->setWindowTitle(QString::fromUtf8("Video"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("video");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        bgWidget = new QWidget(centralwidget);
        bgWidget->setObjectName(QString::fromUtf8("bgWidget"));
        bgWidget->setEnabled(true);
        bgWidget->setGeometry(QRect(0, 400, 854, 80));
        bgWidget->setAutoFillBackground(true);
        videoWidget = new QVideoWidget(centralwidget);
        videoWidget->setObjectName(QString::fromUtf8("videoWidget"));
        videoWidget->setEnabled(true);
        videoWidget->setGeometry(QRect(0, 0, 854, 480));
        fullscreenButton = new QPushButton(centralwidget);
        fullscreenButton->setObjectName(QString::fromUtf8("fullscreenButton"));
        fullscreenButton->setGeometry(QRect(36, 438, 32, 32));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fullscreenButton->sizePolicy().hasHeightForWidth());
        fullscreenButton->setSizePolicy(sizePolicy);
        fullscreenButton->setAutoFillBackground(true);
        fullscreenButton->setText(QString::fromUtf8(""));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("view-fullscreen");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        fullscreenButton->setIcon(icon1);
        playPauseButton = new QPushButton(centralwidget);
        playPauseButton->setObjectName(QString::fromUtf8("playPauseButton"));
        playPauseButton->setGeometry(QRect(2, 438, 32, 32));
        sizePolicy.setHeightForWidth(playPauseButton->sizePolicy().hasHeightForWidth());
        playPauseButton->setSizePolicy(sizePolicy);
        playPauseButton->setAutoFillBackground(true);
        playPauseButton->setText(QString::fromUtf8(""));
        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("media-playback-pause")));
        playPauseButton->setIcon(icon2);
        positionSlider = new QSlider(centralwidget);
        positionSlider->setObjectName(QString::fromUtf8("positionSlider"));
        positionSlider->setGeometry(QRect(2, 411, 852, 20));
        positionSlider->setAutoFillBackground(true);
        positionSlider->setOrientation(Qt::Horizontal);
        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setGeometry(QRect(70, 444, 84, 20));
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setAutoFillBackground(true);
        volumeSlider->setMaximum(100);
        volumeSlider->setPageStep(5);
        volumeSlider->setValue(100);
        volumeSlider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        videoWidget->raise();
        bgWidget->raise();
        fullscreenButton->raise();
        playPauseButton->raise();
        positionSlider->raise();
        volumeSlider->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
