#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <time.h>
#include <array>
#include <vector>

using namespace std;

#define RAND(Min, Max) (rand() % ((Max) - (Min) + 1) + (Min))

struct LC {
  LC() { system("chcp 1251 > nul"); srand(time(0)); }
  ~LC() { cin.get(); cin.get(); }
} _;

ostream& operator<<(ostream& os, const vector<int>& V);
istream& operator>>(istream& is, vector<int>& V);
istream& operator>>(istream& is, vector<string>& V);

bool areParenthesesBalanced(const string& str) {
  stack<char> s;

  for(char ch : str) {
    if(ch == '(' || ch == '{' || ch == '[') {
      s.push(ch);
    }
    else if(ch == ')' || ch == '}' || ch == ']') {
      if(s.empty() || ((ch == ')' && s.top() != '(') || (ch == '}' && s.top() != '{') || (ch == ']' && s.top() != '['))) {
        return false;
      }
      s.pop();
    }
  }

  return s.empty();
}

int main() {
  //vector<int> arr1;
  //vector<int> arr2(10);

  //arr1.resize(12);
  //arr2.resize(15);
  //arr2.resize(arr2.size() + 5);

  //for(int i = 0; i < arr1.size(); i++) {
  //  arr1[i] = i * i;
  //}

  //arr2.clear();
  //arr2.insert(begin(arr2), 789);

  //for(int i = 0; i < 15; i++) {
  //  int temp = RAND(1, 10);
  //  arr2.push_back(temp);
  //}

  //arr2.insert(begin(arr2), 123);
  //arr2.insert(begin(arr2), 456);

  //cout << "Vector arr1: " << arr1;
  //cout << "Vector arr2: " << arr2;

  //vector<string> arr3;
  //cout << "Введите размер для вектора строк: ";
  //cin >> arr3;

  //for(size_t i = 0; i < arr3.size(); i++) {
  //  cout << arr3[i] << endl;
  //}

  string input;
  cout << "Введите строку в круглых скобках: ";
  cin.ignore(); // clear newline character left in the buffer
  getline(cin, input);

  if(areParenthesesBalanced(input)) {
    cout << "Круглые скобки сбалансированы." << endl;
  }
  else {
    cout << "Круглые скобки не сбалансированы." << endl;
  }

  return 0;
}

ostream& operator<<(ostream& os, const vector<int>& V) {
  for(size_t i = 0; i < V.size(); i++) {
    os << V[i] << " ";
  }
  return os << endl;
}

istream& operator>>(istream& is, vector<string>& V) {
  cout << "Введите размер: ";
  size_t temp;
  is >> temp;

  V.resize(temp);
  for(size_t i = 0; i < temp; i++) {
    is >> V[i];
  }
  return is;
}
