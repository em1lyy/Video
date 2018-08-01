#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMultimedia>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QSize>
#include <QTimer>
#include <QShortcut>
#include <QFileDialog>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent, std::string path) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    this->timer = new QTimer(this);
    this->secsTillHide = 3;
    connect(this->timer, &QTimer::timeout, this, &MainWindow::tickDown);
    this->timer->start(1000);

    this->playing = true;
    this->fullscreen = false;

    ui->setupUi(this);

    this->setMouseTracking(true);
    this->ui->centralwidget->setMouseTracking(true);
    this->ui->videoWidget->setMouseTracking(true);
    this->ui->bgWidget->setMouseTracking(true);
    this->ui->playPauseButton->setMouseTracking(true);
    this->ui->volumeSlider->setMouseTracking(true);
    this->ui->fullscreenButton->setMouseTracking(true);
    this->ui->positionSlider->setMouseTracking(true);

    this->player = new QMediaPlayer(this);

    this->player->setVideoOutput(this->ui->videoWidget);

    this->player->setVolume(100);

    connect(this->player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(this->player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(this->ui->positionSlider, &QAbstractSlider::valueChanged, this, &MainWindow::setPosition);
    connect(this->ui->volumeSlider, &QSlider::valueChanged, this->player, &QMediaPlayer::setVolume);
    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &MainWindow::togglePlayingState);
    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &MainWindow::seekForward);
    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &MainWindow::seekBackward);
    QShortcut *increaseShortcut = new QShortcut(Qt::Key_Up, this);
    connect(increaseShortcut, &QShortcut::activated, this, &MainWindow::increaseVolume);
    QShortcut *decreaseShortcut = new QShortcut(Qt::Key_Down, this);
    connect(decreaseShortcut, &QShortcut::activated, this, &MainWindow::decreaseVolume);
    QShortcut *fullscreenShortcut = new QShortcut(Qt::Key_F11, this);
    connect(fullscreenShortcut, &QShortcut::activated, this, &MainWindow::toggleFullscreen);

    std::string fpath = path;
    if (strcmp(fpath.c_str(), "") == 0)
    {
        QString file = QFileDialog::getOpenFileName(this, tr("Open video"), QString(), "*.mp4, *.wmv, *.flv, *.mkv");
        fpath = file.toStdString();
    }

    this->player->setMedia(QUrl::fromLocalFile(QString::fromStdString(fpath)));
    connect(this->player, &QMediaPlayer::metaDataAvailableChanged, this, &MainWindow::updateMetaData);
    this->player->play();
    connect(this->ui->playPauseButton, &QPushButton::clicked, this, &MainWindow::togglePlayingState);
    connect(this->ui->fullscreenButton, &QPushButton::clicked, this, &MainWindow::toggleFullscreen);
}

void MainWindow::togglePlayingState()
{
    if (playing)
    {
        player->pause();
        ui->playPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
        playing = false;
    }
    else
    {
        player->play();
        ui->playPauseButton->setIcon(QIcon::fromTheme("media-playback-pause"));
        playing = true;
    }
}

void MainWindow::toggleFullscreen()
{
    if (fullscreen)
    {
        this->showNormal();
        ui->fullscreenButton->setIcon(QIcon::fromTheme("view-fullscreen"));
        fullscreen = false;
    }
    else
    {
        this->showFullScreen();
        ui->fullscreenButton->setIcon(QIcon::fromTheme("view-restore"));
        fullscreen = true;
    }
}

void MainWindow::updateMetaData()
{
    if (this->player->isMetaDataAvailable())
    {
        QSize res = this->player->metaData(QMediaMetaData::Resolution).value<QSize>();
        if (res.width() > 0 && res.height() > 0)
        {
            this->setFixedSize(res.width(), res.height());
        }
    }
}

void MainWindow::seekForward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::seekBackward()
{
    ui->positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void MainWindow::updateDuration(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
    ui->positionSlider->setEnabled(duration > 0);
    ui->positionSlider->setPageStep(duration / 10);
}

void MainWindow::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(player->position() - position) > 99)
    {
        qDebug("Setting position!");
        player->setPosition(position);
    }
}

void MainWindow::increaseVolume()
{
    ui->volumeSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::decreaseVolume()
{
    ui->volumeSlider->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->secsTillHide = 3;
    this->ui->bgWidget->setVisible(true);
    this->ui->playPauseButton->setVisible(true);
    this->ui->fullscreenButton->setVisible(true);
    this->ui->positionSlider->setVisible(true);
    this->ui->volumeSlider->setVisible(true);
    this->ui->videoWidget->setCursor(Qt::ArrowCursor);
}

void MainWindow::tickDown()
{
    this->secsTillHide--;

    if (this->secsTillHide == 0)
    {
        this->ui->bgWidget->setVisible(false);
        this->ui->playPauseButton->setVisible(false);
        this->ui->fullscreenButton->setVisible(false);
        this->ui->positionSlider->setVisible(false);
        this->ui->volumeSlider->setVisible(false);
        this->ui->videoWidget->setCursor(Qt::BlankCursor);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->ui->videoWidget->setGeometry(0, 0, this->geometry().width(), this->geometry().height());
    this->ui->bgWidget->setGeometry(0, this->geometry().height() - 80, this->geometry().width(), 80);
    this->ui->positionSlider->setGeometry(2, this->geometry().height() - 69, this->geometry(). width() - 4, 20);
    this->ui->volumeSlider->setGeometry(70, this->geometry().height() - 36, 84, 20);
    this->ui->playPauseButton->setGeometry(2, this->geometry().height() - 42, 32, 32);
    this->ui->fullscreenButton->setGeometry(36, this->geometry().height() - 42, 32, 32);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    delete this;
}

MainWindow::~MainWindow()
{
    delete ui;
}
