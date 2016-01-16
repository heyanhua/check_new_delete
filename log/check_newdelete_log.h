//----------------------------------------->
// 1. new    placement new   operator new  和  ::operator new
// 1. new操作符的执行过程
//        a. 调用operator new分配内存
//		  b. 调用构造函数生成类对象
//        c. 返回相应指针
// 2. new操作符本身无法被重载,
//
//
//<-----------------------------------------

#pragma once


#ifdef _DEBUG

#include<new>
#include"OperatorNewCountInfo.h"

extern  void * get_log( char * file,char * function, int line,bool isdelete,void * p);
extern  void   get_log_pre( char * file,char * function, int line);


void *  operator new(std::size_t _Count , char * file,char * function, int line  );
void *  operator new[](std::size_t _Count , char * file,char * function, int line);

void  operator delete(void * object );
void  operator delete[](void * object );









#define new	 new(__FILE__,__FUNCSIG__,__LINE__)

//由于delete的机制， 重载的成对的 new和 delete 只有在new 分配发生异常时，
//delete才会被编译器调用， 自己无法调用，  由编译器调用，  只是提供， 但是
// 没卵用 ,发生异常时，文件可能不会被正常的写入。
#define delete      get_log_pre( __FILE__,__FUNCSIG__,__LINE__);delete





#endif



