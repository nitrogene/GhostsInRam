#ifndef EMULATORTHREAD_H
#define EMULATORTHREAD_H

#include <QThread>
#include <atomic>

class EmulatorThread : public QThread {
    Q_OBJECT
public:
    EmulatorThread(QObject* parent = nullptr);

    void setPaused(bool paused) { m_paused.store(paused, std::memory_order_relaxed); }
    bool isPaused() const { return m_paused.load(std::memory_order_relaxed); }

signals:
    void frameReady();

protected:
    void run() override;

private:
    std::atomic<bool> m_paused { false };
};

#endif // EMULATORTHREAD_H