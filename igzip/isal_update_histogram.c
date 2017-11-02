/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdint.h>
#include "igzip_lib.h"
#include "huffman.h"
#include "huff_codes.h"
#include "encode_df.h"
#include "igzip_level_buf_structs.h"

void isal_update_histogram(uint8_t * start_stream, int length,
        struct isal_huff_histogram *histogram) {
    uint32_t literal = 0, hash;
    uint16_t seen, *last_seen = histogram->hash_table;
    uint8_t *current, *end_stream, *next_hash, *end;
    uint32_t match_length;
    uint32_t dist;
    uint64_t *lit_len_histogram = histogram->lit_len_histogram;
    uint64_t *dist_histogram = histogram->dist_histogram;

    if (length <= 0)
        return;

    end_stream = start_stream + length;
    memset(last_seen, 0, sizeof (histogram->hash_table)); /* Initialize last_seen to be 0. */
    for (current = start_stream; current < end_stream - 3; current++) {
        literal = *(uint32_t *) current;
        hash = compute_hash(literal) & HASH_MASK;
        seen = last_seen[hash];
        last_seen[hash] = (current - start_stream) & 0xFFFF;
        dist = (current - start_stream - seen) & 0xFFFF;
        if (dist - 1 < D - 1) {
            assert(start_stream <= current - dist);
            match_length =
                    compare258(current - dist, current, end_stream - current);
            if (match_length >= SHORTEST_MATCH) {
                next_hash = current;
#ifdef ISAL_LIMIT_HASH_UPDATE
                end = next_hash + 3;
#else
                end = next_hash + match_length;
#endif
                if (end > end_stream - 3)
                    end = end_stream - 3;
                next_hash++;
                for (; next_hash < end; next_hash++) {
                    literal = *(uint32_t *) next_hash;
                    hash = compute_hash(literal) & HASH_MASK;
                    last_seen[hash] = (next_hash - start_stream) & 0xFFFF;
                }

                dist_histogram[convert_dist_to_dist_sym(dist)] += 1;
                lit_len_histogram[convert_length_to_len_sym(match_length)] +=
                        1;
                current += match_length - 1;
                continue;
            }
        }
        lit_len_histogram[literal & 0xFF] += 1;
    }
    literal = literal >> 8;
    hash = compute_hash(literal) & HASH_MASK;
    seen = last_seen[hash];
    last_seen[hash] = (current - start_stream) & 0xFFFF;
    dist = (current - start_stream - seen) & 0xFFFF;
    if (dist < D) {
        match_length = compare258(current - dist, current, end_stream - current);
        if (match_length >= SHORTEST_MATCH) {
            dist_histogram[convert_dist_to_dist_sym(dist)] += 1;
            lit_len_histogram[convert_length_to_len_sym(match_length)] += 1;
            lit_len_histogram[256] += 1;
            return;
        }
    } else
        lit_len_histogram[literal & 0xFF] += 1;
    lit_len_histogram[(literal >> 8) & 0xFF] += 1;
    lit_len_histogram[(literal >> 16) & 0xFF] += 1;
    lit_len_histogram[256] += 1;
    return;
}

