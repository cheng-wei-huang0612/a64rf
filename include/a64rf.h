

#pragma once
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


/* --------------------------------------------------------------------------
 * API 
 * -------------------------------------------------------------------------- */
#include "a64rf/api/gpr.h"
#include "a64rf/api/flags.h"
#include "a64rf/api/vreg/read.h"
#include "a64rf/api/vreg/print.h"
#include "a64rf/api/vreg/write.h"






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