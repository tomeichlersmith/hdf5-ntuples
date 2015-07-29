#ifndef H5_CONTAINER_HH
#define H5_CONTAINER_HH

#include <vector>
#include "H5Cpp.h"

#include <iostream>

namespace h5 {
  template<typename T>
  class vector
  {
  public:
    vector();
    vector(const vector&);
    vector(const std::vector<T>&);
    vector(vector&&);
    vector& operator=(vector);
    ~vector();
    void push_back(T value);
    hvl_t h5;
    // need to own a pointer to keep this POD
    void reset();
    std::vector<T>* _vector;
  private:
  };

  // ______________________________________________________________________
  // implementation
  template<typename T>
  vector<T>::vector(): _vector(0)
  {
    std::cout << "building" << std::endl;
    _vector = new std::vector<T>();
    reset();
  }
  template<typename T>
  vector<T>::vector(const std::vector<T>& old_vec): _vector(0)
  {
    std::cout << "building from std" << std::endl;
    _vector = new std::vector<T>(old_vec);
    reset();
  }
  template<typename T>
  vector<T>::vector(const vector& old)
  {
    std::cout << "copying" << std::endl;
    _vector = new std::vector<T>(*old._vector);
    reset();
  }
  template<typename T>
  vector<T>::vector(vector&& old):
    _vector(old._vector)
  {
    std::cout << "moving" << std::endl;
    old._vector = 0;
    reset();
  }
  template<typename T>
  vector<T>& vector<T>::operator=(vector old)
  {
    std::cout << "assigning" << std::endl;
    std::swap(*this, old);
    return *this;
  }
  template<typename T>
  vector<T>::~vector() {
    std::cout << "destroying" << std::endl;
    delete _vector;
    _vector = 0;
  }

  template<typename T>
  void vector<T>::push_back(T value) {
    _vector->push_back(value);
  }
  template<typename T>
  void vector<T>::reset() {
    std::cout << "trying to reset" << std::endl;
    h5.p = _vector->data();
    h5.len = _vector->size();
    std::cout << "resetting vector location to " << h5.p
	      << " with size " << h5.len << std::endl;
  }

}
#endif
