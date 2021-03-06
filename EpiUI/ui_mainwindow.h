/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QLineEdit *PopulationInput;
    QLineEdit *XInput;
    QLabel *PopulationLabel;
    QLabel *AreaLabel;
    QLineEdit *YInput;
    QLabel *XLabel;
    QLabel *YLabel;
    QLabel *AlreadyInfectedLabel;
    QLineEdit *AlreadyInfectedInput;
    QSlider *InfectionProbabilitySlider;
    QLabel *InfectionProbabilityIndicator;
    QLabel *ProbInfectionLabel;
    QLineEdit *RadOfInfectionInput;
    QLabel *RadOfInfectionLabel;
    QRadioButton *SelectGPU;
    QRadioButton *SelectCPU;
    QSlider *CPUThreadsSlider;
    QLabel *CPUThreadsLabel;
    QLabel *CPUThreadsDisplay;
    QLabel *RemovalDisplay;
    QSlider *RemovalSlider;
    QLabel *RemovalLabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(239, 401);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        StartButton = new QPushButton(centralwidget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(10, 10, 101, 21));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy1);
        StopButton = new QPushButton(centralwidget);
        StopButton->setObjectName(QString::fromUtf8("StopButton"));
        StopButton->setGeometry(QRect(120, 10, 91, 21));
        sizePolicy1.setHeightForWidth(StopButton->sizePolicy().hasHeightForWidth());
        StopButton->setSizePolicy(sizePolicy1);
        PopulationInput = new QLineEdit(centralwidget);
        PopulationInput->setObjectName(QString::fromUtf8("PopulationInput"));
        PopulationInput->setGeometry(QRect(135, 50, 101, 21));
        sizePolicy1.setHeightForWidth(PopulationInput->sizePolicy().hasHeightForWidth());
        PopulationInput->setSizePolicy(sizePolicy1);
        XInput = new QLineEdit(centralwidget);
        XInput->setObjectName(QString::fromUtf8("XInput"));
        XInput->setGeometry(QRect(130, 130, 101, 21));
        sizePolicy1.setHeightForWidth(XInput->sizePolicy().hasHeightForWidth());
        XInput->setSizePolicy(sizePolicy1);
        PopulationLabel = new QLabel(centralwidget);
        PopulationLabel->setObjectName(QString::fromUtf8("PopulationLabel"));
        PopulationLabel->setGeometry(QRect(75, 50, 51, 20));
        sizePolicy1.setHeightForWidth(PopulationLabel->sizePolicy().hasHeightForWidth());
        PopulationLabel->setSizePolicy(sizePolicy1);
        AreaLabel = new QLabel(centralwidget);
        AreaLabel->setObjectName(QString::fromUtf8("AreaLabel"));
        AreaLabel->setGeometry(QRect(60, 105, 101, 20));
        sizePolicy1.setHeightForWidth(AreaLabel->sizePolicy().hasHeightForWidth());
        AreaLabel->setSizePolicy(sizePolicy1);
        YInput = new QLineEdit(centralwidget);
        YInput->setObjectName(QString::fromUtf8("YInput"));
        YInput->setGeometry(QRect(130, 160, 101, 21));
        sizePolicy1.setHeightForWidth(YInput->sizePolicy().hasHeightForWidth());
        YInput->setSizePolicy(sizePolicy1);
        XLabel = new QLabel(centralwidget);
        XLabel->setObjectName(QString::fromUtf8("XLabel"));
        XLabel->setGeometry(QRect(110, 130, 21, 20));
        sizePolicy1.setHeightForWidth(XLabel->sizePolicy().hasHeightForWidth());
        XLabel->setSizePolicy(sizePolicy1);
        YLabel = new QLabel(centralwidget);
        YLabel->setObjectName(QString::fromUtf8("YLabel"));
        YLabel->setGeometry(QRect(110, 160, 21, 16));
        sizePolicy1.setHeightForWidth(YLabel->sizePolicy().hasHeightForWidth());
        YLabel->setSizePolicy(sizePolicy1);
        AlreadyInfectedLabel = new QLabel(centralwidget);
        AlreadyInfectedLabel->setObjectName(QString::fromUtf8("AlreadyInfectedLabel"));
        AlreadyInfectedLabel->setGeometry(QRect(10, 190, 121, 20));
        sizePolicy1.setHeightForWidth(AlreadyInfectedLabel->sizePolicy().hasHeightForWidth());
        AlreadyInfectedLabel->setSizePolicy(sizePolicy1);
        AlreadyInfectedInput = new QLineEdit(centralwidget);
        AlreadyInfectedInput->setObjectName(QString::fromUtf8("AlreadyInfectedInput"));
        AlreadyInfectedInput->setGeometry(QRect(130, 190, 101, 21));
        sizePolicy1.setHeightForWidth(AlreadyInfectedInput->sizePolicy().hasHeightForWidth());
        AlreadyInfectedInput->setSizePolicy(sizePolicy1);
        InfectionProbabilitySlider = new QSlider(centralwidget);
        InfectionProbabilitySlider->setObjectName(QString::fromUtf8("InfectionProbabilitySlider"));
        InfectionProbabilitySlider->setGeometry(QRect(130, 220, 71, 16));
        sizePolicy1.setHeightForWidth(InfectionProbabilitySlider->sizePolicy().hasHeightForWidth());
        InfectionProbabilitySlider->setSizePolicy(sizePolicy1);
        InfectionProbabilitySlider->setOrientation(Qt::Horizontal);
        InfectionProbabilityIndicator = new QLabel(centralwidget);
        InfectionProbabilityIndicator->setObjectName(QString::fromUtf8("InfectionProbabilityIndicator"));
        InfectionProbabilityIndicator->setGeometry(QRect(210, 215, 21, 21));
        sizePolicy1.setHeightForWidth(InfectionProbabilityIndicator->sizePolicy().hasHeightForWidth());
        InfectionProbabilityIndicator->setSizePolicy(sizePolicy1);
        ProbInfectionLabel = new QLabel(centralwidget);
        ProbInfectionLabel->setObjectName(QString::fromUtf8("ProbInfectionLabel"));
        ProbInfectionLabel->setGeometry(QRect(10, 210, 111, 31));
        sizePolicy1.setHeightForWidth(ProbInfectionLabel->sizePolicy().hasHeightForWidth());
        ProbInfectionLabel->setSizePolicy(sizePolicy1);
        RadOfInfectionInput = new QLineEdit(centralwidget);
        RadOfInfectionInput->setObjectName(QString::fromUtf8("RadOfInfectionInput"));
        RadOfInfectionInput->setGeometry(QRect(130, 240, 101, 21));
        sizePolicy1.setHeightForWidth(RadOfInfectionInput->sizePolicy().hasHeightForWidth());
        RadOfInfectionInput->setSizePolicy(sizePolicy1);
        RadOfInfectionLabel = new QLabel(centralwidget);
        RadOfInfectionLabel->setObjectName(QString::fromUtf8("RadOfInfectionLabel"));
        RadOfInfectionLabel->setGeometry(QRect(30, 240, 91, 21));
        sizePolicy1.setHeightForWidth(RadOfInfectionLabel->sizePolicy().hasHeightForWidth());
        RadOfInfectionLabel->setSizePolicy(sizePolicy1);
        SelectGPU = new QRadioButton(centralwidget);
        SelectGPU->setObjectName(QString::fromUtf8("SelectGPU"));
        SelectGPU->setGeometry(QRect(130, 270, 41, 20));
        sizePolicy1.setHeightForWidth(SelectGPU->sizePolicy().hasHeightForWidth());
        SelectGPU->setSizePolicy(sizePolicy1);
        SelectCPU = new QRadioButton(centralwidget);
        SelectCPU->setObjectName(QString::fromUtf8("SelectCPU"));
        SelectCPU->setGeometry(QRect(180, 270, 41, 20));
        sizePolicy1.setHeightForWidth(SelectCPU->sizePolicy().hasHeightForWidth());
        SelectCPU->setSizePolicy(sizePolicy1);
        SelectCPU->setChecked(true);
        CPUThreadsSlider = new QSlider(centralwidget);
        CPUThreadsSlider->setObjectName(QString::fromUtf8("CPUThreadsSlider"));
        CPUThreadsSlider->setGeometry(QRect(190, 310, 16, 71));
        sizePolicy1.setHeightForWidth(CPUThreadsSlider->sizePolicy().hasHeightForWidth());
        CPUThreadsSlider->setSizePolicy(sizePolicy1);
        CPUThreadsSlider->setValue(1);
        CPUThreadsSlider->setOrientation(Qt::Vertical);
        CPUThreadsLabel = new QLabel(centralwidget);
        CPUThreadsLabel->setObjectName(QString::fromUtf8("CPUThreadsLabel"));
        CPUThreadsLabel->setGeometry(QRect(140, 320, 47, 31));
        sizePolicy1.setHeightForWidth(CPUThreadsLabel->sizePolicy().hasHeightForWidth());
        CPUThreadsLabel->setSizePolicy(sizePolicy1);
        CPUThreadsDisplay = new QLabel(centralwidget);
        CPUThreadsDisplay->setObjectName(QString::fromUtf8("CPUThreadsDisplay"));
        CPUThreadsDisplay->setGeometry(QRect(170, 360, 16, 20));
        sizePolicy1.setHeightForWidth(CPUThreadsDisplay->sizePolicy().hasHeightForWidth());
        CPUThreadsDisplay->setSizePolicy(sizePolicy1);
        RemovalDisplay = new QLabel(centralwidget);
        RemovalDisplay->setObjectName(QString::fromUtf8("RemovalDisplay"));
        RemovalDisplay->setGeometry(QRect(215, 80, 16, 16));
        sizePolicy1.setHeightForWidth(RemovalDisplay->sizePolicy().hasHeightForWidth());
        RemovalDisplay->setSizePolicy(sizePolicy1);
        RemovalSlider = new QSlider(centralwidget);
        RemovalSlider->setObjectName(QString::fromUtf8("RemovalSlider"));
        RemovalSlider->setGeometry(QRect(130, 80, 76, 16));
        sizePolicy1.setHeightForWidth(RemovalSlider->sizePolicy().hasHeightForWidth());
        RemovalSlider->setSizePolicy(sizePolicy1);
        RemovalSlider->setValue(5);
        RemovalSlider->setOrientation(Qt::Horizontal);
        RemovalLabel = new QLabel(centralwidget);
        RemovalLabel->setObjectName(QString::fromUtf8("RemovalLabel"));
        RemovalLabel->setGeometry(QRect(46, 80, 81, 13));
        sizePolicy1.setHeightForWidth(RemovalLabel->sizePolicy().hasHeightForWidth());
        RemovalLabel->setSizePolicy(sizePolicy1);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(InfectionProbabilitySlider, SIGNAL(sliderMoved(int)), InfectionProbabilityIndicator, SLOT(setNum(int)));
        QObject::connect(CPUThreadsSlider, SIGNAL(sliderMoved(int)), CPUThreadsDisplay, SLOT(setNum(int)));
        QObject::connect(RemovalSlider, SIGNAL(sliderMoved(int)), RemovalDisplay, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        StartButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        StopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        PopulationInput->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        XInput->setText(QCoreApplication::translate("MainWindow", "316", nullptr));
        PopulationLabel->setText(QCoreApplication::translate("MainWindow", "Population", nullptr));
        AreaLabel->setText(QCoreApplication::translate("MainWindow", "Area Size (Metres)", nullptr));
        YInput->setText(QCoreApplication::translate("MainWindow", "254", nullptr));
        XLabel->setText(QCoreApplication::translate("MainWindow", "X =", nullptr));
        YLabel->setText(QCoreApplication::translate("MainWindow", "Y =", nullptr));
        AlreadyInfectedLabel->setText(QCoreApplication::translate("MainWindow", "People Already Infected", nullptr));
        AlreadyInfectedInput->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        InfectionProbabilityIndicator->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        ProbInfectionLabel->setText(QCoreApplication::translate("MainWindow", "Probability of Infection", nullptr));
        RadOfInfectionInput->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        RadOfInfectionLabel->setText(QCoreApplication::translate("MainWindow", "Radius of Infection", nullptr));
        SelectGPU->setText(QCoreApplication::translate("MainWindow", "GPU", nullptr));
        SelectCPU->setText(QCoreApplication::translate("MainWindow", "CPU", nullptr));
        CPUThreadsSlider->setProperty("min", QVariant(QCoreApplication::translate("MainWindow", "0", nullptr)));
        CPUThreadsSlider->setProperty("max", QVariant(QCoreApplication::translate("MainWindow", "128", nullptr)));
        CPUThreadsSlider->setProperty("to_set", QVariant(QCoreApplication::translate("MainWindow", "CPUThreadsDisplay", nullptr)));
        CPUThreadsLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">CPU<br>Threads</p></body></html>", nullptr));
        CPUThreadsDisplay->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        RemovalDisplay->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        RemovalLabel->setText(QCoreApplication::translate("MainWindow", "Time of Removal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
