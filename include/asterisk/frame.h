/*
 * Asterisk -- A telephony toolkit for Linux.
 *
 * Asterisk internal frame definitions.
 * 
 * Copyright (C) 1999, Mark Spencer
 *
 * Mark Spencer <markster@linux-support.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU Lesser General Public License.  Other components of
 * Asterisk are distributed under The GNU General Public License
 * only.
 */

#ifndef _ASTERISK_FRAME_H
#define _ASTERISK_FRAME_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#include <endian.h>
#include <sys/types.h>

//! Data structure associated with a single frame of data
/* A frame of data read used to communicate between 
   between channels and applications */
struct ast_frame {
	/*! Kind of frame */
	int frametype;				
	/*! Subclass, frame dependent */
	int subclass;				
	/*! Length of data */
	int datalen;				
	/*! Number of 8khz samples in this frame */
	int samples;				
	/*! Was the data malloc'd?  i.e. should we free it when we discard the frame? */
	int mallocd;				
	/*! How far into "data" the data really starts */
	int offset;				
	/*! Optional source of frame for debugging */
	char *src;				
	/*! Pointer to actual data */
	void *data;				
	/*! Next/Prev for linking stand alone frames */
	struct ast_frame *prev;			
	/*! Next/Prev for linking stand alone frames */
	struct ast_frame *next;			
								/* Unused except if debugging is turned on, but left
								   in the struct so that it can be turned on without
								   requiring a recompile of the whole thing */
};

struct ast_frame_chain {
	/* XXX Should ast_frame chain's be just prt of frames, i.e. should they just link? XXX */
	struct ast_frame *fr;
	struct ast_frame_chain *next;
};

#define AST_FRIENDLY_OFFSET 	64		/*! It's polite for a a new frame to
										   have at least this number of bytes
										   of offset before your real frame data
										   so that additional headers can be
										   added. */
/*! Need the header be free'd? */
#define AST_MALLOCD_HDR		(1 << 0)
/*! Need the data be free'd? */
#define AST_MALLOCD_DATA	(1 << 1)
/*! Need the source be free'd? (haha!) */
#define AST_MALLOCD_SRC		(1 << 2)

/* Frame types */
/*! A DTMF digit, subclass is the digit */
#define AST_FRAME_DTMF		1
/*! Voice data, subclass is AST_FORMAT_* */
#define AST_FRAME_VOICE		2
/*! Video frame, maybe?? :) */
#define AST_FRAME_VIDEO		3
/*! A control frame, subclass is AST_CONTROL_* */
#define AST_FRAME_CONTROL	4
/*! An empty, useless frame */
#define AST_FRAME_NULL		5
/*! Inter Aterisk Exchange private frame type */
#define AST_FRAME_IAX		6
/*! Text messages */
#define AST_FRAME_TEXT		7
/*! Image Frames */
#define AST_FRAME_IMAGE		8
/*! HTML Frame */
#define AST_FRAME_HTML		9

/* HTML subclasses */
/*! Sending a URL */
#define AST_HTML_URL		1
/*! Data frame */
#define AST_HTML_DATA		2
/*! Beginning frame */
#define AST_HTML_BEGIN		4
/*! End frame */
#define AST_HTML_END		8
/*! Load is complete */
#define AST_HTML_LDCOMPLETE	16
/*! Peer is unable to support HTML */
#define AST_HTML_NOSUPPORT	17
/*! Send URL, and track */
#define AST_HTML_LINKURL	18
/*! No more HTML linkage */
#define AST_HTML_UNLINK		19
/*! Reject link request */
#define AST_HTML_LINKREJECT	20

/* Data formats for capabilities and frames alike */
/*! G.723.1 compression */
#define AST_FORMAT_G723_1	(1 << 0)
/*! GSM compression */
#define AST_FORMAT_GSM		(1 << 1)
/*! Raw mu-law data (G.711) */
#define AST_FORMAT_ULAW		(1 << 2)
/*! Raw A-law data (G.711) */
#define AST_FORMAT_ALAW		(1 << 3)
/*! MPEG-2 layer 3 */
#define AST_FORMAT_MP3		(1 << 4)
/*! ADPCM (whose?) */
#define AST_FORMAT_ADPCM	(1 << 5)
/*! Raw 16-bit Signed Linear (8000 Hz) PCM */
#define AST_FORMAT_SLINEAR	(1 << 6)
/*! LPC10, 180 samples/frame */
#define AST_FORMAT_LPC10	(1 << 7)
/*! G.729A audio */
#define AST_FORMAT_G729A	(1 << 8)
/*! SpeeX Free Compression */
#define AST_FORMAT_SPEEX	(1 << 9)
/*! Maximum audio format */
#define AST_FORMAT_MAX_AUDIO	(1 << 15)
/*! JPEG Images */
#define AST_FORMAT_JPEG		(1 << 16)
/*! PNG Images */
#define AST_FORMAT_PNG		(1 << 17)
/*! H.261 Video */
#define AST_FORMAT_H261		(1 << 18)
/*! H.263 Video */
#define AST_FORMAT_H263		(1 << 19)

