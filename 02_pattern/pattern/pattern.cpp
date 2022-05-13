#include "pattern.h"
#include "ui_pattern.h"

Pattern::Pattern(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pattern)
{
    ui->setupUi(this);
    this->soft_ui_init();
    this->connect_init();
}

Pattern::~Pattern()
{
    delete ui;
}

void Pattern::soft_ui_init()
{

}

void Pattern::connect_init()
{

}
