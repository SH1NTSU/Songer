#include "../headers/sidebar_section.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

QFrame* createSidebar(QWidget *parent) {
    QFrame *sidebar = new QFrame(parent);
    sidebar->setStyleSheet(
        "QFrame {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"
        "QLabel {"
        "   padding: 10px;"
        "   font-weight: bold;"
        "}"
        "QListWidget {"
        "   background-color: #0f0526;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 5px;"
        "}"
        "QListWidget::item {"
        "   padding: 5px;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #2D4F8B;"
        "}"
    );
    
    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(10, 10, 10, 10);
    sidebarLayout->setSpacing(10);
    
    // Sidebar title
    QLabel *sidebarTitle = new QLabel("Playlists");
    sidebarLayout->addWidget(sidebarTitle);
    
    // Playlist list
    QListWidget *playlistWidget = new QListWidget;
    playlistWidget->addItems({"Favorites", "Recently Played", "Workout Mix", "Chill Vibes"});
    sidebarLayout->addWidget(playlistWidget);
    
    // Add playlist button
    QPushButton *addPlaylistButton = new QPushButton("+ Add Playlist");
    addPlaylistButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #1a0940;"
        "   border: 1px solid #3A5F8E;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2D4F8B;"
        "}"
    );
    sidebarLayout->addWidget(addPlaylistButton);
    
    sidebarLayout->addStretch();
    
    // Set fixed width
    sidebar->setFixedWidth(parent->width() * 0.15);
    
    return sidebar;
}