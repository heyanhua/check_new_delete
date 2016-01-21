
#include"stdafx.h"


#ifdef _DEBUG
#include "OperatorNewCountInfo.h"

#include <fstream>
#include <ios>
using std::hex;
using std::dec;





COperatorNewCountInfo  g_objNewCountInfo;
log_pre           g_log_pre;




COperatorNewCountInfo::COperatorNewCountInfo(void)
{
	stc_log_info  objTmp;
	memset(&objTmp,0,sizeof(objTmp));
	m_vInfo.resize(128);
	m_vInfo.clear();
	int temp = (m_vInfo.begin() == m_vInfo.end());

	_NewCount =0;
	_DeleteCount =0;
}


void  COperatorNewCountInfo::WriteLog(const stc_log_info & obj)
{	//new 操作，正常插入信息
	if(true != obj.isdelete)
	{
		m_vInfo.push_back(obj);
		_NewCount ++;
		return ;
	}
	stc_log_info  objTmp;
	memset(&objTmp,0,sizeof(objTmp));


	//delete操作，先保存原有信息，  写入，  然后用原有部分覆盖
	for(vector<stc_log_info>::iterator it = m_vInfo.begin(); it<m_vInfo.end();it++ )
	{
		
		if(it->p == obj.p && !it->isdelete)
		{
			//保存new信息
			memcpy(objTmp.new_filename,it->new_filename, sizeof(it->new_filename));
			memcpy(objTmp.new_function,it->new_function, sizeof(it->new_function));
			objTmp.new_line = it->new_line;
			
			//写入delete信息
			*it=obj;

			//写回new信息
			memcpy(it->new_filename,objTmp.new_filename, sizeof(objTmp.new_filename));
			memcpy(it->new_function,objTmp.new_function, sizeof(objTmp.new_function));
			it->new_line = objTmp.new_line;


			_DeleteCount ++;
			break;
		}

				
	}


}


COperatorNewCountInfo::~COperatorNewCountInfo(void)
{
	remove("mem_log.txt");
	//写入文件
	ofstream ofs("mem_log.txt",ofstream::out);
	
	ofs<<*this;

	ofs.close();
	//清理
	vector<stc_log_info> v;
	m_vInfo.swap(v);
}


int COperatorNewCountInfo::GetNewCount()
{
	return _NewCount;
}
int COperatorNewCountInfo::GetDeleteCount()
{
	return _DeleteCount;
}


ofstream&  operator <<(ofstream &ofs, COperatorNewCountInfo & obj)
{
	int temp = obj.GetDeleteCount() - obj.GetNewCount(), index =0;
	ofs<<"---------------------------------------------------"<<std::endl;
	ofs<<"统计到new"<<obj.GetNewCount()<<"次"<<"delete"<<obj.GetDeleteCount()<<"次."<<endl;
	if(temp)
		ofs<<"泄漏内存"<<temp<<"次"<<std::endl;
	
	for(vector<stc_log_info>::iterator it = obj.m_vInfo.begin(); it<obj.m_vInfo.end();it++ )
	{
		if(it->isdelete == false)
		{
		ofs<<"  "<<dec<<index++<<endl;
		ofs<<"源文件:\t\t"<<it->new_filename<<endl;
		ofs<<"行号  :\t\t"<<it->new_line<<endl;
		ofs<<"函数名:\t\t"<<it->new_function<<endl;
		ofs<<"内存地址:\t"<<hex<<it->p<<endl;
		ofs<<endl<<endl;
		}
	}
	
	ofs<<"谢谢使用!"<<endl;

	return ofs;
}






#endif