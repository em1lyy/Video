#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QTimer>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool playing;
    bool fullscreen;
    int secsTillHide;
    QTimer *timer;
    QMediaPlayer *player;
    void togglePlayingState();
    void toggleFullscreen();
    void updateMetaData();
    void seekForward();
    void seekBackward();
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void increaseVolume();
    void decreaseVolume();
    void mouseMoveEvent(QMouseEvent *event);
    void tickDown();
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    explicit MainWindow(QWidget *parent = 0, std::string path = "");
    ~MainWindow();

public slots:
    void loadVideoFromFileAndPlayIt(QString filename);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
