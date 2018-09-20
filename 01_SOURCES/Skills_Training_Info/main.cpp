#include "LoginScreen.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QDesktopWidget>

bool VerifyScreenResolution();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if( !VerifyScreenResolution() )
    {
        app.exit();
        return 0;
    }

    app.setStyleSheet("QMainWindow {background-color: rgb(41,38,32)}"

                      " QDockWidget > QWidget { "
                      " border: 1px solid lightgray;"
                      "}"

                      "QDialog {background-color: rgb(41,38,32)}"

                      "QSplitter::handle{height: 2px; background-color:rgb(225,230,234)}"

                      "QWidget {background-color: rgb(41,38,32)}"
                      "QGridLayout {background-color: rgb(41,38,32)}"

                      "QPushButton {background-color: rgb(78,74,67)}"
                      "QPushButton {color: rgb(0,255,0)}"

                      "QPushButton {"
                      "border-style: outset;"
                      "border-width: 2px;"
                      "border-radius: 5px;"
                      "border-color: rgb(193,191,192);"
                      "min-width: 5ex;"
                      "padding: 2px;}"

                      "QPushButton:pressed {"
                      "color: rgb(255,255,128);"
                      "}"

                      "QPushButton:!enabled {"
                      "color: rgb(159,159,159);"
                      "}"

                      "QToolBar {background-color: rgb(41,38,32)}"

                      "QToolButton {color: rgb(255,255,255)}"
                      "QToolButton:checked {background-color: rgb(0,150,200)}"

                      "QLabel {background-color: rgb(41,38,32)}"
                      "QLabel {color: rgb(192,193,195)}"

                      "QLineEdit {background-color: rgb(64,64,64)}"
                      "QLineEdit {color: rgb(255,255,255)}"
                      "QLineEdit {border: 2px rgb(64,64,64)}"

                      "QDateTimeEdit {background-color: rgb(64,64,64)}"
                      "QDateTimeEdit {color: rgb(255,255,255)}"
                      "QDateTimeEdit {border: 2px rgb(64,64,64)}"

                      "QComboBox {background-color: rgb(64,64,64)}"
                      "QComboBox {color: rgb(255,255,255)}"

                      "QComboBox QAbstractItemView {background-color: rgb(64,64,64)}"
                      "QComboBox QAbstractItemView {color: rgb(255,255,255)}"

                      "QGroupBox::title {color:rgb(255,255,255);"
                      "subcontrol-origin: margin;"
                      "subcontrol-position: top centre;"
                      "padding: 0 3px;}"
                      "QGroupBox {border: 2px solid gray;"
                      "border-radius: 5px;"
                      "margin-top: 1ex;}"

                      "QSlider::groove:horizontal {"
                      "border: 1px solid #999999;"
                      "height: 2px;"
                      "background: gray;"
                      "margin: 2px 0;}"

                      "QSlider::handle:horizontal {"
                      "background: darkgray;"
                      "border: 1px solid #5c5c5c;"
                      "width: 18px;"
                      "margin: -2px 0;"
                      "border-radius: 3px;}"

                      "QCheckBox {color:rgb(255,255,255)}"

                      "QRadioButton {color:rgb(255,255,255)}"

                      "QSpinBox {background-color: rgb(64,64,64)}"
                      "QSpinBox {color: rgb(255,255,255)}"
                      "QSpinBox {border: 2px rgb(64,64,64)}"

                      "QMenu {background-color: darkgray; margin: 2px;}"
                      "QMenu::item {padding: 2px 25px 2px 20px; border: 1px solid transparent;}"
                      "QMenu::item:selected {border-color: yellow; background: gray;}"

                      "QMenuBar {background-color: rgb(41,38,32)}"
                      "QMenuBar::item {background-color: rgb(41,38,32)}"
                      "QMenuBar::item {color: rgb(255,255,255)}"
                      "QMenuBar::item {spacing: 3px}"
                      "QMenuBar::item {padding: 1px 4px}"
                      "QMenuBar::item {background: transparent}"
                      "QMenuBar::item {border-radius: 4px}"
                      "QMenuBar::item:selected {background: darkgray;}"
                      "QMenuBar::item:pressed {background: gray;}"

                      "QTableWidget {background-color: rgb(64,64,64)}"
                      "QTableWidget {gridline-color: rgb(200,200,200)}"
                      "QTableWidget {color:rgb(255,255,255)}"

                      "QHeaderView::section { spacing: 10px; "
                      "background-color: darkgray;"
                      "color: black;"
                      "font: bold;"
                      "border: 1px solid darkgray;"
                      "margin: 1px;}"

                      "QListWidget {background-color: rgb(64,64,64)}"
                      "QListWidget {color:rgb(255,255,255)}"

                      "QDockWidget::title { background: gray; }"

                      "QTabWidget::pane {border-top: 2px solid rgb(142,143,145)}"
                      "QTabWidget::pane {border-bottom: 2px solid rgb(142,143,145)}"
                      "QTabWidget::pane {border-left: 2px solid rgb(142,143,145)}"
                      "QTabWidget::pane {border-right: 2px solid rgb(142,143,145)}"
                      "QTabWidget::tab-bar {left: 5px}"
                      "QTabWidget::tab {background: rgb(64,64,64)}"
                      "QTabWidget::tab {border: 2px rgb(255,255,0)}"
                      "QTabWidget::tab {border-bottom-color: rgb(0,0,255)}"
                      "QTabWidget::tab {border-top-left-radius: 4px}"
                      "QTabWidget::tab {border-top-right-radius: 4px}"
                      "QTabWidget::tab {min-width: 8ex}"
                      "QTabWidget::tab {padding: 2px}"

                      "QTabBar::tab {background: darkgray;"
                      "border: 2px solid #C4C4C3;"
                      "border-bottom-color: #C2C7CB;"
                      "border-top-left-radius: 4px;"
                      "border-top-right-radius: 4px;"
                      "min-width: 8ex;"
                      "padding: 2px;}"

                      "QTabBar::tab:selected {"
                      "background: rgb(228,228,228);"
                      "border-color: #9B9B9B;"
                      "border-bottom-color: #C2C7CB;}"

                      "QTabBar::tab:!selected {"
                      "background: rgb(180,180,180);"
                      "margin-top: 2px;}"

                      "QProgressBar {"
                      "border: 2px solid grey;"
                      "border-radius: 5px;"
                      "text-align: center;"
                      "background-color: grey;"
                      " }"

                      "QProgressBar {"
                      "border: 2px solid grey;"
                      "border-radius: 5px;"
                      "text-align: center;"
                      "background-color: grey;"
                      " }"

                      "QScrollBar::handle { "
                      "background: #7B7D7E;"
                      "   border: 4px solid #7B7D7E; "
                      "border-radius: 4px;"
                      "}"

                      "QScrollBar::handle:hover {"
                      "background: #474f54; "
                      "border: 4px solid #474f54; "
                      "border-radius: 4px;"
                      "}"

                      "QScrollBar::handle:pressed { "
                      "background: #4A90D9;  "
                      "border: 4px solid #4A90D9;"
                      "border-radius: 4px;}"

                      "QTextEdit {background:rgb(64,64,64); color:rgb(255,255,255)}"

                      "QSplitter {background-color: rgb(225,230,234) }"

                      );

    QPixmap pixmapObj(":/Images/Images/SkillsIntro.png");

    QSplashScreen qSplashScreenObj(pixmapObj);
    //    qSplashScreenObj.setFixedSize(420, 175);
    qSplashScreenObj.show();

    LoginScreen loginScreenObj;

    QTimer::singleShot(1000, &qSplashScreenObj, SLOT(close()) );
    QTimer::singleShot(1000, &loginScreenObj, SLOT(show()) );

    return app.exec();
}

