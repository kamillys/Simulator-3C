#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <VTF/Math>

namespace Ui {
class MaterialSettingsForm;
}

class MaterialSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialSettingsForm(QWidget *parent = 0);
    ~MaterialSettingsForm();

private slots:
    void on_resetMaterialBtn_clicked();
signals:
    void resetMaterial(glm::ivec2 d, glm::vec3 o, glm::vec3 s);

private:
    Ui::MaterialSettingsForm *ui;
};

#endif // SETTINGSFORM_H
