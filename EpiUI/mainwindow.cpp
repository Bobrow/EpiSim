#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <QString>
#include <QDebug>
#include <sstream>
#include <pugixml.hpp>
#include <pugixml.cpp>
#include <thread>
#include <filesystem>

namespace fs = std::filesystem;

std::string folderName;
std::vector<std::pair<const QString,const QString>> params = {{"PopulationInput","population"},
                                                          {"XInput","AreaX"},
                                                          {"YInput","AreaY"},
                                                          {"AlreadyInfectedInput","AlreadyInfected"},
                                                          {"InfectionProbabilityIndicator","infectProbability"},
                                                          {"RadOfInfectionInput","infectionRadius"},
                                                          {"CPUThreadsDisplay","threads"},
                                                          {"RemovalDisplay","RemovalTime"}
                                                         };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    folderName = std::to_string(time(NULL)) + "/";
    ui->setupUi(this);
    connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(writeToXML()));
    connect(ui->StopButton, SIGNAL(clicked()), this, SLOT(stop_EpiSim()));
    ui->CPUThreadsSlider->setRange(0,128);
    ui->InfectionProbabilitySlider->setRange(0,100);
    ui->CPUThreadsSlider->setRange(0,std::thread::hardware_concurrency());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stop_EpiSim() {
    system("taskkill /f /im EpiSim.exe");
}

Run_Thread::Run_Thread(std::string s) : xmlName(s) {
    ;
}

void Run_Thread::run () {
#ifdef __linux__
    system(("EpiSim.exe "+ xmlName.substr(0, 10)+".xml &").c_str());
#elif _WIN64
    system(("start EpiSim.exe "+ xmlName.substr(0,10)+".xml").c_str());
#else
#error "Platform not supported"
#endif

}

int FourCharToInt(char* buffer) {
    int out = *(reinterpret_cast<int*>(buffer));
    return out;
}

void MainWindow::writeToXML() {
    /*xml_document<> doc;
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);
    xml_node<> *root = doc.allocate_node(node_element, "config");
    for(int i = 0; i < params.size(); i++) {
        bool LineEdit = false;
        std::pair<QLabel*, QLineEdit*> LabelAndLine;
        LabelAndLine.first = ui->centralwidget->findChild<QLabel*>(params.at(i).first);
        if (LabelAndLine.first == nullptr) {
            LineEdit = true;
            LabelAndLine.second = ui->centralwidget->findChild<QLineEdit*>(params.at(i).first);
        }
        QString nodename = params.at(i).second;
        qInfo() << "Setting: "+nodename+" from "+params.at(i).first;
        xml_node<> *param = doc.allocate_node(node_element, QStringToConstCharPoint(nodename));
        xml_attribute<char> *value;
        if (LineEdit) {
            value = doc.allocate_attribute("value", QStringToConstCharPoint(LabelAndLine.second->text()));
        }
        else {
            value = doc.allocate_attribute("value", QStringToConstCharPoint(LabelAndLine.first->text()));
        }
        param->append_attribute(value);
        root->append_node(param);
    }
    doc.append_node(root);
    std::string xmlName = std::to_string(time(NULL))+".xml";
    std::ofstream fileStored(xmlName);
    fileStored << doc;
    fileStored.close();
    doc.clear();*/
    //StartOGL();
    x = ui->XInput->text().toInt();
    y = ui->YInput->text().toInt();
    pugi::xml_document doc;
    pugi::xml_node declarationNode = doc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version")    = "1.0";
    declarationNode.append_attribute("encoding")   = "utf-8";
    pugi::xml_node root = doc.append_child("config");
    for(int i = 0; i < params.size(); i++) {
        bool LineEdit = false;
        std::pair<QLabel*, QLineEdit*> LabelAndLine;
        LabelAndLine.first = ui->centralwidget->findChild<QLabel*>(params.at(i).first);
        if (LabelAndLine.first == nullptr) {
            LineEdit = true;
            LabelAndLine.second = ui->centralwidget->findChild<QLineEdit*>(params.at(i).first);
        }
        QString nodename = params.at(i).second;
        qInfo() << "Setting: "+nodename+" from "+params.at(i).first;
        pugi::xml_node param = root.append_child(nodename.toStdString().c_str());
        if (LineEdit) {
            std::string value = LabelAndLine.second->text().toStdString();
            param.append_attribute("value") = value.c_str();
        }
        else {
            std::string value = LabelAndLine.first->text().toStdString();
            param.append_attribute("value") = value.c_str();
        }
    }
    pugi::xml_node debug = root.append_child("debug");
    debug.append_attribute("value") = 0;
    pugi::xml_node renderType = root.append_child("renderType");
    renderType.append_attribute("value") = 0;
    std::string xmlName = std::to_string(time(NULL))+".xml";
    pugi::xml_node folderNameNode = root.append_child("folderName");
    folderNameNode.append_attribute("value") = xmlName.substr(0,xmlName.size()-4).c_str();
    std::ofstream fileStored(xmlName);
    std::stringstream ss;
    doc.save(ss);
    fileStored << ss.str();
    fileStored.close();
    Run_Thread* thread_run = new Run_Thread(xmlName);
    thread_run->start();

}

