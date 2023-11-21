/*
  TList2.h
*/
#pragma once
#include <iostream>
#include <vector>     // std::vector<>
#include <algorithm>  // ��� std::sort()
using namespace std;

/*
 ������� ������������� ������
  class TList
*/

// ������ ��������� ���� ���������� ������
template <class T>
struct Node
{
  // ������� �������� ������
  T Data;
  // ������� ������ �� ��������� ��������
  Node<T>* pNext; // ��������� �� ��������� �������
  Node<T>* pPrev; // ��������� �� ���������� �������

  // ������������ ��� ����
  Node() : pNext(), pPrev(), Data() {}
  Node(T data) : pNext(), pPrev(), Data(data) {}

  // ������ ��� ����
  Node<T>* GetNext() { return pNext; }
  Node<T>* GetPrev() { return pPrev; }
  void SetNext(Node<T>* next) { pNext = next; }
  void SetPrev(Node<T>* prev) { pPrev = prev; }
};

// ������ ������ ������������� ������
template <class T>
class TList {

  Node<T>* pHead; // ������ ������
  Node<T>* pTail; // ����� ������
  int       Cnt;   // ���-�� ��������� � ������

public:
  // ������������ ��� ������
  TList() : pHead(), pTail(), Cnt() {}

  // TList<string> A("Hello!");
  TList(const T& Val) : TList() // ������ ������ ������
  {
    AddHead(Val); // ��������� ���� �������
    //AddTail(Val); // ��������� ���� �������
    //Insert(Val, 0);
  }

  // ����������� �������
  // TList<string> B = A;
  TList(const TList<T>& V) : TList() { *this = V; }

  // B = A;
  TList<T>& operator=(const TList<T>& V)
  {
    if (this == &V) {
      return *this; // �������� ��  ���������������
    }
    this->Clear(); // ������� ������ ������
    // 1 �������
    Node<T> * temp = V.pHead; // ��������� �� ���� ������� V
    for (int i = 0; i < V.Cnt; i++) {
      this->AddTail(temp->Data); // �������� � ����� ������� ������
      temp = temp->pNext; // ��� ������ �� ������ V
    }
    // 2 �������
    /*Node<T>* temp = V.pHead; // ��������� �� ���� ������� V
    while (temp) {
      this->AddTail( temp->Data ); // �������� � ����� ������� ������
      temp = temp->pNext; // ��� ������ �� ������ V
    }*/
    return *this; // ������� ������ �� ������� ������
  }

  // ����������
  ~TList() { Clear(); }

  // ������
  int GetCnt() const { return Cnt; }
  Node<T>* GetNode(int idx) const
  {
    if (idx >= 0 && idx < Cnt) {
      Node<T>* temp = pHead;
      for (int i = 0; i < idx; i++) {
        // �������� �� ����� ������ ������, �����
        //  ��������� pNext
        temp = temp->pNext;
      }
      return temp; // ���������� ����� ���� ��� �������� idx
    }
    else {
      cout << "������: ����� �� ������� ������!\n";
      return nullptr; // ���������� ������� �����,
      // ��� ����������� ����
    }
  }

  Node<T>* GetHead() { return pHead; }
  Node<T>* GetTail() { return pTail; }
  // ����� ��� �������� ������ ����
  Node<T>* NewNode(const T& data)
  {
    // ������� ���� ��������� ���� ������
    Node<T>* temp = new Node<T>;
    temp->Data = data; // ��������� ������ � ����
    return temp; // ���������� ����� ������ ����
  }
  // ����� ��� �������� ������ ����
  Node<T>* NewNode(const T& data, Node<T>* next, Node<T>* prev)
  {
    // ������� ���� ���� ������ ����������� � ����������
    Node<T>* temp = new Node<T>(data);
    // ����������� �����
    temp->pNext = next;
    temp->pPrev = prev;
    return temp; // ���������� ����� ������ ����
  }

  // void push_back(const T& data);
  void AddTail(const T& data)
  {
    Node<T>* newNode = NewNode(data);
    // ��������� ������ ������ ���� � ������
    newNode->pNext = nullptr; // ��� ������ ������
    newNode->pPrev = pTail;   // ����������� � ������� ������
    // ��������� ������ � ������ ����
    if (pTail) { pTail->pNext = newNode; }
    pTail = newNode; // ������ ��� ����� "�����" ������
    if (pHead == nullptr) { pHead = pTail; }
    Cnt++;
  }

