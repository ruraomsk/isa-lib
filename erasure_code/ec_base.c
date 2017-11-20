/**********************************************************************
  Copyright(c) 2011-2015 Intel Corporation All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
 * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************/

#include <limits.h>
#include <string.h> // for memset
#include "erasure_code.h"
#include "ec_base.h" // for GF tables
#include "types.h"

void ec_init_tables(int k, int rows, unsigned char *a, unsigned char *g_tbls)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < k; j++)
        {
            gf_vect_mul_init(*a++, g_tbls);
            g_tbls += 32;
        }
    }
}

unsigned char gf_mul(unsigned char a, unsigned char b)
{
    int i;

    if ((a == 0) || (b == 0))
        return 0;

    return gff_base[(i = gflog_base[a] + gflog_base[b]) > 254 ? i - 255 : i];
}

unsigned char gf_inv(unsigned char a)
{
    if (a == 0)
        return 0;

    return gff_base[255 - gflog_base[a]];
}

void gf_gen_rs_matrix(unsigned char *a, int m, int k)
{
    int i, j;
    unsigned char p, gen = 1;

    memset(a, 0, k * m);
    for (i = 0; i < k; i++)
        a[k * i + i] = 1;

    for (i = k; i < m; i++)
    {
        p = 1;
        for (j = 0; j < k; j++)
        {
            a[k * i + j] = p;
            p = gf_mul(p, gen);
        }
        gen = gf_mul(gen, 2);
    }
}

void gf_gen_cauchy1_matrix(unsigned char *a, int m, int k)
{
    int i, j;
    unsigned char *p;

    // Identity matrix in high position
    memset(a, 0, k * m);
    for (i = 0; i < k; i++)
        a[k * i + i] = 1;

    // For the rest choose 1/(i + j) | i != j
    p = &a[k * k];
    for (i = k; i < m; i++)
        for (j = 0; j < k; j++)
            *p++ = gf_inv(i ^ j);
}

int gf_invert_matrix(unsigned char *in_mat, unsigned char *out_mat, const int n)
{
    int i, j, k;
    unsigned char temp;

    // Set out_mat[] to the identity matrix
    for (i = 0; i < n * n; i++) // memset(out_mat, 0, n*n)
        out_mat[i] = 0;

    for (i = 0; i < n; i++)
        out_mat[i * n + i] = 1;

    // Inverse
    for (i = 0; i < n; i++)
    {
        // Check for 0 in pivot element
        if (in_mat[i * n + i] == 0)
        {
            // Find a row with non-zero in current column and swap
            for (j = i + 1; j < n; j++)
                if (in_mat[j * n + i])
                    break;

            if (j == n) // Couldn't find means it's singular
                return -1;

            for (k = 0; k < n; k++)
            { // Swap rows i,j
                temp = in_mat[i * n + k];
                in_mat[i * n + k] = in_mat[j * n + k];
                in_mat[j * n + k] = temp;

                temp = out_mat[i * n + k];
                out_mat[i * n + k] = out_mat[j * n + k];
                out_mat[j * n + k] = temp;
            }
        }

        temp = gf_inv(in_mat[i * n + i]); // 1/pivot
        for (j = 0; j < n; j++)
        { // Scale row i by 1/pivot
            in_mat[i * n + j] = gf_mul(in_mat[i * n + j], temp);
            out_mat[i * n + j] = gf_mul(out_mat[i * n + j], temp);
        }

        for (j = 0; j < n; j++)
        {
            if (j == i)
                continue;

            temp = in_mat[j * n + i];
            for (k = 0; k < n; k++)
            {
                out_mat[j * n + k] ^= gf_mul(temp, out_mat[i * n + k]);
                in_mat[j * n + k] ^= gf_mul(temp, in_mat[i * n + k]);
            }
        }
    }
    return 0;
}

// Calculates const table gftbl in GF(2^8) from single input A
// gftbl(A) = {A{00}, A{01}, A{02}, ... , A{0f} }, {A{00}, A{10}, A{20}, ... , A{f0} }

