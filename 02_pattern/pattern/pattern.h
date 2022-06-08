#ifndef PATTERN_H
#define PATTERN_H

#include <QWidget>
#include <QButtonGroup>
#include "spinslider.h"

namespace Ui {
class Pattern;
}

#define CBAR_MAX_NUM 8
#define RGB_MAX_NUM  3

class Pattern : public QWidget
{
    Q_OBJECT

public:
    explicit Pattern(QWidget *parent = 0);
    ~Pattern();
    void soft_ui_init();
    void connect_init();

private:
    Ui::Pattern *ui;
    QButtonGroup *bgBitGroup;
    QButtonGroup *barNumGroup;
    QButtonGroup *barDirpTionGroup;
    QButtonGroup *barGrayGroup;
    SpinSlider   *barcolor[CBAR_MAX_NUM][RGB_MAX_NUM];
};

#endif // PATTERN_H
