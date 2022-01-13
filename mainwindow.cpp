#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->series_def = 50;
    this->events = 30;


  /// S I G N A l S   C O N N E C T ////////////////////////
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(BeginDef()));
}

int MainWindow::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Основная функция программы - определение статистических данных
void MainWindow::BeginDef()
{
    QString Sser;
    QString Sneagle;
    QString Sumn;
    QString Sres;
    QString Sj;
    QString Sjj;
    QString Sjj2;

    int ser = ui->lineEdit_num_ser->text().toInt();      // количество серий испытаний
    int event = ui->lineEdit_num_events->text().toInt(); // количество событий (подкидываний монетки) в каждой серии
                                                         // т.е. всего будет ser*event подкидываний монет
    this->series_def = ser;
    this->events = event;

    int result = 0; // результат одного броска
    int neagle = 0; // количество выпадений орла за серию
    int els_array = 0; // количество элементов массива

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int j = 1; j <= ser; j++)
    {
        neagle = 0;
        for ( int i = 1; i <= event; i++)
        {
            result = getRandomNumber(1,2);        // подбрасываем монетку

            if (result == 2) neagle = neagle + 1; // если выпала 2, то считаем
                                                  // это орлом и суммируем
        }
        Sneagle = QString::number(neagle); //переводим числовое значение в строку
        Sneagle.append(" "); // добавляем пробел, чтобы разделить числа
        Sumn.append(Sneagle); //добавляем к итоговой строке

    ui->textEdit->setText(Sumn); // выводим итоговую строку

    }

    // Преобразование строки Sumn в массив int
    // преобразуем строку Sumn в список строк. Разделителем установим пробел.
    QStringList Slist = Sumn.split(" ",QString::SkipEmptyParts);
    int len = Slist.length();   // определяем длину (кол-во элементов)
                                // контейнера строк (списка строк)
    int *array = new int [len]; // объявляем динамический массив
                                // с кол-вом элементов равным кол-ву
                                // строк в списке Slist
    int i = 0;                  // начальный индекс массива = 0
    int key = 0;

    //cout << "Длина строки: " << len << endl;

    foreach(QString num, Slist) // цикл записи значений списка строк
    {                           // в элементы массива начиная с индекса
                                // массива '0'
        //cout << num.toInt() << endl; //проверка вывод элементов списка
        array[i] = num.toInt();
        i++;
    }
    //for (i=0; i<len; i++)     // проверка каждого элемента массива
    //cout << array[i] << endl; // вывод элементов массива
    els_array = i;              // окончательное значение счетчика сохраняем
                                // в переменной els_array (max index array)
    //cout << "Кол-во элементов: " << els_array << endl;

    // -----------------------------------------------------------------------
    //Подсчет количества элементов массива
    //------------------------------------------------------------------------
    int *array_num = new int [len]; // объявляем новый динамический массив
                                    // для учета количества одинаковых чисел
    i = 0; // обнуляем счетчик

    for (i = 0; i < els_array; i++) // обнуляем все элементы массива
    {
        array_num[i] = 0;
    }

    for (i = 0; i < els_array; i++) //перебираем элементы массива
    {
        int find_tmp = array[i];    //i-й элемент массива берем в качестве
                                    // критерия поиска
        for (int j=0; j < els_array; j++) // используя поисковый критерий
        {                                 // перебираем каждый элемент
            if (array[j] == find_tmp)     // массива.
                array_num[i]++;     // в случае совпадения в соотв. j-й элемент
        }                           // массива записываем количество совпадений
    //    cout << "Find for: " << find_tmp << " = " << array_num[i] << endl;
    }

    //for (int j=0; j<len; j++)     // проверка каждого элемента массива
    //cout << array[j] << " : " << array_num[j] << endl; // вывод всех(!) элементов массивов

    for (int i=0; i<len; i++)      // повторяющимся элементам массива присваиваем
    {                              // значение = 0
        key = array[i];
        for (int j=i+1; j<len; j++)
        {
            if (array[j] == key)
            {
                array[j] = 0;
                array_num[j] =0;
                //iDel(array, len, j);
            }
        }
    }

   // -------------------------- п р о в е р о ч н ы е   ф у н к ц и и -----------------------------------------------------------------
     //вывод всех(!) элементов массивов
     //for (int j=0; j<len; j++)     // проверка каждого элемента массива
     //cout << j << "-й элемент = " << array[j] << ", встречается: " << array_num[j] << " раз"<< endl;

     //вывод без нулевых значений (подготовленные для построения графика)
     for (int j=0; j<len; j++)
     {
          if (array[j] != 0)
          {
          cout << j << "-й элемент = " << array[j] << ", встречается: " << array_num[j] << " раз"<< endl; // вывод всех(!) элементов массивов

          // вывод того же самого в textEdit на форме
          Sj = QString::number(j); //переводим числовое значение в строку
          Sj.append("-й элемент = ");
          Sjj = QString::number(array[j]);
          Sj.append(Sjj);
          Sj.append(", встречается: ");
          Sjj2 = QString::number(array_num[j]);
          Sj.append(Sjj2);
          Sj.append(" раз");
          Sj.append("\n");            // перевод новой строки

          Sres.append(Sj);            // добавляем к итоговой строке
          }
     }

     ui->textEdit_2->setText(Sres); // выводим итоговую строку

     //=================================================
     // Подготовка
     ui->openGLWidget->array = array;
     ui->openGLWidget->array2 = array_num;
     ui->openGLWidget->length_of_arrays = len;
     ui->openGLWidget->flag_start = true;


}

MainWindow::~MainWindow()
{
    delete ui;
}
