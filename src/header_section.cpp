#include "../headers/header_section.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>

QFrame* createHeaderSection(QWidget *parent) {
    QFrame *header = new QFrame(parent);
    header->setFixedHeight(parent->height() * 0.10);
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
    
    // Image on the left
    QLabel *imageLabel = new QLabel;
    QPixmap pixmap("./../assets/musicLogo.png");
    if(pixmap.isNull()) {
        pixmap = QPixmap(100, 50);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(Qt::white);
    }
    imageLabel->setPixmap(pixmap.scaled(100, 50, Qt::KeepAspectRatio));
    headerLayout->addWidget(imageLabel);
    
    // Spacer and buttons
    headerLayout->addStretch();
    
    QPushButton *spotify_link = new QPushButton("open in spotify");
    QPushButton *close = new QPushButton("X");
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
    QObject::connect(close, &QPushButton::clicked, []() {
        QApplication::quit();
    });
    close->setStyleSheet(buttonStyle);
    headerLayout->addWidget(spotify_link);
    headerLayout->addWidget(close);
    
    return header;
}