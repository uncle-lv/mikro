#ifndef __common_h__
#define __common_h__

#ifdef DEBUG
  #define DBG(...) \
    do { \
      printf(__VA_ARGS__); \
      printf("\n"); \
    } while(0)
#else
  #define DBG(...) do{}while(0)
#endif

#endif
