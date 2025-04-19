#include "../headers/content_section.h"
#include "../headers/footer_section.h"
#include "../headers/sidebar_section.h"
#include "../headers/musicplayer.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>




QLayout* createContentSection(QWidget *parent) {
    QHBoxLayout *mainContentLayout = new QHBoxLayout;
    mainContentLayout->setSpacing(10);
    mainContentLayout->setContentsMargins(0, 0, 0, 0);


    QWidget *musicPlayerWidget = createMusicPlayer(parent);
    QMediaPlayer *player = musicPlayerWidget->findChild<QMediaPlayer*>();


    // Left Section with footer
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
    QHBoxLayout *controlsLayout = new QHBoxLayout; // horizontal layout
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

    QPushButton *prevBtn    = new QPushButton(QString::fromUtf8("\u23EE"));   // ⏮️
    QPushButton *pauseBtn   = new QPushButton(QString::fromUtf8("\u23F8"));   // ⏸️
    QPushButton *playBtn    = new QPushButton(QString::fromUtf8("\u25B6"));   // ▶️
    QPushButton *nextBtn    = new QPushButton(QString::fromUtf8("\u23ED"));   // ⏭️


    QList<QPushButton*> buttons = { prevBtn, pauseBtn, playBtn,nextBtn };
    for (QPushButton* btn : buttons) {
        btn->setStyleSheet(buttonStyle);
        controlsLayout->addWidget(btn);
    }
    connectPlayButton(playBtn, player);
    connectPauseButton(pauseBtn, player);
    connectPrevButton(prevBtn, player);
    connectNextButton(nextBtn, player);

    
    controls->setLayout(controlsLayout);
    contentLayout->addWidget(controls);
    contentLayout->addWidget(createMusicPlayer(parent));

    // Add main content to layout
    leftContainerLayout->addWidget(contentFrame, 8);
    leftContainerLayout->addWidget(createFooterSection(parent), 2);

    mainContentLayout->addWidget(leftContainer, 1);
    mainContentLayout->addWidget(createSidebar(parent));


    return mainContentLayout;
}
