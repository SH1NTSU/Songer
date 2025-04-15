#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QPixmap>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // window
    QWidget window;
    window.setWindowTitle("Complex Layout Example");
    window.resize(1000, 800);
    window.setStyleSheet(
        "QWidget#mainWindow {"
        "   background-color: #0f0526;"
        "   border-radius: 15px;"
        "   border: 2px solid #1E3F72;"
        "}"
    );
    window.setObjectName("mainWindow");
    window.setWindowFlags(window.windowFlags() | Qt::FramelessWindowHint);

    // Main container widget
    QWidget *mainContainer = new QWidget(&window);
    
    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    // Header Section (10% height)
    QFrame *header = new QFrame;
    header->setFixedHeight(window.height() * 0.10);
    header->setStyleSheet(
        "QFrame {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"
    );
    
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(10, 10, 10, 10);
    
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap(":/home/ramcel/PROJECTS/musicApp/musicLogo.png");
    if(pixmap.isNull()) {
        pixmap = QPixmap(100, 50);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(Qt::white);
    }
    imageLabel->setPixmap(pixmap.scaled(100, 50, Qt::KeepAspectRatio));
    headerLayout->addWidget(imageLabel);
    //buttons
    headerLayout->addStretch();
    
    QPushButton *spotify_link = new QPushButton("open in spotify");
    QPushButton *btn2 = new QPushButton("Button 2");
    QString buttonStyle = 
        "QPushButton {"
        "   background-color: #1a0940;"
        "   border: 1px solid #3A5F8E;"
        "   border-radius: 5px;"
        "   padding: 5px 10px;"
        "   min-width: 80px;"
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2D4F8B;"
        "}";
    
    spotify_link->setStyleSheet(buttonStyle);
    QObject::connect(spotify_link, &QPushButton::clicked, []() {
        QDesktopServices::openUrl(QUrl("https://open.spotify.com"));
    });
    btn2->setStyleSheet(buttonStyle);
    headerLayout->addWidget(spotify_link);
    headerLayout->addWidget(btn2);
    
    mainLayout->addWidget(header);

    // Main Content Layout
    QHBoxLayout *mainContentLayout = new QHBoxLayout;
    mainContentLayout->setSpacing(10);
    mainContentLayout->setContentsMargins(0, 0, 0, 0);

    // Left Section 
    QWidget *leftContainer = new QWidget;
    QVBoxLayout *leftContainerLayout = new QVBoxLayout(leftContainer);
    leftContainerLayout->setSpacing(10);
    leftContainerLayout->setContentsMargins(0, 0, 0, 0);
    
    // Content Frame
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
    
    leftContainerLayout->addWidget(contentFrame, 8); 
   
    // Footer 
    QFrame *footer = new QFrame;
    footer->setStyleSheet(
        "QFrame {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   color: white;"
        "}"
    );
    footer->setFixedHeight(window.height() * 0.15);
    
    // Foooter Layout
    QHBoxLayout *footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(10, 10, 10, 10);
    footerLayout->setSpacing(10);
    
       QPushButton *prevButton = new QPushButton("⏮");
    QPushButton *playButton = new QPushButton("▶️");
    QPushButton *pauseButton = new QPushButton("⏸");
    QPushButton *restartButton = new QPushButton("🔁");
    QPushButton *nextButton = new QPushButton("⏭");
	
    prevButton->setStyleSheet(buttonStyle);
    playButton->setStyleSheet(buttonStyle);
    pauseButton->setStyleSheet(buttonStyle);
    restartButton->setStyleSheet(buttonStyle);
    nextButton->setStyleSheet(buttonStyle);
    
    footerLayout->addWidget(prevButton);
    footerLayout->addWidget(playButton);
    footerLayout->addWidget(pauseButton);
    footerLayout->addWidget(restartButton);
    footerLayout->addWidget(nextButton);
    
    leftContainerLayout->addWidget(footer, 2); 
    
    mainContentLayout->addWidget(leftContainer, 1);
    // Sidebar
    QLabel *rightSidebar = new QLabel("Sidebar");
    rightSidebar->setAlignment(Qt::AlignCenter);
    rightSidebar->setStyleSheet(
        "QLabel {"
        "   background-color: #1a0940;"
        "   border: 1px solid #1E3F72;"
        "   border-radius: 8px;"
        "   padding: 15px;"
        "   color: white;"
        "}"
    );
    rightSidebar->setFixedWidth(window.width() * 0.15);
    mainContentLayout->addWidget(rightSidebar);

    mainLayout->addLayout(mainContentLayout, 1);

    QVBoxLayout *windowLayout = new QVBoxLayout(&window);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->addWidget(mainContainer);

    window.show();

    return app.exec();
}
