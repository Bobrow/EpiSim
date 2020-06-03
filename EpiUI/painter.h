#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <Q
class Painter
{
public:
    Painter();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};
#endif // PAINTER_H
