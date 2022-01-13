#include "myglwidget.h"
#include <QSurfaceFormat>
#include <QtOpenGL/QtOpenGL>
#include "glchart.h"
#include <FTGL/ftgl.h>
#include <clocale>

//GLChart_bar *Chart;

FTGLPixmapFont static font("data/fonts/TerminusTTF-4.47.0.ttf");

//static SimpleClass sclass;
static GLChart_bar chart;

MyGLWidget::MyGLWidget(QWidget* parent):
    QOpenGLWidget(parent)
{

    QSurfaceFormat format;

    format.setSamples(8); // не работает
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    this->flag_start = false;
}

void MyGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();
    this->scale_scene = 200.0;
    glEnable(GL_MULTISAMPLE); // не работает  
}

void Draw_Quad(GLfloat scale)
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(-0.5f*scale, -0.5f*scale);
    glVertex2f(0.5f*scale, -0.5f*scale);
    glVertex2f(0.5f*scale, 0.5f*scale);
    glVertex2f(-0.5f*scale, 0.5f*scale);
    glEnd();
}


void MyGLWidget::paintGL()
{  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-this->geometry().size().width()/2, this->geometry().size().width()/2,
            -this->geometry().size().height()/2, this->geometry().size().height()/2, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);


    glPushMatrix();

    if (this->flag_start == true)
    {
        ///// this oop code here testing
        chart.DrawChart(this->geometry().size().width(), this->geometry().size().height(), this->array, this->array2, this->length_of_arrays);
    }


    glEnd();
    glPopMatrix();
    //glFlush();
    this->update();
}

/*void MyGLWidget::slotTimer()
{
    if (this->animate == true)
    {
        this->delta_time = ( mtime() - this->start_time) / 1000; // Счетчик времени, сек

    }
    else
    {
        this->delta_time_stop = (mtime() - this->stop_time);
    }
} */
