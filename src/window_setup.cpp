#include "../headers/window_setup.h"
#include "../headers/header_section.h"
#include "../headers/content_section.h"
#include <QVBoxLayout>

QWidget* createMainWindow() {
    QWidget *window = new QWidget;
    window->setWindowTitle("Complex Layout Example");
    window->resize(1000, 800);
    window->setStyleSheet(
        "QWidget#mainWindow {"
        "   background-color: #0f0526;"
        "   border-radius: 15px;"
        "   border: 2px solid #1E3F72;"
        "}"
    );
    window->setObjectName("mainWindow");
    window->setWindowFlags(window->windowFlags() | Qt::FramelessWindowHint);
    return window;
}

void setupMainWindow(QWidget *window) {
    QWidget *mainContainer = new QWidget(window);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    mainLayout->addWidget(createHeaderSection(window));
    mainLayout->addLayout(createContentSection(window));

    QVBoxLayout *windowLayout = new QVBoxLayout(window);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->addWidget(mainContainer);
}