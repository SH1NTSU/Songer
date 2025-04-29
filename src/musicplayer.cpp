#include <QMediaPlayer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QPixmap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "../headers/musicplayer.h"

// Global variables to track current song and song list
int currentSongIndex = 0;
QList<QJsonObject> songsList;

// Function to load songs from JSON
void loadSongsList() {
    QFile file("../assets/songs.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open songs.json");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const QJsonValue &value : array) {
        songsList.append(value.toObject());
    }
}

// Function to play a specific song by index
void playSong(QMediaPlayer *player, int index) {
    if (index < 0 || index >= songsList.size()) return;

    currentSongIndex = index;
    QJsonObject song = songsList.at(index);
    QString filePath = song["path"].toString();
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->play();
}

QWidget* createMusicPlayer(QWidget *parent) {
    // Load songs data
    loadSongsList();

    QWidget *container = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(container);

    // Image
    QLabel *coverImage = new QLabel;
    coverImage->setPixmap(QPixmap("../assets/musicLogo.png").scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(coverImage, 0, Qt::AlignHCenter);

    // Song info label
    QLabel *songInfoLabel = new QLabel;
    layout->addWidget(songInfoLabel, 0, Qt::AlignHCenter);

    // Time label
    QLabel *timeLabel = new QLabel("00:00");
    layout->addWidget(timeLabel, 0, Qt::AlignHCenter);

    // Create player
    QMediaPlayer *player = new QMediaPlayer(container);

    // Play first song
    if (!songsList.isEmpty()) {
        playSong(player, 0);

        // Update song info
        QJsonObject currentSong = songsList.at(0);
        songInfoLabel->setText(currentSong["name"].toString() + " - " + currentSong["artist"].toString());
    }

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

void connectPrevButton(QPushButton *button, QMediaPlayer *player, QLabel *songInfoLabel) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        int newIndex = currentSongIndex - 1;
        if (newIndex < 0) newIndex = songsList.size() - 1; // Wrap around to last song

        playSong(player, newIndex);

        // Update song info
        QJsonObject currentSong = songsList.at(newIndex);
        songInfoLabel->setText(currentSong["name"].toString() + " - " + currentSong["artist"].toString());
    });
}

void connectNextButton(QPushButton *button, QMediaPlayer *player, QLabel *songInfoLabel) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        int newIndex = currentSongIndex + 1;
        if (newIndex >= songsList.size()) newIndex = 0; // Wrap around to first song

        playSong(player, newIndex);

        // Update song info
        QJsonObject currentSong = songsList.at(newIndex);
        songInfoLabel->setText(currentSong["name"].toString() + " - " + currentSong["artist"].toString());
    });
}
