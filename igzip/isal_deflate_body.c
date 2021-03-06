/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdint.h>
#include "igzip_lib.h"
#include "huffman.h"
#include "huff_codes.h"
#include "bitbuf2.h"
static inline void update_state(struct isal_zstream *stream, uint8_t * start_in,
				uint8_t * next_in, uint8_t * end_in)
{
	struct isal_zstate *state = &stream->internal_state;
	uint32_t bytes_written;

	stream->next_in = next_in;
	stream->total_in += next_in - start_in;
	stream->avail_in = end_in - next_in;

	bytes_written = buffer_used(&state->bitbuf);
	stream->total_out += bytes_written;
	stream->next_out += bytes_written;
	stream->avail_out -= bytes_written;

}

void isal_deflate_body(struct isal_zstream *stream)
{
	uint32_t literal, hash;
	uint8_t *start_in, *next_in, *end_in, *end, *next_hash;
	uint16_t match_length;
	uint32_t dist;
	uint64_t code, code_len, code2, code_len2;
	struct isal_zstate *state = &stream->internal_state;
	uint16_t *last_seen = state->head;

	if (stream->avail_in == 0) {
		if (stream->end_of_stream || stream->flush != NO_FLUSH)
			state->state = ZSTATE_FLUSH_READ_BUFFER;
		return;
	}

	set_buf(&state->bitbuf, stream->next_out, stream->avail_out);

	start_in = stream->next_in;
	end_in = start_in + stream->avail_in;
	next_in = start_in;

	while (next_in + ISAL_LOOK_AHEAD < end_in) {

		if (is_full(&state->bitbuf)) {
			update_state(stream, start_in, next_in, end_in);
			return;
		}

		literal = *(uint32_t *) next_in;
		hash = compute_hash(literal) & HASH_MASK;
		dist = (next_in - state->file_start - last_seen[hash]) & 0xFFFF;
		last_seen[hash] = (uint64_t) (next_in - state->file_start);

		/* The -1 are to handle the case when dist = 0 */
		if (dist - 1 < IGZIP_HIST_SIZE - 1) {
			assert(dist != 0);

			match_length = compare258(next_in - dist, next_in, 258);

			if (match_length >= SHORTEST_MATCH) {
				next_hash = next_in;
#ifdef ISAL_LIMIT_HASH_UPDATE
				end = next_hash + 3;
#else
				end = next_hash + match_length;
#endif
				next_hash++;

				for (; next_hash < end; next_hash++) {
					literal = *(uint32_t *) next_hash;
					hash = compute_hash(literal) & HASH_MASK;
					last_seen[hash] =
					    (uint64_t) (next_hash - state->file_start);
				}

				get_len_code(stream->hufftables, match_length, &code,
					     &code_len);
				get_dist_code(stream->hufftables, dist, &code2, &code_len2);

				code |= code2 << code_len;
				code_len += code_len2;

				write_bits(&state->bitbuf, code, code_len);

				next_in += match_length;

				continue;
			}
		}

		get_lit_code(stream->hufftables, literal & 0xFF, &code, &code_len);
		write_bits(&state->bitbuf, code, code_len);
		next_in++;
	}

	update_state(stream, start_in, next_in, end_in);

	assert(stream->avail_in <= ISAL_LOOK_AHEAD);
	if (stream->end_of_stream || stream->flush != NO_FLUSH)
		state->state = ZSTATE_FLUSH_READ_BUFFER;

	return;

}

