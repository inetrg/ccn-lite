#ifndef CCNL_UTILS_H
#define CCNL_UTILS_H

#ifdef USE_DEBUG_MALLOC

void* debug_realloc(void *p, int s, const char *fn, int lno);
void debug_free(void *p, const char *fn, int lno);

#  ifdef CCNL_ARDUINO

void* debug_malloc(int s, const char *fn, int lno, double tstamp);
void* debug_calloc(int n, int s, const char *fn, int lno, double tstamp);
void* debug_strdup(const char *s, const char *fn, int lno, double tstamp);
struct ccnl_buf_s* debug_buf_new(void *data, int len, const char *fn, int lno, double tstamp);

#    define ccnl_malloc(s)        debug_malloc(s, PSTR(__FILE__), __LINE__, CCNL_NOW())
#    define ccnl_calloc(n,s)      debug_calloc(n, s, PSTR(__FILE__), __LINE__, CCNL_NOW())
#    define ccnl_realloc(p,s)     debug_realloc(p, s, PSTR(__FILE__), __LINE__)
#    define ccnl_strdup(s)        debug_strdup(s, PSTR(__FILE__), __LINE__, CCNL_NOW())
#    define ccnl_free(p)          debug_free(p, PSTR(__FILE__), __LINE__)
#    define ccnl_buf_new(p,s)     debug_buf_new(p, s, PSTR(__FILE__), __LINE__, CCNL_NOW())

#  else

void* debug_malloc(int s, const char *fn, int lno, char *tstamp);
void* debug_calloc(int n, int s, const char *fn, int lno, char *tstamp);
void* debug_strdup(const char *s, const char *fn, int lno, char *tstamp);
struct ccnl_buf_s* debug_buf_new(void *data, int len, const char *fn, int lno, char *tstamp);

#    define ccnl_malloc(s)        debug_malloc(s, __FILE__, __LINE__,timestamp())
#    define ccnl_calloc(n,s)      debug_calloc(n, s, __FILE__, __LINE__,timestamp())
#    define ccnl_realloc(p,s)     debug_realloc(p, s, __FILE__, __LINE__)
#    define ccnl_strdup(s)        debug_strdup(s, __FILE__, __LINE__,timestamp())
#    define ccnl_free(p)          debug_free(p, __FILE__, __LINE__)
#    define ccnl_buf_new(p,s)     debug_buf_new(p, s, __FILE__, __LINE__,timestamp())

#  endif

#else

#  define ccnl_malloc(s)                  malloc(s)
#  define ccnl_calloc(n,s)                calloc(n,s)
#  define ccnl_realloc(p,s)               realloc(p,s)
#  define ccnl_free(p)                    free(p)

#endif

#define free_2ptr_list(a,b)       ccnl_free(a), ccnl_free(b)
#define free_3ptr_list(a,b,c)     ccnl_free(a), ccnl_free(b), ccnl_free(c)
#define free_4ptr_list(a,b,c,d)   ccnl_free(a), ccnl_free(b), ccnl_free(c), ccnl_free(d);
#define free_5ptr_list(a,b,c,d,e) ccnl_free(a), ccnl_free(b), ccnl_free(c), ccnl_free(d), ccnl_free(e);
#define free_prefix(p)  do{ if(!p) break; ccnl_free(p->chunknum);  \
                free_4ptr_list(p->bytes,p->comp,p->complen,p); } while(0)
#define free_content(c) do{ /* free_prefix(c->name); */ free_packet(c->pkt); \
                        ccnl_free(c); } while(0)

/* translates link-layer address into a string */
char* ll2ascii(unsigned char *addr, size_t len);

// --- time

char* timestamp(void);

#ifdef CCNL_ARDUINO

double CCNL_NOW(void);

struct timeval {
    uint32_t tv_sec;
    uint32_t tv_usec;
};

void gettimeofday(struct timeval *tv, void *dummy);

#else // !CCNL_ARDUINO

#define CCNL_NOW()                    current_time()

#ifndef CCNL_LINUXKERNEL
double current_time(void);
#endif

#endif // !CCNL_ARDUINO

#ifdef CCNL_UNIX

#ifndef CCNL_OMNET
#  define CCNL_NOW()                    current_time()
#endif

#endif // CCNL_UNIX


#if defined(CCNL_UNIX) || defined (CCNL_RIOT) || defined (CCNL_ARDUINO)

struct ccnl_timer_s {
    struct ccnl_timer_s *next;
    struct timeval timeout;
    void (*fct)(char,int);
    void (*fct2)(void*,void*);
    char node;
    int intarg;
    void *aux1;
    void *aux2;
  //    int handler;
};

void ccnl_get_timeval(struct timeval *tv);
long timevaldelta(struct timeval *a, struct timeval *b);
void* ccnl_set_timer(uint64_t usec, void (*fct)(void *aux1, void *aux2), void *aux1, void *aux2);
void ccnl_rem_timer(void *h);

#endif

#ifdef CCNL_LINUXKERNEL

// we use the kernel's timerlist service, i.e. add_timer()

struct ccnl_timerlist_s {
    struct timer_list tl;
    void (*fct)(void *ptr, void *aux);
    void *ptr, *aux;
};

static struct ccnl_timerlist_s *spare_timer;

inline void ccnl_get_timeval(struct timeval *tv);
int current_time(void);
static void ccnl_timer_callback(unsigned long data);
static void* ccnl_set_timer(int usec, void(*fct)(void*,void*), void *ptr, void *aux);
static void ccnl_rem_timer(void *p);

#else

int ccnl_run_events(void);

#endif // CCNL_LINUXKERNEL

#ifdef USE_SCHEDULER
void* ccnl_set_absolute_timer(struct timeval abstime, void (*fct)(void *aux1, void *aux2), void *aux1, void *aux2);
#endif

#endif /* CCNL-UTILS_H */
