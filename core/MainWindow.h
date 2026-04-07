#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QString>
#include <QMap>
 
class QKeyEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
 
public slots:
    void updateScreen();
 
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
 
private slots:
    void onLoadIniClicked();

private:
    struct KeyPos { int row; int col; };
    void handleKeyEvent(QKeyEvent* event, bool pressed);
    void loadAndParseIniFile(const QString& filePath);
    void updateConfigurationDisplay();
    
    QPushButton* m_loadIniButton;
    QTextEdit* m_configDisplay;
    QMap<QString, QString> m_configuration;
};
 
#endif // MAINWINDOW_H