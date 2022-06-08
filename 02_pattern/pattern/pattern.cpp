#include "pattern.h"
#include "ui_pattern.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

const int PAT_BIT8_INDEX  = 0;
const int PAT_BIT10_INDEX = 1;
const int PAT_BIT12_INDEX = 2;

const int BAR_NUM2_INDEX = 0;
const int BAR_NUM4_INDEX = 1;
const int BAR_NUM8_INDEX = 2;
const int BAR_DIR_HORIZONTAL_INDEX = 0;
const int BAR_DIR_VERTICAL_INDEX   = 1;
const int BAR_INCREASING_INDEX     = 0;
const int BAR_DIMINISHING_INDEX    = 1;


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

    /* 2、cbar ui init */
    this->barNumGroup = new QButtonGroup(this);
    this->barDirpTionGroup = new QButtonGroup(this);
    this->barGrayGroup = new QButtonGroup(this);
    this->barNumGroup->addButton(ui->bar_two, BAR_NUM2_INDEX);
    this->barNumGroup->addButton(ui->bar_four, BAR_NUM4_INDEX);
    this->barNumGroup->addButton(ui->bar_eight, BAR_NUM8_INDEX);
    this->barDirpTionGroup->addButton(ui->bar_direction_h, BAR_DIR_HORIZONTAL_INDEX);
    this->barDirpTionGroup->addButton(ui->bar_direction_v, BAR_DIR_VERTICAL_INDEX);
    this->barGrayGroup->addButton(ui->bar_gray_inc, BAR_INCREASING_INDEX);
    this->barGrayGroup->addButton(ui->bar_gray_dim, BAR_DIMINISHING_INDEX);
    ui->bar_eight->setChecked(true);
    ui->bar_direction_h->setChecked(true);
    ui->bar_gray_inc->setChecked(true);

    QHBoxLayout *barClorHlayout = new QHBoxLayout();
    for (int i = 0; i < CBAR_MAX_NUM; ++i) {
        QVBoxLayout *barClorVlayout = new QVBoxLayout();
        for (int j = 0; j < RGB_MAX_NUM; ++j) {
            this->barcolor[i][j] = new SpinSlider(ui->groupBox);
            barClorVlayout->addWidget(this->barcolor[i][j]);
        }
        barClorHlayout->addLayout(barClorVlayout);
    }
    ui->groupBox->setLayout(barClorHlayout);
    //ui->hlay->addLayout(barClorHlayout);

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
