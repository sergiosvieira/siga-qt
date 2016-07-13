#ifndef __CONVERT_STRING_TEMPLATE__
#define __CONVERT_STRING_TEMPLATE__

typedef enum
{
	CS_NONE,
	CS_ERROR_ON_CONVERT,
	CS_EMPTY_STRING
} ConvertStringErrorCode; // 	CS_NONE, CS_ERROR_ON_CONVERT, CS_EMPTY_STRING 

//template <typename T>
//T ConvertString(const std::string &data, ConvertStringErrorCode& a_errorCode)
//{
//	a_errorCode = CS_NONE;
//	if( !data.empty( ))
//	{
//	T ret;
//	std::istringstream iss( data );
//	if( data.find( "0x" ) != std::string::npos )
//	{
//		iss >> std::hex >> ret;
//	}
//	else
//	{
//		iss >> std::dec >> ret;
//	}

//	if( iss.fail( ))
//	{
//		a_errorCode = CS_ERROR_ON_CONVERT;
//		return T( );
//	}
//	return ret;
//	}
//	else
//	{
//	a_errorCode = CS_EMPTY_STRING;
//	}
//	return T( );
//}

#endif /** __CONVERT_STRING_TEMPLATE__ **/
