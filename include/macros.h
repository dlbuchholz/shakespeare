#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#define FREE_IF_EXISTS(s)  do { if(s != NULL) free(s); } while(0)
