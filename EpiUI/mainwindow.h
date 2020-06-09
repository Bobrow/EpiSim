#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QThread>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    int x;
    int y;
public slots:
    void writeToXML();
    void stop_EpiSim();
};

class Run_Thread : public QThread
{
    Q_OBJECT
public:
    explicit Run_Thread(std::string s);

    void run();
private:
    std::string xmlName;
};

#endif // MAINWINDOW_H