void gf_vect_mul_init(unsigned char c, unsigned char *tbl)
{
    unsigned char c2 = (c << 1) ^ ((c & 0x80) ? 0x1d : 0);   //Mult by GF{2}
    unsigned char c4 = (c2 << 1) ^ ((c2 & 0x80) ? 0x1d : 0); //Mult by GF{2}
    unsigned char c8 = (c4 << 1) ^ ((c4 & 0x80) ? 0x1d : 0); //Mult by GF{2}

    unsigned long long v1, v2, v4, v8, *t;
    unsigned long long v10, v20, v40, v80;
    unsigned char c17, c18, c20, c24;

    t = (unsigned long long *)tbl;

    v1 = c * 0x0100010001000100ull;
    v2 = c2 * 0x0101000001010000ull;
    v4 = c4 * 0x0101010100000000ull;
    v8 = c8 * 0x0101010101010101ull;

    v4 = v1 ^ v2 ^ v4;
    t[0] = v4;
    t[1] = v8 ^ v4;

    c17 = (c8 << 1) ^ ((c8 & 0x80) ? 0x1d : 0);   //Mult by GF{2}
    c18 = (c17 << 1) ^ ((c17 & 0x80) ? 0x1d : 0); //Mult by GF{2}
    c20 = (c18 << 1) ^ ((c18 & 0x80) ? 0x1d : 0); //Mult by GF{2}
    c24 = (c20 << 1) ^ ((c20 & 0x80) ? 0x1d : 0); //Mult by GF{2}

    v10 = c17 * 0x0100010001000100ull;
    v20 = c18 * 0x0101000001010000ull;
    v40 = c20 * 0x0101010100000000ull;
    v80 = c24 * 0x0101010101010101ull;

    v40 = v10 ^ v20 ^ v40;
    t[2] = v40;
    t[3] = v80 ^ v40;
}

void gf_vect_dot_prod_base(int len, int vlen, unsigned char *v,
                           unsigned char **src, unsigned char *dest)
{
    int i, j;
    unsigned char s;
    for (i = 0; i < len; i++)
    {
        s = 0;
        for (j = 0; j < vlen; j++)
            s ^= gf_mul(src[j][i], v[j * 32 + 1]);

        dest[i] = s;
    }
}

void gf_vect_mad_base(int len, int vec, int vec_i,
                      unsigned char *v, unsigned char *src, unsigned char *dest)
{
    int i;
    unsigned char s;
    for (i = 0; i < len; i++)
    {
        s = dest[i];
        s ^= gf_mul(src[i], v[vec_i * 32 + 1]);
        dest[i] = s;
    }
}

void ec_encode_data_base(int len, int srcs, int dests, unsigned char *v,
                         unsigned char **src, unsigned char **dest)
{
    int i, j, l;
    unsigned char s;

    for (l = 0; l < dests; l++)
    {
        for (i = 0; i < len; i++)
        {
            s = 0;
            for (j = 0; j < srcs; j++)
                s ^= gf_mul(src[j][i], v[j * 32 + l * srcs * 32 + 1]);

            dest[l][i] = s;
        }
    }
}

void ec_encode_data_update_base(int len, int k, int rows, int vec_i, unsigned char *v,
                                unsigned char *data, unsigned char **dest)
{
    int i, l;
    unsigned char s;

    for (l = 0; l < rows; l++)
    {
        for (i = 0; i < len; i++)
        {
            s = dest[l][i];
            s ^= gf_mul(data[i], v[vec_i * 32 + l * k * 32 + 1]);

            dest[l][i] = s;
        }
    }
}

void gf_vect_mul_base(int len, unsigned char *a, unsigned char *src, unsigned char *dest)
{
    //2nd element of table array is ref value used to fill it in
    unsigned char c = a[1];
    while (len-- > 0)
        *dest++ = gf_mul(c, *src++);
}
