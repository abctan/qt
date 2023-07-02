#include "binary.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

#define GET_BIT(x, bit)              (((x) >> (bit)) & 1)             /* 获取第bit位 */
#define CLEAR_BIT(x, bit)            ((x) &= ~(1 << (bit)))           /* 清零第bit位 */
#define SET_BIT(x, bit)              ((x) |= (1 << (bit)))            /* 置位第bit位 */
#define GET_BIT_M_TO_N(x, n, m)      ((x << (31 - (m))) >> ((31 - (m)) + (n)))   /* 获取第[n:m]位的值  eg 第二位到第三位:[2:3] */
//#define SET_BIT_N_M_Y(x, n, m, y)    ((x & (~((((1U) << (m - n + 1)) - 1U) << n))) | (y << n))  /* 设置x第[n:m]位的值为y */
#define SET_BIT_N_M_Y(x, n, m, y) ({\
unsigned int mask = ((((~0U) << (31 - (m))) >> (31 - (m) + (n))) << (n));\
(((x) & (~mask)) | (((y) << (n)) & mask));\
})


Binary::Binary(QWidget *parent)
    : QWidget(parent)
{
    this->value = 0;
    this->bitWidth = Binary::BIT_WIDTH_32;
    this->endian = Binary::BIT_LITTLE_ENDIAN;
    this->setWindowTitle("二进制bit位");

    initUi();
    initConnect();
}

Binary::~Binary()
{
}

