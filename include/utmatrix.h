
#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <utility>
#include <string>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class T>
class TVector
{
protected:
	T* pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	T& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	// скалярные операции
	TVector  operator+(const T& val);   // прибавить скаляр
	TVector  operator-(const T& val);   // вычесть скаляр
	TVector  operator*(const T& val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector& v);     // сложение
	TVector  operator-(const TVector& v);     // вычитание
	T  operator*(const TVector& v);     // скалярное произведение
	void InitInt(int a)				  // проинициализировать вектор
	{
		for (int i = StartIndex; i < Size; i++)
			pVector[i] = a;
	}

	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

// Конструктор 
template <class T>
TVector<T>::TVector(int s, int si) : Size(s), StartIndex(si)
{
	if ((s < 1) || (s > MAX_VECTOR_SIZE) || (si < 0) || (si > MAX_MATRIX_SIZE - 1))
		throw string("Wrong arguments");
	pVector = new T[s]{};
}

// Конструктор копирования
template <class T>
TVector<T>::TVector(const TVector<T>& v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new T[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
}

// Деструктор
template <class T>
TVector<T>::~TVector()
{
	delete[] pVector;
}

// Доступ
template <class T>
T& TVector<T>::operator[](int pos)
{
	pos -= StartIndex;
	if ((pos < 0) || (pos >= Size))
		throw string("Wrong argument");
	return pVector[pos];
}

// Сравнение
template <class T>
bool TVector<T>::operator==(const TVector& v) const
{
	if (this == &v)
		return true;
	if (Size != v.Size)
		return false;
	if (StartIndex != v.StartIndex)
		return false;
	for (int i = 0; i < Size; i++) {
		if (pVector[i] != v.pVector[i])
			return false;
	}
	return true;
}

// Сравнение
template <class T>
bool TVector<T>::operator!=(const TVector& v) const
{
	return !(*this == v);
}

// Присваивание
template <class T>
TVector<T>& TVector<T>::operator=(const TVector& v)
{
	if (this == &v)
		return *this;
	if (Size != v.Size) {
		T* tmp = new T[v.Size];
		delete[] pVector;
		pVector = tmp;
		Size = v.Size;
	}
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
	return *this;
}

// Прибавить скаляр
template <class T>
TVector<T> TVector<T>::operator+(const T& val)
{
	TVector<T> out(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		out.pVector[i] = pVector[i] + val;
	return out;
}

template <class T> // вычесть скаляр
TVector<T> TVector<T>::operator-(const T& val)
{
	TVector<T> out(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		out.pVector[i] = pVector[i] - val;
	return out;
}

template <class T> // умножить на скаляр
TVector<T> TVector<T>::operator*(const T& val)
{
	TVector<T> out(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		out.pVector[i] = pVector[i] * val;
	return out;

}

template <class T> // сложение
TVector<T> TVector<T>::operator+(const TVector<T>& v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw string("Different size of TVector's");
	TVector<T> out(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		out.pVector[i] = pVector[i] + v.pVector[i];
	return out;
}

template <class T> // вычитание
TVector<T> TVector<T>::operator-(const TVector<T>& v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw string("Different size of TVector's");
	TVector<T> out(Size, StartIndex);
	for (int i = 0; i < Size; i++)
		out.pVector[i] = pVector[i] - v.pVector[i];
	return out;
}

template <class T> // скалярное произведение
T TVector<T>::operator*(const TVector<T>& v)
{
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
		throw string("Different size of TVector's");
	T sum = 0;
	for (int i = 0; i < Size; i++)
		sum += pVector[i] * v.pVector[i];
	return sum;
}


// Верхнетреугольная матрица
template <class T>
class TMatrix : public TVector<TVector<T>>
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<T> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix operator+ (const TMatrix& mt);         // сложение
	TMatrix operator- (const TMatrix& mt);         // вычитание
	TMatrix operator* (const TMatrix& mt);         // умножение 
	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}

	void InitM(int a)
	{
		for (int i = 0; i < Size; i++)
			pVector[i].InitInt(0);
	}
};

template <class T>
TMatrix<T>::TMatrix(int s) : TVector<TVector<T>>(s)
{
	if ((s < 1) || (s > MAX_MATRIX_SIZE))
		throw string("Wrong argument");
	for (int i = 0; i < s; i++) {
		TVector<T> tmp(s - i, i);
		this->pVector[i] = tmp;
	}
}

template <class T> // конструктор копирования
TMatrix<T>::TMatrix(const TMatrix<T>& mt) :
	TVector<TVector<T>>(mt) {}

template <class T> // конструктор преобразования типа
TMatrix<T>::TMatrix(const TVector<TVector<T> >& mt) :
	TVector<TVector<T>>(mt) {}

template <class T> // сравнение
bool TMatrix<T>::operator==(const TMatrix<T>& mt) const
{
	return TVector<TVector<T>>::operator==(mt);
}

template <class T> // сравнение
bool TMatrix<T>::operator!=(const TMatrix<T>& mt) const
{
	return !(*this == mt);
}

template <class T> // присваивание
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& mt)
{
	if (this == &mt)
		return *this;
	if (this->Size != mt.Size)
	{
		delete[] this->pVector;
		this->Size = mt.Size;
		this->pVector = new TVector<T>[Size];
	}
	for (int i = 0; i < this->Size; i++) {
		this->pVector[i] = mt.pVector[i];
	}
	return *this;
}

template <class T> // сложение
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& mt)
{
	return TVector<TVector<T>>::operator+(mt);
}

template <class T> // вычитание
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& mt)
{
	return TVector<TVector<T>>::operator-(mt);
}

template <class T>
TMatrix<T> TMatrix<T>::operator*(const TMatrix& mt)
{

}

#endif