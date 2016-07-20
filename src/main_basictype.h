//There are some types that all call use.
#include <vector>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stdint.h>
#include <list>
#include <pthread.h>
#include <map>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pin.H"

#ifndef HUST_BASICTYPE_CGCL
#define HUST_BASICTYPE_CGCL

//#define NUMBEROFVEC 5

struct RecordType //Record the necessary information to the detector
{
	int style;
	UINT32 threadID;
	ADDRINT object;
};

struct RecordCond //Record the necessary information to the conditional variable
{
	int style;
	UINT32 threadID;
	ADDRINT cond;
	ADDRINT mutex;
};

struct ShareAddreeStruct //This is the share memory space address
{
	ADDRINT address_name;
	USIZE address_size;
	
	bool operator <(const ShareAddreeStruct& rhs) const
	{
		return address_name < rhs.address_name;
	}
	
	bool operator >(const ShareAddreeStruct& rhs) const
	{
		return address_name > rhs.address_name;
	}
};

struct LockInf //Each share address' lock information
{
	int R;
	int W;
	std::vector<ADDRINT> lockID;
};

struct EachAddressInf //Each share address details
{
	bool RWflag;
	int sumR, sumW;
	int unlockR, unlockW;
	UINT32 threadID;
	ADDRINT address;
	std::vector<LockInf> lock;
	struct EachAddressInf *next;
};

struct MemoryData //Each memory address information
{
	bool SignalStatus;
	ADDRINT SignalAddress;
	std::vector<ADDRINT> veclock;
	struct EachAddressInf *EachShareAddress;
	struct MemoryData *next;
	std::vector<MemoryData *> Prior, Following;
};

struct ThreadInf //Each thread information
{
	int status; //ThreadStart is 1;
	UINT32 threadID;
	UINT32 fartherthreadID;
	struct MemoryData *data;
	struct ThreadInf *next;
};

struct ThreadParent //The relationship between the farther and child
{
	bool liveflag;
	THREADID fatherthreadid;
};

struct CreateThreadInf
{
	UINT32 threadID;
	struct MemoryData *data;
};

struct WriteAccessInf
{
	bool Write;
	bool Access;
};

struct LockDetailVCInf
{
	bool ComparedFlag;
	THREADID threadid;
	list<struct RWVecTime>::iterator FirstFrame;
	list<struct RWVecTime>::iterator LastFrame;
//	map<UINT32, long> AcquiredVC;
//	map<UINT32, long> ReleasedVC;
	map<ADDRINT, WriteAccessInf> SharedMemoryAccess;
};

struct SharedMemoryInf
{
	bool Rstatus, Wstatus;
	set<ADDRINT> RLockAcquired;
	set<ADDRINT> WLockAcquired;
};

struct SharedMemoryAccessInf
{
	bool Rstatus, Wstatus;
	long Rcount, Wcount;
};

struct RWVecTime
{
	string SynName;
	map<UINT32, long> VecTime;
//	map<ADDRINT, SharedMemoryInf> SharedMemory;
	set<ADDRINT> LockAcquired;
	map<ADDRINT, SharedMemoryAccessInf> SharedLocation;
	map<ADDRINT, LockDetailVCInf> NestedLock_RecordOldLock;
};

struct ThreadVecTime
{
	list<struct RWVecTime>::iterator ListAddress;
	list<struct RWVecTime>::iterator BlockFrame;
	list<struct RWVecTime> VecTimeList;
	set<ADDRINT> LockAcquired;
};
#endif
