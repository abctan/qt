#ifndef BINARY_H
#define BINARY_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include "sliderrange.h"

class Binary : public QWidget
{
    Q_OBJECT

    enum eBitWidth {
        BIT_WIDTH_08 = 8,
        BIT_WIDTH_16 = 16,
        BIT_WIDTH_32 = 32,
    };

    enum eEndian {
        BIT_LITTLE_ENDIAN,
        BIT_BIG_ENDIAN
    };

public:
    Binary(QWidget *parent = nullptr);
    ~Binary();
    void initUi(void);
    void initConnect(void);
    unsigned int getVal() const;
    unsigned int getVal(int low, int high) const;
    void setVal(unsigned int val);
    void setVal(unsigned int val, int low, int high);
    int getLeftValue()              const;
    int getRightValue()             const;
    int getMinValue()               const;
    int getMaxValue()               const;

    static QString setPushButtonQss(QPushButton *btn,                               //按钮对象
                                    int radius = 5,                                 //圆角半径
                                    int padding = 8,                                //间距
                                    const QString &normalColor = "#34495E",         //正常颜色
                                    const QString &normalTextColor = "#FFFFFF",     //文字颜色
                                    const QString &hoverColor = "#4E6D8C",          //悬停颜色
                                    const QString &hoverTextColor = "#F0F0F0",      //悬停文字颜色
                                    const QString &pressedColor = "#2D3E50",        //按下颜色
                                    const QString &pressedTextColor = "#B8C6D1",    //按下文字颜色
                                    int transparency = 100);                        //透明度

    void paintEvent(QPaintEvent* e);

signals:
    void changeAssicVal(unsigned int val);
    void sliderChanged(int leftValue, int rightValue);

public slots:
    void changeBinaryDisplay(bool checked);

private:
    unsigned int value;                 // 结果值
    enum eBitWidth bitWidth;            // bit 位宽
    enum eEndian endian;                // 字节序
    QLabel *btnLabel[BIT_WIDTH_32];     // bit位标志
    QPushButton *btnBit[BIT_WIDTH_32];  // bit位按钮
    SliderRange *binSlider;
};
#endif // WIDGET_H
