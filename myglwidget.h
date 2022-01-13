#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QTime>


class MyGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyGLWidget(QWidget* parent = nullptr);
    GLfloat delta_time;
    bool flag_start;
    int *array;
    int *array2;
    int length_of_arrays;

private:
    float scale_scene;

private slots:
    //void slotTimer();

protected:
    void initializeGL() override;
    void paintGL() override;
    QTimer *timer;
};

#endif // MYGLWIDGET_H
