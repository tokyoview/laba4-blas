#pragma once
#include "TVector.h"
#include <fstream>

template<class T>
class TMatrix : public TVector<TVector<T>>
{
public:
  TMatrix();
  TMatrix(int rows, int columns);
  TMatrix(const TMatrix<T>& m);
  TMatrix(TMatrix<T>&& m);
  virtual ~TMatrix();

  int GetRows() const;
  int GetColumns() const;

  virtual TMatrix<T> operator+(const TMatrix<T>& m);
  virtual TMatrix<T> operator-(const TMatrix<T>& m);
  virtual TMatrix<T> operator*(const TMatrix<T>& m);
  virtual TMatrix<T> operator*(const T mul);
  virtual TMatrix<T> operator/(const T div);

  virtual TMatrix<T>& operator=(const TMatrix<T>& obj);
  virtual TMatrix<T>& operator=(TMatrix<T>&& obj);
  virtual bool operator==(const TMatrix<T>& obj);

  virtual TVector<T>& operator[](int index);
  virtual const TVector<T>& operator[](int index) const;

  template <class O>
  friend std::ostream& operator<<(std::ostream& o, TMatrix<O>& p);
  template <class I>
  friend std::istream& operator>>(std::istream& i, TMatrix<I>& p);

  virtual int ValueCount(const T value);
  virtual TMatrix AllOccurs(const T value);

  virtual void Rand();

  virtual void SaveToFile(const char* dest = "./data.txt");
  virtual void ReadFromFile(const char* dest = "./data.txt");
};

template<class T>
inline TMatrix<T>::TMatrix() : TVector<TVector<T>>::TVector()
{}

template<class T>
inline TMatrix<T>::TMatrix(int rows, int columns) : TVector<TVector<T>>::TVector(rows)
{
  /* for (auto t: (*this))
  {
    t = TVector<T>(columns);
  } */

 for (int i = 0; i < rows; ++i)
 {
  (*this)[i] = TVector<T>(columns);
 }
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
}

template<class T>
inline int TMatrix<T>::GetRows() const
{
  return (*this).GetLen();
  //return TVector<TVector<T>>::GetLen();
}

template<class T>
inline int TMatrix<T>::GetColumns() const
{
  if (GetRows() == 0) return 0;
  return (*this)[0].GetLen();
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix& m)
{
  int rw = GetRows();
  int col = GetColumns();
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      (*this)[i][j] = m[i][j];
}

template<class T>
inline TMatrix<T>::TMatrix(TMatrix<T>&& m)
{
  *this = m;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix& m)
{
  int rw = GetRows();
  int col = GetColumns();
  if (rw != m.GetRows() || col != m.GetColumns()) throw "bad size";
  TMatrix<T> res(rw, col);
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      res.vector[i][j] = (*this)[i][j] + m[i][j];
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix& m)
{
  int rw = GetRows();
  int col = GetColumns();
  if (rw != m.GetRows() || col != m.GetColumns()) throw "bad size";
  TMatrix<T> res(rw, col);
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      res.vector[i][j] = (*this)[i][j] - m[i][j];
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const TMatrix& m)
{
  int rw = GetRows();
  int col = GetColumns();
  if (rw != m.GetColumns()) throw "wrong size";
  TMatrix<T> res(rw, col);
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < m.GetColumns(); ++j)
      {
        res.vector[i][j] = 0;
        for (int k = 0; k < col; ++k)
          res.vector[i][j] += (*this)[i][k] * m[k][j];
      }
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const T mul)
{
  int rw = GetRows();
  int col = GetColumns();
  TMatrix<T> res(rw, col);
  if (mul == 0) return res;
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      {
        res.vector[i][j] = (*this)[i][j] * mul;
      }
  return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator/(const T div)
{
  int rw = GetRows();
  int col = GetColumns();
  if (div == 0) throw "podumay";
  TMatrix<T> res(rw, col);
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      {
        res.vector[i][j] = (*this)[i][j] / div;
      }
  return res;
}

template<class T>
inline TVector<T>& TMatrix<T>::operator[](int index)
{
  if (index < 0 || index >= GetRows()) throw "bad index";
  return TVector<TVector<T>>::operator[](index);
}

template<class T>
inline const TVector<T>& TMatrix<T>::operator[](int index) const
{
  if (index < 0 || index >= GetRows()) throw "bad index";
  return TVector<TVector<T>>::operator[](index);
}


// NOTE: left operand must be already initialized with preffered size
template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& obj)
{
  int rw = GetRows();
  int col = GetColumns();
  //(*this) = TMatrix<T>(obj.GetRows(), obj.GetColumns());
  if (rw != obj.GetRows() || col != obj.GetColumns()) throw "wrong size";
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      (*this)[i][j] = obj[i][j];
  return *this;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(TMatrix<T>&& obj)
{
  *this = obj;
  return *this;
}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix<T>& obj)
{
  int rw = GetRows();
  int col = GetColumns();
  if (rw != obj.GetRows() || col != obj.GetColumns()) throw "wrong size";
  bool flag = true;
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      if ((*this)[i][j] != obj[i][j]) flag = false;
  return flag;
}


template <class O>
inline std::ostream& operator<<(std::ostream& o, TMatrix<O>& p)
{
  int rw = p.GetRows();
  int col = p.GetColumns();
  for (int i = 0; i < rw; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      o << p[i][j] << "\t";
    }
    o << std::endl;
  }
  return o;
}

template <class I>
inline std::istream& operator>>(std::istream& is, TMatrix<I>& p)
{
  int rw = p.GetRows();
  int col = p.GetColumns();
  for (int i = 0; i < rw; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      std::cout << "Enter a[" << i << "][" << j << "]: ";
      is >> p[i][j];
    }
  }
  return is;
}

template <class T>
inline int TMatrix<T>::ValueCount(const T value)
{
  int rw = GetRows();
  int col = GetColumns();
  int count = 0;
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      if ((*this)[i][j] == value) count++;
  return count;
}

template <class T>
inline TMatrix<T> TMatrix<T>::AllOccurs(const T value)
{
  int rw = GetRows();
  int col = GetColumns();
  int count = ValueCount(value);
  TMatrix<T> res(count, 2);
  int n = 0;
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      if ((*this)[i][j] == value) 
      {
        res[n][0] = i;
        res[n++][1] = j;
      }
  return res;
}

template<class T>
inline void TMatrix<T>::Rand()
{
  int rw = GetRows();
  int col = GetColumns();
  for (int i = 0; i < rw; ++i)
    for (int j = 0; j < col; ++j)
      (*this)[i][j] = std::rand();
}

template<class T>
inline void TMatrix<T>::SaveToFile(const char* dest)
{
  std::ofstream skibidi(dest);
  if (!skibidi.is_open())
    throw "bad file!";
  if (skibidi.is_open())
  {
    skibidi << GetRows() << "\n";
    skibidi << GetColumns() << "\n";
    for (int i = 0; i < GetRows(); ++i)
    {
      for (int j = 0; j < GetColumns(); ++j)
        skibidi << (*this)[i][j] << "\n";
    }
  }
  skibidi.close();
}

template<class T>
inline void TMatrix<T>::ReadFromFile(const char* dest)
{
  std::ifstream skibidi(dest);
  if (!skibidi.is_open())
    throw "bad file!";
  if (skibidi.is_open())
  {
    int rw = 0, col = 0;
    skibidi >> rw;
    skibidi >> col;
    if (rw != GetRows() || col != GetColumns())
      throw "cannot read from file to that matrix!";
    for (int i = 0; i < rw; ++i)
      for (int j = 0; j < col; ++j)
        skibidi >> (*this)[i][j];
  }
  skibidi.close();
}