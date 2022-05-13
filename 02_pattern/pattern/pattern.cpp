#include "pattern.h"
#include "ui_pattern.h"
#include <QDebug>

const int PAT_BIT8_INDEX  = 0;
const int PAT_BIT10_INDEX = 1;
const int PAT_BIT12_INDEX = 2;

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
    /* 1、bg ui init */
    ui->bg_r->setText("R");
    ui->bg_g->setText("G");
    ui->bg_b->setText("B");
    this->bgBitGroup = new QButtonGroup(this);
    this->bgBitGroup->addButton(ui->bg_bit10, PAT_BIT10_INDEX);
    this->bgBitGroup->addButton(ui->bg_bit12, PAT_BIT12_INDEX);
}

void Pattern::connect_init()
{
    // 1、listWidget 切换
    connect(ui->listWidget, &QListWidget::currentRowChanged, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(this->bgBitGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
        int max = (id == PAT_BIT10_INDEX) ? 1023 : 4095;
        ui->bg_r->setMaximum(max);
        ui->bg_g->setMaximum(max);
        ui->bg_b->setMaximum(max);
    });
}
