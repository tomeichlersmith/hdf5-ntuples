#ifndef ENTRY_HH
#define ENTRY_HH

#include "H5Cpp.h"
#include "h5container.hh"
#include "Track.hh"

/**
 * Entry struct to mimic entries in ROOT TTrees
 */
struct Entry {
  double value_d;
  int value_i;

  // Variable length containers have to be stored in special vectors.
  // Internally these wrap a hvl_t structure.
  //
  // Note the `h5` (lowercase) namespace: these are deinfed in
  // `h5container.hh`, and should not be confused with stuff in the
  // `H5` (uppercase) namespace which is provided in the official
  // `H5Cpp.h` header.
  h5::string value_s;
  h5::vector<double> vector_d;
  h5::vector<h5::string> vector_s;
  h5::vector<h5::vector<int> > vv_i;
  h5::vector<Track> tracks;
  static H5::CompType type();
};

#endif
