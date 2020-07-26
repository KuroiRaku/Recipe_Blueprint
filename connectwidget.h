#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <stdlib.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class ConnectWidget : public QWidget
{
public:
    ConnectWidget( QWidget *parent=0, const char *name=0 );
   ~ConnectWidget();
protected:
    void        paintEvent( QPaintEvent * );
    void        mousePressEvent( QMouseEvent *);
    void        mouseReleaseEvent( QMouseEvent *);
    void        mouseMoveEvent( QMouseEvent *);
private:
    QPoint     *points;                         // point array
    QColor     *colors;                         // color array
    int         count;                          // count = number of points
    bool        down;                           // TRUE if mouse down
};

#endif // CONNECTWIDGET_H
