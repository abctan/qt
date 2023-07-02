#ifndef CALC_H
#define CALC_H

#include <QWidget>

namespace Ui {
class Calc;
}

class Calc : public QWidget
{
    Q_OBJECT

    enum bitMoveDirectionType {
        BIT_MOVE_LEFT,
        BIT_MOVE_RIGHT,
        BIT_MOVE_CLEAN_ZERO_ALL,
        BIT_MOVE_SET_ONE_ALL,
        BIT_MOVE_REVERSE
    };
public:
    explicit Calc(QWidget *parent = nullptr);
    ~Calc();

    void initConnect();
    void setBindispVal(enum bitMoveDirectionType type, int moveOffest);
    void setAsciiEdit(unsigned int val);
    void setAsciiEdit(unsigned int val, int low, int high);

private slots:
    void setSelectShowLabel();
private:
    Ui::Calc *ui;
};

#endif // CALC_H
