#include <QApplication>
#include <QMessageBox>
#include <vector>

#include "Core/Logging.h"
#include "Core/MainWindow.h"
#include "Core/EmulatorThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initializeLogging();
    qInfo(core) << "Démarrage de l'application";

    MainWindow w;
    w.setWindowTitle("TODO");
    w.resize(800, 600);
    w.show();
	
	EmulatorThread emuThread;

	emuThread.setPaused(true);
    emuThread.start();

	// TODO
  
    int exitCode = a.exec();
    
    qInfo("Extinction de l'émulateur...");
	
    emuThread.requestInterruption();
    emuThread.wait();
    
    return exitCode;
}
