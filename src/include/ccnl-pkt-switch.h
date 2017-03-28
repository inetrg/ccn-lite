/*
 * @f pkt-switch.h
 * @b CCN lite - encoding for switching packet formats
 *
 * Copyright (C) 2014-15, Christian Tschudin, University of Basel
 * Copyright (C) 2017 Inria
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
 * 2017-03-27 created
 */

#ifndef CCNL_PKT_SWITCH_H
#define CCNL_PKT_SWITCH_H

int
ccnl_switch_dehead(unsigned char **buf, int *len, int *code);

int
ccnl_enc2suite(int enc);

// ----------------------------------------------------------------------

#ifdef NEEDS_PACKET_CRAFTING

int
ccnl_switch_prependCodeVal(unsigned long val, int *offset, unsigned char *buf);

int
ccnl_switch_prependCoding(unsigned int code, int *offset, unsigned char *buf);

#endif // NEEDS_PACKET_CRAFTING


#endif /* CCNL-PKT-SWITCH_H */