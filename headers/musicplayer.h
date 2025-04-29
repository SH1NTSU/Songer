#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>

QWidget* createMusicPlayer(QWidget *parent = nullptr);
void connectPlayButton(QPushButton *button, QMediaPlayer *player);
void connectPauseButton(QPushButton *button, QMediaPlayer *player);
void connectPrevButton(QPushButton *button, QMediaPlayer *player, QLabel *songInfoLabel);
void connectNextButton(QPushButton *button, QMediaPlayer *player, QLabel *songInfoLabel);

#endif // MUSICPLAYER_H
