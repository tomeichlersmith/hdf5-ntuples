// Example showing how to write a one-dimensional dataset.
//
// In this case we're saving one compound type per entry, which is
// pretty close to a standard HEP ntuple.

// Writing on every entry is slow, so we buffer entries and then write
// them as blocks. The OneDimBuffer handles this, although with some
// caveats for variable-length containers.
#include "OneDimBuffer.hh"
// The the `vector` defined in `h5container.hh` takes care of some of
// the interesting issues which arise when dealing with variable-length
// arrays. As a rule, use these vectors to write out data.
#include "h5container.hh"
// Type deduction helpers
#include "DeduceDataType.hh"
// Track user-defined type
#include "Track.hh"
#include "Entry.hh"

#include "H5Cpp.h"

#include <vector>
// #include <iostream>
#include <cstddef>
#include <cmath>

int main(int argc, char* argv[]) {

  // Build the output file. Since multiple writes happen throughout
  // the run we have to build this _before_ looping through entries.
  //
  // I'm using HDF_ACC_TRUNC here, which tells HDF5 to overwrite
  // existing files. It's safer to use H5F_ACC_EXCL, which will throw
  // an exception rather than overwrite.
  H5::H5File file("test.h5", H5F_ACC_TRUNC);

  // The output buffer is periodically flushed.
  const size_t buffer_size = 100;

  // Instance one example buffer. We'll call this one `ints` and have
  // it store one integer per event using the `itype` defined above.
  OneDimBuffer<int> int_buffer(file, "ints", DeduceDataType<int>::type(), buffer_size);
  // The more complicated buffer stores entries of type `entryType`
  // from above.
  OneDimBuffer<Entry> ebuffer(file, "entries", DeduceDataType<Entry>::type(), buffer_size);

  // _______________________________________________________________________
  // Part 4: generate some bogus data

  for (int iii = 0; iii < 500; iii++) {
    // the int_buffer is easy: just push back.
    int_buffer.push_back(iii);

    // Create an `Entry` object and fill it with garbage data.
    Entry entry;
    entry.value_d = std::sqrt(iii);
    entry.value_i = iii;
    entry.value_s = "this is " + std::to_string(iii);
    for (int jjj = 0; jjj < (iii % 10); jjj++) {
      entry.vector_d.push_back(jjj / double(iii + 1));
      entry.vector_s.push_back(std::to_string(jjj));
      entry.tracks.push_back({100.0*jjj, std::sin(jjj)});
      h5::vector<int> iv;
      for (int kkk = 0; kkk < jjj; kkk++) {
    	iv.push_back(kkk);
      }
      entry.vv_i.push_back(iv);
    }

    // add the `Entry` to the buffer.
    ebuffer.push_back(entry);
  }
  // Buffers need to be flushed after the loop, since `flush` is only
  // called automatically when the buffer fills up.
  int_buffer.flush();
  ebuffer.flush();
  return 0;
}
