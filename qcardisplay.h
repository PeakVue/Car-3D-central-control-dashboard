#ifndef QCARDISPLAY_H
#define QCARDISPLAY_H

#include <QWidget>

#include <QPainter>
#include <QtMath>

class QCarDisplay : public QWidget
{
    Q_OBJECT

public:
    QCarDisplay(QWidget *parent = nullptr);
    ~QCarDisplay();
public:
    void setvalues(qreal iValues);
    void paintEvent(QPaintEvent *evevt) override;
private:
    qreal qValues;
    const static int radius;
    const static int maxv;
    const static int minv;
};
#endif // QCARDISPLAY_H
