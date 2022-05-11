#ifndef PATTERN_H
#define PATTERN_H

#include <QWidget>

namespace Ui {
class Pattern;
}

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
};

#endif // PATTERN_H