bool VerifyScreenResolution()
{
    QDesktopWidget desk;

    int screencount = desk.screenCount();
    qDebug() << "screen count = " << screencount;

    QRect screen1Geometry, screen2Geometry;
    QMessageBox popUpMsg;

    if(screencount == 1)
    {
        screen1Geometry = QApplication::desktop()->screenGeometry();

        qDebug() << "width = " << screen1Geometry.width()
                 << "height = " << screen1Geometry.height();

        if((screen1Geometry.width() < 1024 || screen1Geometry.width() > 1920)
                || (screen1Geometry.height() < 768 || screen1Geometry.height() > 1200))
        {
            popUpMsg.setText("Current Screen Resolution is not supported");
            popUpMsg.exec();
            return false;
        }

    }
    else if(screencount == 2)
    {
        screen1Geometry = QApplication::desktop()->screenGeometry(1);

        qDebug() << "width1 = " << screen1Geometry.width()
                 << "height1 = " << screen1Geometry.height();

        screen2Geometry = QApplication::desktop()->screenGeometry(2);

        qDebug() << "width2 = " << screen2Geometry.width()
                 << "height2 = " << screen2Geometry.height();

        if((screen1Geometry.width() < 1024 || screen1Geometry.width() > 1920)
                || (screen1Geometry.height() < 768 || screen1Geometry.height() > 1200))
        {
            popUpMsg.setText("First Screen Resolution is not supported");
            popUpMsg.exec();
            return false;
        }

        if((screen2Geometry.width() < 1024 || screen2Geometry.width() > 1920)
                || (screen2Geometry.height() < 768 || screen2Geometry.height() > 1080))
        {
            popUpMsg.setText("Second Screen Resolution is not supported");
            popUpMsg.exec();
            return false;
        }

        qDebug() << "width = " << QApplication::desktop()->availableGeometry(2).width()
                 << "height = " << QApplication::desktop()->availableGeometry(2).height();
    }

    return true;
}
