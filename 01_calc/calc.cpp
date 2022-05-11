#include "calc.h"
#include "ui_calc.h"
#include <QSpacerItem>
#include <QDebug>

Calc::Calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calc)
{
    this->m_bit_num = 32;
    this->m_fix_any_bit_width = 20;
    this->m_fix_any_bit_heigh = 20;
    this->set_value(0);
    this->ui->setupUi(this);
    this->init_ui();
    this->init_connect();
    this->binary_conversion(DECIMAL, QString::number(this->get_value()));
    // 关闭最大化
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
}

Calc::~Calc()
{
    delete ui;
}

void Calc::init_ui()
{
    QFrame *frame = this->ui->bin_list_frame;
    QHBoxLayout *frame_hlayout = new QHBoxLayout();
    QVBoxLayout *frame_vlayout = new QVBoxLayout();
    QHBoxLayout *lab_bit_hlayout = new QHBoxLayout();

    for (int i = this->m_bit_num - 1; i >= 0; --i) {
        // bit位上方文字
        this->label_bit[i] = new QLabel(QString::number(i), frame);
        this->label_bit[i]->setAlignment(Qt::AlignCenter);
        this->label_bit[i]->setFixedSize(this->m_fix_any_bit_width, this->m_fix_any_bit_heigh);
        this->label_bit[i]->setStyleSheet("border:1px solid rgb(200, 200, 200);font: bold;color: #74b9ff;");
        lab_bit_hlayout->addWidget(this->label_bit[i]);
        if (i % 4 == 0 && i != 0) {
            QSpacerItem *ite = new QSpacerItem(this->m_fix_any_bit_width / 2, this->m_fix_any_bit_heigh / 2);
            lab_bit_hlayout->addSpacerItem(ite);
        }

        // bit位按钮
        this->btn_bit[i] = new QPushButton(0, this->ui->bin_list_frame);
        this->btn_bit[i]->setStyleSheet("background-color: #ebeee8;font: bold;color: red");
        this->btn_bit[i]->setFixedSize(this->m_fix_any_bit_width, this->m_fix_any_bit_heigh);
        frame_hlayout->addWidget(this->btn_bit[i]);
        if (i % 4 == 0 && i != 0) {
            QSpacerItem *ite = new QSpacerItem(this->m_fix_any_bit_width / 2, this->m_fix_any_bit_heigh / 2);
            frame_hlayout->addSpacerItem(ite);
        }
    }
    frame_vlayout->addLayout(lab_bit_hlayout);
    frame_vlayout->addLayout(frame_hlayout);

    this->rangeslider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, frame);
    this->rangeslider->setMinimum(0);
    this->rangeslider->setMaximum(31);
    frame_vlayout->addWidget(this->rangeslider);

    frame->setLayout(frame_vlayout);
}

