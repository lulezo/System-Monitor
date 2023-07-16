#include <string>

#include "format.h"

using std::string;

// This is a helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
  int h, m, s;
  string up_time;
  h = seconds / 3600;
  m = (seconds % 3600) / 60;
  if (m > 59) {
    m = 0;
    h += 1;
  }
  s = (seconds % 3600) % 60;
  if (s > 59) {
    s = 0;
    m += 1;
    if (m > 59) {
        m = 0;
        h += 1;
    }
  }
  up_time = std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
  return up_time;
}
