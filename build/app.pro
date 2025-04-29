QT += core gui widgets multimedia
TARGET = app
SOURCES = ../src/main.cpp \
          ../src/window_setup.cpp \
          ../src/header_section.cpp \
          ../src/content_section.cpp \
          ../src/footer_section.cpp \
          ../src/sidebar_section.cpp\
          ../src/musicplayer.cpp
HEADERS = ../headers/window_setup.h \
          ../headers/header_section.h \
          ../headers/content_section.h \
          ../headers/footer_section.h \
          ../headers/sidebar_section.h
# Additional configuration
CONFIG += c++11
DESTDIR = ./
OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui
