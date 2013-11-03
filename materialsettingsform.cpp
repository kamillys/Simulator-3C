#include "materialsettingsform.h"
#include "ui_materialsettingsform.h"

MaterialSettingsForm::MaterialSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialSettingsForm)
{
    ui->setupUi(this);
}

MaterialSettingsForm::~MaterialSettingsForm()
{
    delete ui;
}

void MaterialSettingsForm::on_resetMaterialBtn_clicked()
{
    glm::vec3 o(ui->originX->value(),
                ui->originY->value(),
                ui->originZ->value());
    glm::vec3 s(ui->matX->value(),
                ui->matY->value(),
                ui->matZ->value());
    glm::ivec2 d(ui->densityX->value(),
                 ui->densityY->value());
    emit resetMaterial(d, o, s);
}
