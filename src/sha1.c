﻿/*
 * Copyright (c) 2014 - 2021 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <gmssl/sha1.h>
#include "endian.h"


#define F0(B, C, D)	(((B) & (C)) | ((~(B)) & (D)))
#define F1(B, C, D)	((B) ^ (C) ^ (D))
#define F2(B, C, D)	(((B) & (C)) | ((B) & (D)) | ((C) & (D)))
#define F3(B, C, D)	((B) ^ (C) ^ (D))

#define K0 0x5A827999
#define K1 0x6ED9EBA1
#define K2 0x8F1BBCDC
#define K3 0xCA62C1D6

static void sha1_compress_blocks(uint32_t state[5],
	const unsigned char *data, size_t blocks)
{
	uint32_t A;
	uint32_t B;
	uint32_t C;
	uint32_t D;
	uint32_t E;
	uint32_t T;
	uint32_t W[80];
	int i;

	while (blocks--) {

		A = state[0];
		B = state[1];
		C = state[2];
		D = state[3];
		E = state[4];

		for (i = 0; i < 16; i++) {
			W[i] = GETU32(data);
			data += 4;
		}
		for (; i < 80; i++) {
			W[i] = ROL32(W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16], 1);
		}

		/* see https://en.wikipedia.org/wiki/SHA-1#/media/File:SHA-1.svg */
		for (i = 0; i < 20; i++) {
			T = E + F0(B, C, D) + ROL32(A, 5) + W[i] + K0;
			E = D;
			D = C;
			C = ROL32(B, 30);
			B = A;
			A = T;
		}
		for (; i < 40; i++) {
			T = E + F1(B, C, D) + ROL32(A, 5) + W[i] + K1;
			E = D;
			D = C;
			C = ROL32(B, 30);
			B = A;
			A = T;
		}
		for (; i < 60; i++) {
			T = E + F2(B, C, D) + ROL32(A, 5) + W[i] + K2;
			E = D;
			D = C;
			C = ROL32(B, 30);
			B = A;
			A = T;
		}
		for (; i < 80; i++) {
			T = E + F3(B, C, D) + ROL32(A, 5) + W[i] + K3;
			E = D;
			D = C;
			C = ROL32(B, 30);
			B = A;
			A = T;
		}

		state[0] += A;
		state[1] += B;
		state[2] += C;
		state[3] += D;
		state[4] += E;
	}
}

void sha1_init(SHA1_CTX *ctx)
{
	memset(ctx, 0, sizeof(*ctx));
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xEFCDAB89;
	ctx->state[2] = 0x98BADCFE;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xC3D2E1F0;
}

void sha1_update(SHA1_CTX *ctx, const unsigned char *data, size_t datalen)
{
	size_t blocks;

	ctx->num &= 0x3f;
	if (ctx->num) {
		unsigned int left = SHA1_BLOCK_SIZE - ctx->num;
		if (datalen < left) {
			memcpy(ctx->block + ctx->num, data, datalen);
			ctx->num += datalen;
			return;
		} else {
			memcpy(ctx->block + ctx->num, data, left);
			sha1_compress_blocks(ctx->state, ctx->block, 1);
			ctx->nblocks++;
			data += left;
			datalen -= left;
		}
	}

	blocks = datalen / SHA1_BLOCK_SIZE;
	sha1_compress_blocks(ctx->state, data, blocks);
	ctx->nblocks += blocks;
	data += SHA1_BLOCK_SIZE * blocks;
	datalen -= SHA1_BLOCK_SIZE * blocks;

	ctx->num = datalen;
	if (datalen) {
		memcpy(ctx->block, data, datalen);
	}
}

void sha1_finish(SHA1_CTX *ctx, unsigned char *dgst)
{
	int i;

	ctx->num &= 0x3f;
	ctx->block[ctx->num] = 0x80;

	if (ctx->num <= SHA1_BLOCK_SIZE - 9) {
		memset(ctx->block + ctx->num + 1, 0, SHA1_BLOCK_SIZE - ctx->num - 9);
	} else {
		memset(ctx->block + ctx->num + 1, 0, SHA1_BLOCK_SIZE - ctx->num - 1);
		sha1_compress_blocks(ctx->state, ctx->block, 1);
		memset(ctx->block, 0, SHA1_BLOCK_SIZE - 8);
	}
	PUTU32(ctx->block + 56, ctx->nblocks >> 23);
	PUTU32(ctx->block + 60, (ctx->nblocks << 9) + (ctx->num << 3));

	sha1_compress_blocks(ctx->state, ctx->block, 1);
	for (i = 0; i < 5; i++) {
		PUTU32(dgst + i*4, ctx->state[i]);
	}
	memset(ctx, 0, sizeof(*ctx));
}

void sha1_digest(const unsigned char *data, size_t datalen,
	unsigned char dgst[SHA1_DIGEST_SIZE])
{
	SHA1_CTX ctx;
	sha1_init(&ctx);
	sha1_update(&ctx, data, datalen);
	memset(&ctx, 0, sizeof(ctx));
}
