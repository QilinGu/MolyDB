


#ifndef _JK_UTILITY_LX3BG8E_H_
#define _JK_UTILITY_LX3BG8E_H_

#ifdef WIN32
#include <windows.h>
#else
#endif

// io
#ifdef WIN32
#define JK_SPRITF( dst, fmt, ... )  sprintf_s( dst, fmt, __VA_ARGS__ )
#define JK_SPRITF_S(dst,size,fmt,...) sprintf_s(dst,size,fmt,__VA_ARGS__ )
#define JK_STRTOK_S(str,del,context) strtok_s(str,del,context)

#define JK_OPENFILE_S(fptr,fname,mod)	fopen_s(&fptr,fname,mod)
#define JK_STRERROR_S(size,err) strerror_s(size,err)
#define JK_MEMCPY_S(dst,dstsize,src,cnt) memcpy_s(dst,dstsize,src,cnt)
#else
#define JK_SPRITF(dst, fmt, ... ) sprintf( dst, fmt, __VA_ARGS__ )
#define JK_SPRITF_S(dst,size,fmt,...) snprintf(dst,size,fmt,__VA_ARGS__ )
#define JK_STRTOK_S(str,del,context) strtok(str,del)

#define JK_OPENFILE_S(fptr,fname,fmt) (fptr=fopen(fname,fmt))
#define JK_STRERROR_S(size,err) strerror(err)
#define JK_MEMCPY_S(dst,dstsize,src,cnt) memcpy(dst,src,cnt)
#endif


// sys
#ifdef WIN32
#define JK_GETPID() GetCurrentProcessId()
#else
#define JK_GETPID() getpid()
#endif


class JK_Utility
{
public:
	void static jk_str_split( char **arr, char *str, const char *del )
	{
		char* pNext = NULL;
		char *s	= JK_STRTOK_S( str, del, &pNext); 
		while( NULL != s)
		{
			*arr++ = s;
			s = JK_STRTOK_S( NULL, del, &pNext ); 	
		}
	}


};



#endif
