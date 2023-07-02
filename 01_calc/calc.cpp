#include "calc.h"
#include "ui_calc.h"

Calc::Calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calc)
{
    ui->setupUi(this);
    this->setFixedSize(714, 131);
    this->setSelectShowLabel();
    this->initConnect();
}

Calc::~Calc()
{
    delete ui;
}

void Calc::initConnect()
{
    connect(ui->btnLeftMove, &QPushButton::clicked, this, [=]() {
        int moveVal = ui->editMoveVal->text().toInt();
        if (moveVal <= 0) {
            return;
        }
        this->setBindispVal(BIT_MOVE_LEFT, moveVal);
    });
    connect(ui->btnRightMove, &QPushButton::clicked, this, [=]() {
        int moveVal = ui->editMoveVal->text().toInt();
        if (moveVal <= 0) {
            return;
        }
        this->setBindispVal(BIT_MOVE_RIGHT, moveVal);
    });
    connect(ui->btnAllZero, &QPushButton::clicked, this, [=]() {
        this->setBindispVal(BIT_MOVE_CLEAN_ZERO_ALL, 0);
    });
    connect(ui->btnAllOne, &QPushButton::clicked, this, [=]() {
        this->setBindispVal(BIT_MOVE_SET_ONE_ALL, 0);
    });
    connect(ui->btnReverse, &QPushButton::clicked, this, [=]() {
        this->setBindispVal(BIT_MOVE_REVERSE, 0);
    });

    connect(ui->editHex, &QLineEdit::textEdited, this, [=](QString str) {
        bool ok;
        setAsciiEdit(str.toUInt(&ok, 16));
    });
    connect(ui->editDec, &QLineEdit::textEdited, this, [=](QString str) {
        bool ok;
        setAsciiEdit(str.toUInt(&ok, 10));
    });
    connect(ui->editOct, &QLineEdit::textEdited, this, [=](QString str) {
        bool ok;
        setAsciiEdit(str.toUInt(&ok, 8));
    });
    connect(ui->editSelectVal, &QLineEdit::textEdited, this, [=](QString str) {
        bool ok;
        int lower = ui->binDisp->getLeftValue();
        int upper = ui->binDisp->getRightValue();
        int hBit, lBit;
        hBit = ui->binDisp->getMaxValue() - lower;
        lBit = ui->binDisp->getMaxValue() - upper;
        setAsciiEdit(str.toUInt(&ok, 16), lBit, hBit);
    });
    connect(ui->binDisp, &Binary::changeAssicVal, this, [=](unsigned int val) {
        setAsciiEdit(val);
    });
    connect(ui->binDisp, &Binary::sliderChanged, this, &Calc::setSelectShowLabel);

    connect(ui->btnTop, &QPushButton::clicked, this, [=](bool checked) {
        if (checked == true) {
            this->setWindowFlag(Qt::WindowStaysOnTopHint, true);
        } else {
            this->setWindowFlag(Qt::WindowStaysOnTopHint, false);
        }
        this->show();
    });

    connect(ui->btnSelectEdit, &QPushButton::clicked, this, [=](bool checked) {
        if (checked == true) {
            ui->editSelectVal->setEnabled(true);
        } else {
            ui->editSelectVal->setEnabled(false);
        }
    });
}

void Calc::setBindispVal(bitMoveDirectionType type, int moveOffest)
{
    unsigned int val = this->ui->binDisp->getVal();

    switch (type) {
    case BIT_MOVE_LEFT:
        this->setAsciiEdit(val << moveOffest);
        break;
    case BIT_MOVE_RIGHT:
        this->setAsciiEdit(val >> moveOffest);
        break;
    case BIT_MOVE_CLEAN_ZERO_ALL:
        this->setAsciiEdit(0U);
        break;
    case BIT_MOVE_SET_ONE_ALL:
        this->setAsciiEdit(~0U);
        break;
    case BIT_MOVE_REVERSE:
        this->setAsciiEdit(~val);
        break;
    }
}

void Calc::setAsciiEdit(unsigned int val)
{
    this->ui->binDisp->setVal(val);
    unsigned int newVal = this->ui->binDisp->getVal();

    this->ui->editHex->setText(QString::number(newVal, 16).toUpper());
    this->ui->editDec->setText(QString::number(newVal, 10));
    this->ui->editOct->setText(QString::number(newVal, 8));

    this->setSelectShowLabel();
}

void Calc::setAsciiEdit(unsigned int val, int low, int high)
{
    this->ui->binDisp->setVal(val, low, high);

    unsigned int newVal = this->ui->binDisp->getVal();
    qDebug() << val << low << high <<newVal;
    this->ui->editHex->setText(QString::number(newVal, 16).toUpper());
    this->ui->editDec->setText(QString::number(newVal, 10));
    this->ui->editOct->setText(QString::number(newVal, 8));

    this->setSelectShowLabel();
}

void Calc::setSelectShowLabel()
{
    int lower = ui->binDisp->getLeftValue();
    int upper = ui->binDisp->getRightValue();
    int hBit, lBit;

    hBit = ui->binDisp->getMaxValue() - lower;
    lBit = ui->binDisp->getMaxValue() - upper;

    unsigned int rangeVal = ui->binDisp->getVal(lBit, hBit);

    ui->laSelectRange->setText(QString("选择[%1-%2]").arg(lBit).arg(hBit));
    ui->editSelectVal->setText(QString::number(rangeVal, 16).toUpper());
}


