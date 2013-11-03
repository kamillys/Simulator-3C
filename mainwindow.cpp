#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>
#include "Paths/parser.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->materialSettingsWidget, SIGNAL(resetMaterial(glm::ivec2,glm::vec3,glm::vec3)),
            ui->renderWidget, SLOT(resizeMaterial(glm::ivec2,glm::vec3,glm::vec3)));
    connect(ui->animationSettingsForm, SIGNAL(pauseAnim()),
            ui->renderWidget, SLOT(pauseAnimation()));
    connect(ui->animationSettingsForm, SIGNAL(resetAnim()),
            ui->renderWidget, SLOT(resetAnimation()));
    connect(ui->animationSettingsForm, SIGNAL(startAnim()),
            ui->renderWidget, SLOT(startAnimation()));
    connect(ui->animationSettingsForm, SIGNAL(resumeAnim()),
            ui->renderWidget, SLOT(resumeAnimation()));

    connect(ui->animationSettingsForm, SIGNAL(fastSkipAction()),
            ui->renderWidget, SLOT(skipAnimation()));
    connect(ui->animationSettingsForm, SIGNAL(aniStepsChanged(int)),
            ui->renderWidget, SLOT(setAnimationSteps(int)));

    connect(ui->renderWidget, SIGNAL(animStarted()),
            ui->animationSettingsForm, SLOT(animStarted()));
    connect(ui->renderWidget, SIGNAL(animStopped()),
            ui->animationSettingsForm, SLOT(animStopped()));
    connect(ui->renderWidget, SIGNAL(animPaused()),
            ui->animationSettingsForm, SLOT(animPaused()));
    connect(ui->renderWidget, SIGNAL(animResumed()),
            ui->animationSettingsForm, SLOT(animResumed()));
    connect(ui->renderWidget, SIGNAL(animResetted()),
            ui->animationSettingsForm, SLOT(animResetted()));

    connect(ui->animationSettingsForm, SIGNAL(displayPathsChanged(bool)),
            ui->renderWidget, SLOT(setShowingPaths(bool)));

    connect(ui->cutterSettingsWidget, SIGNAL(CutterChanged(CutterType,double)),
            ui->renderWidget, SLOT(cutterChanged(CutterType,double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(this);
    if (path.isNull())
        return;
    QFile f(path);
    if(!f.open(QFile::ReadOnly))
    {
        QMessageBox::critical(this,"Error loading file", "Cannot open file!");
        //qDebug() << f;
        return;
    }
    CNCCommandList commandList = CNCParser::parse(f);
    ui->renderWidget->parseCommands(commandList);
}
