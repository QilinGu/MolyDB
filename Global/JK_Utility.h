


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

	int static jk_str_match( const char *pattern, int patternLen, const char *string, int stringLen, int nocase )
	{
		while(patternLen) 
		{
			switch(pattern[0]) 
			{
			case '*':
				while (pattern[1] == '*') 
				{
					pattern++;
					patternLen--;
				}
				if (patternLen == 1)
				{
					return 1; /* match */
				}
				while(stringLen) 
				{
					if ( jk_str_match(pattern+1, patternLen-1,string, stringLen, nocase) )
					{
						return 1; /* match */
					}
					string++;
					stringLen--;
				}
				return 0; /* no match */
				break;
			case '?':
				if (stringLen == 0)
				{
					return 0; /* no match */
				}
				string++;
				stringLen--;
				break;
			case '[':
				{
					int not, match;
					pattern++;
					patternLen--;
					not = pattern[0] == '^';
					if (not) 
					{
						pattern++;
						patternLen--;
					}
					match = 0;
					while(1) 
					{
						if (pattern[0] == '\\') 
						{
							pattern++;
							patternLen--;
							if (pattern[0] == string[0])
							{
								match = 1;
							}
						} else if (pattern[0] == ']')
						{
							break;
						} 
						else if (patternLen == 0)
						{
							pattern--;
							patternLen++;
							break;
						} 
						else if (pattern[1] == '-' && patternLen >= 3) 
						{
							int start = pattern[0];
							int end = pattern[2];
							int c = string[0];
							if (start > end)
							{
								int t = start;
								start = end;
								end = t;
							}
							if (nocase) 
							{
								start = tolower(start);
								end = tolower(end);
								c = tolower(c);
							}
							pattern += 2;
							patternLen -= 2;
							if (c >= start && c <= end)
								match = 1;
						} 
						else 
						{
							if (!nocase) 
							{
								if (pattern[0] == string[0])
								{
									match = 1;
								}
							} 
							else 
							{
								if (tolower((int)pattern[0]) == tolower((int)string[0]))
								{
									match = 1;
								}
							}
						}
						pattern++;
						patternLen--;
					}
					if (not)
					{
						match = !match;
					}
					if (!match)
					{
						return 0; /* no match */
					}
					string++;
					stringLen--;
					break;
				}
			case '\\':
				if (patternLen >= 2)
				{
					pattern++;
					patternLen--;
				}
				/* fall through */
			default:
				if (!nocase) 
				{
					if (pattern[0] != string[0])
					{
						return 0; /* no match */
					}
				} 
				else 
				{
					if (tolower((int)pattern[0]) != tolower((int)string[0]))
					{
						return 0; /* no match */
					}
				}
				string++;
				stringLen--;
				break;
			}
			pattern++;
			patternLen--;
			if (stringLen == 0) 
			{
				while(*pattern == '*')
				{
					pattern++;
					patternLen--;
				}
				break;
			}
		}
		if (patternLen == 0 && stringLen == 0)
		{
			return 1;
		}
		return 0;
	}
};



#endif
