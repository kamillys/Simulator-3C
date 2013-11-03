#ifndef ANIMATIONSETTINGSFORM_H
#define ANIMATIONSETTINGSFORM_H

#include <QWidget>

namespace Ui {
class AnimationSettingsForm;
}

class AnimationSettingsForm : public QWidget
{
    Q_OBJECT

    bool paused = false;
public:
    explicit AnimationSettingsForm(QWidget *parent = 0);
    ~AnimationSettingsForm();
signals:
    void startAnim();
    void pauseAnim();
    void resumeAnim();
    void resetAnim();
    void displayPathsChanged(bool);
    void aniStepsChanged(int);
    void fastSkipAction();

public slots:
    void animStopped();
    void animStarted();
    void animPaused();
    void animResumed();
    void animResetted();

private slots:
    void on_startB_clicked();

    void on_pauseB_clicked();

    void on_resetB_clicked();

    void on_showPathsBox_toggled(bool checked);

    void on_fastSkipButton_clicked();

    void on_stepsBox_valueChanged(int arg1);

private:
    Ui::AnimationSettingsForm *ui;
};

#endif // ANIMATIONSETTINGSFORM_H
