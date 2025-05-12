#include <gtest.h>
#include "TMatrix.h"
#include <fstream>

// Тест конструктора по умолчанию
TEST(TMatrixTest, DefaultConstructor) 
{
  TMatrix<int> matrix;
  EXPECT_EQ(0, matrix.GetRows());
  EXPECT_EQ(0, matrix.GetColumns());
}

// Тест конструктора с параметрами
TEST(TMatrixTest, ParametrizedConstructor) 
{
  TMatrix<int> matrix(3, 4);
  EXPECT_EQ(3, matrix.GetRows());
  EXPECT_EQ(4, matrix.GetColumns());
  
  // Проверяем, что все элементы инициализированы (значения зависят от реализации TVector)
  for (int i = 0; i < matrix.GetRows(); ++i) 
  {
    for (int j = 0; j < matrix.GetColumns(); ++j) 
    {
      EXPECT_EQ(0, matrix[i][j]); // Предполагаем, что TVector инициализирует элементы нулями
    }
  }
}

// Тест оператора сложения
TEST(TMatrixTest, AdditionOperator) 
{
  TMatrix<int> matrix1(2, 2);
  matrix1[0][0] = 1; matrix1[0][1] = 2;
  matrix1[1][0] = 3; matrix1[1][1] = 4;
  
  TMatrix<int> matrix2(2, 2);
  matrix2[0][0] = 5; matrix2[0][1] = 6;
  matrix2[1][0] = 7; matrix2[1][1] = 8;
  
  TMatrix<int> result = matrix1 + matrix2;
  
  EXPECT_EQ(6, result[0][0]);
  EXPECT_EQ(8, result[0][1]);
  EXPECT_EQ(10, result[1][0]);
  EXPECT_EQ(12, result[1][1]);
  
  // Проверка на исключение при разных размерах
  TMatrix<int> matrix3(3, 3);
  EXPECT_THROW(matrix1 + matrix3, const char*);
}

// Тест оператора вычитания
TEST(TMatrixTest, SubtractionOperator) 
{
  TMatrix<int> matrix1(2, 2);
  matrix1[0][0] = 5; matrix1[0][1] = 6;
  matrix1[1][0] = 7; matrix1[1][1] = 8;
  
  TMatrix<int> matrix2(2, 2);
  matrix2[0][0] = 1; matrix2[0][1] = 2;
  matrix2[1][0] = 3; matrix2[1][1] = 4;
  
  TMatrix<int> result = matrix1 - matrix2;
  
  EXPECT_EQ(4, result[0][0]);
  EXPECT_EQ(4, result[0][1]);
  EXPECT_EQ(4, result[1][0]);
  EXPECT_EQ(4, result[1][1]);
}

// Тест оператора умножения матриц
TEST(TMatrixTest, MultiplicationOperator) 
{
  TMatrix<int> matrix1(2, 3);
  matrix1[0][0] = 1; matrix1[0][1] = 2; matrix1[0][2] = 3;
  matrix1[1][0] = 4; matrix1[1][1] = 5; matrix1[1][2] = 6;
  
  TMatrix<int> matrix2(3, 2);
  matrix2[0][0] = 7;  matrix2[0][1] = 8;
  matrix2[1][0] = 9;  matrix2[1][1] = 10;
  matrix2[2][0] = 11; matrix2[2][1] = 12;
  
  TMatrix<int> result = matrix1 * matrix2;
  
  EXPECT_EQ(58, result[0][0]);
  EXPECT_EQ(64, result[0][1]);
  EXPECT_EQ(139, result[1][0]);
  EXPECT_EQ(154, result[1][1]);
}

// Тест оператора умножения на скаляр
TEST(TMatrixTest, ScalarMultiplication) 
{
  TMatrix<int> matrix(2, 2);
  matrix[0][0] = 1; matrix[0][1] = 2;
  matrix[1][0] = 3; matrix[1][1] = 4;
  
  TMatrix<int> result = matrix * 2;
  
  EXPECT_EQ(2, result[0][0]);
  EXPECT_EQ(4, result[0][1]);
  EXPECT_EQ(6, result[1][0]);
  EXPECT_EQ(8, result[1][1]);
}

// Тест оператора деления на скаляр
TEST(TMatrixTest, ScalarDivision) 
{
  TMatrix<int> matrix(2, 2);
  matrix[0][0] = 4; matrix[0][1] = 6;
  matrix[1][0] = 8; matrix[1][1] = 10;
  
  TMatrix<int> result = matrix / 2;
  
  EXPECT_EQ(2, result[0][0]);
  EXPECT_EQ(3, result[0][1]);
  EXPECT_EQ(4, result[1][0]);
  EXPECT_EQ(5, result[1][1]);
  
  // Проверка деления на ноль
  EXPECT_THROW(matrix / 0, const char*);
}

// Тест оператора присваивания
TEST(TMatrixTest, AssignmentOperator) 
{
  TMatrix<int> matrix1(2, 2);
  matrix1[0][0] = 1; matrix1[0][1] = 2;
  matrix1[1][0] = 3; matrix1[1][1] = 4;
  
  TMatrix<int> matrix2(2,2);
  matrix2 = matrix1;
  
  EXPECT_EQ(2, matrix2.GetRows());
  EXPECT_EQ(2, matrix2.GetColumns());
  EXPECT_EQ(1, matrix2[0][0]);
  EXPECT_EQ(2, matrix2[0][1]);
  EXPECT_EQ(3, matrix2[1][0]);
  EXPECT_EQ(4, matrix2[1][1]);
}

// Тест оператора сравнения
TEST(TMatrixTest, EqualityOperator) 
{
  TMatrix<int> matrix1(2, 2);
  matrix1[0][0] = 1; matrix1[0][1] = 2;
  matrix1[1][0] = 3; matrix1[1][1] = 4;
  
  TMatrix<int> matrix2(2, 2);
  matrix2[0][0] = 1; matrix2[0][1] = 2;
  matrix2[1][0] = 3; matrix2[1][1] = 4;
  
  EXPECT_TRUE(matrix1 == matrix2);
  
  matrix2[1][1] = 5;
  EXPECT_FALSE(matrix1 == matrix2);
}

// Тест метода ValueCount
TEST(TMatrixTest, ValueCountMethod) 
{
  TMatrix<int> matrix(3, 3);
  matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
  matrix[1][0] = 2; matrix[1][1] = 3; matrix[1][2] = 2;
  matrix[2][0] = 3; matrix[2][1] = 2; matrix[2][2] = 1;
  
  EXPECT_EQ(2, matrix.ValueCount(1));
  EXPECT_EQ(4, matrix.ValueCount(2));
  EXPECT_EQ(0, matrix.ValueCount(5));
}

// Тест метода AllOccurs
TEST(TMatrixTest, AllOccursMethod) 
{
  TMatrix<int> matrix(3, 3);
  matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
  matrix[1][0] = 2; matrix[1][1] = 3; matrix[1][2] = 2;
  matrix[2][0] = 3; matrix[2][1] = 2; matrix[2][2] = 1;
  
  TMatrix<int> result = matrix.AllOccurs(2);
  EXPECT_EQ(4, result.GetRows());
  EXPECT_EQ(2, result.GetColumns());
  
  // Проверяем координаты всех вхождений 2
  // Порядок может быть разным, поэтому проверяем все возможные комбинации
  bool found1 = false, found2 = false, found3 = false, found4 = false;
  for (int i = 0; i < result.GetRows(); ++i) 
  {
    if (result[i][0] == 0 && result[i][1] == 1) found1 = true;
    if (result[i][0] == 1 && result[i][1] == 0) found2 = true;
    if (result[i][0] == 1 && result[i][1] == 2) found3 = true;
    if (result[i][0] == 2 && result[i][1] == 1) found4 = true; // Это тоже должно быть найдено
  }
  EXPECT_TRUE(found1);
  EXPECT_TRUE(found2);
  EXPECT_TRUE(found3);
  EXPECT_TRUE(found4);
}

// Тест метода Rand
TEST(TMatrixTest, RandMethod) 
{
  TMatrix<int> matrix(3, 3);
  matrix.Rand();
  
  // Проверяем, что все элементы заполнены (точные значения нельзя проверить)
  for (int i = 0; i < matrix.GetRows(); ++i) 
  {
    for (int j = 0; j < matrix.GetColumns(); ++j) 
    {
      EXPECT_NE(0, matrix[i][j]); // Хотя есть небольшая вероятность, что rand() вернет 0
    }
  }
}


// Тест для SaveToFile и ReadFromFile
TEST(TMatrixFileIOTest, SaveAndReadFile) {
    // Создаем тестовую матрицу
    TMatrix<int> originalMatrix(2, 3);
    originalMatrix[0][0] = 1; originalMatrix[0][1] = 2; originalMatrix[0][2] = 3;
    originalMatrix[1][0] = 4; originalMatrix[1][1] = 5; originalMatrix[1][2] = 6;

    const char* testFileName = "test_matrix.txt";

    // Сохраняем матрицу в файл
    originalMatrix.SaveToFile(testFileName);

    // Проверяем, что файл создан
    std::ifstream testFile(testFileName);
    EXPECT_TRUE(testFile.is_open());
    testFile.close();

    // Создаем новую матрицу для чтения
    TMatrix<int> loadedMatrix(2, 3);
    loadedMatrix.ReadFromFile(testFileName);

    // Проверяем, что матрицы идентичны
    EXPECT_EQ(2, loadedMatrix.GetRows());
    EXPECT_EQ(3, loadedMatrix.GetColumns());
    
    for (int i = 0; i < originalMatrix.GetRows(); ++i) {
        for (int j = 0; j < originalMatrix.GetColumns(); ++j) {
            EXPECT_EQ(originalMatrix[i][j], loadedMatrix[i][j]);
        }
    }

    // Удаляем тестовый файл
    remove(testFileName);
}

// Тест для проверки исключения при несовпадении размеров
TEST(TMatrixFileIOTest, ReadWithWrongSize) {
    // Создаем тестовую матрицу
    TMatrix<int> originalMatrix(2, 2);
    originalMatrix[0][0] = 1; originalMatrix[0][1] = 2;
    originalMatrix[1][0] = 3; originalMatrix[1][1] = 4;

    const char* testFileName = "test_matrix.txt";

    // Сохраняем матрицу в файл
    originalMatrix.SaveToFile(testFileName);

    // Пытаемся прочитать в матрицу другого размера
    TMatrix<int> wrongSizeMatrix(3, 3);
    EXPECT_THROW(wrongSizeMatrix.ReadFromFile(testFileName), const char*);

    // Удаляем тестовый файл
    remove(testFileName);
}

// Тест для пустой матрицы
TEST(TMatrixFileIOTest, EmptyMatrix) {
    TMatrix<int> emptyMatrix;
    const char* testFileName = "empty_matrix.txt";

    // Сохраняем пустую матрицу
    emptyMatrix.SaveToFile(testFileName);

    // Проверяем содержимое файла
    std::ifstream testFile(testFileName);
    int rows, cols;
    testFile >> rows >> cols;
    EXPECT_EQ(0, rows);
    EXPECT_EQ(0, cols);
    testFile.close();

    // Пытаемся прочитать
    TMatrix<int> loadedMatrix;
    loadedMatrix.ReadFromFile(testFileName);
    EXPECT_EQ(0, loadedMatrix.GetRows());
    EXPECT_EQ(0, loadedMatrix.GetColumns());

    // Удаляем тестовый файл
    remove(testFileName);
}

// Тест для проверки обработки несуществующего файла
TEST(TMatrixFileIOTest, NonExistentFile) {
    TMatrix<int> matrix(2, 2);
    const char* nonExistentFile = "non_existent_file.txt";
    
    EXPECT_THROW(matrix.ReadFromFile(nonExistentFile), const char*);
}