#pragma once

template <typename TData>
class CArray 
{
public: // Interface

  // Конструктор по умолчанию
  CArray()
    : m_size(0),
    m_data(nullptr)
  {
  }

  // Копирующий конструктор
  CArray(
      const CArray & _array
    )
    : m_size(_array.size()),
    m_data(new TData[m_size])
  {
    for (unsigned int i = 0; i < m_size; ++i)
    {
      m_data[i] = _array[i];
    }
  }

  // Деструктор
  ~CArray()
  {
    if (m_data)
    {
      delete[] m_data;
    }
  }

  // Добавить элемент в конец массива
  void push_back(
      const TData & _value
    )
  {
    auto newSize = m_size + 1;
    auto newBuffer = new TData[newSize];
    for (unsigned int i = 0; i < m_size; ++i)
    {
      newBuffer[i] = m_data[i];
    }
    newBuffer[newSize - 1] = _value;

    delete[] m_data;
    m_data = newBuffer;
    m_size = newSize;
  }

  // Добавить элемент в массив по заданному индексу
  void insert(
      unsigned int _index,
      const TData & _value
    )
  {
    auto newSize = m_size + 1;
    auto newBuffer = new TData[newSize];
    auto isInserted = false;
    for (unsigned int i = 0; i < newSize; ++i)
    {
      if (i == _index)
      {
        newBuffer[i] = _value;
        isInserted = true;
        continue;
      }

      if (!isInserted)
      {
        newBuffer[i] = m_data[i];
      }
      else
      {
        newBuffer[i] = m_data[i - 1];
      }
    }

    delete[] m_data;
    m_data = newBuffer;
    m_size = newSize;
  }

  // Удалить элемент массива по заданному индексу
  void erase(
      unsigned int _index
    )
  {
    auto newSize = m_size - 1;
    auto newBuffer = new TData[newSize];
    auto isErased = false;
    for (unsigned int i = 0; i < newSize; ++i)
    {
      if (i == _index)
      {
        isErased = true;
      }

      if (!isErased)
      {
        newBuffer[i] = m_data[i];
      }
      else
      {
        newBuffer[i] = m_data[i + 1];
      }
    }

    delete[] m_data;
    m_data = newBuffer;
    m_size = newSize;
  }

  // Очистить массив
  void clear()
  {
    delete[] m_data;
    m_size = 0;
    m_data = nullptr;
  }

  // Получить размер массива
  unsigned int size() const
  {
    return m_size;
  }

  // Получить элемент массива по заданному индексу
  TData & operator[](
      unsigned int _index
    )
  {
    return m_data[_index];
  }

  // Получить элемент массива по заданному индексу (const)
  TData& operator[](
    unsigned int _index
    ) const
  {
    return m_data[_index];
  }

  // Получить начало контейнера
  TData* begin()
  {
    return m_data;
  }

  // Получить конец контейнера
  TData* end()
  {
    return m_data + m_size;
  }

protected: // Attributes
  unsigned int m_size;
  TData * m_data;
};