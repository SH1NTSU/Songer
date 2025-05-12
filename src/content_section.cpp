#include "../headers/content_section.h"
#include "../headers/footer_section.h"
#include "../headers/sidebar_section.h"
#include "../headers/musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

QLayout* createContentSection(QWidget *parent) {
    QHBoxLayout *mainContentLayout = new QHBoxLayout;
    mainContentLayout->setSpacing(10);
    mainContentLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *musicPlayerWidget = createMusicPlayer(parent);
    QMediaPlayer *player = musicPlayerWidget->findChild<QMediaPlayer*>();
    QLabel *coverImageLabel = musicPlayerWidget->findChild<QLabel*>("coverImage");

    QWidget *leftContainer = new QWidget;
    QVBoxLayout *leftContainerLayout = new QVBoxLayout(leftContainer);
    leftContainerLayout->setSpacing(10);
    leftContainerLayout->setContentsMargins(0, 0, 0, 0);

    // Content area
    QFrame *contentFrame = new QFrame;
    contentFrame->setStyleSheet(
        "QFrame {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"
    );
    QVBoxLayout *contentLayout = new QVBoxLayout(contentFrame);
    contentLayout->setSpacing(8);
    contentLayout->setContentsMargins(10, 10, 10, 10);

    // Control buttons container
    QFrame *controls = new QFrame;
    controls->setStyleSheet("color: white;");
    controls->setFixedSize(250,80);
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->setSpacing(10);

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

    QPushButton *prevBtn = new QPushButton(QString::fromUtf8("\u23EE"));
    QPushButton *pauseBtn = new QPushButton(QString::fromUtf8("\u23F8"));
    QPushButton *playBtn = new QPushButton(QString::fromUtf8("\u25B6"));
    QPushButton *nextBtn = new QPushButton(QString::fromUtf8("\u23ED"));
    QPushButton *loopBtn = new QPushButton(QString::fromUtf8("\U0001F501"));
    QPushButton *shuffleBtn = new QPushButton(QString::fromUtf8("\xF0\x9F\x94\x80"));
    QList<QPushButton*> buttons = { prevBtn, pauseBtn, playBtn, nextBtn, shuffleBtn, loopBtn };
    for (QPushButton* btn : buttons) {
        btn->setStyleSheet(buttonStyle);
        controlsLayout->addWidget(btn);
    }

    connectPlayButton(playBtn, player);
    connectPauseButton(pauseBtn, player);
    connectPrevButton(prevBtn, player, coverImageLabel);
    connectNextButton(nextBtn, player, coverImageLabel);
    shuffleButton(shuffleBtn, player, coverImageLabel);
    loopButton(loopBtn, player, coverImageLabel);

    controls->setLayout(controlsLayout);
    contentLayout->addWidget(controls);
    contentLayout->addWidget(musicPlayerWidget);  // Use the existing widget instead of creating new one

    leftContainerLayout->addWidget(contentFrame, 8);
    leftContainerLayout->addWidget(createFooterSection(parent, player), 2);

    mainContentLayout->addWidget(leftContainer, 1);
    mainContentLayout->addWidget(createSidebar(parent));

    return mainContentLayout;
}
