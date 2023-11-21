/*
  TList2.h
*/
#pragma once
#include <iostream>
#include <vector>     // std::vector<>
#include <algorithm>  // для std::sort()
using namespace std;

/*
 Шаблонн двусвязанного списка
  class TList
*/

// Шаблон структуры узла двусязного списка
template <class T>
struct Node
{
  // Область полезных данных
  T Data;
  // область ссылок на связанные элементы
  Node<T>* pNext; // Указатель на следующий элемент
  Node<T>* pPrev; // Указатель на предыдущий элемент

  // Конструкторы для узла
  Node() : pNext(), pPrev(), Data() {}
  Node(T data) : pNext(), pPrev(), Data(data) {}

  // Методы для узла
  Node<T>* GetNext() { return pNext; }
  Node<T>* GetPrev() { return pPrev; }
  void SetNext(Node<T>* next) { pNext = next; }
  void SetPrev(Node<T>* prev) { pPrev = prev; }
};

// Шаблон класса двусвязанного списка
template <class T>
class TList {

  Node<T>* pHead; // голова списка
  Node<T>* pTail; // хвост списка
  int       Cnt;   // кол-во элементов в списке

public:
  // Конструкторы для списка
  TList() : pHead(), pTail(), Cnt() {}

  // TList<string> A("Hello!");
  TList(const T& Val) : TList() // делаем пустой список
  {
    AddHead(Val); // добавляем один элемент
    //AddTail(Val); // добавляем один элемент
    //Insert(Val, 0);
  }

  // Копирование списков
  // TList<string> B = A;
  TList(const TList<T>& V) : TList() { *this = V; }

  // B = A;
  TList<T>& operator=(const TList<T>& V)
  {
    if (this == &V) {
      return *this; // проверка на  самокопирование
    }
    this->Clear(); // удаляем старые данные
    // 1 вариант
    Node<T> * temp = V.pHead; // указатель на узлы объекта V
    for (int i = 0; i < V.Cnt; i++) {
      this->AddTail(temp->Data); // добавить в хвост текщего списка
      temp = temp->pNext; // шаг вперед по списку V
    }
    // 2 вариант
    /*Node<T>* temp = V.pHead; // указатель на узлы объекта V
    while (temp) {
      this->AddTail( temp->Data ); // добавить в хвост текщего списка
      temp = temp->pNext; // шаг вперед по списку V
    }*/
    return *this; // вернуть ссылку на текущий объект
  }

  // Деструктор
  ~TList() { Clear(); }

  // Методы
  int GetCnt() const { return Cnt; }
  Node<T>* GetNode(int idx) const
  {
    if (idx >= 0 && idx < Cnt) {
      Node<T>* temp = pHead;
      for (int i = 0; i < idx; i++) {
        // движение по узлам списка вперед, через
        //  указатель pNext
        temp = temp->pNext;
      }
      return temp; // возвращаем адрес узла под индексом idx
    }
    else {
      cout << "Ошибка: Выход за границы списка!\n";
      return nullptr; // возвращаем нулевой адрес,
      // нет подходящего узла
    }
  }

  Node<T>* GetHead() { return pHead; }
  Node<T>* GetTail() { return pTail; }
  // Метод для создания нового узла
  Node<T>* NewNode(const T& data)
  {
    // создать один экземпляр узла списка
    Node<T>* temp = new Node<T>;
    temp->Data = data; // сохраняем данные в узел
    return temp; // возвращаем адрес нового узла
  }
  // Метод для создания нового узла
  Node<T>* NewNode(const T& data, Node<T>* next, Node<T>* prev)
  {
    // создаем один узел счерез конструктор с параметром
    Node<T>* temp = new Node<T>(data);
    // настраиваем связи
    temp->pNext = next;
    temp->pPrev = prev;
    return temp; // возвращаем адрес нового узла
  }

  // void push_back(const T& data);
  void AddTail(const T& data)
  {
    Node<T>* newNode = NewNode(data);
    // настройка связей нового узла к списку
    newNode->pNext = nullptr; // для нового хвоста
    newNode->pPrev = pTail;   // прикрепляем к старому хвосту
    // настройка списка к новому узлу
    if (pTail) { pTail->pNext = newNode; }
    pTail = newNode; // теперь это новый "хвост" списка
    if (pHead == nullptr) { pHead = pTail; }
    Cnt++;
  }

  // void push_front(const T& data);
  void AddHead(const T& data)
  {
    Node<T>* newNode = NewNode(data);
    // настройка связей нового узла к списку
    newNode->pNext = pHead;
    newNode->pPrev = nullptr;
    // настройка списка к новому узлу
    if (pHead) { pHead->pPrev = newNode; }
    pHead = newNode;
    if (pTail == nullptr) { pTail = pHead; }
    Cnt++;
  }

