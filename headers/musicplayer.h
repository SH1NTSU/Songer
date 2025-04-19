#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>

// Function to create the music player widget
QWidget* createMusicPlayer(QWidget *parent = nullptr);

// Functions to connect player controls
void connectPlayButton(QPushButton *button, QMediaPlayer *player);
void connectPauseButton(QPushButton *button, QMediaPlayer *player);
void connectPrevButton(QPushButton *button, QMediaPlayer *player);
void connectNextButton(QPushButton *button, QMediaPlayer *player);

#endif // MUSICPLAYER_H