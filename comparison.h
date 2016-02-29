#ifndef COMPARISON__H
#define COMPARISON__H


template <class T>
class Comparison{
public:
Comparison(T f1):f(f1){}

bool operator()(T* f1) {
  return f1->getId()==f.getId();
}
private:
T f;

};
#endif
