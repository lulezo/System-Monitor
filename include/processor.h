#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization(); 

 private:
  float prevuser = 0;
  float prevnice = 0;
  float prevsystem = 0;
  float previrq = 0;
  float prevsoftirq = 0;
  float prevsteal = 0;
  float previdle = 0;
  float previowait = 0;
};

#endif
