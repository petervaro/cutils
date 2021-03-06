/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.80.107 (20140721)                       **
**                                                                            **
**                                File: carg.h                                **
**                                                                            **
**   For more information about the project, visit <http://www.cutils.org>.   **
**                       Copyright (C) 2014 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_ARGUMENTS_H_19836769466709525_
#define _C_ARGUMENTS_H_19836769466709525_

/* Make macro variables available */
#undef __args8
#undef __comma
#undef __paren
#undef __paste
#undef __isempty
#undef __CASE1110
#undef __empty
#undef __unite
#undef __merge
#undef __vargs1
#undef __vargs2
#undef __vargs3
#undef __vargs4
#undef __vargs5
#undef __vargs6
#undef __vargs7
#undef __vargs8
#undef __vargs9
#undef __vargs10
#undef __vargs11
#undef __vargs12
#undef __vargs13
#undef __vargs14
#undef __vargs15
#undef __vargs16
#undef __vargs17
#undef __vargs18
#undef __vargs19
#undef __vargs20
#undef __vargs21
#undef __vargs22
#undef __vargs23
#undef __vargs24
#undef __vargs25
#undef __vargs26
#undef __vargs27
#undef __vargs28
#undef __vargs29
#undef __vargs30
#undef __vargs31
#undef __vargs32
#undef __vargs33
#undef __vargs34
#undef __vargs35
#undef __vargs36
#undef __vargs37
#undef __vargs38
#undef __vargs39
#undef __vargs40
#undef __vargs41
#undef __vargs42
#undef __vargs43
#undef __vargs44
#undef __vargs45
#undef __vargs46
#undef __vargs47
#undef __vargs48
#undef __vargs49
#undef __vargs50
#undef __vargs51
#undef __vargs52
#undef __vargs53
#undef __vargs54
#undef __vargs55
#undef __vargs56
#undef __vargs57
#undef __vargs58
#undef __vargs59
#undef __vargs60
#undef __vargs61
#undef __vargs62
#undef __vargs63
#undef __vargs64
#undef __state0
#undef __state1
#undef cutils_carg_vargs

/*
 * Empty argument list detection based on Jens Gustedt's blogpost 2010
 * https://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments
 */

// #define __args16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,N,...) N
#define __args64(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,              \
                 _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,              \
                 _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,              \
                 _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,a,b,N,...) N
// #define __comma(...) __args16(__VA_ARGS__,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)
#define __comma(...) __args64(__VA_ARGS__,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       \
                                          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       \
                                          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       \
                                          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       \
                                          0,0,1)
#define __paren(...) ,

/* Merge five tokens */
#define __paste(_0,_1,_2,_3,_4) _0##_1##_2##_3##_4
/* ... */
#define __isempty(_0,_1,_2,_3) __comma(__paste(__CASE,_0,_1,_2,_3))
/* Test case result */
#define __CASE1110 ,

/* Test if the following cases are true (1) or false (0) */
#define __empty(...)                                                           \
    __isempty(__comma(__VA_ARGS__),            /* one arg, an empty one */     \
              __comma(__paren __VA_ARGS__),    /* __paren+args = comma */      \
              __comma(__VA_ARGS__ ()),         /* args+parens = comma */       \
              __comma(__paren __VA_ARGS__ ())) /* __paren+args+parens = comma */

/* Two indirections of concatanation */
#define __unite(a, b) a ## b
#define __merge(a, b) __unite(a, b)

/* Number of args dispatcher */
#define __vargs1(_0,token,...) token
#define __vargs2(_0,_1,token,...) token
#define __vargs3(_0,_1,_2,token,...) token
#define __vargs4(_0,_1,_2,_3,token,...) token
#define __vargs5(_0,_1,_2,_3,_4,token,...) token
#define __vargs6(_0,_1,_2,_3,_4,_5,token,...) token
#define __vargs7(_0,_1,_2,_3,_4,_5,_6,token,...) token
#define __vargs8(_0,_1,_2,_3,_4,_5,_6,_7,token,...) token
#define __vargs9(_0,_1,_2,_3,_4,_5,_6,_7,_8,token,...) token
#define __vargs10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,token,...) token
#define __vargs11(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,token,...) token
#define __vargs12(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,token,...) token
#define __vargs13(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,token,...) token
#define __vargs14(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,token,...) token
#define __vargs15(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,token,...) token
#define __vargs16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,token,...) token
#define __vargs17(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                   _g,token,...) token
#define __vargs18(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,token,...) token
#define __vargs19(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,token,...) token
#define __vargs20(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,token,...) token
#define __vargs21(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,token,...) token
#define __vargs22(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,token,...) token
#define __vargs23(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,token,...) token
#define __vargs24(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,token,...) token
#define __vargs25(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,token,...) token
#define __vargs26(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,token,...) token
#define __vargs27(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,token,...) token
#define __vargs28(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,token,...) token
#define __vargs29(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,token,...) token
#define __vargs30(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,token,...) token
#define __vargs31(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,token,...) token
#define __vargs32(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,token,...) token
#define __vargs33(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,token,...) token
#define __vargs34(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,token,...) token
#define __vargs35(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,token,...) token
#define __vargs36(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,token,...) token
#define __vargs37(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,token,...) token
#define __vargs38(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,token,...) token
#define __vargs39(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,token,...) token
#define __vargs40(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,token,...) token
#define __vargs41(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,token,...) token
#define __vargs42(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,token,...) token
#define __vargs43(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,token,...) token
#define __vargs44(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,token,...) token
#define __vargs45(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,token,...) token
#define __vargs46(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,token,...) token
#define __vargs47(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,token,...) token
#define __vargs48(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,token,...) token
#define __vargs49(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,token,...) token
#define __vargs50(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,token,...) token
#define __vargs51(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,token,...) token
#define __vargs52(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,token,...) token
#define __vargs53(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,token,...) token
#define __vargs54(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,token,...) token
#define __vargs55(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,token,...) token
#define __vargs56(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,token,...) token
#define __vargs57(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,token,...) token
#define __vargs58(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,token,...) token
#define __vargs59(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,token,...) token
#define __vargs60(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,token,...) token
#define __vargs61(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,token,...) token
#define __vargs62(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,a,token,...) token
#define __vargs63(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,a,b,token,...) token
#define __vargs64(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,             \
                  _g,_h,_j,_k,_l,_m,_n,_o,_p,_q,_r,_s,_t,_u,_v,_w,             \
                  _x,_y,_z,_A,_B,_C,_D,_E,_F,_G,_H,_I,_J,_K,_L,_M,             \
                  _N,_O,_P,_Q,_R,_S,_T,_U,_V,_W,_X,_Y,_Z,a,b,c,token,...) token

/* Catch empty arguments */
static inline void cutils_carg_zero(char empty){}

/* If zero argument or if one or more argument */
#define __state0(n) __vargs1
#define __state1(n) __merge(__vargs, n)

/* Generic dispatcher */
/* Decide whether the macro was called with zero or one or more arguments */
#define cutils_carg_vargs(...) __merge(__state, __empty(__VA_ARGS__))

#endif /* _C_ARGUMENTS_H_19836769466709525_ */
