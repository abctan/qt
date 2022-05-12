#include "pattern.h"
#include "ui_pattern.h"
#include <QDebug>

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
    // 1、listWidget 切换
    connect(ui->listWidget, &QListWidget::currentRowChanged, this, [=](int currentRow) {
        ui->stackedWidget->setCurrentIndex(currentRow);
    });
}
