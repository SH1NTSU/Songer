#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QPixmap>
#include <QFileDialog>
#include <QWidget>
#include "../headers/musicplayer.h"

QWidget* createMusicPlayer(QWidget *parent) {
    QWidget *container = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(container);

    // Image
    QLabel *coverImage = new QLabel;
    coverImage->setPixmap(QPixmap("../assets/musicLogo.png").scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(coverImage, 0, Qt::AlignHCenter);

    // Time label
    QLabel *timeLabel = new QLabel("00:00");
    timeLabel->setStyleSheet("color: white; font-size: 16px;");
    layout->addWidget(timeLabel, 0, Qt::AlignHCenter);

    // Create player
    QMediaPlayer *player = new QMediaPlayer(container);
    player->setMedia(QUrl::fromLocalFile("../songs/RatherLie.mp3"));
    player->setVolume(50);
    player->play();

    // Timer to update time
    QTimer *timer = new QTimer(container);
    QObject::connect(timer, &QTimer::timeout, [=]() {
        int ms = player->position();
        int secs = ms / 1000;
        int minutes = secs / 60;
        secs = secs % 60;
        timeLabel->setText(QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(secs, 2, 10, QChar('0')));
    });
    timer->start(1000);

    return container;
}
void connectPlayButton(QPushButton *button, QMediaPlayer *player) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        player->play();
    });
}

void connectPauseButton(QPushButton *button, QMediaPlayer *player) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        player->pause();
    });
}

void connectPrevButton(QPushButton *button, QMediaPlayer *player) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        player->setPosition(0);  // Go to beginning
    });
}

void connectNextButton(QPushButton *button, QMediaPlayer *player) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        player->setPosition(player->duration());  // Skip to end
    });
}