void Binary::initUi()
{
    QSize everyBlockSize = QSize(22, 22);
    for (int i = 0; i < this->bitWidth; ++i) {
        this->btnLabel[i] = new QLabel(QString::number(i), this);
        this->btnLabel[i]->setMinimumSize(everyBlockSize);
        this->btnLabel[i]->setAlignment(Qt::AlignCenter);
        this->btnLabel[i]->setStyleSheet("color: deepskyblue");
        QFont f = this->btnLabel[i]->font();
        f.setPixelSize(10);
        this->btnLabel[i]->setFont(f);

        this->btnBit[i] = new QPushButton("0", this);
        this->btnBit[i]->setObjectName(QString::number(i));
        this->btnBit[i]->setMinimumSize(everyBlockSize);

        QFont btnFont = this->btnBit[i]->font();
        btnFont.setPixelSize(13);
        this->btnBit[i]->setFont(btnFont);
        Binary::setPushButtonQss(this->btnBit[i], 0, 0, "white", "red", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1", 70);
    }

    this->binSlider = new SliderRange(0, this->bitWidth - 1, this);
    this->binSlider->setMaximumHeight(everyBlockSize.height());

    QVBoxLayout *vBinlayout = new QVBoxLayout();
    QHBoxLayout *hBtnlayout = new QHBoxLayout();
    QHBoxLayout *hBtnLabellayout = new QHBoxLayout();

    vBinlayout->setContentsMargins(0, 0, 0, 0);
    vBinlayout->setSpacing(0);
    hBtnlayout->setContentsMargins(0, 0, 0, 0);
    hBtnlayout->setSpacing(0);
    hBtnLabellayout->setContentsMargins(0, 0, 0, 0);
    hBtnLabellayout->setSpacing(0);

    for (int i = this->bitWidth - 1; i >= 0; --i) {
        hBtnLabellayout->addWidget(this->btnLabel[i]);
        hBtnlayout->addWidget(this->btnBit[i]);
    }

    vBinlayout->addLayout(hBtnLabellayout);
    vBinlayout->addLayout(hBtnlayout);
    vBinlayout->addWidget(this->binSlider);
    this->setLayout(vBinlayout);
}

void Binary::initConnect()
{
    for (int i = 0; i < this->bitWidth; ++i) {
        connect(this->btnBit[i], &QPushButton::clicked, this, &Binary::changeBinaryDisplay);
    }
    connect(this->binSlider, &SliderRange::valueChanged, this, [=](int leftValue, int rightValue) {
        emit this->sliderChanged(leftValue, rightValue);
    });
}

unsigned int Binary::getVal() const
{
    return this->value;
}

unsigned int Binary::getVal(int low, int high) const
{
    if (high <= low) {
        return 0;
    }
    return GET_BIT_M_TO_N(this->value, low, high);
}

void Binary::setVal(unsigned int val)
{
    char bitWidh;
    QString normalColor;

    this->value = val;

    for (int i = 0; i < this->bitWidth; ++i) {
        bitWidh = GET_BIT(this->value, i);
        this->btnBit[i]->setText(QString::number(bitWidh));
        normalColor = bitWidh ? "blue" : "red";
        Binary::setPushButtonQss(this->btnBit[i], 0, 0, "white", normalColor, "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1", 70);
    }
}

void Binary::setVal(unsigned int val, int low, int high)
{
    if (high <= low) {
        return;
    }

    char bitWidh;
    QString normalColor;
    this->value = SET_BIT_N_M_Y(this->value, low, high, val);

    for (int i = 0; i < this->bitWidth; ++i) {
        bitWidh = GET_BIT(this->value, i);
        this->btnBit[i]->setText(QString::number(bitWidh));
        normalColor = bitWidh ? "blue" : "red";
        Binary::setPushButtonQss(this->btnBit[i], 0, 0, "white", normalColor, "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1", 70);
    }
}

int Binary::getLeftValue() const
{
    return this->binSlider->getLeftValue();
}

int Binary::getRightValue() const
{
    return this->binSlider->getRightValue();
}

int Binary::getMinValue() const
{
    return this->binSlider->getMinValue();
}

int Binary::getMaxValue() const
{
    return this->binSlider->getMaxValue();
}

QString Binary::setPushButtonQss(QPushButton *btn, int radius, int padding,
                                    const QString &normalColor,
                                    const QString &normalTextColor,
                                    const QString &hoverColor,
                                    const QString &hoverTextColor,
                                    const QString &pressedColor,
                                    const QString &pressedTextColor,
                                    int transparency)
{
    QStringList list;
    QColor clr(normalColor);
    int r, g, b;
    clr.getRgb(&r, &g, &b);
    list.append(QString("QPushButton{border-style:none;padding:%1px;border-radius:%2px;color:%3;background-color:rgba(%4,%5,%6,%7%);}")
                    .arg(padding).arg(radius).arg(normalTextColor).arg(r).arg(g).arg(b).arg(transparency));
    list.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    list.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));

    QString qss = list.join("");
    btn->setStyleSheet(qss);
    return qss;
}

void Binary::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter paint(this);
    paint.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    paint.drawRect(this->rect());

    int step = 8;
    QRect btnRect = this->btnBit[0]->geometry();
    for (int i = this->bitWidth - 1; i >= step; i -= step) {
        QRect rect = this->btnLabel[i]->geometry();
        paint.drawLine(rect.width() * step + rect.x(), rect.y(),
                       rect.width() * step + rect.x(), rect.y() + rect.height() + btnRect.height());
    }
    QRect rect = this->btnLabel[0]->geometry();
    paint.drawLine(0, rect.height(), this->width(), rect.height());
    paint.drawLine(0, rect.height() + btnRect.height(), this->width(), rect.height() + btnRect.height());
}

void Binary::changeBinaryDisplay(bool checked)
{
    Q_UNUSED(checked);

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString text = btn->text();
    int bitOffset = btn->objectName().toInt();
    int setBit = !text.toInt();
    btn->setText(QString::number(setBit));
    QString normalColor;
    if (setBit == 0) {
        CLEAR_BIT(this->value, bitOffset);
        normalColor = "red";
    } else {
        SET_BIT(this->value, bitOffset);
        normalColor = "blue";
    }
    Binary::setPushButtonQss(btn, 0, 0, "white", normalColor, "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1", 70);

    emit changeAssicVal(this->value);  // 发送信号
}




















