#include <iostream>
#include "TVector.h"
#include "TMatrix.h"

/* int main()
{ */
  /* TVector<int> A, B;
  TVector<int> C = A;
  std::cout<< "A = \n" << A << "\n\n" << "B = \n" << B << "\n\nC = \n" << C << std::endl;

  int n = 20;
  int* mas = new int[n];
  for (int i = 0; i < n; i++)
    mas[i] = rand();

  A.SetVector(&(mas[0]), 10);
  B.SetVector(&(mas[10]), 10);


  C = A + B;
  TVector<int> D = A + C;

  std::cout << "A = \n" << A << "\n\n" << "B = \n" << B << "\n\nC = \n" << C << "\n\nD = \n" << D << std::endl;
  delete[] mas; */



  //std::vector<int> vect1 = { 1, 2, 3, 4 };

  //for (auto j = vect1.begin(); j != vect1.end(); j++)
  //for (auto j : vect1)
  //  std::cout << j << std::endl;


  //for (auto k = D.begin(); k != D.end(); k++)
  //for (TVectorIterator<int>& k = D.begin(); k != D.end(); k++)
  /* for (auto k : D)
    std::cout << k << std::endl; */

  /* TMatrix<int> aboba(3,3);
  aboba[0][0] = 1; aboba[0][1] = 2; aboba[0][2] = 1;
  aboba[1][0] = 1; aboba[1][1] = 4; aboba[1][2] = 3;
  aboba[2][0] = 2; aboba[2][1] = 5; aboba[2][2] = 1;

  //TMatrix<int> bebra(2,2);
  bebra[0][0] = 1;
  bebra[0][1] = 2;
  bebra[1][0] = 3;
  bebra[1][1] = 4; 
  //bebra.Rand();
  //TMatrix<int> lol = aboba.AllOccurs(1);

  aboba.SaveToFile();

  //std::cout << bebra << std::endl;

  TMatrix<int> ohio(3,3);

  ohio.ReadFromFile();

  std::cout << ohio << std::endl;

  return 0;
} */

// Вывод системы уравнений
void sysout(TMatrix<double> &matr, TVector<double> &equals, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      std::cout << matr[i][j] << "*x" << j;
      if (j < n - 1)
        std::cout << " + ";
    }
    std::cout << " = " << equals[i] << std::endl;
  }
}

TVector<double> gauss(TMatrix<double> &matr, TVector<double> &equals, int n)
{
  TVector<double> x(n);
  double max;
  int k, index;
  const double eps = 0.00001;  // точность
  k = 0;
  while (k < n) // к - идет по диагонали матрицы слева сверху
  {
    // Поиск строки с максимальным элементом в нынешнем столбце
    max = std::abs(matr[k][k]);
    index = k;
    for (int i = k + 1; i < n; i++)
      if (std::abs(matr[i][k]) > max)
      {
        max = std::abs(matr[i][k]);
        index = i; // индекс строки с макс. эелеметном
      }
    
    // Перестановка строк
    if (max < eps)
    {
      // нулевой столбец
      std::cout << "Решение получить невозможно из-за нулевого столбца ";
      std::cout << index << " матрицы A" << std::endl;
      return TVector<double>();
    }

    double temp;
    // меняем нынешнюю строку со строкой с макс элементом:
    for (int j = 0; j < n; j++) 
    {
      temp = matr[k][j];
      matr[k][j] = matr[index][j];
      matr[index][j] = temp;
    }
    // то же самое для вектора значений с другой стороны равенства:
    temp = equals[k];
    equals[k] = equals[index];
    equals[index] = temp;

    // Нормализация уравнений
    for (int i = k; i < n; i++)
    {
      temp = matr[i][k];
      if (std::abs(temp) < eps) continue; // для нулевого коэффициента пропустить
      for (int j = k; j < n; j++)
        matr[i][j] /= temp;
      equals[i] /= temp;
      if (i == k)  continue; // уравнение не вычитать само из себя
      for (int j = 0; j < n; j++)
        matr[i][j] -= matr[k][j];
      equals[i] -= equals[k];
    }
    k++;
  }

  // обратная подстановка
  for (k = n - 1; k > -1; k--)
  {
    x[k] = equals[k];
    for (int i = 0; i < k; i++)
      equals[i] -= matr[i][k] * x[k];
  }
  return x;
}

int main()
{
  int n;
  std::cout << "Введите количество уравнений: ";
  std::cin >> n;
  TMatrix<double> matr(n, n);
  TVector<double> equals(n);
  std::cin >> matr;
  std::cin >> equals;
  sysout(matr, equals, n);
  TVector<double> x = gauss(matr, equals, n);

  for (int i = 0; i < n; i++)
    std::cout << "x[" << i << "] = " << x[i] << std::endl;

  return 0;
}
