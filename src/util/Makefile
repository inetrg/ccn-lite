# ccnl/util/Makefile

CC?=gcc
INCLUDES += ../include
CFLAGS=-Wall -g -DUSE_UTIL -Wno-error=deprecated-declarations -std=c99 -Werror -I${INCLUDES}
EXTLIBS=-lcrypto
CREATE_BIN=mkdir -p ../../bin && cd ../../bin && ln -f -s ../src/util/$@ $@


PROGS=	ccn-lite-ccnb2xml \
	ccn-lite-cryptoserver\
	ccn-lite-ctrl \
	ccn-lite-fetch \
	ccn-lite-mkC \
	ccn-lite-mkI \
	ccn-lite-mkF \
	ccn-lite-peek \
	ccn-lite-pktdump \
	ccn-lite-produce \
	ccn-lite-rpc \
	ccn-lite-simplenfn \
	ccn-lite-valid

CCNB_LIB =   ../include/ccnl-pkt-ccnb.h ../pkt-formats/ccnb.c ../lib-sha256.c
CCNTLV_LIB = ../include/ccnl-pkt-ccntlv.h ../pkt-formats/ccntlv.c
CISTLV_LIB = ../include/ccnl-pkt-cisntlv.h ../pkt-formats/cistlv.c
IOTTLV_LIB = ../include/ccnl-pkt-iottlv.h ../pkt-formats/iottlv.c
LOCALRPC_LIB = ../include/ccnl-pkt-localrpc.h ../pkt-formats/localrpc.c ../ext/localrpc.c
NDNTLV_LIB = ../include/ccnl-pkt-ndntlv.h ../pkt-formats/ndntlv.c

SUITE_LIBS = ${CCNB_LIB} ${CCNTLV_LIB} ${LOCALRPC_LIB} ${NDNTLV_LIB}


CCNL_CORE_LIB = ../include/ccnl-defs.h ../include/ccnl-core.h ../core/core.c

CCNL_PLATFORM_LIB = ../include/ccnl-includes.h \
                    ../ext/debug.c ../include/ccnl-ext.h ../ccnl-platform.c  \
                    ../ext/frag.c ../ext/sched.c ../ext/hmac.c \
                    ../ext/logging.c


NFN_LIB = ../ext/nfn.c krivine.c krivine-common.c

# CCNL_NFN_MONITOR to log messages to nfn-scala montior
NFNFLAGS += -DUSE_NFN -DUSE_NFN_MONITOR
NACKFLAGS += -DUSE_NACK -DUSE_NFN_MONITOR

ifdef USE_NFN
    $(info *** With NFN ***)
    CFLAGS += ${NFNFLAGS}
endif

# ----------------------------------------------------------------------

all: $(PROGS)

ccn-lite-ccnb2xml: Makefile ccn-lite-ccnb2xml.c \
		${CCNB_LIB} ../include/ccnl-defs.h common.c
	$(CC) $(CFLAGS) ccn-lite-ccnb2xml.c -o $@ ${EXTLIBS}
	@${CREATE_BIN}

ccn-lite-ctrl: Makefile ccn-lite-ctrl.c ${CCNB_LIB} \
		../include/ccnl-defs.h common.c
	$(CC) $(CFLAGS) ccn-lite-ctrl.c -o $@ ${EXTLIBS}
	@${CREATE_BIN}

ccn-lite-peek: Makefile ccn-lite-peek.c \
		${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} \
		../include/ccnl-defs.h ../core/util.c
	$(CC) $(CFLAGS) ccn-lite-peek.c -o $@
	@${CREATE_BIN}

ccn-lite-fetch: Makefile ccn-lite-fetch.c \
		${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} \
		../include/ccnl-defs.h ../core/util.c common.c
	$(CC) $(CFLAGS) ccn-lite-fetch.c -o $@
	@${CREATE_BIN}

ccn-lite-pktdump: Makefile ccn-lite-pktdump.c \
		${CCNB_LIB} ${CCNTLV_LIB} ${IOTTLV_LIB} ${NDNTLV_LIB} \
		${LOCALRPC_LIB}
	$(CC) $(CFLAGS) ccn-lite-pktdump.c -o $@
	@${CREATE_BIN}

ccn-lite-simplenfn: Makefile ccn-lite-simplenfn.c \
		${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} \
		../include/ccnl-defs.h ../core/util.c
	$(CC) $(CFLAGS) ccn-lite-simplenfn.c -o $@
	@${CREATE_BIN}

ccn-lite-rpc: Makefile ccn-lite-rpc.c \
		${NDNTLV_LIB} ${LOCALRPC_LIB} ../include/ccnl-defs.h common.c
	$(CC) $(CFLAGS) ccn-lite-rpc.c -o $@
	@${CREATE_BIN}

ccn-lite-deF: Makefile ccn-lite-deF.c ${CCNB_LIB} ../include/ccnl-defs.h ccnl-frag.h
	$(CC) $(CFLAGS) ccn-lite-deF.c -o $@
	@${CREATE_BIN}

ccn-lite-mkC: Makefile ccn-lite-mkC.c ${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} ../include/ccnl-defs.h
	$(CC) $(CFLAGS) ccn-lite-mkC.c -o $@ ${EXTLIBS}
	@${CREATE_BIN}

ccn-lite-mkF: Makefile ccn-lite-mkF.c ${CCNB_LIB} ${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} ../include/ccnl-defs.h
	$(CC) $(CFLAGS) ccn-lite-mkF.c -o $@
	@${CREATE_BIN}

ccn-lite-mkI: Makefile ccn-lite-mkI.c ${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} ../include/ccnl-defs.h
	$(CC) $(CFLAGS) ccn-lite-mkI.c -o $@
	@${CREATE_BIN}

ccn-lite-cryptoserver: Makefile ccn-lite-cryptoserver.c
	$(CC) $(CFLAGS) ccn-lite-cryptoserver.c -o $@ ${EXTLIBS}
	@${CREATE_BIN}

ccn-lite-produce: Makefile ccn-lite-produce.c ${CCNB_LIB} ${CCNTLV_LIB} ${NDNTLV_LIB} ../include/ccnl-defs.h
	$(CC) $(CFLAGS) ccn-lite-produce.c -o $@ ${EXTLIBS}
	@${CREATE_BIN}

ccn-lite-valid: Makefile ccn-lite-valid.c common.c \
		${CCNTLV_LIB} ${NDNTLV_LIB} \
		../include/ccnl-defs.h ../core/util.c
	$(CC) $(CFLAGS) ccn-lite-valid.c -o $@
	@${CREATE_BIN}

demo: $(PROGS)
	./ccn-lite-mkI /ccn-lite/says/hello/world/äöü | ./ccn-lite-pktdump
	./ccn-lite-mkI /ccn-lite/says/hello/world/äöü | ./ccn-lite-ccnb2xml

install: all
	install ${PROGS} ${INSTALL_PATH}/bin

uninstall:
	cd ${INSTALL_PATH}/bin && rm -f ${PROGS} && cd - > /dev/null

clean:
	rm -rf *~ $(PROGS)
	rm -rf ../../bin
