/*===========================================================================*/
/*  a64rf_umbrella.h  ──  三層列印控制（V3：修正 atexit 與 nested func）     */
/*---------------------------------------------------------------------------*/
/*  開關：                                                                   */
/*    A64RF_PRINT_ASM          是否列印                                      */
/*    A64RF_OUTPUT_PATH        有→寫檔；無→stdout                           */
/*    A64RF_OUTPUT_GLABEL      有→加 .text/.global 雙 label 與結尾 ret       */
/*===========================================================================*/
#pragma once
#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------*/
/* 0️⃣  完全靜默                                                      */
/*--------------------------------------------------------------------*/
#ifndef A64RF_PRINT_ASM
#   define A64RF_EMIT_ASM(...)   ((void)0)

/*--------------------------------------------------------------------*/
#else  /* A64RF_PRINT_ASM 已定義 */
/*--------------------------------------------------------------------*/
/* 1️⃣  最底層輸出巨集 A64RF_EMIT_ASM_BASE                              */
/*--------------------------------------------------------------------*/
#   ifdef A64RF_OUTPUT_PATH             /*── 寫檔 ──*/
        static FILE *a64rf__fp = NULL;
        static inline void a64rf__open_file(void)
        {
            if (!a64rf__fp) {
                a64rf__fp = fopen(A64RF_OUTPUT_PATH, "w");
                if (!a64rf__fp) a64rf__fp = stdout;
                else            atexit((void (*)(void))fclose);
            }
        }
#       define A64RF_EMIT_ASM_BASE(...)            \
            do {                                   \
                a64rf__open_file();                \
                fprintf(a64rf__fp, __VA_ARGS__);   \
            } while (0)
#   else                                           /*── stdout ──*/
#       define A64RF_EMIT_ASM_BASE(...)  do { printf(__VA_ARGS__); } while (0)
#   endif /* A64RF_OUTPUT_PATH */

/*--------------------------------------------------------------------*/
/* 2️⃣  字串化輔助（允許不加引號傳旗標）                               */
/*--------------------------------------------------------------------*/
#   define A64RF__STR1(x)  #x
#   define A64RF__STR(x)   A64RF__STR1(x)

/*--------------------------------------------------------------------*/
/* 3️⃣  若定義 GLABEL → 自動補 header + footer                         */
/*--------------------------------------------------------------------*/
#   ifdef A64RF_OUTPUT_GLABEL

        /* 供 atexit 使用的 footer，必須在檔案層級定義 ----------------*/
        static void a64rf__emit_footer(void)
        {
            A64RF_EMIT_ASM_BASE("ret\n");
        }

        static inline void a64rf__emit_header_once(void)
        {
            static int emitted = 0;
            if (!emitted) {
                emitted = 1;
                const char *lbl = A64RF__STR(A64RF_OUTPUT_GLABEL);

                A64RF_EMIT_ASM_BASE(
                    ".text\n"
                    ".global %s\n"
                    ".global _%s\n"
                    "%s:\n"
                    "_%s:\n",
                    lbl, lbl, lbl, lbl);

                atexit(a64rf__emit_footer);
            }
        }

        /*  最終對外巨集：先 header → 再輸出指令 --------------------*/
#       define A64RF_EMIT_ASM(...)                   \
            do {                                     \
                a64rf__emit_header_once();           \
                A64RF_EMIT_ASM_BASE(__VA_ARGS__);    \
            } while (0)

#   else  /* 無 GLABEL：單純映射 --------------------------------------- */
#       define A64RF_EMIT_ASM(...)   A64RF_EMIT_ASM_BASE(__VA_ARGS__)
#   endif /* A64RF_OUTPUT_GLABEL */

#endif  /* A64RF_PRINT_ASM */
/*===========================================================================*/



/*
 *  a64rf.h — Public umbrella header for the A64 Register‑File simulation library.
 *
 *  Including this file gives clients access to the whole public API in one line:
 *
 *      #include "a64rf.h"
 *
 *  The header merely re‑exports the individual building blocks; it contains
 *  no implementation logic on its own, so it is very light to include.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * Core type definitions 
 * -------------------------------------------------------------------------- */
#include "types.h"   /* basic enums & structures (state, regs, flags)   */

#include "a64rf/state_utils.h"
#include "a64rf/program.h"
#include "a64rf/run_program.h"


/* --------------------------------------------------------------------------
 * API 
 * -------------------------------------------------------------------------- */
#include "a64rf/api/gpr.h"
#include "a64rf/api/flags.h"
#include "a64rf/api/vreg/read.h"
#include "a64rf/api/vreg/print.h"
#include "a64rf/api/vreg/write.h"

#include "a64rf/api/state.h"
#include "a64rf/api/mem.h"




/* --------------------------------------------------------------------------
 * Operation helpers
 * -------------------------------------------------------------------------- */
#include "a64rf/op/a64rf_op_gpr.h"  /* scalar A64 instructions operating on GPRs       */
#include "a64rf/op/a64rf_op_neon.h" /* SIMD / NEON instructions                        */



/* --------------------------------------------------------------------------
 * Version information
 * -------------------------------------------------------------------------- */
#define A64RF_VERSION_MAJOR 0
#define A64RF_VERSION_MINOR 1
#define A64RF_VERSION_PATCH 0
#define A64RF_VERSION_STR  "0.1.0"

/* Convenience macro for runtime version checks */
#define A64RF_VERSION_GE(major, minor, patch) \
    ((A64RF_VERSION_MAJOR >  (major)) ||                                      \
     (A64RF_VERSION_MAJOR == (major) && A64RF_VERSION_MINOR >  (minor)) ||    \
     (A64RF_VERSION_MAJOR == (major) && A64RF_VERSION_MINOR == (minor) &&     \
      A64RF_VERSION_PATCH >= (patch)))

#ifdef __cplusplus
} /* extern "C" */
#endif