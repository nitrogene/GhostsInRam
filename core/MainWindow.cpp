#include "MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent)
{
	qInfo();
}

MainWindow::~MainWindow()
{
	qInfo();	
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