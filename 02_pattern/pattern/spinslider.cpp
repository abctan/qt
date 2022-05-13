#include "spinslider.h"
#include "ui_spinslider.h"

SpinSlider::SpinSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinSlider)
{
    ui->setupUi(this);
    this->soft_init();
}

SpinSlider::~SpinSlider()
{
    delete ui;
}

void SpinSlider::soft_init()
{
    connect(ui->horizontalSlider, &QSlider::sliderMoved, ui->spinBox, &QSpinBox::setValue);
    connect(ui->spinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->horizontalSlider, &QSlider::setValue);
}

void SpinSlider::setMaximum(int max)
{
    ui->horizontalSlider->setMaximum(max);
    ui->spinBox->setMaximum(max);
}

int SpinSlider::getMaximum() const
{
    return ui->spinBox->maximum();
}

void SpinSlider::setMinimum(int min)
{
    ui->horizontalSlider->setMinimum(min);
    ui->spinBox->setMinimum(min);
}

int SpinSlider::getMinimum() const
{
    return ui->spinBox->minimum();
}

void SpinSlider::setValue(int val)
{
    ui->horizontalSlider->setValue(val);
    ui->spinBox->setValue(val);
}

int SpinSlider::value() const
{
    return ui->spinBox->value();
}

void SpinSlider::setText(const QString &string)
{
    ui->label->setText(string);
}

QString SpinSlider::text() const
{
    return ui->label->text();
}
