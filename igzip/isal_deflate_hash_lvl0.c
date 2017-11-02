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

void isal_deflate_hash_lvl0(struct isal_zstream *stream, uint8_t * dict, uint32_t dict_len)
{
    uint8_t *next_in = dict;
    uint8_t *end_in = dict + dict_len - SHORTEST_MATCH;
    uint32_t literal;
    uint32_t hash;
    uint16_t lookup_val = stream->total_in - dict_len;
    uint16_t *last_seen = stream->internal_state.head;

    while (next_in <= end_in) {
        literal = *(uint32_t *) next_in;
        hash = compute_hash(literal) & HASH_MASK;
        last_seen[hash] = lookup_val;
        lookup_val++;
        next_in++;
    }
}

