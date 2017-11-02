/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdint.h>
#include "igzip_lib.h"
#include "huff_codes.h"
#include "igzip_checksums.h"

struct rfc1951_tables rfc_lookup_table;

/* structure contain lookup data based on RFC 1951 */
struct rfc1951_tables {
    uint8_t dist_extra_bit_count[32];
    uint32_t dist_start[32];
    uint8_t len_extra_bit_count[32];
    uint16_t len_start[32];

};
static inline void  inflate_in_load(struct inflate_state *state, int min_required) {
    uint64_t temp = 0;
    uint8_t new_bytes;

    if (state->read_in_length >= 64)
        return;

    if (state->avail_in >= 8) {
        /* If there is enough space to load a 64 bits, load the data and use
         * that to fill read_in */
        new_bytes = 8 - (state->read_in_length + 7) / 8;
        temp = *(uint64_t *) state->next_in;

        state->read_in |= temp << state->read_in_length;
        state->next_in += new_bytes;
        state->avail_in -= new_bytes;
        state->read_in_length += new_bytes * 8;

    } else {
        /* Else fill the read_in buffer 1 byte at a time */
        while (state->read_in_length < 57 && state->avail_in > 0) {
            temp = *state->next_in;
            state->read_in |= temp << state->read_in_length;
            state->next_in++;
            state->avail_in--;
            state->read_in_length += 8;

        }
    }
}
static inline uint16_t decode_next_large(struct inflate_state *state,
        struct inflate_huff_code_large *huff_code) {
    uint16_t next_bits;
    uint16_t next_sym;
    uint32_t bit_count;
    uint32_t bit_mask;

    if (state->read_in_length <= ISAL_DEF_MAX_CODE_LEN)
        inflate_in_load(state, 0);

    next_bits = state->read_in & ((1 << ISAL_DECODE_LONG_BITS) - 1);

    /* next_sym is a possible symbol decoded from next_bits. If bit 15 is 0,
     * next_code is a symbol. Bits 9:0 represent the symbol, and bits 14:10
     * represent the length of that symbols huffman code. If next_sym is not
     * a symbol, it provides a hint of where the large symbols containin
     * this code are located. Note the hint is at largest the location the
     * first actual symbol in the long code list.*/
    next_sym = huff_code->short_code_lookup[next_bits];

    if (next_sym < 0x8000) {
        /* Return symbol found if next_code is a complete huffman code
         * and shift in buffer over by the length of the next_code */
        bit_count = next_sym >> 9;
        state->read_in >>= bit_count;
        state->read_in_length -= bit_count;

        if (bit_count == 0)
            next_sym = 0x1FF;

        return next_sym & 0x1FF;

    } else {
        /* If a symbol is not found, perform a linear search of the long code
         * list starting from the hint in next_sym */
        bit_mask = (next_sym - 0x8000) >> 9;
        bit_mask = (1 << bit_mask) - 1;
        next_bits = state->read_in & bit_mask;
        next_sym =
                huff_code->long_code_lookup[(next_sym & 0x1FF) +
                (next_bits >> ISAL_DECODE_LONG_BITS)];
        bit_count = next_sym >> 9;
        state->read_in >>= bit_count;
        state->read_in_length -= bit_count;

        if (bit_count == 0)
            next_sym = 0x1FF;

        return next_sym & 0x1FF;

    }
}
static inline uint64_t  inflate_in_read_bits(struct inflate_state *state, uint8_t bit_count) {
    uint64_t ret;
    assert(bit_count < 57);

    /* Load inflate_in if not enough data is in the read_in buffer */
    if (state->read_in_length < bit_count)
        inflate_in_load(state, bit_count);

    ret = (state->read_in) & ((1 << bit_count) - 1);
    state->read_in >>= bit_count;
    state->read_in_length -= bit_count;

    return ret;
}
static inline uint16_t  decode_next_small(struct inflate_state *state,
        struct inflate_huff_code_small *huff_code) {
    uint16_t next_bits;
    uint16_t next_sym;
    uint32_t bit_count;
    uint32_t bit_mask;

    if (state->read_in_length <= ISAL_DEF_MAX_CODE_LEN)
        inflate_in_load(state, 0);

    next_bits = state->read_in & ((1 << ISAL_DECODE_SHORT_BITS) - 1);

    /* next_sym is a possible symbol decoded from next_bits. If bit 15 is 0,
     * next_code is a symbol. Bits 9:0 represent the symbol, and bits 14:10
     * represent the length of that symbols huffman code. If next_sym is not
     * a symbol, it provides a hint of where the large symbols containin
     * this code are located. Note the hint is at largest the location the
     * first actual symbol in the long code list.*/
    next_sym = huff_code->short_code_lookup[next_bits];

    if (next_sym < 0x8000) {
        /* Return symbol found if next_code is a complete huffman code
         * and shift in buffer over by the length of the next_code */
        bit_count = next_sym >> 9;
        state->read_in >>= bit_count;
        state->read_in_length -= bit_count;

        if (bit_count == 0)
            next_sym = 0x1FF;

        return next_sym & 0x1FF;

    } else {
        /* If a symbol is not found, perform a linear search of the long code
         * list starting from the hint in next_sym */
        bit_mask = (next_sym - 0x8000) >> 9;
        bit_mask = (1 << bit_mask) - 1;
        next_bits = state->read_in & bit_mask;
        next_sym =
                huff_code->long_code_lookup[(next_sym & 0x1FF) +
                (next_bits >> ISAL_DECODE_SHORT_BITS)];
        bit_count = next_sym >> 9;
        state->read_in >>= bit_count;
        state->read_in_length -= bit_count;
        return next_sym & 0x1FF;

    }
}
static inline void  byte_copy(uint8_t * dest, uint64_t lookback_distance, int repeat_length) {
    uint8_t *src = dest - lookback_distance;

    for (; repeat_length > 0; repeat_length--)
        *dest++ = *src++;
}

