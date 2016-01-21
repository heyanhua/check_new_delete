

#include"stdafx.h"


#ifdef _DEBUG
#include<new>
#include"OperatorNewCountInfo.h"





extern  void * get_log( char * file,char * function, int line,bool isdelete,void * p);
extern  void   get_log_pre( char * file,char * function, int line);

#undef new
#undef delete

void *  operator new(std::size_t _Count , char * file,char * function, int line ) 
{
	return  get_log( file,function,line,false, ::operator new( _Count));
}


void *  operator new[](std::size_t _Count , char * file,char * function, int line) 
{
	return get_log( file,function,line,false,::operator new[] (_Count));
}


void operator delete(void * object )
{
	
	free(object);	
	get_log(g_log_pre.delete_filename, g_log_pre.delete_function, g_log_pre.delete_line, true, object );
}
void operator delete[](void * object )
{
	free(object);
	get_log(g_log_pre.delete_filename, g_log_pre.delete_function, g_log_pre.delete_line, true, object );

}



void operator  delete( void * object, char * file,char * function, int line)
{
	 operator delete(object);
}

void operator delete[](void * object , char * file,char * function, int line)
{
	operator delete[](object);
}































 void * get_log( char * file,char * function, int line,bool isdelete,void * p)
{
	stc_log_info objTmp;
	memset(&objTmp,0,sizeof(objTmp));
		objTmp.isdelete = isdelete;
	if(!isdelete)
	{
	strcpy_s(objTmp.new_filename,sizeof(objTmp.new_filename), file);
	strcpy_s(objTmp.new_function,sizeof(objTmp.new_function), function);
	objTmp.new_line = line;
	objTmp.p = p;
	}else
	{
	strcpy_s(objTmp.delete_filename,sizeof(objTmp.delete_filename), file);
	strcpy_s(objTmp.delete_function,sizeof(objTmp.delete_function), function);
	objTmp.delete_line = line;
	objTmp.p = p;
	}

	g_objNewCountInfo.WriteLog(objTmp);


	return p;


}

  void  get_log_pre( char * file,char * function, int line)
  {
	  strcpy_s(g_log_pre.delete_filename,sizeof(g_log_pre.delete_filename),file);
	  strcpy_s(g_log_pre.delete_function,sizeof(g_log_pre.delete_function),function);
	  g_log_pre.delete_line = line;
  }







#endif