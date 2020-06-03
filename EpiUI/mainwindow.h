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
    void Render(std::vector<std::vector<int> >);
    void clearscene(int h,int w);
    int x;
    int y;
private:
    QGraphicsScene *scene;
    void draw_Person(QBrush* brush, int x, int y, QGraphicsScene* scene);
public slots:
    void writeToXML();
    void stop_EpiSim();
};

class Run_Thread : public QThread
{
    Q_OBJECT
public:
    explicit Run_Thread(std::string s, MainWindow* MainWindow);

    void run();
private:
    std::string xmlName;
    MainWindow* Main;
    int curEpoch = 0;
    bool followEpochs = true;
    void readEpoch(int num);

public slots:
    void ChangeViewedEpoch(int);
};

#endif // MAINWINDOW_H
