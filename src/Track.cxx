
#include "Track.hh"
#include "DeduceDataType.hh"

H5::CompType Track::type() {
  H5::CompType track_type(sizeof(Track));
  track_type.insertMember("pt", offsetof(Track, pt), DeduceDataType<double>::type());
  track_type.insertMember("eta", offsetof(Track, eta), DeduceDataType<double>::type());
  return track_type;
}
