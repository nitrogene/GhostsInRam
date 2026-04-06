#include "MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_loadIniButton(new QPushButton(tr("Load INI"), this))
{
    qInfo();

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    layout->addWidget(m_loadIniButton);
    central->setLayout(layout);
    setCentralWidget(central);

    connect(m_loadIniButton, &QPushButton::clicked, this, &MainWindow::onLoadIniClicked);
}

MainWindow::~MainWindow()
{
    qInfo();
}

void MainWindow::onLoadIniClicked()
{
    qInfo() << "Load INI button clicked";
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    handleKeyEvent(event, true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    handleKeyEvent(event, false);
}

void MainWindow::handleKeyEvent(QKeyEvent* event, bool pressed)
{

}

void MainWindow::updateScreen()
{

}