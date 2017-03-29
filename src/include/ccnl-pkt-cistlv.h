/*
 * @f pkt-cistlv.h
 * @b header file for CCN lite, Mark Stapp's (Cisco) defs for TLV (Jan 6, 2015);
 *
 * Copyright (C) 2015, Christian Tschudin, University of Basel
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
 * 2015-01-06 created
 */
#ifndef CCNL_PKT_CISTLV_H
#define CCNL_PKT_CISTLV_H

#include "ccnl-core.h"


// ----------------------------------------------------------------------
// Header

struct cisco_tlvhdr_201501_s {
    unsigned char version;
    unsigned char pkttype;
    unsigned short pktlen;
    unsigned char hoplim;  // not used for data
    unsigned char flags;
    unsigned char resvd;
    unsigned char hlen;
} __attribute__((packed));


// Non-TLV values for the packettype in the header
#define CISCO_PT_Interest                        1
#define CISCO_PT_Content                         2
#define CISCO_PT_Nack                            3

// ----------------------------------------------------------------------
// TLV message

// Version
#define CISCO_TLV_V1                             1

// T values

#define CISCO_TLV_Interest                       1
#define CISCO_TLV_Content                        2

#define CISCO_TLV_Name                           1
#define CISCO_TLV_NameComponent                  1
#define CISCO_TLV_NameSegment                    2
#define CISCO_TLV_ContentData                    4
#define CISCO_TLV_Certificate                    5
#define CISCO_TLV_SignedInfo                     6
#define CISCO_TLV_ContentDigest                  7
#define CISCO_TLV_PublicKey                      8
#define CISCO_TLV_KeyName                        9
#define CISCO_TLV_KeyNameComponent               1
#define CISCO_TLV_Signature                      10
#define CISCO_TLV_Timestamp                      11
#define CISCO_TLV_Witness                        12
#define CISCO_TLV_SignatureBits                  13
#define CISCO_TLV_DigestAlgorithm                14
#define CISCO_TLV_FinalSegmentID                 15
#define CISCO_TLV_PublisherPublicKeyDigest       16
#define CISCO_TLV_PublisherPublicKeyName         17
#define CISCO_TLV_ContentExpiration              18
#define CISCO_TLV_CacheTTL                       19
#define CISCO_TLV_VendorSpecific                 20
#define CISCO_TLV_VendorId                       21

#define CISCO_ERR_NOROUTE                        1
#define CISCO_ERR_CONGESTED                      2
#define CISCO_ERR_NORESOURCE                     3
#define CISCO_ERR_POLICY                         4

// convert network order byte array into local unsigned integer value
int
ccnl_cistlv_extractNetworkVarInt(unsigned char *buf, int len,
                                 int *intval);

// returns hdr length to skip before the payload starts.
int
ccnl_cistlv_getHdrLen(unsigned char *data, int len);

// parse TL (returned in typ and vallen) and adjust buf and len
int
ccnl_cistlv_dehead(unsigned char **buf, int *len,
                   unsigned int *typ, unsigned int *vallen);

// we use one extraction routine for both interest and data pkts
struct ccnl_pkt_s*
ccnl_cistlv_bytes2pkt(unsigned char *start, unsigned char **data, int *datalen);

// ----------------------------------------------------------------------

#ifdef NEEDS_PREFIX_MATCHING

// returns: 0=match, -1=otherwise
int
ccnl_cistlv_cMatch(struct ccnl_pkt_s *p, struct ccnl_content_s *c);

#endif

// ----------------------------------------------------------------------
// packet composition

#ifdef NEEDS_PACKET_CRAFTING

// write given TL *before* position buf+offset, adjust offset and return len
int
ccnl_cistlv_prependTL(unsigned int type, unsigned short len,
                      int *offset, unsigned char *buf);

// write len bytes *before* position buf[offset], adjust offset
int
ccnl_cistlv_prependBlob(unsigned short type, unsigned char *blob,
                        unsigned short len, int *offset, unsigned char *buf);


// write (in network order and with the minimal number of bytes);
// the given integer val *before* position buf[offset], adjust offset
// and return number of bytes prepended. 0 is represented as %x00
int
ccnl_cistlv_prependNetworkVarInt(unsigned short type, unsigned int intval,
                                 int *offset, unsigned char *buf);

// write (in network order and with the minimal number of bytes);
// the given integer val *before* position buf[offset], adjust offset
// and return number of bytes prepended. 0 is represented as %x00
int
ccnl_cistlv_prepend4BInt(unsigned short type, unsigned int intval,
                         int *offset, unsigned char *buf);

// write *before* position buf[offset] the Cisco fixed header,
// returns total packet len
int
ccnl_cistlv_prependFixedHdr(unsigned char ver,
                            unsigned char packettype,
                            unsigned short payloadlen,
                            unsigned char hoplimit,
                            int *offset, unsigned char *buf);

// write given prefix and chunknum *before* buf[offs], adjust offset
// and return bytes used
int
ccnl_cistlv_prependName(struct ccnl_prefix_s *name,
                        int *offset, unsigned char *buf);

// write Interest payload *before* buf[offs], adjust offs and return bytes used
int
ccnl_cistlv_prependInterest(struct ccnl_prefix_s *name,
                            int *offset, unsigned char *buf);

// write Interest packet *before* buf[offs], adjust offs and return bytes used
int
ccnl_cistlv_prependChunkInterestWithHdr(struct ccnl_prefix_s *name,
                                        int *offset, unsigned char *buf);

// write Interest packet *before* buf[offs], adjust offs and return bytes used
int
ccnl_cistlv_prependInterestWithHdr(struct ccnl_prefix_s *name,
                                int *offset, unsigned char *buf);

// write Content payload *before* buf[offs], adjust offs and return bytes used
int
ccnl_cistlv_prependContent(struct ccnl_prefix_s *name,
                           unsigned char *payload, int paylen,
                           unsigned int *lastchunknum, int *offset,
                           int *contentpos, unsigned char *buf);

// write Content packet *before* buf[offs], adjust offs and return bytes used
int
ccnl_cistlv_prependContentWithHdr(struct ccnl_prefix_s *name,
                                  unsigned char *payload, int paylen,
                                  unsigned int *lastchunknum, int *offset,
                                  int *contentpos, unsigned char *buf);

#endif // NEEDS_PACKET_CRAFTING

#endif // USE_SUITE_CISTLV


// eof
// #endif /* CCNL-PKT-CISTLV_H */
