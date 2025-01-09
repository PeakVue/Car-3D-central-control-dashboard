#include "qcardisplay.h"

const int QCarDisplay::radius=150;
const int QCarDisplay::maxv=400;
const int QCarDisplay::minv=0;

QCarDisplay::QCarDisplay(QWidget *parent)
    : QWidget(parent)
{
    qValues=0;
}

QCarDisplay::~QCarDisplay()
{

}

void QCarDisplay::setvalues(qreal iValues)
{
    qValues=iValues;
    update();
}


void QCarDisplay::paintEvent(QPaintEvent *evevt)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint center(width()/2,height()/2);
    painter.save();

    //draw background
    painter.translate(center);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(142,142,142));
    const int bkRadius=radius+3;
    painter.drawEllipse(QPoint(),bkRadius,bkRadius);

    painter.rotate(-135);
    const int longstep=10;
    const int shortstep=50;

    for (int i=0;i<=shortstep;i++)
    {
        //80% green 20 red
        painter.setPen(i<shortstep*0.8?QColor(32,243,32):QColor(243,32,32));
        if(i%(shortstep/longstep)!=0)
        {
            QPoint p1(0,-(radius-8));
            QPoint p2(0,-radius);
            painter.drawLine(p1,p2);
        }
        else
        {
            QPoint p1(0,-(radius-14));
            QPoint p2(0,-radius);
            painter.drawLine(p1,p2);
        }
        painter.rotate(270.0/shortstep);
    }


    painter.restore();
    QFontMetrics fm=painter.fontMetrics();
    int tx=center.x();
    int ty=int(center.y()+(radius/1.4142));

    QString title="instrument panel";
    QSize tsz=fm.size(0,title);
    QRect trect(QPoint(tx-tsz.width()/2,ty-tsz.height()/2),tsz);
    painter.setPen(QColor(127,127,127));
    painter.setBrush(QColor(173,163,163));
    painter.drawRoundedRect(trect.adjusted(-6,-4,6,4),3,3);
    painter.setPen(QColor(243,243,243));
    painter.setBrush(Qt::NoBrush);
    painter.drawText(trect,title);
    painter.setPen(QColor(243,243,243));
    const int hand=radius-21;

    for(int i=0;i<=longstep;i++)
    {
        qreal angle=qDegreesToRadians(-135.0+i*(270.0/longstep));
        QString etext=QString::number(minv+i*(maxv-minv)/longstep);
        QPointF dirvec(qSin(angle),-qCos(angle));
        QPointF ecenter(center.x()+hand*dirvec.x(),center.y()+hand*dirvec.y());
        QSize esz=fm.size(0,etext);
        QRectF erect(QPointF(ecenter.x()-esz.width()/2,ecenter.y()-esz.height()/2),esz);
        painter.drawText(erect,etext);
    }


    painter.save();
    QPoint triangle[]={
        {-5,0},
        {0,25-radius},
        {5,0}
    };
    qreal degree=-135.0+270.0*(qValues-minv)/(maxv-minv);
    painter.translate(center);
    painter.rotate(degree);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawPolygon(triangle,3);
    painter.setPen(QPen(QColor(214,0,0),2));
    painter.drawEllipse(QPoint(),7,7);
}
