#log功能:
  !内存泄漏统计。 引用_debug宏开关,默认release版本不会开启。

#使用方式:
1. 添加log文件夹到源文件目录。
2. 将OperatorNewCountInfo.cpp  和  check_newdelete_log.cpp在项目中编译。
3. 将check_newdelete_log.h 添加到每一个cpp文件头，或者添加进“stdafx.h”头文件。
4. 每次运行结束后在源文件目录找到统计信息mem_log.txt

#注意:
1. 每统计一次new和delete信息，至少需要额外消耗内存512字节，注意内存消耗。
2. 应该在什么时候使用内存统计?最好不使用。 养成一个良好的new  delete配对习惯可能更好。


#如有bug可联系:heyanhua


