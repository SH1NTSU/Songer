// #include <QApplication>
// #include <QWidget>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QLabel>
// #include <QPushButton>
// #include <QFrame>
// #include <QPixmap>
// #include <QPainter>
// #include <QDesktopServices>
// #include <QUrl>

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
    
//     // Create main window with rounded corners and background color
//     QWidget window;
//     window.setWindowTitle("Complex Layout Example");
//     window.resize(1000, 800);
//     window.setStyleSheet(
//         "QWidget#mainWindow {"
//         "   background-color: #0f0526;"
//         "   border-radius: 15px;"
//         "   border: 2px solid #1E3F72;"
//         "}"
//     );
//     window.setObjectName("mainWindow");
//     window.setWindowFlags(window.windowFlags() | Qt::FramelessWindowHint);
// 	string playlist = {"./songs/The End - LLow.mp3", "./songs/Travis Scott - MY EYES (Official Audio).mp3", "./songs/Playboi Carti & The Weeknd - RATHER LIE (Official Audio).mp3"}

//     // Main container widget for proper margins
//     QWidget *mainContainer = new QWidget(&window);
    
//     // Main Vertical Layout
//     QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);
//     mainLayout->setSpacing(10);
//     mainLayout->setContentsMargins(15, 15, 15, 15);

//     // Header Section (10% height)
//     QFrame *header = new QFrame;
//     header->setFixedHeight(window.height() * 0.10);
//     header->setStyleSheet(
//         "QFrame {"
//         "   background-color: #1a0940;"
//         "   border: 1px solid #1E3F72;"
//         "   border-radius: 8px;"
//         "   color: white;"
//         "}"
//     );
    
//     QHBoxLayout *headerLayout = new QHBoxLayout(header);
//     headerLayout->setContentsMargins(10, 10, 10, 10);
    
//     // Image on the left
//     QLabel *imageLabel = new QLabel;
//     QPixmap pixmap(":/home/ramcel/PROJECTS/musicApp/musicLogo.png");
//     if(pixmap.isNull()) {
//         pixmap = QPixmap(100, 50);
//         pixmap.fill(Qt::transparent);
//         QPainter painter(&pixmap);
//         painter.setPen(Qt::white);
//     }
//     imageLabel->setPixmap(pixmap.scaled(100, 50, Qt::KeepAspectRatio));
//     headerLayout->addWidget(imageLabel);
    
//     // Spacer and buttons
//     headerLayout->addStretch();
    
//     QPushButton *spotify_link = new QPushButton("open in spotify");
//     QPushButton *btn2 = new QPushButton("Button 2");
//     QString buttonStyle = 
//         "QPushButton {"
//         "   background-color: #1a0940;"
//         "   border: 1px solid #3A5F8E;"
//         "   border-radius: 5px;"
//         "   padding: 5px 10px;"
//         "   min-width: 80px;"
//         "   color: white;"
//         "}"
//         "QPushButton:hover {"
//         "   background-color: #2D4F8B;"
//         "}";
    
//     spotify_link->setStyleSheet(buttonStyle);
//     QObject::connect(spotify_link, &QPushButton::clicked, []() {
//         QDesktopServices::openUrl(QUrl("https://open.spotify.com"));
//     });
//     btn2->setStyleSheet(buttonStyle);
//     headerLayout->addWidget(spotify_link);
//     headerLayout->addWidget(btn2);
    
//     mainLayout->addWidget(header);

//     // Main Content Area
//     QHBoxLayout *mainContentLayout = new QHBoxLayout;
//     mainContentLayout->setSpacing(10);
//     mainContentLayout->setContentsMargins(0, 0, 0, 0);

//     // Left Section with footer (footer takes 20% of height)
//     QWidget *leftContainer = new QWidget;
//     QVBoxLayout *leftContainerLayout = new QVBoxLayout(leftContainer);
//     leftContainerLayout->setSpacing(10);
//     leftContainerLayout->setContentsMargins(0, 0, 0, 0);
    
//     // Content area (80% height)
//     QFrame *contentFrame = new QFrame;
//     contentFrame->setStyleSheet(
//         "QFrame {"
//         "   background-color: #1a0940;"
//         "   border: 1px solid #1E3F72;"
//         "   border-radius: 8px;"
//         "   color: white;"
//         "}"
//     );
//     QVBoxLayout *contentLayout = new QVBoxLayout(contentFrame);
//     contentLayout->setSpacing(8);
//     contentLayout->setContentsMargins(10, 10, 10, 10);
    
//     leftContainerLayout->addWidget(contentFrame, 8); // 80% of space
    
//     // Footer (20% height)
//     QFrame *footer = new QFrame;
//     footer->setStyleSheet(
//         "QFrame {"
//         "   background-color: #1a0940;"
//         "   border: 1px solid #1E3F72;"
//         "   border-radius: 8px;"
//         "   color: white;"
//         "}"
//     );
//     footer->setFixedHeight(window.height() * 0.15);
    
//     // Footer layout with music control buttons
//     QHBoxLayout *footerLayout = new QHBoxLayout(footer);
//     footerLayout->setContentsMargins(10, 10, 10, 10);
//     footerLayout->setSpacing(10);
    
//     // Create the 5 music control buttons
//     QPushButton *prevButton = new QPushButton("Poprzednia piosenka");
//     QPushButton *playButton = new QPushButton("Uruchom piosenkę");
//     QPushButton *pauseButton = new QPushButton("Pauza");
//     QPushButton *restartButton = new QPushButton("Od początku");
//     QPushButton *nextButton = new QPushButton("Następna piosenka");
    
//     // Apply style to all buttons
//     prevButton->setStyleSheet(buttonStyle);
//     playButton->setStyleSheet(buttonStyle);
//     pauseButton->setStyleSheet(buttonStyle);
//     restartButton->setStyleSheet(buttonStyle);
//     nextButton->setStyleSheet(buttonStyle);
    
//     // Add buttons to footer layout
//     footerLayout->addWidget(prevButton);
//     footerLayout->addWidget(playButton);
//     footerLayout->addWidget(pauseButton);
//     footerLayout->addWidget(restartButton);
//     footerLayout->addWidget(nextButton);
    
//     leftContainerLayout->addWidget(footer, 2); // 20% of space
    
//     mainContentLayout->addWidget(leftContainer, 1);

//     // Right Sidebar
//     QLabel *rightSidebar = new QLabel("Sidebar");
//     rightSidebar->setAlignment(Qt::AlignCenter);
//     rightSidebar->setStyleSheet(
//         "QLabel {"
//         "   background-color: #1a0940;"
//         "   border: 1px solid #1E3F72;"
//         "   border-radius: 8px;"
//         "   padding: 15px;"
//         "   color: white;"
//         "}"
//     );
//     rightSidebar->setFixedWidth(window.width() * 0.15);
//     mainContentLayout->addWidget(rightSidebar);

//     // Add to main layout
//     mainLayout->addLayout(mainContentLayout, 1); // Takes remaining space

//     // Set main container as central widget
//     QVBoxLayout *windowLayout = new QVBoxLayout(&window);
//     windowLayout->setContentsMargins(0, 0, 0, 0);
//     windowLayout->addWidget(mainContainer);

//     window.show();

//     return app.exec();
// }
#include <QApplication>
#include "../headers/window_setup.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QWidget *window = createMainWindow();
    setupMainWindow(window);
    
    window->show();
    return app.exec();
}