  void Insert(const T& data, int idx)
  {
    if (idx == 0) { AddHead(data); }
    else if (idx == Cnt) { AddTail(data); }
    else if (idx > 0 && idx < Cnt)
    { // добавление узла внутри списка
      Node<T>* newNode = NewNode(data);
      // два узла перед и после новым узлом
      Node<T>* Prev = GetNode(idx - 1);
      Node<T>* Next = Prev->pNext; //Node<T> * Next = GetNode(idx);
      // новый узел привязываем к списку
      newNode->pPrev = Prev;
      newNode->pNext = Next;
      // список привязываем к новому узлу
      Prev->pNext = newNode;
      Next->pPrev = newNode;
      // увеличиваем кол-во
      Cnt++;
    }
    else
    { // ошибка
      cout << "Ошибка: неверный индекс для вставки!\n";
    }
  }

  void Delete(int idx)
  {
    Node<T>* forDel = GetNode(idx);
    if (forDel != nullptr)
    { // узел для удаления найден
      Node<T>* Prev = forDel->pPrev;
      Node<T>* Next = forDel->pNext;
      if (Prev) { Prev->pNext = Next; }
      else { pHead = Next; }
      if (Next) { Next->pPrev = Prev; }
      else { pTail = Prev; }
      delete forDel;
      Cnt--;
    }
  }

  // cout << A.GetAt(3);
  T  GetAt(int idx) const {
    // получить укзатель на узел под индексом idx
    Node<T>* res = GetNode(idx);
    if (res != nullptr) {
      return res->Data; // возвращаем данные узла по значению - копия Data
    }
    throw exception("GetAt() - Выход за границы списка!");
  }

  // A.GetAt(3) = 123
  T& GetAt(int idx) {
    // получить укзатель на узел под индексом idx
    Node<T>* res = GetNode(idx);
    if (res != nullptr) {
      return res->Data; // возвращаем данные узла по ссылке - адрес Data
    }
    throw exception("GetAt() - Выход за границы списка!");
  }

  // A.SetAt(3, 123);
  bool SetAt(const T& data, int idx) {
    // получить укзатель на узел под индексом idx
    Node<T>* res = GetNode(idx);
    if (res) { // if(res != nullptr)
      res->Data = data;
      return true; // OK
    }
    else {
      cout << "Ошибка(SetAt): Выход за границы списка!" << endl;
      return false; // ERROR
    }
  }

  // нехарактерный оператор для списков
  T  operator[](int idx) const { return GetAt(idx); } // cout << A[3];
  T& operator[](int idx)       { return GetAt(idx); } // A[3] = 123;

  // Найти данные в списке
  // Возвращает индекс найденного узла
  //  или -1, если таких данных в списке нет
  int Search(const T& data)
  {
    //Node<T> * temp = GetHead();
    Node<T>* temp = pHead; // временная переменная для обхода списка
    int i = 0; // счетчик узлов
    while (temp) { // while (temp != nullptr)
      if (temp->Data == data) {
        return i; // возвращаем индекс найденного узла
      }
      temp = temp->pNext; // шаг вперед по списку
      i++; // индекс
    }
    return -1; // если таких данных в списке нет
  }

  // очистить список - удалить все узлы
  void Clear() {
    // while(Cnt > 0)
    while (pHead != nullptr) { // пока есть "голова" списка
      Delete(0); // удаляем головной элемент
    }
  }

  // Быстрая сортировка с помощью временного массива
  void Sort()
  {
    if (Cnt == 0) { return; }
    //T * mas = new T[Cnt]; // 1 - создать временный массив размером Cnt
    vector<T> mas(Cnt); // 1 - создать временный вектор размером Cnt
    // 2 - заполнить массив данными из списка
    Node<T>* temp = pHead;
    int i = 0;
    while (temp) {
      mas[i] = temp->Data;
      temp = temp->pNext; // шаг по списку
      i++; // шаг по массиву
    }
    // 3 - сортировка массива
    //sort( mas, mas + Cnt ); // для динамического массива
    sort( begin(mas), end(mas) ); // для объекта типа vector<>
    //sort( mas.begin(), mas.end() ); // для объекта типа vector<>
    // 4 - возвращаем массив в список
    temp = pHead;
    i = 0;
    while (temp) {
      temp->Data = mas[i];
      temp = temp->pNext; // шаг по списку
      i++; // шаг по массиву
    }
    // 5 - удаляем временный массив - для динамического массива
    //delete[]mas;
  } // mas.~vector()

  template <class T>
  friend ostream& operator<<(ostream& os, const TList<T>& obj);

}; // class TList

// Реализация шаблона перегруженного оператора вывода в поток
//  для шаблонного объекта двусвязный список TList<>
template <class T>
ostream& operator<<(ostream& os, const TList<T>& obj)
{
  os << "Size = " << obj.GetCnt() << endl;
  // 1 вариант
  /*Node<T>* temp = obj.pHead;
  while (temp) {
    os << temp->Data << endl;
    temp = temp->pNext;
  }*/
  // 2 вариант
  for (int i = 0; i < obj.GetCnt(); i++)
  {
    os << obj[i] << endl;
  }
  return os;
}
