#ifndef _SIMHWRT_LOCAL_STORE_H_
#define _SIMHWRT_LOCAL_STORE_H_

#include "FunctionalUnit.h"
#include "ThreadState.h"
#include "FourByte.h"
#include <map>
#include <vector>

// Hard-code these values since we only use one type of localstore
#define LOCALSTORE_AREA .01396329
#define LOCALSTORE_ENERGY .00692867

#define LOCAL_SIZE 32768

class LocalStore : public FunctionalUnit {
 public:
  LocalStore(int latency, int width);
  ~LocalStore();
  virtual bool SupportsOp(Instruction::Opcode op) const;
  virtual bool AcceptInstruction(Instruction& ins, IssueUnit* issuer, ThreadState* thread);
  virtual void ClockRise();
  virtual void ClockFall();
  virtual void print();
  virtual double Utilization();

  bool IssueLoad(int write_reg, int address, ThreadState* thread, IssueUnit* issuer, long long int write_cycle, Instruction& ins);
  bool IssueStore(reg_value write_val, int address, ThreadState* thread, long long int write_cycle, Instruction& ins);
  void LoadJumpTable(char* jump_table, int _size);
  reg_value LoadWordLeft(ThreadState* thread, int address, int write_reg, long long int current_cycle);
  reg_value LoadWordRight(ThreadState* thread, int address, int write_reg, long long int current_cycle);
  void StoreWordLeft(ThreadState* thread, int address, reg_value write_val);
  void StoreWordRight(ThreadState* thread, int address, reg_value write_val);
  void AddWatchPoint(ThreadState* thread, int address);
  void RemoveWatchPoint(ThreadState* thread, int address);

  int jtable_size;
  int width;
  int issued_this_cycle;

  std::map<int, std::vector<ThreadState*> > watchpoints;
  bool watchPointHit;

  FourByte ** storage;
};

#endif // _SIMHWRT_LOCAL_STORE_H_