  // void push_front(const T& data);
  void AddHead(const T& data)
  {
    Node<T>* newNode = NewNode(data);
    // ��������� ������ ������ ���� � ������
    newNode->pNext = pHead;
    newNode->pPrev = nullptr;
    // ��������� ������ � ������ ����
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
    { // ���������� ���� ������ ������
      Node<T>* newNode = NewNode(data);
      // ��� ���� ����� � ����� ����� �����
      Node<T>* Prev = GetNode(idx - 1);
      Node<T>* Next = Prev->pNext; //Node<T> * Next = GetNode(idx);
      // ����� ���� ����������� � ������
      newNode->pPrev = Prev;
      newNode->pNext = Next;
      // ������ ����������� � ������ ����
      Prev->pNext = newNode;
      Next->pPrev = newNode;
      // ����������� ���-��
      Cnt++;
    }
    else
    { // ������
      cout << "������: �������� ������ ��� �������!\n";
    }
  }

  void Delete(int idx)
  {
    Node<T>* forDel = GetNode(idx);
    if (forDel != nullptr)
    { // ���� ��� �������� ������
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
    // �������� �������� �� ���� ��� �������� idx
    Node<T>* res = GetNode(idx);
    if (res != nullptr) {
      return res->Data; // ���������� ������ ���� �� �������� - ����� Data
    }
    throw exception("GetAt() - ����� �� ������� ������!");
  }

  // A.GetAt(3) = 123
  T& GetAt(int idx) {
    // �������� �������� �� ���� ��� �������� idx
    Node<T>* res = GetNode(idx);
    if (res != nullptr) {
      return res->Data; // ���������� ������ ���� �� ������ - ����� Data
    }
    throw exception("GetAt() - ����� �� ������� ������!");
  }

  // A.SetAt(3, 123);
  bool SetAt(const T& data, int idx) {
    // �������� �������� �� ���� ��� �������� idx
    Node<T>* res = GetNode(idx);
    if (res) { // if(res != nullptr)
      res->Data = data;
      return true; // OK
    }
    else {
      cout << "������(SetAt): ����� �� ������� ������!" << endl;
      return false; // ERROR
    }
  }

  // ������������� �������� ��� �������
  T  operator[](int idx) const { return GetAt(idx); } // cout << A[3];
  T& operator[](int idx)       { return GetAt(idx); } // A[3] = 123;

  // ����� ������ � ������
  // ���������� ������ ���������� ����
  //  ��� -1, ���� ����� ������ � ������ ���
  int Search(const T& data)
  {
    //Node<T> * temp = GetHead();
    Node<T>* temp = pHead; // ��������� ���������� ��� ������ ������
    int i = 0; // ������� �����
    while (temp) { // while (temp != nullptr)
      if (temp->Data == data) {
        return i; // ���������� ������ ���������� ����
      }
      temp = temp->pNext; // ��� ������ �� ������
      i++; // ������
    }
    return -1; // ���� ����� ������ � ������ ���
  }

  // �������� ������ - ������� ��� ����
  void Clear() {
    // while(Cnt > 0)
    while (pHead != nullptr) { // ���� ���� "������" ������
      Delete(0); // ������� �������� �������
    }
  }

  // ������� ���������� � ������� ���������� �������
  void Sort()
  {
    if (Cnt == 0) { return; }
    //T * mas = new T[Cnt]; // 1 - ������� ��������� ������ �������� Cnt
    vector<T> mas(Cnt); // 1 - ������� ��������� ������ �������� Cnt
    // 2 - ��������� ������ ������� �� ������
    Node<T>* temp = pHead;
    int i = 0;
    while (temp) {
      mas[i] = temp->Data;
      temp = temp->pNext; // ��� �� ������
      i++; // ��� �� �������
    }
    // 3 - ���������� �������
    //sort( mas, mas + Cnt ); // ��� ������������� �������
    sort( begin(mas), end(mas) ); // ��� ������� ���� vector<>
    //sort( mas.begin(), mas.end() ); // ��� ������� ���� vector<>
    // 4 - ���������� ������ � ������
    temp = pHead;
    i = 0;
    while (temp) {
      temp->Data = mas[i];
      temp = temp->pNext; // ��� �� ������
      i++; // ��� �� �������
    }
    // 5 - ������� ��������� ������ - ��� ������������� �������
    //delete[]mas;
  } // mas.~vector()

  template <class T>
  friend ostream& operator<<(ostream& os, const TList<T>& obj);

}; // class TList

// ���������� ������� �������������� ��������� ������ � �����
//  ��� ���������� ������� ���������� ������ TList<>
template <class T>
ostream& operator<<(ostream& os, const TList<T>& obj)
{
  os << "Size = " << obj.GetCnt() << endl;
  // 1 �������
  /*Node<T>* temp = obj.pHead;
  while (temp) {
    os << temp->Data << endl;
    temp = temp->pNext;
  }*/
  // 2 �������
  for (int i = 0; i < obj.GetCnt(); i++)
  {
    os << obj[i] << endl;
  }
  return os;
}