int decode_huffman_code_block_stateless(struct inflate_state *state) {
    uint16_t next_lit;
    uint8_t next_dist;
    uint32_t repeat_length;
    uint32_t look_back_dist;
    uint64_t read_in_tmp;
    int32_t read_in_length_tmp;
    uint8_t *next_in_tmp;
    uint32_t avail_in_tmp;

    state->copy_overflow_length = 0;
    state->copy_overflow_distance = 0;

    while (state->block_state == ISAL_BLOCK_CODED) {
        /* While not at the end of block, decode the next
         * symbol */
        inflate_in_load(state, 0);

        read_in_tmp = state->read_in;
        read_in_length_tmp = state->read_in_length;
        next_in_tmp = state->next_in;
        avail_in_tmp = state->avail_in;

        next_lit = decode_next_large(state, &state->lit_huff_code);

        if (state->read_in_length < 0) {
            state->read_in = read_in_tmp;
            state->read_in_length = read_in_length_tmp;
            state->next_in = next_in_tmp;
            state->avail_in = avail_in_tmp;
            return ISAL_END_INPUT;
        }

        if (next_lit < 256) {
            /* If the next symbol is a literal,
             * write out the symbol and update state
             * data accordingly. */
            if (state->avail_out < 1) {
                state->read_in = read_in_tmp;
                state->read_in_length = read_in_length_tmp;
                state->next_in = next_in_tmp;
                state->avail_in = avail_in_tmp;
                return ISAL_OUT_OVERFLOW;
            }

            *state->next_out = next_lit;
            state->next_out++;
            state->avail_out--;
            state->total_out++;

        } else if (next_lit == 256) {
            /* If the next symbol is the end of
             * block, update the state data
             * accordingly */
            state->block_state = ISAL_BLOCK_NEW_HDR;

        } else if (next_lit < 286) {
            /* Else if the next symbol is a repeat
             * length, read in the length extra
             * bits, the distance code, the distance
             * extra bits. Then write out the
             * corresponding data and update the
             * state data accordingly*/
            repeat_length =
                    rfc_lookup_table.len_start[next_lit - 257] +
                    inflate_in_read_bits(state,
                    rfc_lookup_table.len_extra_bit_count[next_lit
                    - 257]);
            next_dist = decode_next_small(state, &state->dist_huff_code);

            if (next_dist >= DIST_LEN)
                return ISAL_INVALID_SYMBOL;

            look_back_dist = rfc_lookup_table.dist_start[next_dist] +
                    inflate_in_read_bits(state,
                    rfc_lookup_table.dist_extra_bit_count
                    [next_dist]);

            if (state->read_in_length < 0) {
                state->read_in = read_in_tmp;
                state->read_in_length = read_in_length_tmp;
                state->next_in = next_in_tmp;
                state->avail_in = avail_in_tmp;
                return ISAL_END_INPUT;
            }

            if (look_back_dist > state->total_out + state->dict_length)
                return ISAL_INVALID_LOOKBACK;

            if (state->avail_out < repeat_length) {
                state->copy_overflow_length = repeat_length - state->avail_out;
                state->copy_overflow_distance = look_back_dist;
                repeat_length = state->avail_out;
            }

            if (look_back_dist > repeat_length)
                memcpy(state->next_out,
                    state->next_out - look_back_dist, repeat_length);
            else
                byte_copy(state->next_out, look_back_dist, repeat_length);

            state->next_out += repeat_length;
            state->avail_out -= repeat_length;
            state->total_out += repeat_length;

            if (state->copy_overflow_length > 0)
                return ISAL_OUT_OVERFLOW;
        } else
            /* Else the read in bits do not
             * correspond to any valid symbol */
            return ISAL_INVALID_SYMBOL;
    }
    return 0;
}

