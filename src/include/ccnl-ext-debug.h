/*
 * @f ccnl-ext-debug.h
 * @b CCNL debugging support, dumping routines, memory tracking, stats
 *
 * Copyright (C) 2011-13, Christian Tschudin, University of Basel
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * File history:
 * 2014-10-30 created <christopher.scherb@unibas.ch
 */

#ifndef CCNL_EXT_DEBUG_H
#define CCNL_EXT_DEBUG_H

#include <stdio.h>

struct mhdr {
    struct mhdr *next;
    char *fname;
    int lineno, size;
#ifdef CCNL_ARDUINO
    double tstamp;
#else
    char *tstamp; // Linux kernel (no double), also used for CCNL_UNIX
#endif
} *mem;

#ifndef CCNL_LINUXKERNEL
struct ccnl_stats_s {
    void* log_handler;
    FILE *ofp;
    int log_sent;
    int log_recv;
    int log_recv_old;
    int log_sent_old;
    int log_need_rt_seqn;
    int log_content_delivery_rate_per_s;
    double log_start_t;
    double log_cdr_t;
    //
    FILE *ofp_r, *ofp_s, *ofp_q;
    double log_recv_t_i;
    double log_recv_t_c;
    double log_sent_t_i;
    double log_sent_t_c;
};
#endif // CCNL_LINUXKERNEL

#ifdef USE_LOGGING
extern int debug_level;

#define FATAL   0  // FATAL
#define ERROR   1  // ERROR
#define WARNING 2  // WARNING
#define INFO    3  // INFO
#define DEBUG   4  // DEBUG
#define VERBOSE 5  // VERBOSE
#define TRACE 	6  // TRACE


// ----------------------------------------------------------------------
// _TRACE macro

#ifdef CCNL_ARDUINO

#define _TRACE(F,P) do {                    \
    if (debug_level >= TRACE) { char *cp;   \
          Serial.print("[");                \
          Serial.print(P); \
          Serial.print("] ");               \
          Serial.print(timestamp());        \
          Serial.print(": ");               \
          strcpy_P(logstr, PSTR(__FILE__)); \
          cp = logstr + strlen(logstr);     \
          while (cp >= logstr && *cp != '/') cp--; \
          Serial.print(cp+1);               \
          Serial.print(":");                \
          Serial.print(__LINE__);           \
          Serial.println("\r");             \
     }} while(0)

#else

#ifdef CCNL_LINUXKERNEL

#define _TRACE(F,P) do {                                    \
    if (debug_level >= TRACE) {                             \
        printk("%s: ", THIS_MODULE->name);                  \
        printk("%s() in %s:%d\n", (F), __FILE__, __LINE__); \
    }} while (0)

#else

#define _TRACE(F,P) do {                                    \
    if (debug_level >= TRACE) {                             \
        fprintf(stderr, "[%c] %s: %s() in %s:%d\n",         \
                (P), timestamp(), (F), __FILE__, __LINE__); \
    }} while (0)

#endif // CCNL_LINUXKERNEL

#endif // CCNL_ARDUINO

#define DEBUGSTMT(LVL, ...) do { \
        if ((LVL)>debug_level) break; \
        __VA_ARGS__; \
} while (0)

// ----------------------------------------------------------------------
// DEBUGMSG macro

#ifdef CCNL_LINUXKERNEL

#  define DEBUGMSG(LVL, ...) do {       \
        if ((LVL)>debug_level) break;   \
        printk("%s: ", THIS_MODULE->name);      \
        printk(__VA_ARGS__);            \
    } while (0)
#  define fprintf(fd, ...)      printk(__VA_ARGS__)

#elif defined(CCNL_ANDROID)

#  define DEBUGMSG(LVL, ...) do { int len;          \
        if ((LVL)>debug_level) break;               \
        len = sprintf(android_logstr, "[%c] %s: ",  \
            ccnl_debugLevelToChar(LVL),             \
            timestamp());                           \
        len += sprintf(android_logstr+len, __VA_ARGS__);   \
        jni_append_to_log(android_logstr);          \
    } while (0)

#elif defined(CCNL_ARDUINO)

#  define DEBUGMSG_OFF(...) do{}while(0)
#  define DEBUGMSG_ON(L,FMT, ...) do {     \
        if ((L) <= debug_level) {       \
          Serial.print("[");            \
          Serial.print(ccnl_debugLevelToChar(debug_level)); \
          Serial.print("] ");           \
          sprintf_P(logstr, PSTR(FMT), ##__VA_ARGS__); \
          Serial.print(timestamp());    \
          Serial.print(" ");            \
          Serial.print(logstr);         \
          Serial.print("\r");           \
        }                               \
   } while(0)

#else

#  define DEBUGMSG(LVL, ...) do {                   \
        if ((LVL)>debug_level) break;               \
        fprintf(stderr, "[%c] %s: ",                \
            ccnl_debugLevelToChar(LVL),             \
            timestamp());                           \
        fprintf(stderr, __VA_ARGS__);               \
    } while (0)

#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define TRACEIN(F)    do { _TRACE(__func__, '>'); } while (0)
#  define TRACEOUT(F)   do { _TRACE(__func__, '<'); } while (0)
#else
#  define TRACEIN(F)    do { _TRACE("" F, '>'); } while (0)
#  define TRACEOUT(F)   do { _TRACE("" F, '<'); } while (0)
#endif

// ----------------------------------------------------------------------

#else // !USE_LOGGING
#  define DEBUGSTMT(...)                   do {} while(0)
#  define DEBUGMSG(...)                    do {} while(0)
#  define DEBUGMSG_ON(...)                 do {} while(0)
#  define DEBUGMSG_OFF(...)                do {} while(0)
#  define TRACEIN(...)                     do {} while(0)
#  define TRACEOUT(...)                    do {} while(0)

#endif // USE_LOGGING

// only in the Arduino case we wish to control debugging on a module basis
#ifndef CCNL_ARDUINO
// core source files
# define DEBUGMSG_CORE(...) DEBUGMSG(__VA_ARGS__)
# define DEBUGMSG_CFWD(...) DEBUGMSG(__VA_ARGS__)
# define DEBUGMSG_CUTL(...) DEBUGMSG(__VA_ARGS__)
// extensions
# define DEBUGMSG_EFRA(...) DEBUGMSG(__VA_ARGS__)
// packet formats
# define DEBUGMSG_PCNX(...) DEBUGMSG(__VA_ARGS__)
# define DEBUGMSG_PIOT(...) DEBUGMSG(__VA_ARGS__)
# define DEBUGMSG_PNDN(...) DEBUGMSG(__VA_ARGS__)
#endif

// eof
#endif /* CCNL-EXT-DEBUG_H */
