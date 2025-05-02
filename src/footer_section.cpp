#include "../headers/footer_section.h"
#include "../headers/musicplayer.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QJsonObject>
#include <QDebug>
#include <QMediaPlayer>
#include <iostream>

// Forward declarations
extern int currentSongIndex;
extern QList<QJsonObject> songsList;

// Global footer widgets
static QLabel *songNameLabel = nullptr;
static QLabel *artistLabel = nullptr;
static QLabel *durationLabel = nullptr;

// Function to update footer labels
void updateFooter() {
    if (!songsList.isEmpty() && currentSongIndex >= 0 && currentSongIndex < songsList.size()) {
        const QJsonObject &song = songsList.at(currentSongIndex);
        if (songNameLabel) songNameLabel->setText(song["name"].toString());
        if (artistLabel) artistLabel->setText(song["artist"].toString());
        if (durationLabel) durationLabel->setText(song["time"].toString());
    }
}

QFrame* createFooterSection(QWidget *parent ,QMediaPlayer *player) {
    QFrame *footer = new QFrame(parent);
    footer->setStyleSheet(
        "QFrame {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"
    );
    footer->setFixedHeight(140);

    QHBoxLayout *footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(10, 10, 10, 10);
    footerLayout->setSpacing(40);

    // Slider setup
    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setRange(0, 100);
    volume->setValue(50);
    volume->setFixedWidth(200);
    volume->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #3A5F8E;"
        "    height: 8px;"
        "    background: #1a0940;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background:rgb(197, 219, 7);"
        "    border: 1px solid #3A5F8E;"
        "    width: 18px;"
        "    height: 18px;"
        "    margin: -5px 0;"
        "    border-radius: 9px;"
        "}"
        "QSlider::sub-page:horizontal {"
        "    background: rgb(197, 219, 7);"
        "    border-radius: 4px;"
        "}"
        "QSlider::add-page:horizontal {"
        "    background: #3A5F8E;"
        "    border-radius: 4px;"
        "}"
    );

    QObject::connect(volume, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

    // Buttons
    QString buttonStyle =
        "QPushButton {"
        "   background-color: #1a0940;"
        "   border-radius: 25px;"
        "   padding: 5px 10px;"
        "   max-width:40px;"
        "   min-height:40px;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2D4F8B;"
        "}";

    QFrame *ButtonsBlock = new QFrame;
    ButtonsBlock->setFrameStyle(QFrame::Panel | QFrame::Raised);
    ButtonsBlock->setLineWidth(2);
    ButtonsBlock->setStyleSheet("color: white;");

    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    QPushButton *favorite = new QPushButton("♥️");
    QPushButton *loopBtn = new QPushButton(QString::fromUtf8("\U0001F501"));
    QPushButton *startBtn    = new QPushButton(QString::fromUtf8("\u23F9"));
    QList<QPushButton*> buttons = {favorite, startBtn, loopBtn};

    for (QPushButton *btn : buttons) {
        btn->setFixedSize(40, 40);
        btn->setStyleSheet(buttonStyle);
        ButtonsLayout->addWidget(btn);
    }
    ButtonsBlock->setLayout(ButtonsLayout);

    // Song info labels
    QFrame *textBlock = new QFrame;
        textBlock->setFrameStyle(QFrame::Panel | QFrame::Raised);
        textBlock->setLineWidth(2);
        textBlock->setStyleSheet("color: white;");

        QVBoxLayout *textLayout = new QVBoxLayout;

        // Initialize the global labels
        songNameLabel = new QLabel;
        artistLabel = new QLabel;
        durationLabel = new QLabel;

        // Set initial song info
        updateFooter();

        songNameLabel->setStyleSheet("color: white; font-weight: bold;");
        artistLabel->setStyleSheet("color: white;");
        durationLabel->setStyleSheet("color: white;");

        startButton(startBtn, player);
        loopButton(loopBtn, player);  // Added coverImageLabel

        textLayout->addWidget(songNameLabel);
        textLayout->addWidget(artistLabel);
        textLayout->addWidget(durationLabel);
        textBlock->setLayout(textLayout);

    footerLayout->addWidget(volume);
    footerLayout->addWidget(textBlock);
    footerLayout->addWidget(ButtonsBlock);

    // Store pointers to the labels for later updates
    footer->setProperty("songNameLabel", QVariant::fromValue(songNameLabel));
    footer->setProperty("artistLabel", QVariant::fromValue(artistLabel));
    footer->setProperty("durationLabel", QVariant::fromValue(durationLabel));
    setUpdateFooterCallback(updateFooter);
    return footer;
}