/* Control frame types */
/*! Other end has hungup */
#define AST_CONTROL_HANGUP		1
/*! Local ring */
#define AST_CONTROL_RING		2
/*! Remote end is ringing */
#define AST_CONTROL_RINGING 		3
/*! Remote end has answered */
#define AST_CONTROL_ANSWER		4
/*! Remote end is busy */
#define AST_CONTROL_BUSY		5
/*! Make it go off hook */
#define AST_CONTROL_TAKEOFFHOOK		6
/*! Line is off hook */
#define AST_CONTROL_OFFHOOK		7
/*! Congestion (circuits busy) */
#define AST_CONTROL_CONGESTION		8
/*! Flash hook */
#define AST_CONTROL_FLASH		9
/*! Wink */
#define AST_CONTROL_WINK		10
/*! Set a low-level option */
#define AST_CONTROL_OPTION		11
/*! Key Radio */
#define	AST_CONTROL_RADIO_KEY		12
/*! Un-Key Radio */
#define	AST_CONTROL_RADIO_UNKEY		13

/* Option identifiers and flags */
#define AST_OPTION_FLAG_REQUEST		0
#define AST_OPTION_FLAG_ACCEPT		1
#define AST_OPTION_FLAG_REJECT		2
#define AST_OPTION_FLAG_QUERY		4
#define AST_OPTION_FLAG_ANSWER		5
#define AST_OPTION_FLAG_WTF		6

/* Verify touchtones by muting audio transmission 
	(and reception) and verify the tone is still present */
#define AST_OPTION_TONE_VERIFY		1		

/* Put a compatible channel into TDD (TTY for the hearing-impared) mode */
#define	AST_OPTION_TDD			2

/* Relax the parameters for DTMF reception (mainly for radio use) */
#define	AST_OPTION_RELAXDTMF		3

struct ast_option_header {
	/* Always keep in network byte order */
#if __BYTE_ORDER == __BIG_ENDIAN
        u_int16_t flag:3;
        u_int16_t option:13;
#else
#if __BYTE_ORDER == __LITTLE_ENDIAN
        u_int16_t option:13;
        u_int16_t flag:3;
#else
#error Byte order not defined
#endif
#endif
		u_int8_t data[0];
};

// Requests a frame to be allocated
/* 
 * \param source 
 * Request a frame be allocated.  source is an optional source of the frame, 
 * len is the requested length, or "0" if the caller will supply the buffer 
 */
#if 0 /* Unimplemented */
struct ast_frame *ast_fralloc(char *source, int len);
#endif

//! Frees a frame
/*! 
 * \param fr Frame to free
 * Free a frame, and the memory it used if applicable
 * no return.
 */
void ast_frfree(struct ast_frame *fr);

//! Copies a frame
/*! 
 * \param fr frame to act upon
 * Take a frame, and if it's not been malloc'd, make a malloc'd copy
 * and if the data hasn't been malloced then make the
 * data malloc'd.  If you need to store frames, say for queueing, then
 * you should call this function.
 * Returns a frame on success, NULL on error
 */
struct ast_frame *ast_frisolate(struct ast_frame *fr);

//! Copies a frame
/*! 
 * \param fr frame to copy
 * Dupliates a frame -- should only rarely be used, typically frisolate is good enough
 * Returns a frame on success, NULL on error
 */
struct ast_frame *ast_frdup(struct ast_frame *fr);

//! Chains a frame -- unimplemented
#if 0 /* unimplemented */
void ast_frchain(struct ast_frame_chain *fc);
#endif

//! Reads a frame from an fd
/*! 
 * \param fd an opened fd to read from
 * Read a frame from a stream or packet fd, as written by fd_write
 * returns a frame on success, NULL on error
 */
struct ast_frame *ast_fr_fdread(int fd);

//! Writes a frame to an fd
/*! 
 * \param fd Which fd to write to
 * \param frame frame to write to the fd
 * Write a frame to an fd
 * Returns 0 on success, -1 on failure
 */
int ast_fr_fdwrite(int fd, struct ast_frame *frame);

//! Sends a hangup to an fd
/*! 
 * \param fd fd to write to
 * Send a hangup (NULL equivalent) on an fd
 * Returns 0 on success, -1 on failure
 */
int ast_fr_fdhangup(int fd);

//! Get a format from a name
/*!
 * \param name string of format
 * Gets a format from a name.
 * This returns the form of the format in binary on success, 0 on error.
 */
extern int ast_getformatbyname(char *name);

//! Pick the best codec 
/* Choose the best codec...  Uhhh...   Yah. */
extern int ast_best_codec(int fmts);

struct ast_smoother;

extern struct ast_smoother *ast_smoother_new(int bytes);
extern void ast_smoother_free(struct ast_smoother *s);
extern void ast_smoother_reset(struct ast_smoother *s, int bytes);
extern int ast_smoother_feed(struct ast_smoother *s, struct ast_frame *f);
extern struct ast_frame *ast_smoother_read(struct ast_smoother *s);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif


#endif
