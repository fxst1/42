#if defined (_WIN32) || defined (WIN32) || defined (__WIN32__)
# define OS_FT WINDOWS
# define ARCH_FT 32
# define PATH_SEPARATOR "\\"
# define PATH_SEPARATOR_LEN 1
#elif defined (_WIN64) || defined (WIN64) || defined (__WIN64__)
# define OS_FT WINDOWS
# define ARCH_FT 64
# define PATH_SEPARATOR "/"
# define PATH_SEPARATOR_LEN 1
#elif defined (__APPLE__) || defined (__MAC__)
# define OS_FT MAC
# define ARCH_FT 64
# define PATH_SEPARATOR "/"
# define PATH_SEPARATOR_LEN 1
#elif defined (__unix__) || defined (unix)
# define OS_FT UNIX
# define ARCH_FT 64
# define PATH_SEPARATOR "/"
# define PATH_SEPARATOR_LEN 1
#else
# define OS_FT UNKNOWN
# define ARCH_FT 0
# define PATH_SEPARATOR "\0"
# define PATH_SEPARATOR_LEN 0
#endif
