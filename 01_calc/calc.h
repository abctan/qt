#ifndef CALC_H
#define CALC_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QSlider>
#include <QLabel>
#include "RangeSlider.h"

namespace Ui {
class Calc;
}

enum TextType {
    BINARY = 0,
    OCTAL,
    DECIMAL,
    HEX
};

class Calc : public QWidget
{
    Q_OBJECT

public:
    explicit Calc(QWidget *parent = 0);
    ~Calc();
    void init_ui();
    void init_connect();
    void binary_conversion(enum TextType type, const QString &text);
    void set_value(unsigned int val);
    unsigned int get_value() const;

public slots:
    void slots_set_rangeslider();

private:
    Ui::Calc *ui;
    QPainter *painter;
    QPushButton *btn_bit[32];
    QLabel *label_bit[32];
    RangeSlider *rangeslider;
    unsigned int m_value;
    unsigned int m_bit_num;
    unsigned int m_fix_any_bit_width;
    unsigned int m_fix_any_bit_heigh;
};

#endif // CALC_H
