#include "processor.h"
#include "linux_parser.h"
#include<string>
#include<vector>
#include<istream>
#include<fstream>
#include<iostream>
#include<sstream>
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  string line;
  string cpu;
  std::vector<string> utilization = LinuxParser::CpuUtilization();
  double user = stod(utilization[0]);
  double nice = stod(utilization[1]); 
  double system = stod(utilization[2]);
  double idle = stod(utilization[3]);
  double iowait = stod(utilization[4]);
  double irq = stod(utilization[5]);
  double softirq = stod(utilization[6]);
  double steal = stod(utilization[7]);
  //calculations
  double PrevIdle = previdle + previowait;
  double Idle = idle + iowait;
  double PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
  double NonIdle = user + nice + system + irq + softirq + steal;
  double PrevTotal = PrevIdle + PrevNonIdle;
  double Total = Idle + NonIdle;
  double totald = Total - PrevTotal;
  double idled = Idle - PrevIdle;
  //output
  float output = (totald - idled) / totald;
  //updating prev.. values
  double previdle = idle;
  double previowait = iowait;
  double prevuser = user;
  double prevnice = nice;
  double prevsystem = system;
  double previrq = irq;
  double prevsoftirq = softirq;
  double prevsteal = steal;
  
  return output;
}
