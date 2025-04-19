#include "../headers/footer_section.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QDebug>

QFrame* createFooterSection(QWidget *parent) {
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

    // Slider setup (FIXED: No unsafe capture)
    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setRange(0, 100);
    volume->setValue(50);  // Default volume
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

    // Safe connection (no capture needed)
    QObject::connect(volume, &QSlider::valueChanged, [](int newValue) {
        qDebug() << "Volume set to:" << newValue;  // Optional debug
    });

    // Rest of your code (buttons, labels, etc.)...
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
    QPushButton *restartBtn = new QPushButton(QString::fromUtf8("\U0001F501")); // 🔁
    QPushButton *stopBtn    = new QPushButton(QString::fromUtf8("\u23F9"));    // ⏹️
    QList<QPushButton*> buttons = {favorite, restartBtn, stopBtn};
    
    for (QPushButton *btn : buttons) {
        btn->setFixedSize(40, 40);
        btn->setStyleSheet(buttonStyle);
        ButtonsLayout->addWidget(btn);
    }
    ButtonsBlock->setLayout(ButtonsLayout);

    QFrame *textBlock = new QFrame;
    textBlock->setFrameStyle(QFrame::Panel | QFrame::Raised);
    textBlock->setLineWidth(2);
    textBlock->setStyleSheet("color: white;");

    QVBoxLayout *textLayout = new QVBoxLayout;
    QLabel *line1 = new QLabel("Top Text");
    QLabel *line2 = new QLabel("Middle Text");
    QLabel *line3 = new QLabel("Bottom Text");

    line1->setStyleSheet("color: white;");
    line2->setStyleSheet("color: white;");
    line3->setStyleSheet("color: white;");

    textLayout->addWidget(line1);
    textLayout->addWidget(line2);
    textLayout->addWidget(line3);
    textBlock->setLayout(textLayout);

    footerLayout->addWidget(volume);
    footerLayout->addWidget(textBlock);
    footerLayout->addWidget(ButtonsBlock);

    return footer;
}
