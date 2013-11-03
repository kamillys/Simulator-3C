#include "cuttersettingsform.h"
#include "ui_cuttersettingsform.h"

CutterSettingsForm::CutterSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CutterSettingsForm)
{
    ui->setupUi(this);
}

CutterSettingsForm::~CutterSettingsForm()
{
    delete ui;
}

void CutterSettingsForm::on_resetButton_clicked()
{
    CutterType type = CutterType::Flat;
    if (ui->typeBox->currentText() == "Round")
        type = CutterType::Round;
    emit CutterChanged(type, ui->diameterBox->value());
}
