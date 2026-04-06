#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
 
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
 
private:
    struct KeyPos { int row; int col; };
    void handleKeyEvent(QKeyEvent* event, bool pressed);
};
 
#endif // MAINWINDOW_H