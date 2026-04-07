#include "MainWindow.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_loadIniButton(new QPushButton(tr("Load INI"), this)),
    m_configDisplay(new QTextEdit(this))
{
    qInfo();

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    layout->addWidget(m_loadIniButton);
    m_configDisplay->setReadOnly(true);
    m_configDisplay->setPlaceholderText("Configuration will appear here after loading an INI file");
    layout->addWidget(m_configDisplay);
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
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open Configuration File"), "",
        tr("INI Files (*.ini);;All Files (*)"));
    
    if (!filePath.isEmpty())
    {
        loadAndParseIniFile(filePath);
    }
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

void MainWindow::loadAndParseIniFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << filePath;
        return;
    }
    
    QTextStream in(&file);
    QString currentSection;
    
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        
        // Skip empty lines and comments
        if (line.isEmpty() || line.startsWith(";") || line.startsWith("#"))
            continue;
        
        // Check for section header
        if (line.startsWith("[") && line.endsWith("]"))
        {
            currentSection = line.mid(1, line.length() - 2);
            continue;
        }
        
        // Parse key=value or just value
        if (!currentSection.isEmpty())
        {
            QString value = line;
            int eqPos = line.indexOf("=");
            if (eqPos != -1)
            {
                // If format is key=value, extract the value part
                value = line.mid(eqPos + 1).trimmed();
            }
            
            if (!value.isEmpty())
            {
                m_configuration[currentSection] = value;
            }
        }
    }
    
    file.close();
    
    // Log configuration
    qInfo() << "Configuration loaded from:" << filePath;
    qInfo() << "CPU:" << m_configuration.value("CPU", "");
    qInfo() << "Memory:" << m_configuration.value("Memory", "");
    qInfo() << "IO:" << m_configuration.value("IO", "");
    
    // Update UI display
    updateConfigurationDisplay();
}

void MainWindow::updateConfigurationDisplay()
{
    QString displayText = "=== Configuration ===";
    displayText += "\n\nCPU: " + m_configuration.value("CPU", "Not specified");
    displayText += "\n\nMemory: " + m_configuration.value("Memory", "Not specified");
    displayText += "\n\nIO: " + m_configuration.value("IO", "Not specified");
    
    m_configDisplay->setPlainText(displayText);
}

void MainWindow::updateScreen()
{

}