
#include "Entry.hh"
#include "DeduceDataType.hh"

H5::CompType Entry::type() {
  // We're more interested in storing compound types. These can
  // contain any collection of int, float, strings, or `hvl_t`
  // (variable length) types.
  //
  // The ugly c-style code below is to tell HDF5 where to look for
  // entries, since we're going to pass the HDF5 API a void*
  // corresponding to the array of `Entry` objects. This throws away
  // type info so we have to tell HDF5 what type we're working with.
  // You can change the name of the subtype (first argument in
  // `insertMember`), but be careful with the others.
  //
  // Just for fun, add a vector of compound types to the `Entry`
  // structure.
  // now define the main `Entry` structure
  H5::CompType entryType(sizeof(Entry));
  entryType.insertMember("value_d", offsetof(Entry, value_d),
                         DeduceDataType<double>::type());
  entryType.insertMember("value_i", offsetof(Entry, value_i),
                         DeduceDataType<int>::type());
  // Note that for variable length DeduceDataTypes we need to use special
  // containers each of these has an `h5` member which HDF5 can recognize. Since
  // this is the first member of the classes the offset within the class is
  // technically zero, but better to point to it explicitly.
  entryType.insertMember("value_s", offsetof(Entry, value_s.h5),
                         DeduceDataType<std::string>::type());
  entryType.insertMember("vector_d", offsetof(Entry, vector_d.h5),
                         DeduceDataType<std::vector<double>>::type());
  entryType.insertMember("vector_s", offsetof(Entry, vector_s.h5),
                         DeduceDataType<std::vector<std::string>>::type());
  entryType.insertMember("vv_i", offsetof(Entry, vv_i.h5),
                         DeduceDataType<std::vector<std::vector<int>>>::type());
  entryType.insertMember("tracks", offsetof(Entry, tracks.h5),
                         DeduceDataType<std::vector<Track>>::type());
  return entryType;
}

