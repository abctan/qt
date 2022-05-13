#ifndef SPINSLIDER_H
#define SPINSLIDER_H

#include <QWidget>

namespace Ui {
class SpinSlider;
}

class SpinSlider : public QWidget
{
    Q_OBJECT

public:
    explicit SpinSlider(QWidget *parent = 0);
    ~SpinSlider();
    void soft_init();

    void setMaximum(int max);
    int getMaximum() const;
    void setMinimum(int min);
    int getMinimum() const;
    void setValue(int val);
    int value() const;
    void setText(const QString &string);
    QString text() const;

private:
    Ui::SpinSlider *ui;
};

#endif // SPINSLIDER_H
