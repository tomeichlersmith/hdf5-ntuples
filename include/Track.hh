#ifndef TRACK_HH
#define TRACK_HH

#include "H5Cpp.h"

/**
 * Dummy Data Class for testing and an example of user-defined data struct
 *
 * This will be put inside a STL vector.
 */
struct Track {
  double pt;
  double eta;
  /// required by type deduction mechanism
  static H5::CompType type();
};

#endif