void Calc::init_connect()
{
    connect(ui->line_edit_dec, &QLineEdit::textEdited, this, [=](const QString &text) {
        binary_conversion(DECIMAL, text);
    });
    connect(ui->line_edit_bin, &QLineEdit::textEdited, this, [=](const QString &text) {
        binary_conversion(BINARY, text);
    });
    connect(ui->line_edit_hex, &QLineEdit::textEdited, this, [=](const QString &text) {
        binary_conversion(HEX, text);
    });
    connect(ui->line_edit_oct, &QLineEdit::textEdited, this, [=](const QString &text) {
        binary_conversion(OCTAL, text);
    });
    connect(ui->btn_clean_zero, &QPushButton::clicked, this, [=]() {
        this->binary_conversion(DECIMAL, QString::number(0));
    });
    connect(ui->btn_clean_one, &QPushButton::clicked, this, [=]() {
        unsigned int val = 0xFFFFFFFF;
        this->binary_conversion(HEX, QString::number(val, 16));
    });
    connect(ui->btn_reverse, &QPushButton::clicked, this, [=]() {
        unsigned int val = this->get_value();
        this->binary_conversion(DECIMAL, QString::number(~val));
    });
    connect(ui->btn_left_bit, &QPushButton::clicked, this, [=]() {
        unsigned int move = this->ui->spin_move_bit->value();
        unsigned int val = this->get_value();
        val = val << move;
        this->binary_conversion(DECIMAL, QString::number(val));
    });
    connect(ui->btn_right_bit, &QPushButton::clicked, this, [=]() {
        unsigned int move = this->ui->spin_move_bit->value();
        unsigned int val = this->get_value();
        val = val >> move;
        this->binary_conversion(DECIMAL, QString::number(val));
    });
    for (int i = 0; i < 32; ++i) {
        connect(this->btn_bit[i], &QPushButton::clicked, this, [=]() {
            bool ok = false;

            unsigned char bit = this->btn_bit[i]->text().toInt(&ok, 2);
            if (ok != true) {
                return;
            }

            unsigned int val = this->get_value();
            if (bit == 1) {
                val = val & (~(0x1 << i));
            } else {
                val = val | (0x1 << i);
            }

            this->binary_conversion(DECIMAL, QString::number(val, 10));
        });
    }

    connect(this->rangeslider, &RangeSlider::lowerValueChanged, this, &Calc::slots_set_rangeslider);
    connect(this->rangeslider, &RangeSlider::upperValueChanged, this, &Calc::slots_set_rangeslider);
    connect(ui->line_edit_rang_hex, &QLineEdit::textEdited, this, [=](const QString &text) {
        bool ok = false;
        int upper = this->rangeslider->GetUpperValue();
        int lower = this->rangeslider->GetLowerValue();
        unsigned int val = this->get_value();
        unsigned int rang_val = text.toUInt(&ok, 16);
        if (ok != true) {
            return;
        }
        for (int i = 31 - upper, k = 0; i<= 31 - lower; ++i, ++k) {
            val = (val & (~(0x1 << i)));
            val = val | (((rang_val >> k) & 0x1) << i);
        }
        this->binary_conversion(DECIMAL, QString::number(val, 10));
    });
    connect(ui->line_edit_rang_dec, &QLineEdit::textEdited, this, [=](const QString &text) {
        bool ok = false;
        int upper = this->rangeslider->GetUpperValue();
        int lower = this->rangeslider->GetLowerValue();
        unsigned int val = this->get_value();
        unsigned int rang_val = text.toUInt(&ok, 10);
        if (ok != true) {
            return;
        }
        for (int i = 31 - upper, k = 0; i<= 31 - lower; ++i, ++k) {
            val = (val & (~(0x1 << i)));
            val = val | (((rang_val >> k) & 0x1) << i);
        }
        this->binary_conversion(DECIMAL, QString::number(val, 10));
    });
}

void Calc::binary_conversion(enum TextType type, const QString &text)
{
    bool ok = false;
    unsigned int val, bit_val;

    switch(type) {
        case BINARY:
            val = text.toUInt(&ok, 2);
            break;
        case OCTAL:
            val = text.toUInt(&ok, 8);
            break;
        case DECIMAL:
            val = text.toUInt(&ok, 10);
            break;
        case HEX:
            val = text.toUInt(&ok, 16);
            break;
        default:
            val = 0;
            break;
    }

    if (ok != true) {
        val = 0;
    }

    this->ui->line_edit_bin->setText(QString::number(val, 2));
    this->ui->line_edit_oct->setText(QString::number(val, 8));
    this->ui->line_edit_dec->setText(QString::number(val, 10));
    this->ui->line_edit_hex->setText(QString::number(val, 16).toUpper());

    for (unsigned char i = 0; i < 32; ++i) {
        bit_val = ((val >> i) & 0x1);
        this->btn_bit[i]->setText(QString::number(bit_val, 10));
        if (bit_val == 0x1) {
            this->btn_bit[i]->setStyleSheet("background-color: #ebeee8;font: bold;color: blue");
        } else {
            this->btn_bit[i]->setStyleSheet("background-color: #ebeee8;font: bold;color: red");
        }
    }

    this->set_value(val);
    slots_set_rangeslider();
}

void Calc::set_value(unsigned int val)
{
    this->m_value = val;
}

unsigned int Calc::get_value() const
{
    return this->m_value;
}

void Calc::slots_set_rangeslider()
{
    int upper = this->rangeslider->GetUpperValue();
    int lower = this->rangeslider->GetLowerValue();
    this->ui->label_select->setText(QString("选择：[%1-%2]").arg(31 - lower).arg(31 - upper));
    unsigned int val = this->m_value;
    val = (((val << lower) >> lower)) >> (31 - upper);
    this->ui->line_edit_rang_hex->setText(QString::number(val, 16).toUpper());
    this->ui->line_edit_rang_dec->setText(QString::number(val, 10));
}
