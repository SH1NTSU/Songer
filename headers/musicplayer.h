#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>

extern int currentSongIndex;
extern QList<QJsonObject> songsList;
extern void (*updateFooterCallback)();  // Declare callback function pointer

QWidget* createMusicPlayer(QWidget *parent = nullptr);
void connectPlayButton(QPushButton *button, QMediaPlayer *player);
void connectPauseButton(QPushButton *button, QMediaPlayer *player);
void connectPrevButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage);
void connectNextButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage);
void shuffleButton(QPushButton *button, QMediaPlayer *player, QLabel *coverImage);
void loopButton(QPushButton *button, QMediaPlayer *player);
void startButton(QPushButton *button, QMediaPlayer *player);
void setUpdateFooterCallback(void (*callback)());  // Function to set the callback

#endif // MUSICPLAYER_H
