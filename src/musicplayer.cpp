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
#include <cstdlib>
#include <iostream>
#include "../headers/musicplayer.h"
#include <taglib/fileref.h>
#include <taglib/audioproperties.h>


// Global variables
int currentSongIndex = 0;
QList<QJsonObject> songsList;
void (*updateFooterCallback)() = nullptr;  // Callback function pointer

// Function to set the callback
void setUpdateFooterCallback(void (*callback)()) {
    updateFooterCallback = callback;
}

void updateAudioProperties(const QString &filePath, QLabel *mixrateLabel, QLabel *bitrateLabel) {
    TagLib::FileRef f(filePath.toUtf8().constData());
    if (!f.isNull() && f.audioProperties()) {
        TagLib::AudioProperties *properties = f.audioProperties();
        int bitrate = properties->bitrate();       // kbps
        int sampleRate = properties->sampleRate(); // Hz

        // Update the labels directly
        bitrateLabel->setText(QString("Bitrate: %1 kbps").arg(bitrate));
        mixrateLabel->setText(QString("Mixrate: %1 Hz").arg(sampleRate));
    } else {
        bitrateLabel->setText("Bitrate: N/A");
        mixrateLabel->setText("MixRate:N/A");
    }
}

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

void playSong(QMediaPlayer *player, int index, QLabel *coverImage = nullptr) {
    if (index < 0 || index >= songsList.size()) return;

    currentSongIndex = index;
    QJsonObject song = songsList.at(index);
    QString filePath = song["path"].toString();
    player->setMedia(QUrl::fromLocalFile(filePath));
    player->play();

    if (coverImage && song.contains("image")) {
        QString imagePath = song["image"].toString();
        QPixmap pix(imagePath);
        if (!pix.isNull()) {
            coverImage->setPixmap(pix.scaled(200, 200, Qt::KeepAspectRatio));
        } else {
            qWarning() << "Failed to load image:" << imagePath;
        }
    }

    // Call the footer update callback if it exists
    if (updateFooterCallback) {
        updateFooterCallback();
    }
}


QWidget* createMusicPlayer(QWidget *parent) {
    // Load songs data
    loadSongsList();

    QWidget *container = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(container);

    // Create labels for audio properties
    QLabel *mixrateLabel = new QLabel("Sample Rate: N/A | Channels: N/A");
    QLabel *bitrateLabel = new QLabel("Bitrate: N/A");

    // Image
    QLabel *coverImage = new QLabel;
    coverImage->setPixmap(QPixmap("../assets/musicLogo.png").scaled(200, 200, Qt::KeepAspectRatio));
    layout->addWidget(coverImage, 0, Qt::AlignHCenter);
    coverImage->setObjectName("coverImage");

    // Time label
    QLabel *timeLabel = new QLabel("00:00");
    layout->addWidget(timeLabel, 0, Qt::AlignHCenter);

    // Add audio properties labels to layout
    layout->addWidget(bitrateLabel, 0, Qt::AlignHCenter);
    layout->addWidget(mixrateLabel, 0, Qt::AlignHCenter);

    // Create player
    QMediaPlayer *player = new QMediaPlayer(container);

    // Lambda function to handle song changes
    auto updateSongInfo = [=](int index) {
        if (index < 0 || index >= songsList.size()) return;

        QJsonObject song = songsList.at(index);
        QString filePath = song["path"].toString();

        // Update audio properties labels
        updateAudioProperties(filePath, mixrateLabel, bitrateLabel);

        // Update cover image if needed
        if (song.contains("image")) {
            QString imagePath = song["image"].toString();
            QPixmap pix(imagePath);
            if (!pix.isNull()) {
                coverImage->setPixmap(pix.scaled(200, 200, Qt::KeepAspectRatio));
            }
        }
    };

    // Connect media status changed to update info when song loads
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia) {
            updateSongInfo(currentSongIndex);
        }
    });

    // Play first song if available
    if (!songsList.isEmpty()) {
        playSong(player, 0, coverImage);
        updateSongInfo(0);
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

void connectNextButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        int newIndex = currentSongIndex + 1;
        if (newIndex >= songsList.size()) newIndex = 0;

        playSong(player, newIndex, coverImage);
    });
}

void connectPrevButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        int newIndex = currentSongIndex - 1;
        if (newIndex < 0) newIndex = songsList.size() - 1;

        playSong(player, newIndex, coverImage);
    });
}
void startButton(QPushButton *button, QMediaPlayer *player) {
    QObject::connect(button, &QPushButton::clicked, [=]() {
        player->setPosition(0);
    });
}

void loopButton(QPushButton *button, QMediaPlayer *player) {
    static bool looping = false;

    QObject::connect(button, &QPushButton::clicked, [=]() mutable {
        looping = !looping;
        button->setText(looping ? "🔁" : "➡️");

        // Disconnect any previous connections

        if (looping) {
            QObject::connect(player, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
                if (status == QMediaPlayer::EndOfMedia) {
                    player->setPosition(0);
                    player->play();
                }
            });
        }
    });
}


void shuffleButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage) {

    QObject::connect(button, &QPushButton::clicked, [=]() {
        srand(time(0));
        int value = rand() % songsList.size();
        int newIndex  = value;
        playSong(player, newIndex, coverImage);
    });
}
