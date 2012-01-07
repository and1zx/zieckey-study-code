/****************************** Module Header ********************************\
    Name: assert_ext.h
 Created: 2012/01/07 7:1:2012 17:27
  Author: weizili

 Purpose: 
\*****************************************************************************/
#ifndef OSLIB_ASSERT_EXT_H_
#define OSLIB_ASSERT_EXT_H_

#include "osl/include/platform_micros.h"
#include "osl/include/QStringUtil.h"

#include <string>
#include <iosfwd>

//only use VC
//typedef char __error__[(expr)];
#define __static_assert2( expr , line ) typedef char __compiler_check__false__##line##__ [(expr)];
#define __static_assert1( expr , line ) __static_assert2( (expr) , line )

//! \def static_assert(expr,error) 
//! \brief static assert, now only can work on VC, similar with C++0x static_assert
#define static_assert(expr,error) __static_assert1( (expr) ,  __LINE__ )

namespace osl
{
    //! Trace the message.If in debug mode, it will print both to default log and output window,
    //! if in release mode, it only print to default log.
    _EXPORT_OSLIB void h_trace( const char* fmt, ... );

    // no matter use or do not use ASSERT, we define the function.
    _EXPORT_OSLIB void h_assert( const char *expr,
        const char *filename,
        unsigned lineno );

}

    // if assert is enabled.
#ifdef H_DEBUG_MODE
    #define H_ASSERT( exp )  ( (exp) || (::osl::h_assert(#exp, __FILE__, __LINE__), 0) )
#else
    #define H_ASSERT( exp )
#endif

namespace osl
{
    inline void h_trace( const char* fmt, ... )
    {
#ifdef H_DEBUG_MODE
        char out[2048] = {};

        va_list body;
        va_start( body, fmt );
        vsnprintf( out, sizeof(out), fmt, body ); //
        va_end( body );

        printf("%s\n", out);
#else
        // do nothing.
#endif
    }


    //----------------------------------------------------------
    inline void h_assert( const char *expr,
                          const char *filename,
                          unsigned lineno )
    {
#ifdef H_DEBUG_MODE
#	ifdef H_OS_WINDOWS
        _wassert( StringUtil::mbsToWs(expr).c_str(), StringUtil::mbsToWs(filename).c_str(), lineno );
#	elif defined(H_OS_FREEBSD)
        __assert( __func__, filename, lineno, expr );
#	elif defined(H_OS_LINUX)
        __assert( expr, filename, lineno );
#	endif
#endif
    }

}


#endif //end of #ifndef OSLIB_ASSERT_EXT_H_