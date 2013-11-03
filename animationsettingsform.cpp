#include "animationsettingsform.h"
#include "ui_animationsettingsform.h"

AnimationSettingsForm::AnimationSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnimationSettingsForm)
{
    ui->setupUi(this);
    animResetted();
}

AnimationSettingsForm::~AnimationSettingsForm()
{
    delete ui;
}

void AnimationSettingsForm::animStopped()
{
    ui->pauseB->setDisabled(true);
    ui->startB->setDisabled(false);
}

void AnimationSettingsForm::animStarted()
{
    ui->pauseB->setDisabled(false);
    ui->startB->setDisabled(true);
    paused = false;
}

void AnimationSettingsForm::animPaused()
{
    paused = true;
}

void AnimationSettingsForm::animResumed()
{
    paused = false;
}

void AnimationSettingsForm::animResetted()
{
    ui->startB->setDisabled(false);
    ui->pauseB->setDisabled(true);
}

void AnimationSettingsForm::on_startB_clicked()
{
    emit startAnim();
}

void AnimationSettingsForm::on_pauseB_clicked()
{
    if (paused)
        emit resumeAnim();
    else
        emit pauseAnim();
}

void AnimationSettingsForm::on_resetB_clicked()
{
    emit resetAnim();
}

void AnimationSettingsForm::on_showPathsBox_toggled(bool checked)
{
    emit displayPathsChanged(checked);
}

void AnimationSettingsForm::on_fastSkipButton_clicked()
{
    emit fastSkipAction();
}

void AnimationSettingsForm::on_stepsBox_valueChanged(int arg1)
{
    emit aniStepsChanged(arg1);
}
