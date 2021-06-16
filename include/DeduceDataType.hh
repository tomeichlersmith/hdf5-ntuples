#ifndef DEDUCEDATATYPE_H_
#define DEDUCEDATATYPE_H_

/**
 * DeduceDataType.hh
 *
 * Helper type-deduction structs for converting familiar STL C++
 * types into H5 types. We use template specialization of these
 * structs so that we can call
 *  DeduceDataType<T>::type()
 * to determine the H5 type for all C++ objects we are using.
 *
 * The requirement for user-defined types is that they define
 * a public static member function that constructs the H5 type
 * corresponding to their struct.
 */

#include "H5Cpp.h"
#include <vector>

// Default assumes type has static member ::type() defined.
template <typename T>
struct DeduceDataType {
  static H5::DataType type() {
    return T::type();
  }
};

template <>
struct DeduceDataType<double> {
  static H5::DataType type() {
    return H5::PredType::NATIVE_DOUBLE;
  }
};

template <>
struct DeduceDataType<int> {
  static H5::DataType type() {
    return H5::PredType::NATIVE_INT;
  }
};

template <>
struct DeduceDataType<std::string> {
  static H5::DataType type() {
    return H5::StrType(H5::PredType::C_S1, H5T_VARIABLE);
  }
};

template <typename C>
struct DeduceDataType<std::vector<C>> {
  static H5::DataType type() {
    auto content_type = DeduceDataType<C>::type();
    return H5::VarLenType(&content_type);
  }
};

#endif
