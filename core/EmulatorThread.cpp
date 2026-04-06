#include "EmulatorThread.h"
#include "Logging.h"

EmulatorThread::EmulatorThread(QObject* parent)
    : QThread(parent)
{
	qInfo();
}

void EmulatorThread::run()
{
    qInfo();

    while (!isInterruptionRequested()) {
        if (m_paused.load(std::memory_order_relaxed)) {
            msleep(20);
            continue;
        }

		// TODO
      
        emit frameReady();

        msleep(20);
    }
}