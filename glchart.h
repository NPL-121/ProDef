#ifndef GLCHART_H
#define GLCHART_H
#include <GLFW/glfw3.h>
#include <QtOpenGL/QtOpenGL>

// простой класс для примера
class SimpleClass
{
public:
    SimpleClass();
    void Message();
};


class GLChart_bar
{
    public:
            GLChart_bar(); //constructor
            void DrawChart(GLfloat width, GLfloat height, int *array, int *array2, int length_of_arrays);
            int *array;
            int *array2;
            int length_of_arrays;
            GLfloat num_tmp;
    private:
            void DrawAxis(GLfloat scale_x, GLfloat scale_y);
            void PlotScattered(int *array, int *array2, int length_of_arrays, int shiftX, int shiftY, int width, int height, GLfloat scale);
            void Draw_Bar(GLfloat scale_x, GLfloat scale_y, int coordX, int sizeY);
            GLfloat axisXlength;
            GLfloat axisYlength;
            GLfloat ScreenWidth;
            GLfloat ScreenHeight;
            GLfloat scale_max_y;    // масштаб по максимальному значению из array2
            GLfloat scale_max_x;    // масштаб по максимальному значению из array
            GLfloat max_x;          // max значение из массива array
            GLfloat max_y;          // max значение из массива array2
            GLfloat shift_x;        // коэфф. сдига матрицы по оси Х; def = 0.6;


};



#endif // GLCHART_H
