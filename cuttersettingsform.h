#ifndef CUTTERSETTINGSFORM_H
#define CUTTERSETTINGSFORM_H

#include <QWidget>

namespace Ui {
class CutterSettingsForm;
}

enum class CutterType
{
    Flat,
    Round
};

class CutterSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CutterSettingsForm(QWidget *parent = 0);
    ~CutterSettingsForm();

private slots:
    void on_resetButton_clicked();

signals:
    void CutterChanged(CutterType type, double diameter);

private:
    Ui::CutterSettingsForm *ui;
};

#endif // CUTTERSETTINGSFORM_H
