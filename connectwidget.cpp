#include "connectwidget.h"

#include <qwidget.h>
#include <qpainter.h>
#include <qapplication.h>
#include <stdlib.h>


const int MAXPOINTS = 2000;                     // maximum number of points
const int MAXCOLORS = 40;
//
// Constructs a ConnectWidget.
//



ConnectWidget::ConnectWidget( QWidget *parent, const char *name )
    : QWidget( parent)
{
    //setBackgroundColor( Qt::black );                // white background
    count = 0;
    down = false;
    points = new QPoint[MAXPOINTS];
    colors = new QColor[MAXCOLORS];
    for ( int i=0; i<MAXCOLORS; i++ )           // init color array
        colors[i] = QColor( rand()&255, rand()&255, rand()&255 );
}

ConnectWidget::~ConnectWidget()
{
    delete[] points;                            // cleanup
    delete[] colors;
}


//
// Handles paint events for the connect widget.
//

void ConnectWidget::paintEvent( QPaintEvent * )
{
    QPainter paint( this );
    for ( int i=0; i<count-1; i++ ) {           // connect all points
        for ( int j=i+1; j<count; j++ ) {
            paint.setPen( colors[rand()%MAXCOLORS] ); // set random pen color
            paint.drawLine( points[i], points[j] ); // draw line
        }
    }
}


//
// Handles mouse press events for the connect widget.
//

void ConnectWidget::mousePressEvent( QMouseEvent * )
{
    down = true;
    count = 0;                                  // start recording points
    QWidget::erase();                                    // erase widget contents
}


//
// Handles mouse release events for the connect widget.
//

void ConnectWidget::mouseReleaseEvent( QMouseEvent * )
{
    down = false;                               // done recording points
    update();                                   // draw the lines
}


//
// Handles mouse move events for the connect widget.
//

void ConnectWidget::mouseMoveEvent( QMouseEvent *e )
{
    if ( down && count < MAXPOINTS ) {
        QPainter paint( this );
        points[count++] = e->pos();             // add point
        paint.drawPoint( e->pos() );            // plot point
    }
}
