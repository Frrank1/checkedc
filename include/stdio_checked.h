//---------------------------------------------------------------------//
// Bounds-safe interfaces for functions in math.h that                 //
// take pointer arguments.                                             //
//                                                                     //
// These are listed in the same order that they occur in the C11       //
// specification.                                                      //
//                                                                     //
// TODO: revise string types after support for pointers to             //
// null-terminated arrays is added to C.                               //
//                                                                     //
// TODO: Better Support for _FORTIFY_SOURCE > 0                        //
/////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#pragma BOUNDS_CHECKED ON

#if defined(_WIN32) || defined(_WIN64)
// stdin, stdout, and stderr only have to be expressions that have
// type FILE *.  On Windows, they are function calls, so we need to change
// the return type of the function being called.
_ACRTIMP_ALT FILE* __cdecl __acrt_iob_func(unsigned) : itype(_Ptr<FILE>);
#else
extern FILE *stdin : itype(_Ptr<FILE>);
extern FILE *stdout : itype(_Ptr<FILE>);
extern FILE *stderr : itype(_Ptr<FILE>);
#endif

// TODO: handle strings
// int remove(const char *name);
// int rename(const char *from, const char *to);
FILE *tmpfile(void) : itype(_Ptr<FILE>);
// TODO: handle strings
// char *tmpnam(char *source);
int fclose(FILE *stream : itype(_Ptr<FILE>));
int fflush(FILE *stream : itype(_Ptr<FILE>));
_Unchecked
FILE *fopen(const char * restrict filename,
            const char * restrict mode) : itype(_Ptr<FILE>);
_Unchecked
FILE *freopen(const char * restrict filename,
              const char * restrict mode,
              FILE * restrict stream : itype(restrict _Ptr<FILE>)) :
  itype(_Ptr<FILE>);

void setbuf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            char * restrict buf : count(BUFSIZ));
int setvbuf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            char * restrict buf : count(size),
            int mode, size_t size);

//
// TODO: printing and scanning functions are still mostly
// unchecked because of the use of varargs.
// * There may not be enough arguments for the format string.
// * Any pointer arguments may not meet the requirements of the
//  format string.
//
_Unchecked
int fprintf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            const char * restrict format, ...);
_Unchecked
int fscanf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
           const char * restrict format, ...);
// TODO: handle strings
// int printf(const char * restrict format, ...);
// int scanf(const char * restrict format, ...);

// OMITTED INTENTIONALLY:
// sprintf cannot be made checked.  It is missing the bounds
// for the output buffer.
// int sprintf(char * restrict s,
//            const char * restrict format, ...);
//
// TODO: handle strings
// int sscanf(const char * restrict s,
//            const char * restrict format, ...);
// TODO: Apple System Headers Support
#if !defined (__APPLE__) && _FORTIFY_SOURCE > 0
_Unchecked
int snprintf(char * restrict s : count(n), size_t n,
             const char * restrict format, ...);
#endif

_Unchecked
int vfprintf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
             const char * restrict format,
             va_list arg);
_Unchecked
int vfscanf(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            const char * restrict format,
            va_list arg);

// TODO: handle strings
// int vprintf(const char * restrict format,
//             va_list arg);
// int vscanf(const char * restrict format,
//            va_list arg);
// TODO: Apple System Headers Support
#if !defined (__APPLE__) && _FORTIFY_SOURCE > 0
_Unchecked
int vsnprintf(char * restrict s : count(n), size_t n,
              const char * restrict format,
              va_list arg);
#endif
// OMITTED INTENTIONALLY:
// vsprintf cannot be made checked. it is missing the bounds
// for the output buffer.
// int vsprintf(char * restrict s,
//             const char * restrict format,
//             va_list arg);
// TODO: handle strings
// int vsscanf(const char * restrict s,
//            const char * restrict format,
//            va_list arg);

int fgetc(FILE *stream : itype(_Ptr<FILE>));
int fputc(int c, FILE *stream : itype(_Ptr<FILE>));
_Unchecked
char *fgets(char * restrict s : count(n), int n,
            FILE * restrict stream : itype(restrict _Ptr<FILE>)) :
  bounds(s, s + n);
_Unchecked
int fputs(const char * restrict s,
          FILE * restrict stream : itype(restrict _Ptr<FILE>));
int getc(FILE *stream : itype(_Ptr<FILE>));
int putc(int c, FILE *stream : itype(_Ptr<FILE>));
// TODO: strings
// int puts(const char *str);
int ungetc(int c, FILE *stream : itype(_Ptr<FILE>));

size_t fread(void * restrict pointer : byte_count(size * nmemb),
             size_t size, size_t nmemb,
             FILE * restrict stream : itype(restrict _Ptr<FILE>));

size_t fwrite(const void * restrict pointer : byte_count(size * nmemb),
              size_t size, size_t nmemb,
              FILE * restrict stream : itype(restrict _Ptr<FILE>));

int fgetpos(FILE * restrict stream : itype(restrict _Ptr<FILE>),
            fpos_t * restrict pos : itype(restrict _Ptr<fpos_t>));

int fseek(FILE *stream : itype(_Ptr<FILE>), long int offset, int whence);
int fsetpos(FILE *stream : itype(_Ptr<FILE>),
            const fpos_t *pos :  itype(_Ptr<const fpos_t>));

long int ftell(FILE *stream : itype(_Ptr<FILE>));
void rewind(FILE *stream : itype(_Ptr<FILE>));

void clearerr(FILE *stream : itype(_Ptr<FILE>));
int feof(FILE *stream : itype(_Ptr<FILE>));
int ferror(FILE *stream : itype(_Ptr<FILE>));
// TODO: strings
// void perror(const char *s);

#include "_builtin_stdio_checked.h"

#pragma BOUNDS_CHECKED OFF
