#include <iostream>
#include <QSurfaceFormat>
#include <QtOpenGL/QtOpenGL>
#include <FTGL/ftgl.h>
#include "glchart.h"

#include FT_FREETYPE_H

using namespace std;

FTGLPixmapFont static font("data/fonts/TerminusTTF-4.47.0.ttf");

void GLChart_bar::Draw_Bar(GLfloat scale_x, GLfloat scale_y, int coordX, int sizeY)
{
    scale_y = scale_y*1.0f;                      // <- тут возможно применить коэфф. пропорциональности
    glTranslatef(coordX*scale_x*this->shift_x,0.0f,0.0f); // <- сдвиг центра координат
    glBegin(GL_QUADS);                           // т.е. сдвиг матрицы на
    glColor3f(1.0f, 0.0f, 1.0f);                 // 0.6 полной шкалы
    glVertex2f(-0.1f*scale_x, 0.0f*scale_y);     // для отрисовки всех
    glVertex2f(0.1f*scale_x, 0.0f*scale_y);      // значений в центре оси Х
    glVertex2f(0.1f*scale_x, sizeY*scale_y);
    glVertex2f(-0.1f*scale_x, sizeY*scale_y);
    glEnd();
    glTranslatef(-coordX*scale_x*this->shift_x,0.0f,0.0f);

}

void GLChart_bar::PlotScattered(int *array, int *array2, int length_of_arrays, int shiftX, int shiftY, int width, int height, GLfloat scale)
{
    //char buff[100]; // переменная для текстовых переменных для FTGL
    GLfloat max = 0;
    GLfloat max2 = 0;
    GLfloat loc_scale_x = 0;
    GLfloat loc_scale_y = 0;

    glTranslatef(-shiftX+50,-shiftY+50,0.0f);
    //нахождение макс. значений
    for (int i = 0; i < length_of_arrays; i++)
    {
         if (array2[i] > max)
             max = array2[i];
    }
    for (int i = 0; i < length_of_arrays; i++)
    {
         if (array[i] > max2)
             max2 = array[i];
    }

    loc_scale_y = 0.8f*height/max;    // вычисление масштабов по осям в зависимости от
    loc_scale_x = width/max2;         // максимальных значений в массивах данных

    for (int i = 0; i < length_of_arrays; i++)
    {
         Draw_Bar(loc_scale_x, loc_scale_y, array[i], array2[i]);
    }

   // тест для отладки шкалы
   // Draw_Bar(loc_scale_x, loc_scale_y, 5.0f, 5.0f);

   // запись вычисленных значений в глобальные переменные
   this->scale_max_y = loc_scale_y;
   this->scale_max_x = loc_scale_x;
   this->max_y = max;
   this->max_x = max2;
   this->axisXlength = max2/this->shift_x;
   this->axisYlength = max;
}


SimpleClass::SimpleClass()
{
    cout << "SimpleClass constructor" << endl;
}

void SimpleClass::Message()
{
    cout << "Message class" << endl;
}

// GLChart_bar
GLChart_bar::GLChart_bar()
{
    cout << "GLChart constructor" << endl;
    this->axisXlength = 5.0f;
    this->axisYlength = 5.0f;
    this->shift_x = 0.6f;
}

// Draw Axis for chart
void GLChart_bar::DrawAxis(GLfloat scale_x, GLfloat scale_y)
{
    char buff[100]; // переменная для текстовых переменных для FTGL
    glColor3f(0.5f, 0.5f, 0.5f); // grey color

    // A x i s -------------------------------------------------------
    glBegin(GL_LINE_STRIP); // draw axis Y
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, scale_y*this->axisYlength*1.0f);
    glEnd();

    glBegin(GL_LINE_STRIP); // draw axis X
    glVertex2f(0.0f, 0.0f);
    glVertex2f(scale_x*0.9f*this->shift_x*this->axisXlength, 0.0f);
    glEnd();

    // M a r k s ------------------------------------------------------
    GLint j = 0;
    GLint i = 0;

    while ( i < scale_y*this->axisYlength) // рисуем деления на шкале Y
    {
        i++;
        if ((i % 5 == 0) or (i % 5 == 5)) // если остаток от деления = 0 или 5
         if (i*scale_y < scale_y*this->axisYlength)
        {                                 // то это число кратно 5
            glBegin(GL_LINE_STRIP);
            glVertex2f(-3.0f, i*scale_y);
            glVertex2f(3.0f, i*scale_y);
            glEnd();
            // градуировка шкалы Y
            font.FaceSize(16);
            glRasterPos2i(-30, i*scale_y-5.0f);
            sprintf (buff, "%d", i);
            font.Render(buff);
        }
    }

    while ( j < scale_x*0.9f*this->shift_x*this->axisXlength) // рисуем деления на шкале X
    {
        j++;
        if ((j % 5 == 0) or (j % 5 == 5)) // если остаток от деления = 0 или 5
            if (j*this->shift_x*scale_x < scale_x*0.9f*this->shift_x*this->axisXlength)
        {                                 // то это число кратно 5
            glBegin(GL_LINE_STRIP);
            glVertex2f(j*this->shift_x*scale_x, -3.0f);
            glVertex2f(j*this->shift_x*scale_x, 3.0f);
            glEnd();
            // градуировка шкалы X
            font.FaceSize(16);
            glRasterPos2i(static_cast<int>(j*this->shift_x*scale_x-5.0f), -20.0f);
            sprintf (buff, "%d", j);
            font.Render(buff);
        }
    }

    // Title plot
    font.FaceSize(18);
    glRasterPos2i(static_cast<int>(scale_x*0.2f*this->shift_x*this->axisXlength), static_cast<int>(scale_y*this->axisYlength*1.05f));
    font.Render("График распределения результатов выпадения орла по сериям испытаний");

    // Title Y axis
    font.FaceSize(15);

        glPushMatrix();
        glTranslatef(5*this->shift_x*scale_x, static_cast<int>(scale_y*this->axisYlength*1.05f), 0.0);
        glRotatef(45.0f, 0.0f, 0.0f, -1.0f);
            glBegin(GL_LINE_STRIP);
                glVertex2f(0.0, -20);
                glVertex2f(0.0, 20);
            glEnd();
        glRasterPos2i(20, 0);
        font.Render("Серии");
        glPopMatrix();
        glFlush();


    //font.Render("График распределения результатов выпадения орла по сериям испытаний");

    glEnd();
}

void GLChart_bar::DrawChart(GLfloat width, GLfloat height, int *array, int *array2, int length_of_arrays)
{
    this->ScreenWidth = width;
    this->ScreenHeight = height;
    GLfloat scale = width/this->axisXlength;

    //draw chart
    GLChart_bar::PlotScattered(array, array2, length_of_arrays, width/2.0f, height/2.0f, width, height, scale);

    // draw axis for this chart
    GLChart_bar::DrawAxis(this->scale_max_x, this->scale_max_y);

}


