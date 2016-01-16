

#pragma once

#ifdef _DEBUG

#include <vector>    //need  vector
#include <fstream>   //need  fostream



using std::vector;
using std::ofstream;
using std::endl;

typedef struct  _stc_log_info
{
   void * p;
   char  new_filename[256];//¾ø¶ÔÂ·¾¶
   char  new_function[256];
   char  delete_filename[256];
   char  delete_function[256];
   int   new_line;
   int   delete_line;
   bool  isdelete;
}stc_log_info;



typedef struct _log_pre
{
   char  delete_filename[256];
   char  delete_function[256];
   int   delete_line;

}log_pre;





class COperatorNewCountInfo
{
public:
	COperatorNewCountInfo(void);
	~COperatorNewCountInfo(void);
	void WriteLog(const stc_log_info & obj);
	friend  ofstream&  operator <<(ofstream &ofs, COperatorNewCountInfo & obj);
private:
	vector<_stc_log_info> m_vInfo;

};




//export
extern  COperatorNewCountInfo  g_objNewCountInfo;
extern  log_pre				   g_log_pre;


#endif