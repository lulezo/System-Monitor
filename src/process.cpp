#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Set this process's ID
void Process::pidSetter(int i) {
  pid_ = i;
}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
  double utime, stime, cutime, cstime, starttime, total_time, seconds; 
  long uptime = LinuxParser::UpTime();
  float cpu_usage;
  string value;
  int counter = 0;
  std::ifstream filestream(LinuxParser::kProcDirectory + std::to_string(pid_) + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (filestream >> value) {
      counter += 1;
      if (counter == 14) { utime = std::stol(value); }
      else if (counter == 15) { stime = std::stol(value); }
      else if (counter == 16) { cutime = std::stol(value); }
      else if (counter == 17) { cstime = std::stol(value); }
      else if (counter == 22) { starttime = std::stol(value); }
    }
  }
  total_time = utime + stime + cutime + cstime;
  seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
  cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
  return cpu_usage;
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// Overloading the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return a.CpuUtilization() < CpuUtilization();
}
