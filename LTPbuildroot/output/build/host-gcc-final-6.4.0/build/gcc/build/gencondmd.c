/* Generated automatically by the program `genconditions' from the target
   machine description file.  */

#include "bconfig.h"
#define INCLUDE_STRING
#include "system.h"

/* It is necessary, but not entirely safe, to include the headers below
   in a generator program.  As a defensive measure, don't do so when the
   table isn't going to have anything in it.  */
#if GCC_VERSION >= 3001

/* Do not allow checking to confuse the issue.  */
#undef CHECKING_P
#define CHECKING_P 0
#undef ENABLE_TREE_CHECKING
#undef ENABLE_RTL_CHECKING
#undef ENABLE_RTL_FLAG_CHECKING
#undef ENABLE_GC_CHECKING
#undef ENABLE_GC_ALWAYS_COLLECT

#include "coretypes.h"
#include "tm.h"
#include "insn-constants.h"
#include "rtl.h"
#include "tm_p.h"
#include "hard-reg-set.h"
#include "function.h"
#include "emit-rtl.h"

/* Fake - insn-config.h doesn't exist yet.  */
#define MAX_RECOG_OPERANDS 10
#define MAX_DUP_OPERANDS 10
#define MAX_INSNS_PER_SPLIT 5

#include "regs.h"
#include "recog.h"
#include "output.h"
#include "flags.h"
#include "hard-reg-set.h"
#include "predict.h"
#include "basic-block.h"
#include "bitmap.h"
#include "df.h"
#include "resource.h"
#include "diagnostic-core.h"
#include "reload.h"
#include "tm-constrs.h"

#define HAVE_eh_return 1
#include "except.h"

/* Dummy external declarations.  */
extern rtx_insn *insn;
extern rtx ins1;
extern rtx operands[];

#endif /* gcc >= 3.0.1 */

/* Structure definition duplicated from gensupport.h rather than
   drag in that file and its dependencies.  */
struct c_test
{
  const char *expr;
  int value;
};

/* This table lists each condition found in the machine description.
   Each condition is mapped to its truth value (0 or 1), or -1 if that
   cannot be calculated at compile time.
   If we don't have __builtin_constant_p, or it's not acceptable in array
   initializers, fall back to assuming that all conditions potentially
   vary at run time.  It works in 3.0.1 and later; 3.0 only when not
   optimizing.  */

#if GCC_VERSION >= 3001
static const struct c_test insn_conditions[] = {

#line 1090 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && !flag_pic",
    __builtin_constant_p 
#line 1090 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !flag_pic)
    ? (int) 
#line 1090 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !flag_pic)
    : -1 },
#line 5973 "../../gcc/config/arm/arm.md"
  { "flag_pic",
    __builtin_constant_p 
#line 5973 "../../gcc/config/arm/arm.md"
(flag_pic)
    ? (int) 
#line 5973 "../../gcc/config/arm/arm.md"
(flag_pic)
    : -1 },
#line 8621 "../../gcc/config/arm/arm.md"
  { "arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM)",
    __builtin_constant_p 
#line 8621 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM))
    ? (int) 
#line 8621 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM))
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V4HImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4HImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4HImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT\n\
   && TARGET_SOFT_FLOAT\n\
   && (!MEM_P (operands[0])\n\
       || register_operand (operands[1], SFmode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6633 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_SOFT_FLOAT
   && (!MEM_P (operands[0])
       || register_operand (operands[1], SFmode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6633 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_SOFT_FLOAT
   && (!MEM_P (operands[0])
       || register_operand (operands[1], SFmode))))
    : -1 },
#line 1473 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && arm_arch6 && optimize_size",
    __builtin_constant_p 
#line 1473 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6 && optimize_size)
    ? (int) 
#line 1473 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6 && optimize_size)
    : -1 },
#line 5665 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && reload_completed && IS_VFP_REGNUM (REGNO (operands[0]))",
    __builtin_constant_p 
#line 5665 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed && IS_VFP_REGNUM (REGNO (operands[0])))
    ? (int) 
#line 5665 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed && IS_VFP_REGNUM (REGNO (operands[0])))
    : -1 },
#line 1496 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && reload_completed",
    __builtin_constant_p 
#line 1496 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed)
    ? (int) 
#line 1496 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed)
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V8QImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V8QImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V8QImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V4HFmode)\n\
       || register_operand (operands[1], V4HFmode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4HFmode)
       || register_operand (operands[1], V4HFmode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4HFmode)
       || register_operand (operands[1], V4HFmode)))
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HARD_TP)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10908 "../../gcc/config/arm/arm.md"
(TARGET_HARD_TP))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10908 "../../gcc/config/arm/arm.md"
(TARGET_HARD_TP))
    : -1 },
#line 10223 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM\n\
   && (((unsigned HOST_WIDE_INT) INTVAL (operands[1]))\n\
       == (((unsigned HOST_WIDE_INT) INTVAL (operands[1])) >> 24) << 24)",
    __builtin_constant_p 
#line 10223 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && (((unsigned HOST_WIDE_INT) INTVAL (operands[1]))
       == (((unsigned HOST_WIDE_INT) INTVAL (operands[1])) >> 24) << 24))
    ? (int) 
#line 10223 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && (((unsigned HOST_WIDE_INT) INTVAL (operands[1]))
       == (((unsigned HOST_WIDE_INT) INTVAL (operands[1])) >> 24) << 24))
    : -1 },
#line 10935 "../../gcc/config/arm/arm.md"
  { "TARGET_GNU2_TLS",
    __builtin_constant_p 
#line 10935 "../../gcc/config/arm/arm.md"
(TARGET_GNU2_TLS)
    ? (int) 
#line 10935 "../../gcc/config/arm/arm.md"
(TARGET_GNU2_TLS)
    : -1 },
#line 360 "../../gcc/config/arm/vfp.md"
  { "TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   s_register_operand (operands[0], SFmode)\n\
       || s_register_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 360 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode)))
    ? (int) 
#line 360 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode)))
    : -1 },
#line 150 "../../gcc/config/arm/ldrdstrd.md"
  { "TARGET_LDRD\n\
  && current_tune->prefer_ldrd_strd\n\
  && !optimize_function_for_size_p (cfun)",
    __builtin_constant_p 
#line 150 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD
  && current_tune->prefer_ldrd_strd
  && !optimize_function_for_size_p (cfun))
    ? (int) 
#line 150 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD
  && current_tune->prefer_ldrd_strd
  && !optimize_function_for_size_p (cfun))
    : -1 },
#line 3060 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !TARGET_IWMMXT",
    __builtin_constant_p 
#line 3060 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_IWMMXT)
    ? (int) 
#line 3060 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_IWMMXT)
    : -1 },
#line 345 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_DSP_MULTIPLY",
    __builtin_constant_p 
#line 345 "../../gcc/config/arm/arm-fixed.md"
(TARGET_DSP_MULTIPLY)
    ? (int) 
#line 345 "../../gcc/config/arm/arm-fixed.md"
(TARGET_DSP_MULTIPLY)
    : -1 },
#line 2829 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2]))",
    __builtin_constant_p 
#line 2829 "../../gcc/config/arm/arm.md"
(TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2])))
    ? (int) 
#line 2829 "../../gcc/config/arm/arm.md"
(TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2])))
    : -1 },
#line 5119 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && ((unsigned HOST_WIDE_INT) INTVAL (operands[3])\n\
       == (GET_MODE_MASK (GET_MODE (operands[5]))\n\
           & (GET_MODE_MASK (GET_MODE (operands[5]))\n\
	      << (INTVAL (operands[2])))))",
    __builtin_constant_p 
#line 5119 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && ((unsigned HOST_WIDE_INT) INTVAL (operands[3])
       == (GET_MODE_MASK (GET_MODE (operands[5]))
           & (GET_MODE_MASK (GET_MODE (operands[5]))
	      << (INTVAL (operands[2]))))))
    ? (int) 
#line 5119 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && ((unsigned HOST_WIDE_INT) INTVAL (operands[3])
       == (GET_MODE_MASK (GET_MODE (operands[5]))
           & (GET_MODE_MASK (GET_MODE (operands[5]))
	      << (INTVAL (operands[2]))))))
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V16QImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V16QImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V16QImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && XVECLEN (operands[0], 0) == 5)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 287 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 5))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 287 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 5))
    : -1 },
#line 11116 "../../gcc/config/arm/arm.md"
  { "TARGET_EITHER && (arm_arch6 || !optimize_size)",
    __builtin_constant_p 
#line 11116 "../../gcc/config/arm/arm.md"
(TARGET_EITHER && (arm_arch6 || !optimize_size))
    ? (int) 
#line 11116 "../../gcc/config/arm/arm.md"
(TARGET_EITHER && (arm_arch6 || !optimize_size))
    : -1 },
#line 395 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && !arm_arch6",
    __builtin_constant_p 
#line 395 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch6)
    ? (int) 
#line 395 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch6)
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V4SImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4SImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4SImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
#line 362 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_32BIT && XVECLEN (operands[0], 0) == 5",
    __builtin_constant_p 
#line 362 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 5)
    ? (int) 
#line 362 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 5)
    : -1 },
#line 5535 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON",
    __builtin_constant_p 
#line 5535 "../../gcc/config/arm/neon.md"
(TARGET_NEON)
    ? (int) 
#line 5535 "../../gcc/config/arm/neon.md"
(TARGET_NEON)
    : -1 },
#line 1187 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE",
    __builtin_constant_p 
#line 1187 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE)
    ? (int) 
#line 1187 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 414 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 414 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch6))
    : -1 },
#line 309 "../../gcc/config/arm/iwmmxt.md"
  { "TARGET_REALLY_IWMMXT",
    __builtin_constant_p 
#line 309 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT)
    ? (int) 
#line 309 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT)
    : -1 },
#line 1092 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_32BIT && XVECLEN (operands[0], 0) == 2",
    __builtin_constant_p 
#line 1092 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 2)
    ? (int) 
#line 1092 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 2)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (unaligned_access)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4291 "../../gcc/config/arm/arm.md"
(unaligned_access))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4291 "../../gcc/config/arm/arm.md"
(unaligned_access))
    : -1 },
#line 7436 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT",
    __builtin_constant_p 
#line 7436 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_HARD_FLOAT)
    ? (int) 
#line 7436 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_HARD_FLOAT)
    : -1 },
#line 3699 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch6 && SMAX != SMIN\n\
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)",
    __builtin_constant_p 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMIN
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))
    ? (int) 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMIN
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   s_register_operand (operands[0], SFmode)\n\
       || s_register_operand (operands[1], SFmode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 360 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 360 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode))))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V4SFmode)\n\
       || register_operand (operands[1], V4SFmode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4SFmode)
       || register_operand (operands[1], V4SFmode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4SFmode)
       || register_operand (operands[1], V4SFmode)))
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V4HImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4HImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4HImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
#line 2233 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32\n\
      && INTVAL (operands[1]) > 0 \n\
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8\n\
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32)",
    __builtin_constant_p 
#line 2233 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32
      && INTVAL (operands[1]) > 0 
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32))
    ? (int) 
#line 2233 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32
      && INTVAL (operands[1]) > 0 
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32))
    : -1 },
#line 173 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], OImode)\n\
       || register_operand (operands[1], OImode))",
    __builtin_constant_p 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], OImode)
       || register_operand (operands[1], OImode)))
    ? (int) 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], OImode)
       || register_operand (operands[1], OImode)))
    : -1 },
#line 7964 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM  && use_simple_return_p ()",
    __builtin_constant_p 
#line 7964 "../../gcc/config/arm/arm.md"
(TARGET_ARM  && use_simple_return_p ())
    ? (int) 
#line 7964 "../../gcc/config/arm/arm.md"
(TARGET_ARM  && use_simple_return_p ())
    : -1 },
#line 385 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_INT_SIMD",
    __builtin_constant_p 
#line 385 "../../gcc/config/arm/arm-fixed.md"
(TARGET_INT_SIMD)
    ? (int) 
#line 385 "../../gcc/config/arm/arm-fixed.md"
(TARGET_INT_SIMD)
    : -1 },
#line 5952 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && peep2_reg_dead_p (2, operands[0])",
    __builtin_constant_p 
#line 5952 "../../gcc/config/arm/arm.md"
(TARGET_ARM && peep2_reg_dead_p (2, operands[0]))
    ? (int) 
#line 5952 "../../gcc/config/arm/arm.md"
(TARGET_ARM && peep2_reg_dead_p (2, operands[0]))
    : -1 },
#line 2670 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed\n\
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0])))\n\
   && ! IS_IWMMXT_REGNUM (REGNO (operands[0]))",
    __builtin_constant_p 
#line 2670 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0])))
   && ! IS_IWMMXT_REGNUM (REGNO (operands[0])))
    ? (int) 
#line 2670 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0])))
   && ! IS_IWMMXT_REGNUM (REGNO (operands[0])))
    : -1 },
#line 3623 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !arm_eliminable_register (operands[1])\n\
   && !(arm_restrict_it && CONST_INT_P (operands[3]))",
    __builtin_constant_p 
#line 3623 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1])
   && !(arm_restrict_it && CONST_INT_P (operands[3])))
    ? (int) 
#line 3623 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1])
   && !(arm_restrict_it && CONST_INT_P (operands[3])))
    : -1 },
#line 785 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], QImode)\n\
       || register_operand (operands[1], QImode))",
    __builtin_constant_p 
#line 785 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    ? (int) 
#line 785 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2\n\
  && (register_operand (operands[0], HImode)\n\
     || register_operand (operands[1], HImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 325 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
  && (register_operand (operands[0], HImode)
     || register_operand (operands[1], HImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 325 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
  && (register_operand (operands[0], HImode)
     || register_operand (operands[1], HImode))))
    : -1 },
  { "(TARGET_NEON) && ( reload_completed)",
    __builtin_constant_p (
#line 4343 "../../gcc/config/arm/neon.md"
(TARGET_NEON) && 
#line 4345 "../../gcc/config/arm/neon.md"
( reload_completed))
    ? (int) (
#line 4343 "../../gcc/config/arm/neon.md"
(TARGET_NEON) && 
#line 4345 "../../gcc/config/arm/neon.md"
( reload_completed))
    : -1 },
  { "(TARGET_THUMB1) && ( reload_completed)",
    __builtin_constant_p (
#line 1801 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1) && 
#line 1803 "../../gcc/config/arm/thumb1.md"
( reload_completed))
    ? (int) (
#line 1801 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1) && 
#line 1803 "../../gcc/config/arm/thumb1.md"
( reload_completed))
    : -1 },
#line 7903 "../../gcc/config/arm/arm.md"
  { "(TARGET_ARM || (TARGET_THUMB2\n\
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL\n\
                   && !IS_STACKALIGN (arm_current_func_type ())))\n\
     && USE_RETURN_INSN (FALSE)",
    __builtin_constant_p 
#line 7903 "../../gcc/config/arm/arm.md"
((TARGET_ARM || (TARGET_THUMB2
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL
                   && !IS_STACKALIGN (arm_current_func_type ())))
     && USE_RETURN_INSN (FALSE))
    ? (int) 
#line 7903 "../../gcc/config/arm/arm.md"
((TARGET_ARM || (TARGET_THUMB2
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL
                   && !IS_STACKALIGN (arm_current_func_type ())))
     && USE_RETURN_INSN (FALSE))
    : -1 },
#line 476 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN",
    __builtin_constant_p 
#line 476 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN)
    ? (int) 
#line 476 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN)
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V4SImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4SImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4SImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 5966 "../../gcc/config/arm/arm.md"
  { "TARGET_VXWORKS_RTP && TARGET_ARM && flag_pic",
    __builtin_constant_p 
#line 5966 "../../gcc/config/arm/arm.md"
(TARGET_VXWORKS_RTP && TARGET_ARM && flag_pic)
    ? (int) 
#line 5966 "../../gcc/config/arm/arm.md"
(TARGET_VXWORKS_RTP && TARGET_ARM && flag_pic)
    : -1 },
#line 5765 "../../gcc/config/arm/arm.md"
  { "TARGET_THUMB2\n\
   && arm_disable_literal_pool\n\
   && reload_completed\n\
   && GET_CODE (operands[1]) == SYMBOL_REF",
    __builtin_constant_p 
#line 5765 "../../gcc/config/arm/arm.md"
(TARGET_THUMB2
   && arm_disable_literal_pool
   && reload_completed
   && GET_CODE (operands[1]) == SYMBOL_REF)
    ? (int) 
#line 5765 "../../gcc/config/arm/arm.md"
(TARGET_THUMB2
   && arm_disable_literal_pool
   && reload_completed
   && GET_CODE (operands[1]) == SYMBOL_REF)
    : -1 },
#line 7776 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && !SIBLING_CALL_P (insn)\n\
   && (GET_CODE (operands[1]) == SYMBOL_REF)\n\
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1]))",
    __builtin_constant_p 
#line 7776 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !SIBLING_CALL_P (insn)
   && (GET_CODE (operands[1]) == SYMBOL_REF)
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1])))
    ? (int) 
#line 7776 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !SIBLING_CALL_P (insn)
   && (GET_CODE (operands[1]) == SYMBOL_REF)
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1])))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch5)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10810 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10810 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5))
    : -1 },
#line 8183 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT || optimize_size || flag_pic",
    __builtin_constant_p 
#line 8183 "../../gcc/config/arm/arm.md"
(TARGET_32BIT || optimize_size || flag_pic)
    ? (int) 
#line 8183 "../../gcc/config/arm/arm.md"
(TARGET_32BIT || optimize_size || flag_pic)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math\n\
  && !TARGET_VFP_SINGLE)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1277 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math
  && !TARGET_VFP_SINGLE))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1277 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math
  && !TARGET_VFP_SINGLE))
    : -1 },
#line 6506 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && (   register_operand (operands[0], QImode)\n\
       || register_operand (operands[1], QImode))",
    __builtin_constant_p 
#line 6506 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    ? (int) 
#line 6506 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode)))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 ) && (TARGET_VFP)",
    __builtin_constant_p (
#line 1336 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    ? (int) (
#line 1336 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    : -1 },
#line 520 "../../gcc/config/arm/vfp.md"
  { "TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP && !arm_restrict_it",
    __builtin_constant_p 
#line 520 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP && !arm_restrict_it)
    ? (int) 
#line 520 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP && !arm_restrict_it)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && XVECLEN (operands[0], 0) == 5)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 362 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 5))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 362 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 5))
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4HImode != V2SFmode && V4HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode)))
    : -1 },
#line 6113 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch4",
    __builtin_constant_p 
#line 6113 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch4)
    ? (int) 
#line 6113 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch4)
    : -1 },
  { "(TARGET_THUMB2 && !arm_restrict_it) && ( reload_completed\n\
    && REGNO (operands [0]) != REGNO (operands[3]))",
    __builtin_constant_p (
#line 640 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !arm_restrict_it) && 
#line 645 "../../gcc/config/arm/thumb2.md"
( reload_completed
    && REGNO (operands [0]) != REGNO (operands[3])))
    ? (int) (
#line 640 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !arm_restrict_it) && 
#line 645 "../../gcc/config/arm/thumb2.md"
( reload_completed
    && REGNO (operands [0]) != REGNO (operands[3])))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], TImode)\n\
       || register_operand (operands[1], TImode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], TImode)
       || register_operand (operands[1], TImode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], TImode)
       || register_operand (operands[1], TImode)))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V4SImode)\n\
       || register_operand (operands[1], V4SImode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4SImode)
       || register_operand (operands[1], V4SImode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4SImode)
       || register_operand (operands[1], V4SImode)))
    : -1 },
#line 565 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && TARGET_SOFT_FLOAT",
    __builtin_constant_p 
#line 565 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && TARGET_SOFT_FLOAT)
    ? (int) 
#line 565 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && TARGET_SOFT_FLOAT)
    : -1 },
#line 771 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math",
    __builtin_constant_p 
#line 771 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math)
    ? (int) 
#line 771 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math)
    : -1 },
#line 5519 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && reload_completed\n\
   && (arm_const_double_inline_cost (operands[1])\n\
       <= arm_max_const_double_inline_cost ())",
    __builtin_constant_p 
#line 5519 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && reload_completed
   && (arm_const_double_inline_cost (operands[1])
       <= arm_max_const_double_inline_cost ()))
    ? (int) 
#line 5519 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && reload_completed
   && (arm_const_double_inline_cost (operands[1])
       <= arm_max_const_double_inline_cost ()))
    : -1 },
#line 5338 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && arm_arch6",
    __builtin_constant_p 
#line 5338 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6)
    ? (int) 
#line 5338 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && GET_CODE (operands[2]) != MULT)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 8331 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && GET_CODE (operands[2]) != MULT))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 8331 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && GET_CODE (operands[2]) != MULT))
    : -1 },
#line 3699 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch6 && SMIN != SMAX\n\
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)",
    __builtin_constant_p 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMAX
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))
    ? (int) 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMAX
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && (TARGET_VFP_DOUBLE)",
    __builtin_constant_p (
#line 1376 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    ? (int) (
#line 1376 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    : -1 },
#line 287 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_ARM && XVECLEN (operands[0], 0) == 5",
    __builtin_constant_p 
#line 287 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 5)
    ? (int) 
#line 287 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 5)
    : -1 },
#line 11305 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[1], operands[2],\n\
                                  operands[0], -4, false, false))",
    __builtin_constant_p 
#line 11305 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], -4, false, false)))
    ? (int) 
#line 11305 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], -4, false, false)))
    : -1 },
#line 115 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune != cortexa8\n\
   && (   register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))\n\
   && !(TARGET_NEON && CONST_INT_P (operands[1])\n\
        && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL))",
    __builtin_constant_p 
#line 115 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune != cortexa8
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode))
   && !(TARGET_NEON && CONST_INT_P (operands[1])
        && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL)))
    ? (int) 
#line 115 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune != cortexa8
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode))
   && !(TARGET_NEON && CONST_INT_P (operands[1])
        && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL)))
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
  { "(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER) && ( reload_completed)",
    __builtin_constant_p (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    ? (int) (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    : -1 },
#line 352 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
   && INTVAL (operands[5]) == INTVAL (operands[2]) + 4",
    __builtin_constant_p 
#line 352 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && INTVAL (operands[5]) == INTVAL (operands[2]) + 4)
    ? (int) 
#line 352 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && INTVAL (operands[5]) == INTVAL (operands[2]) + 4)
    : -1 },
#line 58 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V2DImode != V2SFmode && V2DImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode))",
    __builtin_constant_p 
#line 58 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2DImode != V2SFmode && V2DImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode)))
    ? (int) 
#line 58 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2DImode != V2SFmode && V2DImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode)))
    : -1 },
#line 173 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], CImode)\n\
       || register_operand (operands[1], CImode))",
    __builtin_constant_p 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], CImode)
       || register_operand (operands[1], CImode)))
    ? (int) 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], CImode)
       || register_operand (operands[1], CImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_REALLY_IWMMXT)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 899 "../../gcc/config/arm/iwmmxt2.md"
(TARGET_REALLY_IWMMXT))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 899 "../../gcc/config/arm/iwmmxt2.md"
(TARGET_REALLY_IWMMXT))
    : -1 },
#line 950 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_THUMB1 && XVECLEN (operands[0], 0) == 3",
    __builtin_constant_p 
#line 950 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 3)
    ? (int) 
#line 950 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 3)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 8268 "../../gcc/config/arm/arm.md"
(TARGET_ARM))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 8268 "../../gcc/config/arm/arm.md"
(TARGET_ARM))
    : -1 },
#line 2747 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed",
    __builtin_constant_p 
#line 2747 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed)
    ? (int) 
#line 2747 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed)
    : -1 },
#line 1414 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && (!false || flag_unsafe_math_optimizations)\n\
   && !BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 1414 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!false || flag_unsafe_math_optimizations)
   && !BYTES_BIG_ENDIAN)
    ? (int) 
#line 1414 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!false || flag_unsafe_math_optimizations)
   && !BYTES_BIG_ENDIAN)
    : -1 },
#line 1670 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && GET_CODE (operands[0]) == SYMBOL_REF\n\
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0]))",
    __builtin_constant_p 
#line 1670 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (operands[0]) == SYMBOL_REF
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0])))
    ? (int) 
#line 1670 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (operands[0]) == SYMBOL_REF
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0])))
    : -1 },
#line 1414 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && (!true || flag_unsafe_math_optimizations)\n\
   && !BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 1414 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!true || flag_unsafe_math_optimizations)
   && !BYTES_BIG_ENDIAN)
    ? (int) 
#line 1414 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!true || flag_unsafe_math_optimizations)
   && !BYTES_BIG_ENDIAN)
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V2SFmode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V2SFmode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V2SFmode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 717 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && satisfies_constraint_Pe (operands[1])",
    __builtin_constant_p 
#line 717 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_Pe (operands[1]))
    ? (int) 
#line 717 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_Pe (operands[1]))
    : -1 },
#line 414 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_32BIT && arm_arch6",
    __builtin_constant_p 
#line 414 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch6)
    ? (int) 
#line 414 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch6)
    : -1 },
#line 678 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && INTVAL (operands[2]) == -INTVAL (operands[3])",
    __builtin_constant_p 
#line 678 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && INTVAL (operands[2]) == -INTVAL (operands[3]))
    ? (int) 
#line 678 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && INTVAL (operands[2]) == -INTVAL (operands[3]))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (arm_arch_thumb2)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10965 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10965 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2))
    : -1 },
#line 731 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], HImode)\n\
       || register_operand (operands[1], HImode))",
    __builtin_constant_p 
#line 731 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    ? (int) 
#line 731 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    : -1 },
#line 11273 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))\n\
     && (operands_ok_ldrd_strd (operands[2], operands[4],\n\
                                  operands[0], INTVAL (operands[1]),\n\
                                  false, false))",
    __builtin_constant_p 
#line 11273 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))
     && (operands_ok_ldrd_strd (operands[2], operands[4],
                                  operands[0], INTVAL (operands[1]),
                                  false, false)))
    ? (int) 
#line 11273 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))
     && (operands_ok_ldrd_strd (operands[2], operands[4],
                                  operands[0], INTVAL (operands[1]),
                                  false, false)))
    : -1 },
#line 494 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDACQ",
    __builtin_constant_p 
#line 494 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ)
    ? (int) 
#line 494 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ)
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 && TARGET_VFP_DOUBLE) && (TARGET_VFP_DOUBLE)",
    __builtin_constant_p (
#line 1336 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    ? (int) (
#line 1336 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_FPU_ARMV8 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    : -1 },
#line 1606 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && arm_arch5 && !SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 1606 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch5 && !SIBLING_CALL_P (insn))
    ? (int) 
#line 1606 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch5 && !SIBLING_CALL_P (insn))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_INT_SIMD)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 424 "../../gcc/config/arm/arm-fixed.md"
(TARGET_INT_SIMD))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 424 "../../gcc/config/arm/arm-fixed.md"
(TARGET_INT_SIMD))
    : -1 },
#line 1617 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && !arm_arch5 && !SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 1617 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch5 && !SIBLING_CALL_P (insn))
    ? (int) 
#line 1617 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch5 && !SIBLING_CALL_P (insn))
    : -1 },
#line 4079 "../../gcc/config/arm/arm.md"
  { "TARGET_THUMB1 || arm_arch_thumb2",
    __builtin_constant_p 
#line 4079 "../../gcc/config/arm/arm.md"
(TARGET_THUMB1 || arm_arch_thumb2)
    ? (int) 
#line 4079 "../../gcc/config/arm/arm.md"
(TARGET_THUMB1 || arm_arch_thumb2)
    : -1 },
#line 69 "../../gcc/config/arm/vfp.md"
  { "TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT\n\
   && (   s_register_operand (operands[0], SImode)\n\
       || s_register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 69 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode)))
    ? (int) 
#line 69 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode)))
    : -1 },
#line 1038 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && reload_completed\n\
   && (!CONST_INT_P (operands[2])\n\
       || (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 64))",
    __builtin_constant_p 
#line 1038 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed
   && (!CONST_INT_P (operands[2])
       || (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 64)))
    ? (int) 
#line 1038 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed
   && (!CONST_INT_P (operands[2])
       || (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 64)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && XVECLEN (operands[0], 0) == 2)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1038 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 2))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1038 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 2))
    : -1 },
#line 3015 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM\n\
   && !const_ok_for_arm (INTVAL (operands[2]))\n\
   && const_ok_for_arm (~INTVAL (operands[2]))",
    __builtin_constant_p 
#line 3015 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && !const_ok_for_arm (INTVAL (operands[2]))
   && const_ok_for_arm (~INTVAL (operands[2])))
    ? (int) 
#line 3015 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && !const_ok_for_arm (INTVAL (operands[2]))
   && const_ok_for_arm (~INTVAL (operands[2])))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM\n\
   && arm_arch4\n\
   && (register_operand (operands[0], HImode)\n\
       || register_operand (operands[1], HImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6364 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && arm_arch4
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6364 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && arm_arch4
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode))))
    : -1 },
#line 407 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && arm_arch6",
    __builtin_constant_p 
#line 407 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch6)
    ? (int) 
#line 407 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch6)
    : -1 },
#line 173 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], XImode)\n\
       || register_operand (operands[1], XImode))",
    __builtin_constant_p 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], XImode)
       || register_operand (operands[1], XImode)))
    ? (int) 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], XImode)
       || register_operand (operands[1], XImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2])))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 2829 "../../gcc/config/arm/arm.md"
(TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2]))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 2829 "../../gcc/config/arm/arm.md"
(TARGET_ARM || (TARGET_THUMB2 && CONST_INT_P (operands[2]))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT\n\
   && (   s_register_operand (operands[0], SImode)\n\
       || s_register_operand (operands[1], SImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 27 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 27 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && USE_RETURN_INSN (FALSE))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 7921 "../../gcc/config/arm/arm.md"
(TARGET_ARM && USE_RETURN_INSN (FALSE)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 7921 "../../gcc/config/arm/arm.md"
(TARGET_ARM && USE_RETURN_INSN (FALSE)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_IDIV)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4343 "../../gcc/config/arm/arm.md"
(TARGET_IDIV))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4343 "../../gcc/config/arm/arm.md"
(TARGET_IDIV))
    : -1 },
  { "(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && (TARGET_VFP_DOUBLE)",
    __builtin_constant_p (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    ? (int) (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT\n\
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32\n\
      && INTVAL (operands[1]) > 0 \n\
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8\n\
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 2233 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32
      && INTVAL (operands[1]) > 0 
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 2233 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32
      && INTVAL (operands[1]) > 0 
      && INTVAL (operands[1]) + (INTVAL (operands[2]) & 1) <= 8
      && INTVAL (operands[1]) + INTVAL (operands[2]) <= 32)))
    : -1 },
#line 1109 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && flag_pic",
    __builtin_constant_p 
#line 1109 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && flag_pic)
    ? (int) 
#line 1109 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && flag_pic)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 65 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 65 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT))
    : -1 },
#line 5886 "../../gcc/config/arm/arm.md"
  { "TARGET_THUMB1 && flag_pic",
    __builtin_constant_p 
#line 5886 "../../gcc/config/arm/arm.md"
(TARGET_THUMB1 && flag_pic)
    ? (int) 
#line 5886 "../../gcc/config/arm/arm.md"
(TARGET_THUMB1 && flag_pic)
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SImode != V2SFmode && V4SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN\n\
	&& TARGET_HAVE_MEMORY_BARRIER)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER))
    : -1 },
#line 700 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_ARM && XVECLEN (operands[0], 0) == 4",
    __builtin_constant_p 
#line 700 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 4)
    ? (int) 
#line 700 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 4)
    : -1 },
#line 5870 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && flag_pic",
    __builtin_constant_p 
#line 5870 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && flag_pic)
    ? (int) 
#line 5870 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && flag_pic)
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 771 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 771 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && !flag_rounding_math))
    : -1 },
#line 10845 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch5e",
    __builtin_constant_p 
#line 10845 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5e)
    ? (int) 
#line 10845 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5e)
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V4HImode)\n\
       || register_operand (operands[1], V4HImode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4HImode)
       || register_operand (operands[1], V4HImode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V4HImode)
       || register_operand (operands[1], V4HImode)))
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SFmode != V2SFmode && V2SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 476 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 476 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ && ARM_DOUBLEWORD_ALIGN))
    : -1 },
#line 3699 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch6 && SMIN != SMIN\n\
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)",
    __builtin_constant_p 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMIN
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))
    ? (int) 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMIN
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))
    : -1 },
#line 233 "../../gcc/config/arm/ldrdstrd.md"
  { "TARGET_LDRD && TARGET_ARM\n\
   && current_tune->prefer_ldrd_strd\n\
   && !optimize_function_for_size_p (cfun)\n\
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))\n\
       ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))\n\
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))\n\
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4]))",
    __builtin_constant_p 
#line 233 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD && TARGET_ARM
   && current_tune->prefer_ldrd_strd
   && !optimize_function_for_size_p (cfun)
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))
       ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4])))
    ? (int) 
#line 233 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD && TARGET_ARM
   && current_tune->prefer_ldrd_strd
   && !optimize_function_for_size_p (cfun)
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))
       ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4])))
    : -1 },
#line 1316 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && optimize_size && reload_completed",
    __builtin_constant_p 
#line 1316 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size && reload_completed)
    ? (int) 
#line 1316 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size && reload_completed)
    : -1 },
#line 4892 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT ",
    __builtin_constant_p 
#line 4892 "../../gcc/config/arm/arm.md"
(TARGET_32BIT )
    ? (int) 
#line 4892 "../../gcc/config/arm/arm.md"
(TARGET_32BIT )
    : -1 },
#line 11397 "../../gcc/config/arm/arm.md"
  { "unaligned_access",
    __builtin_constant_p 
#line 11397 "../../gcc/config/arm/arm.md"
(unaligned_access)
    ? (int) 
#line 11397 "../../gcc/config/arm/arm.md"
(unaligned_access)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && ((TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && (TARGET_VFP_DOUBLE))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE)))
    : -1 },
#line 66 "../../gcc/config/arm/ldrdstrd.md"
  { "TARGET_LDRD\n\
     && current_tune->prefer_ldrd_strd\n\
     && !optimize_function_for_size_p (cfun)",
    __builtin_constant_p 
#line 66 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD
     && current_tune->prefer_ldrd_strd
     && !optimize_function_for_size_p (cfun))
    ? (int) 
#line 66 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD
     && current_tune->prefer_ldrd_strd
     && !optimize_function_for_size_p (cfun))
    : -1 },
#line 3043 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !flag_rounding_math",
    __builtin_constant_p 
#line 3043 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !flag_rounding_math)
    ? (int) 
#line 3043 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !flag_rounding_math)
    : -1 },
  { "(TARGET_32BIT) && ( (CONST_INT_P (operands[1])\n\
       && !const_ok_for_arm (INTVAL (operands[1]))))",
    __builtin_constant_p (
#line 1198 "../../gcc/config/arm/arm.md"
(TARGET_32BIT) && 
#line 1209 "../../gcc/config/arm/arm.md"
( (CONST_INT_P (operands[1])
       && !const_ok_for_arm (INTVAL (operands[1])))))
    ? (int) (
#line 1198 "../../gcc/config/arm/arm.md"
(TARGET_32BIT) && 
#line 1209 "../../gcc/config/arm/arm.md"
( (CONST_INT_P (operands[1])
       && !const_ok_for_arm (INTVAL (operands[1])))))
    : -1 },
#line 677 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && satisfies_constraint_J (operands[1])",
    __builtin_constant_p 
#line 677 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_J (operands[1]))
    ? (int) 
#line 677 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_J (operands[1]))
    : -1 },
#line 1393 "../../gcc/config/arm/vfp.md"
  { "TARGET_VFP && TARGET_HARD_FLOAT",
    __builtin_constant_p 
#line 1393 "../../gcc/config/arm/vfp.md"
(TARGET_VFP && TARGET_HARD_FLOAT)
    ? (int) 
#line 1393 "../../gcc/config/arm/vfp.md"
(TARGET_VFP && TARGET_HARD_FLOAT)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE\n\
  && !flag_rounding_math)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 793 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE
  && !flag_rounding_math))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 793 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE
  && !flag_rounding_math))
    : -1 },
#line 112 "../../gcc/config/arm/iwmmxt.md"
  { "TARGET_REALLY_IWMMXT\n\
   && (   register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 112 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 112 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
#line 10908 "../../gcc/config/arm/arm.md"
  { "TARGET_HARD_TP",
    __builtin_constant_p 
#line 10908 "../../gcc/config/arm/arm.md"
(TARGET_HARD_TP)
    ? (int) 
#line 10908 "../../gcc/config/arm/arm.md"
(TARGET_HARD_TP)
    : -1 },
#line 1277 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math\n\
  && !TARGET_VFP_SINGLE",
    __builtin_constant_p 
#line 1277 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math
  && !TARGET_VFP_SINGLE)
    ? (int) 
#line 1277 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math
  && !TARGET_VFP_SINGLE)
    : -1 },
#line 1157 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP",
    __builtin_constant_p 
#line 1157 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP)
    ? (int) 
#line 1157 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP)
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode)))
    : -1 },
#line 1242 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
   && satisfies_constraint_Px (operands[2])",
    __builtin_constant_p 
#line 1242 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && satisfies_constraint_Px (operands[2]))
    ? (int) 
#line 1242 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && satisfies_constraint_Px (operands[2]))
    : -1 },
#line 40 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_MEMORY_BARRIER",
    __builtin_constant_p 
#line 40 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_MEMORY_BARRIER)
    ? (int) 
#line 40 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_MEMORY_BARRIER)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 399 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 399 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && arm_arch4 && !arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5325 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4 && !arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5325 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4 && !arm_arch6))
    : -1 },
#line 11242 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[0], operands[2],\n\
                                  operands[1], 0, false, true))",
    __builtin_constant_p 
#line 11242 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], 0, false, true)))
    ? (int) 
#line 11242 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], 0, false, true)))
    : -1 },
#line 8528 "../../gcc/config/arm/arm.md"
  { "arm_arch5 && TARGET_32BIT",
    __builtin_constant_p 
#line 8528 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT)
    ? (int) 
#line 8528 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT)
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V16QImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && ! TARGET_IWMMXT\n\
   && !(TARGET_HARD_FLOAT && TARGET_VFP)\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5716 "../../gcc/config/arm/arm.md"
(TARGET_ARM && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5716 "../../gcc/config/arm/arm.md"
(TARGET_ARM && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode))))
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V8HImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V8HImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V8HImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 106 "../../gcc/config/arm/sync.md"
(ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 106 "../../gcc/config/arm/sync.md"
(ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE))
    : -1 },
#line 3699 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch6 && SMAX != SMAX\n\
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)",
    __builtin_constant_p 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMAX
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))
    ? (int) 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMAX
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))
    : -1 },
#line 324 "../../gcc/config/arm/vfp.md"
  { "TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   s_register_operand (operands[0], SFmode)\n\
       || s_register_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 324 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode)))
    ? (int) 
#line 324 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode)))
    : -1 },
#line 10920 "../../gcc/config/arm/arm.md"
  { "TARGET_SOFT_TP",
    __builtin_constant_p 
#line 10920 "../../gcc/config/arm/arm.md"
(TARGET_SOFT_TP)
    ? (int) 
#line 10920 "../../gcc/config/arm/arm.md"
(TARGET_SOFT_TP)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && ((TARGET_HARD_FLOAT && TARGET_VFP5 ) && (TARGET_VFP))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 1322 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 1322 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREX)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 409 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 409 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX))
    : -1 },
#line 443 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2",
    __builtin_constant_p 
#line 443 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2)
    ? (int) 
#line 443 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2)
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V2DImode)\n\
       || register_operand (operands[1], V2DImode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2DImode)
       || register_operand (operands[1], V2DImode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2DImode)
       || register_operand (operands[1], V2DImode)))
    : -1 },
#line 158 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && TARGET_FP16",
    __builtin_constant_p 
#line 158 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FP16)
    ? (int) 
#line 158 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FP16)
    : -1 },
#line 9181 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed\n\
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)\n\
       != CCmode)",
    __builtin_constant_p 
#line 9181 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       != CCmode))
    ? (int) 
#line 9181 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       != CCmode))
    : -1 },
#line 120 "../../gcc/config/arm/sync.md"
  { "(TARGET_HAVE_LDREXD || TARGET_HAVE_LPAE || TARGET_HAVE_LDACQ)\n\
   && ARM_DOUBLEWORD_ALIGN",
    __builtin_constant_p 
#line 120 "../../gcc/config/arm/sync.md"
((TARGET_HAVE_LDREXD || TARGET_HAVE_LPAE || TARGET_HAVE_LDACQ)
   && ARM_DOUBLEWORD_ALIGN)
    ? (int) 
#line 120 "../../gcc/config/arm/sync.md"
((TARGET_HAVE_LDREXD || TARGET_HAVE_LPAE || TARGET_HAVE_LDACQ)
   && ARM_DOUBLEWORD_ALIGN)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch6 && SMAX != SMIN\n\
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMIN
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMIN
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && XVECLEN (operands[0], 0) == 2)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1092 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 2))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1092 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 2))
    : -1 },
#line 497 "../../gcc/config/arm/vfp.md"
  { "TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP",
    __builtin_constant_p 
#line 497 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP)
    ? (int) 
#line 497 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP)
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SFmode)))
    : -1 },
#line 3277 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON_RDMA",
    __builtin_constant_p 
#line 3277 "../../gcc/config/arm/neon.md"
(TARGET_NEON_RDMA)
    ? (int) 
#line 3277 "../../gcc/config/arm/neon.md"
(TARGET_NEON_RDMA)
    : -1 },
#line 706 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && peep2_reg_dead_p (3, operands[2])",
    __builtin_constant_p 
#line 706 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && peep2_reg_dead_p (3, operands[2]))
    ? (int) 
#line 706 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && peep2_reg_dead_p (3, operands[2]))
    : -1 },
#line 4170 "../../gcc/config/arm/arm.md"
  { "arm_arch_thumb2",
    __builtin_constant_p 
#line 4170 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2)
    ? (int) 
#line 4170 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && reload_completed\n\
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)\n\
       || REG_P (operands[2])))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1160 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
       || REG_P (operands[2]))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1160 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
       || REG_P (operands[2]))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2]))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5705 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2])))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5705 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2])))
    : -1 },
#line 7725 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && arm_arch5 && !SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 7725 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch5 && !SIBLING_CALL_P (insn))
    ? (int) 
#line 7725 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch5 && !SIBLING_CALL_P (insn))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1068 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1068 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_arch6))
    : -1 },
#line 1106 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_32BIT && XVECLEN (operands[0], 0) == 3",
    __builtin_constant_p 
#line 1106 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 3)
    ? (int) 
#line 1106 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 3)
    : -1 },
#line 4978 "../../gcc/config/arm/arm.md"
  { "!TARGET_THUMB2 && !arm_arch6",
    __builtin_constant_p 
#line 4978 "../../gcc/config/arm/arm.md"
(!TARGET_THUMB2 && !arm_arch6)
    ? (int) 
#line 4978 "../../gcc/config/arm/arm.md"
(!TARGET_THUMB2 && !arm_arch6)
    : -1 },
#line 7752 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && !SIBLING_CALL_P (insn)\n\
   && (GET_CODE (operands[0]) == SYMBOL_REF)\n\
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0]))",
    __builtin_constant_p 
#line 7752 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !SIBLING_CALL_P (insn)
   && (GET_CODE (operands[0]) == SYMBOL_REF)
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0])))
    ? (int) 
#line 7752 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !SIBLING_CALL_P (insn)
   && (GET_CODE (operands[0]) == SYMBOL_REF)
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[0])))
    : -1 },
#line 446 "../../gcc/config/arm/vfp.md"
  { "TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 446 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    ? (int) 
#line 446 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    : -1 },
#line 409 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREX",
    __builtin_constant_p 
#line 409 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX)
    ? (int) 
#line 409 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && optimize_size && reload_completed)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1316 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size && reload_completed))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1316 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size && reload_completed))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && ! TARGET_IWMMXT\n\
   && !(TARGET_HARD_FLOAT && TARGET_VFP)\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 281 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 281 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode))))
    : -1 },
  { "(TARGET_HARD_FLOAT && TARGET_VFP5 ) && (TARGET_VFP)",
    __builtin_constant_p (
#line 1376 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    ? (int) (
#line 1376 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 ) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    : -1 },
#line 625 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && reload_completed\n\
   && arm_general_register_operand (operands[0], DFmode)",
    __builtin_constant_p 
#line 625 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && reload_completed
   && arm_general_register_operand (operands[0], DFmode))
    ? (int) 
#line 625 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && reload_completed
   && arm_general_register_operand (operands[0], DFmode))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10976 "../../gcc/config/arm/arm.md"
(arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10976 "../../gcc/config/arm/arm.md"
(arm_arch6))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && XVECLEN (operands[0], 0) == 4)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 700 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 4))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 700 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 4))
    : -1 },
#line 173 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], EImode)\n\
       || register_operand (operands[1], EImode))",
    __builtin_constant_p 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], EImode)
       || register_operand (operands[1], EImode)))
    ? (int) 
#line 173 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], EImode)
       || register_operand (operands[1], EImode)))
    : -1 },
#line 9243 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)\n\
       == CCmode)",
    __builtin_constant_p 
#line 9243 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       == CCmode))
    ? (int) 
#line 9243 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       == CCmode))
    : -1 },
#line 1346 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (GET_CODE (operands[4]) == EQ\n\
       || GET_CODE (operands[4]) == NE\n\
       || GET_CODE (operands[4]) == GE\n\
       || GET_CODE (operands[4]) == LT)",
    __builtin_constant_p 
#line 1346 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (GET_CODE (operands[4]) == EQ
       || GET_CODE (operands[4]) == NE
       || GET_CODE (operands[4]) == GE
       || GET_CODE (operands[4]) == LT))
    ? (int) 
#line 1346 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (GET_CODE (operands[4]) == EQ
       || GET_CODE (operands[4]) == NE
       || GET_CODE (operands[4]) == GE
       || GET_CODE (operands[4]) == LT))
    : -1 },
#line 164 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN\n\
	&& TARGET_HAVE_MEMORY_BARRIER",
    __builtin_constant_p 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER)
    ? (int) 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER)
    : -1 },
#line 4932 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed && !IS_VFP_REGNUM (REGNO (operands[0]))",
    __builtin_constant_p 
#line 4932 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed && !IS_VFP_REGNUM (REGNO (operands[0])))
    ? (int) 
#line 4932 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed && !IS_VFP_REGNUM (REGNO (operands[0])))
    : -1 },
#line 637 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 637 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    ? (int) 
#line 637 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    : -1 },
#line 765 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_32BIT && XVECLEN (operands[0], 0) == 4",
    __builtin_constant_p 
#line 765 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 4)
    ? (int) 
#line 765 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 4)
    : -1 },
#line 10875 "../../gcc/config/arm/arm.md"
  { "TARGET_EITHER",
    __builtin_constant_p 
#line 10875 "../../gcc/config/arm/arm.md"
(TARGET_EITHER)
    ? (int) 
#line 10875 "../../gcc/config/arm/arm.md"
(TARGET_EITHER)
    : -1 },
#line 164 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER",
    __builtin_constant_p 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER)
    ? (int) 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1006 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1006 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16))
    : -1 },
#line 11290 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[1], operands[2],\n\
                                  operands[0], 0, false, false))",
    __builtin_constant_p 
#line 11290 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], 0, false, false)))
    ? (int) 
#line 11290 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], 0, false, false)))
    : -1 },
  { "(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN\n\
	&& TARGET_HAVE_MEMORY_BARRIER) && ( reload_completed)",
    __builtin_constant_p (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    ? (int) (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD && ARM_DOUBLEWORD_ALIGN
	&& TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && ((TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && (TARGET_VFP_DOUBLE))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 1322 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 1322 "../../gcc/config/arm/vfp.md"
(TARGET_HARD_FLOAT && TARGET_VFP5 && TARGET_VFP_DOUBLE) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP_DOUBLE)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && !arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5058 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5058 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch6))
    : -1 },
#line 2440 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM || arm_arch_thumb2",
    __builtin_constant_p 
#line 2440 "../../gcc/config/arm/arm.md"
(TARGET_ARM || arm_arch_thumb2)
    ? (int) 
#line 2440 "../../gcc/config/arm/arm.md"
(TARGET_ARM || arm_arch_thumb2)
    : -1 },
#line 7736 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && !arm_arch5 && !SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 7736 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch5 && !SIBLING_CALL_P (insn))
    ? (int) 
#line 7736 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch5 && !SIBLING_CALL_P (insn))
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8HImode)))
    : -1 },
#line 10828 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch_thumb2",
    __builtin_constant_p 
#line 10828 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch_thumb2)
    ? (int) 
#line 10828 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch_thumb2)
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V8QImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V8QImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V8QImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
#line 329 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_DSP_MULTIPLY && arm_arch_thumb2",
    __builtin_constant_p 
#line 329 "../../gcc/config/arm/arm-fixed.md"
(TARGET_DSP_MULTIPLY && arm_arch_thumb2)
    ? (int) 
#line 329 "../../gcc/config/arm/arm-fixed.md"
(TARGET_DSP_MULTIPLY && arm_arch_thumb2)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))\n\
     && (operands_ok_ldrd_strd (operands[0], operands[3],\n\
                                  operands[1], INTVAL (operands[2]),\n\
                                  false, true)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11225 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))
     && (operands_ok_ldrd_strd (operands[0], operands[3],
                                  operands[1], INTVAL (operands[2]),
                                  false, true))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11225 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))
     && (operands_ok_ldrd_strd (operands[0], operands[3],
                                  operands[1], INTVAL (operands[2]),
                                  false, true))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch6 && SMIN != SMIN\n\
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMIN
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMIN
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)))
    : -1 },
#line 11212 "../../gcc/config/arm/arm.md"
  { "arm_arch6",
    __builtin_constant_p 
#line 11212 "../../gcc/config/arm/arm.md"
(arm_arch6)
    ? (int) 
#line 11212 "../../gcc/config/arm/arm.md"
(arm_arch6)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1531 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1531 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2))
    : -1 },
#line 1145 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && reload_completed\n\
   && GET_CODE(operands[3]) != PLUS\n\
   && GET_CODE(operands[3]) != MINUS",
    __builtin_constant_p 
#line 1145 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && GET_CODE(operands[3]) != PLUS
   && GET_CODE(operands[3]) != MINUS)
    ? (int) 
#line 1145 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && GET_CODE(operands[3]) != PLUS
   && GET_CODE(operands[3]) != MINUS)
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V8QImode)\n\
       || register_operand (operands[1], V8QImode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8QImode)
       || register_operand (operands[1], V8QImode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8QImode)
       || register_operand (operands[1], V8QImode)))
    : -1 },
#line 637 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && TARGET_FMA && flag_unsafe_math_optimizations",
    __builtin_constant_p 
#line 637 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FMA && flag_unsafe_math_optimizations)
    ? (int) 
#line 637 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FMA && flag_unsafe_math_optimizations)
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V4SFmode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4SFmode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V4SFmode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT )",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4892 "../../gcc/config/arm/arm.md"
(TARGET_32BIT ))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 4892 "../../gcc/config/arm/arm.md"
(TARGET_32BIT ))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREXBH)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 388 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 388 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH))
    : -1 },
#line 281 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && ! TARGET_IWMMXT\n\
   && !(TARGET_HARD_FLOAT && TARGET_VFP)\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 281 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    ? (int) 
#line 281 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    : -1 },
#line 3167 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && CONST_INT_P (operands[2])\n\
   && !const_ok_for_arm (INTVAL (operands[2]))",
    __builtin_constant_p 
#line 3167 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !const_ok_for_arm (INTVAL (operands[2])))
    ? (int) 
#line 3167 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !const_ok_for_arm (INTVAL (operands[2])))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch6 && SMAX != SMAX\n\
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMAX
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMAX != SMAX
   && arm_sat_operator_match (operands[2], operands[1], NULL, NULL)))
    : -1 },
#line 1006 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16",
    __builtin_constant_p 
#line 1006 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16)
    ? (int) 
#line 1006 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16)
    : -1 },
#line 1963 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && TARGET_FMA",
    __builtin_constant_p 
#line 1963 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FMA)
    ? (int) 
#line 1963 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FMA)
    : -1 },
#line 734 "../../gcc/config/arm/neon.md"
  { "reload_completed && \n\
   (TARGET_NEON && !(IS_VFP_REGNUM (REGNO (operands[0]))))",
    __builtin_constant_p 
#line 734 "../../gcc/config/arm/neon.md"
(reload_completed && 
   (TARGET_NEON && !(IS_VFP_REGNUM (REGNO (operands[0])))))
    ? (int) 
#line 734 "../../gcc/config/arm/neon.md"
(reload_completed && 
   (TARGET_NEON && !(IS_VFP_REGNUM (REGNO (operands[0])))))
    : -1 },
#line 2993 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && CONST_INT_P (operands[2])\n\
   && !(const_ok_for_arm (INTVAL (operands[2]))\n\
        || (TARGET_THUMB2 && const_ok_for_arm (~INTVAL (operands[2]))))",
    __builtin_constant_p 
#line 2993 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !(const_ok_for_arm (INTVAL (operands[2]))
        || (TARGET_THUMB2 && const_ok_for_arm (~INTVAL (operands[2])))))
    ? (int) 
#line 2993 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !(const_ok_for_arm (INTVAL (operands[2]))
        || (TARGET_THUMB2 && const_ok_for_arm (~INTVAL (operands[2])))))
    : -1 },
#line 599 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && CONST_INT_P (operands[2])\n\
   && !const_ok_for_op (INTVAL (operands[2]), PLUS)\n\
   && (reload_completed || !arm_eliminable_register (operands[1]))",
    __builtin_constant_p 
#line 599 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !const_ok_for_op (INTVAL (operands[2]), PLUS)
   && (reload_completed || !arm_eliminable_register (operands[1])))
    ? (int) 
#line 599 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !const_ok_for_op (INTVAL (operands[2]), PLUS)
   && (reload_completed || !arm_eliminable_register (operands[1])))
    : -1 },
#line 106 "../../gcc/config/arm/sync.md"
  { "ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE",
    __builtin_constant_p 
#line 106 "../../gcc/config/arm/sync.md"
(ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE)
    ? (int) 
#line 106 "../../gcc/config/arm/sync.md"
(ARM_DOUBLEWORD_ALIGN && TARGET_HAVE_LPAE)
    : -1 },
#line 492 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && reload_completed",
    __builtin_constant_p 
#line 492 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && reload_completed)
    ? (int) 
#line 492 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && reload_completed)
    : -1 },
#line 10622 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && (reload_in_progress || reload_completed)",
    __builtin_constant_p 
#line 10622 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (reload_in_progress || reload_completed))
    ? (int) 
#line 10622 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (reload_in_progress || reload_completed))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && ((TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && (TARGET_VFP))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch6 && SMIN != SMAX\n\
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMAX
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 3699 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch6 && SMIN != SMAX
   && arm_sat_operator_match (operands[1], operands[2], NULL, NULL)))
    : -1 },
#line 3578 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !arm_eliminable_register (operands[1]) && !arm_restrict_it",
    __builtin_constant_p 
#line 3578 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1]) && !arm_restrict_it)
    ? (int) 
#line 3578 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1]) && !arm_restrict_it)
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V4SFmode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4SFmode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V4SFmode != V2SFmode && V4SFmode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V4SFmode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 5288 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && arm_arch4",
    __builtin_constant_p 
#line 5288 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4)
    ? (int) 
#line 5288 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4)
    : -1 },
#line 6551 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)\n\
   && (	  s_register_operand (operands[0], HFmode)\n\
       || s_register_operand (operands[1], HFmode))",
    __builtin_constant_p 
#line 6551 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    ? (int) 
#line 6551 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    : -1 },
#line 2306 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && flag_unsafe_math_optimizations",
    __builtin_constant_p 
#line 2306 "../../gcc/config/arm/neon.md"
(TARGET_NEON && flag_unsafe_math_optimizations)
    ? (int) 
#line 2306 "../../gcc/config/arm/neon.md"
(TARGET_NEON && flag_unsafe_math_optimizations)
    : -1 },
#line 9117 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_OR_Y)\n\
       != CCmode)",
    __builtin_constant_p 
#line 9117 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_OR_Y)
       != CCmode))
    ? (int) 
#line 9117 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_OR_Y)
       != CCmode))
    : -1 },
#line 11370 "../../gcc/config/arm/arm.md"
  { "TARGET_SOFT_FLOAT && arm_arch_thumb2",
    __builtin_constant_p 
#line 11370 "../../gcc/config/arm/arm.md"
(TARGET_SOFT_FLOAT && arm_arch_thumb2)
    ? (int) 
#line 11370 "../../gcc/config/arm/arm.md"
(TARGET_SOFT_FLOAT && arm_arch_thumb2)
    : -1 },
#line 6364 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM\n\
   && arm_arch4\n\
   && (register_operand (operands[0], HImode)\n\
       || register_operand (operands[1], HImode))",
    __builtin_constant_p 
#line 6364 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && arm_arch4
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    ? (int) 
#line 6364 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && arm_arch4
   && (register_operand (operands[0], HImode)
       || register_operand (operands[1], HImode)))
    : -1 },
#line 566 "../../gcc/config/arm/vfp.md"
  { "TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && !arm_restrict_it",
    __builtin_constant_p 
#line 566 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && !arm_restrict_it)
    ? (int) 
#line 566 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE && !arm_restrict_it)
    : -1 },
#line 2177 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && CONST_INT_P (operands[2])\n\
   && !(const_ok_for_arm (INTVAL (operands[2]))\n\
	|| const_ok_for_arm (~INTVAL (operands[2])))",
    __builtin_constant_p 
#line 2177 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !(const_ok_for_arm (INTVAL (operands[2]))
	|| const_ok_for_arm (~INTVAL (operands[2]))))
    ? (int) 
#line 2177 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && CONST_INT_P (operands[2])
   && !(const_ok_for_arm (INTVAL (operands[2]))
	|| const_ok_for_arm (~INTVAL (operands[2]))))
    : -1 },
#line 11200 "../../gcc/config/arm/arm.md"
  { "arm_arch6\n\
   && aarch_rev16_shleft_mask_imm_p (operands[3], SImode)\n\
   && aarch_rev16_shright_mask_imm_p (operands[2], SImode)",
    __builtin_constant_p 
#line 11200 "../../gcc/config/arm/arm.md"
(arm_arch6
   && aarch_rev16_shleft_mask_imm_p (operands[3], SImode)
   && aarch_rev16_shright_mask_imm_p (operands[2], SImode))
    ? (int) 
#line 11200 "../../gcc/config/arm/arm.md"
(arm_arch6
   && aarch_rev16_shleft_mask_imm_p (operands[3], SImode)
   && aarch_rev16_shright_mask_imm_p (operands[2], SImode))
    : -1 },
#line 884 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_THUMB1 && XVECLEN (operands[0], 0) == 2",
    __builtin_constant_p 
#line 884 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 2)
    ? (int) 
#line 884 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 2)
    : -1 },
#line 7578 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && TARGET_SOFT_FLOAT",
    __builtin_constant_p 
#line 7578 "../../gcc/config/arm/arm.md"
(TARGET_ARM && TARGET_SOFT_FLOAT)
    ? (int) 
#line 7578 "../../gcc/config/arm/arm.md"
(TARGET_ARM && TARGET_SOFT_FLOAT)
    : -1 },
#line 1157 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && reload_completed",
    __builtin_constant_p 
#line 1157 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed)
    ? (int) 
#line 1157 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed)
    : -1 },
#line 5796 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && TARGET_USE_MOVT && GET_CODE (operands[1]) == SYMBOL_REF\n\
   && !flag_pic && !target_word_relocations\n\
   && !arm_tls_referenced_p (operands[1])",
    __builtin_constant_p 
#line 5796 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_USE_MOVT && GET_CODE (operands[1]) == SYMBOL_REF
   && !flag_pic && !target_word_relocations
   && !arm_tls_referenced_p (operands[1]))
    ? (int) 
#line 5796 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_USE_MOVT && GET_CODE (operands[1]) == SYMBOL_REF
   && !flag_pic && !target_word_relocations
   && !arm_tls_referenced_p (operands[1]))
    : -1 },
#line 2264 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32\n\
       && INTVAL (operands[2]) > 0 \n\
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8\n\
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32)",
    __builtin_constant_p 
#line 2264 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32
       && INTVAL (operands[2]) > 0 
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32))
    ? (int) 
#line 2264 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32
       && INTVAL (operands[2]) > 0 
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32))
    : -1 },
#line 276 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !BYTES_BIG_ENDIAN && unaligned_access",
    __builtin_constant_p 
#line 276 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !BYTES_BIG_ENDIAN && unaligned_access)
    ? (int) 
#line 276 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !BYTES_BIG_ENDIAN && unaligned_access)
    : -1 },
#line 1552 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
   && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32)\n\
   && peep2_reg_dead_p (2, operands[0])",
    __builtin_constant_p 
#line 1552 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32)
   && peep2_reg_dead_p (2, operands[0]))
    ? (int) 
#line 1552 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && (INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) < 32)
   && peep2_reg_dead_p (2, operands[0]))
    : -1 },
#line 388 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREXBH",
    __builtin_constant_p 
#line 388 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH)
    ? (int) 
#line 388 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH)
    : -1 },
#line 793 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE\n\
  && !flag_rounding_math",
    __builtin_constant_p 
#line 793 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE
  && !flag_rounding_math)
    ? (int) 
#line 793 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE
  && !flag_rounding_math)
    : -1 },
#line 7384 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && !TARGET_VFP_SINGLE",
    __builtin_constant_p 
#line 7384 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && !TARGET_VFP_SINGLE)
    ? (int) 
#line 7384 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && !TARGET_VFP_SINGLE)
    : -1 },
#line 2365 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && !reg_overlap_mentioned_p (operands[0], operands[3])",
    __builtin_constant_p 
#line 2365 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !reg_overlap_mentioned_p (operands[0], operands[3]))
    ? (int) 
#line 2365 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !reg_overlap_mentioned_p (operands[0], operands[3]))
    : -1 },
#line 690 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && satisfies_constraint_K (operands[1])",
    __builtin_constant_p 
#line 690 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_K (operands[1]))
    ? (int) 
#line 690 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && satisfies_constraint_K (operands[1]))
    : -1 },
#line 7964 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM  && USE_RETURN_INSN (TRUE)",
    __builtin_constant_p 
#line 7964 "../../gcc/config/arm/arm.md"
(TARGET_ARM  && USE_RETURN_INSN (TRUE))
    ? (int) 
#line 7964 "../../gcc/config/arm/arm.md"
(TARGET_ARM  && USE_RETURN_INSN (TRUE))
    : -1 },
  { "(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && (TARGET_VFP)",
    __builtin_constant_p (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    ? (int) (
#line 963 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FMA) && 
#line 49 "../../gcc/config/arm/iterators.md"
(TARGET_VFP))
    : -1 },
#line 9177 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)\n\
       != CCmode)",
    __builtin_constant_p 
#line 9177 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       != CCmode))
    ? (int) 
#line 9177 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (arm_select_dominance_cc_mode (operands[3], operands[6], DOM_CC_X_AND_Y)
       != CCmode))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT\n\
   && (   register_operand (operands[0], QImode)\n\
       || register_operand (operands[1], QImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6506 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6506 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (   register_operand (operands[0], QImode)
       || register_operand (operands[1], QImode))))
    : -1 },
#line 166 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8\n\
    && (   register_operand (operands[0], DImode)\n\
        || register_operand (operands[1], DImode))\n\
    && !(TARGET_NEON && CONST_INT_P (operands[1])\n\
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL))",
    __builtin_constant_p 
#line 166 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8
    && (   register_operand (operands[0], DImode)
        || register_operand (operands[1], DImode))
    && !(TARGET_NEON && CONST_INT_P (operands[1])
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL)))
    ? (int) 
#line 166 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8
    && (   register_operand (operands[0], DImode)
        || register_operand (operands[1], DImode))
    && !(TARGET_NEON && CONST_INT_P (operands[1])
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL)))
    : -1 },
#line 10810 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch5",
    __builtin_constant_p 
#line 10810 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5)
    ? (int) 
#line 10810 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch5)
    : -1 },
#line 164 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER",
    __builtin_constant_p 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER)
    ? (int) 
#line 164 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER)
    : -1 },
#line 1139 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && reload_completed\n\
   && INTVAL (operands[2]) > 0 && INTVAL (operands[2]) <= 64",
    __builtin_constant_p 
#line 1139 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed
   && INTVAL (operands[2]) > 0 && INTVAL (operands[2]) <= 64)
    ? (int) 
#line 1139 "../../gcc/config/arm/neon.md"
(TARGET_NEON && reload_completed
   && INTVAL (operands[2]) > 0 && INTVAL (operands[2]) <= 64)
    : -1 },
#line 1160 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && reload_completed\n\
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)\n\
       || REG_P (operands[2]))",
    __builtin_constant_p 
#line 1160 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
       || REG_P (operands[2])))
    ? (int) 
#line 1160 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
       || REG_P (operands[2])))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1219 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1219 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP))
    : -1 },
#line 2700 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && reload_completed\n\
   && operands[0] != operands[1]",
    __builtin_constant_p 
#line 2700 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && reload_completed
   && operands[0] != operands[1])
    ? (int) 
#line 2700 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && reload_completed
   && operands[0] != operands[1])
    : -1 },
#line 217 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_NEON_FP16\n\
   && (   s_register_operand (operands[0], HFmode)\n\
       || s_register_operand (operands[1], HFmode))",
    __builtin_constant_p 
#line 217 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_NEON_FP16
   && (   s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    ? (int) 
#line 217 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_NEON_FP16
   && (   s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    : -1 },
#line 7903 "../../gcc/config/arm/arm.md"
  { "(TARGET_ARM || (TARGET_THUMB2\n\
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL\n\
                   && !IS_STACKALIGN (arm_current_func_type ())))\n\
     && use_simple_return_p ()",
    __builtin_constant_p 
#line 7903 "../../gcc/config/arm/arm.md"
((TARGET_ARM || (TARGET_THUMB2
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL
                   && !IS_STACKALIGN (arm_current_func_type ())))
     && use_simple_return_p ())
    ? (int) 
#line 7903 "../../gcc/config/arm/arm.md"
((TARGET_ARM || (TARGET_THUMB2
                   && ARM_FUNC_TYPE (arm_current_func_type ()) == ARM_FT_NORMAL
                   && !IS_STACKALIGN (arm_current_func_type ())))
     && use_simple_return_p ())
    : -1 },
#line 146 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_THUMB1 && XVECLEN (operands[0], 0) == 5",
    __builtin_constant_p 
#line 146 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 5)
    ? (int) 
#line 146 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 5)
    : -1 },
  { "(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER) && ( reload_completed)",
    __builtin_constant_p (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    ? (int) (
#line 372 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREX && TARGET_HAVE_MEMORY_BARRIER) && 
#line 374 "../../gcc/config/arm/sync.md"
( reload_completed))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && reload_completed)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1410 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1410 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed))
    : -1 },
#line 863 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 863 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    ? (int) 
#line 863 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    : -1 },
#line 7238 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT || TARGET_THUMB1",
    __builtin_constant_p 
#line 7238 "../../gcc/config/arm/arm.md"
(TARGET_32BIT || TARGET_THUMB1)
    ? (int) 
#line 7238 "../../gcc/config/arm/arm.md"
(TARGET_32BIT || TARGET_THUMB1)
    : -1 },
#line 5594 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD\n\
  && reg_overlap_mentioned_p (operands[0], operands[1])\n\
  && reg_overlap_mentioned_p (operands[0], operands[2])",
    __builtin_constant_p 
#line 5594 "../../gcc/config/arm/arm.md"
(TARGET_LDRD
  && reg_overlap_mentioned_p (operands[0], operands[1])
  && reg_overlap_mentioned_p (operands[0], operands[2]))
    ? (int) 
#line 5594 "../../gcc/config/arm/arm.md"
(TARGET_LDRD
  && reg_overlap_mentioned_p (operands[0], operands[1])
  && reg_overlap_mentioned_p (operands[0], operands[2]))
    : -1 },
#line 10205 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM",
    __builtin_constant_p 
#line 10205 "../../gcc/config/arm/arm.md"
(TARGET_ARM)
    ? (int) 
#line 10205 "../../gcc/config/arm/arm.md"
(TARGET_ARM)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && XVECLEN (operands[0], 0) == 4)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 765 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 4))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 765 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 4))
    : -1 },
#line 750 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && !arm_restrict_it",
    __builtin_constant_p 
#line 750 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !arm_restrict_it)
    ? (int) 
#line 750 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && !arm_restrict_it)
    : -1 },
#line 1650 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && !arm_arch5",
    __builtin_constant_p 
#line 1650 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch5)
    ? (int) 
#line 1650 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && !arm_arch5)
    : -1 },
#line 1229 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && !const_ok_for_arm (INTVAL (operands[1]))\n\
   && const_ok_for_arm (~INTVAL (operands[1]))",
    __builtin_constant_p 
#line 1229 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !const_ok_for_arm (INTVAL (operands[1]))
   && const_ok_for_arm (~INTVAL (operands[1])))
    ? (int) 
#line 1229 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !const_ok_for_arm (INTVAL (operands[1]))
   && const_ok_for_arm (~INTVAL (operands[1])))
    : -1 },
#line 4706 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed\n\
   && arm_general_register_operand (operands[0], DImode)",
    __builtin_constant_p 
#line 4706 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && arm_general_register_operand (operands[0], DImode))
    ? (int) 
#line 4706 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && arm_general_register_operand (operands[0], DImode))
    : -1 },
#line 579 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_THUMB1 && XVECLEN (operands[0], 0) == 4",
    __builtin_constant_p 
#line 579 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 4)
    ? (int) 
#line 579 "../../gcc/config/arm/ldmstm.md"
(TARGET_THUMB1 && XVECLEN (operands[0], 0) == 4)
    : -1 },
#line 116 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (unsigned HOST_WIDE_INT) (INTVAL (operands[1])) < 1024\n\
   && (INTVAL (operands[1]) & 3) == 0",
    __builtin_constant_p 
#line 116 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (unsigned HOST_WIDE_INT) (INTVAL (operands[1])) < 1024
   && (INTVAL (operands[1]) & 3) == 0)
    ? (int) 
#line 116 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (unsigned HOST_WIDE_INT) (INTVAL (operands[1])) < 1024
   && (INTVAL (operands[1]) & 3) == 0)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1245 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1245 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREXD)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 429 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 429 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD))
    : -1 },
#line 803 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (	  s_register_operand (operands[0], HFmode)\n\
       || s_register_operand (operands[1], HFmode))",
    __builtin_constant_p 
#line 803 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    ? (int) 
#line 803 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    : -1 },
#line 325 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
  && (register_operand (operands[0], HImode)\n\
     || register_operand (operands[1], HImode))",
    __builtin_constant_p 
#line 325 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
  && (register_operand (operands[0], HImode)
     || register_operand (operands[1], HImode)))
    ? (int) 
#line 325 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
  && (register_operand (operands[0], HImode)
     || register_operand (operands[1], HImode)))
    : -1 },
#line 1600 "../../gcc/config/arm/thumb2.md"
  { "TARGET_32BIT",
    __builtin_constant_p 
#line 1600 "../../gcc/config/arm/thumb2.md"
(TARGET_32BIT)
    ? (int) 
#line 1600 "../../gcc/config/arm/thumb2.md"
(TARGET_32BIT)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[1], operands[2],\n\
                                  operands[0], -4, false, false)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11305 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], -4, false, false))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11305 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], -4, false, false))))
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4HImode)))
    : -1 },
#line 5093 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && (!MEM_P (operands[1])) && ! BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 5093 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (!MEM_P (operands[1])) && ! BYTES_BIG_ENDIAN)
    ? (int) 
#line 5093 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (!MEM_P (operands[1])) && ! BYTES_BIG_ENDIAN)
    : -1 },
  { "(TARGET_32BIT) && ( reload_completed)",
    __builtin_constant_p (
#line 3228 "../../gcc/config/arm/arm.md"
(TARGET_32BIT) && 
#line 3230 "../../gcc/config/arm/arm.md"
( reload_completed))
    ? (int) (
#line 3228 "../../gcc/config/arm/arm.md"
(TARGET_32BIT) && 
#line 3230 "../../gcc/config/arm/arm.md"
( reload_completed))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT\n\
   && (   s_register_operand (operands[0], SImode)\n\
       || s_register_operand (operands[1], SImode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 69 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 69 "../../gcc/config/arm/vfp.md"
(TARGET_THUMB2 && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode))))
    : -1 },
#line 10405 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && reload_completed",
    __builtin_constant_p 
#line 10405 "../../gcc/config/arm/arm.md"
(TARGET_ARM && reload_completed)
    ? (int) 
#line 10405 "../../gcc/config/arm/arm.md"
(TARGET_ARM && reload_completed)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch_thumb2)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10819 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch_thumb2))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10819 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch_thumb2))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V8HFmode)\n\
       || register_operand (operands[1], V8HFmode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8HFmode)
       || register_operand (operands[1], V8HFmode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8HFmode)
       || register_operand (operands[1], V8HFmode)))
    : -1 },
#line 3626 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !arm_eliminable_register (operands[1]) && reload_completed",
    __builtin_constant_p 
#line 3626 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1]) && reload_completed)
    ? (int) 
#line 3626 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_eliminable_register (operands[1]) && reload_completed)
    : -1 },
#line 7886 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && SIBLING_CALL_P (insn)",
    __builtin_constant_p 
#line 7886 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && SIBLING_CALL_P (insn))
    ? (int) 
#line 7886 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && SIBLING_CALL_P (insn))
    : -1 },
#line 1425 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (GET_CODE (operands[3]) == EQ\n\
       || GET_CODE (operands[3]) == NE\n\
       || GET_CODE (operands[3]) == GE\n\
       || GET_CODE (operands[3]) == LT)",
    __builtin_constant_p 
#line 1425 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (GET_CODE (operands[3]) == EQ
       || GET_CODE (operands[3]) == NE
       || GET_CODE (operands[3]) == GE
       || GET_CODE (operands[3]) == LT))
    ? (int) 
#line 1425 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (GET_CODE (operands[3]) == EQ
       || GET_CODE (operands[3]) == NE
       || GET_CODE (operands[3]) == GE
       || GET_CODE (operands[3]) == LT))
    : -1 },
#line 1212 "../../gcc/config/arm/ldmstm.md"
  { "((((REGNO (operands[6]) == REGNO (operands[0]))\n\
         && (REGNO (operands[7]) == REGNO (operands[1])))\n\
      || ((REGNO (operands[7]) == REGNO (operands[0]))\n\
         && (REGNO (operands[6]) == REGNO (operands[1]))))\n\
    && (peep2_regno_dead_p (3, REGNO (operands[0]))\n\
      || (REGNO (operands[0]) == REGNO (operands[4])))\n\
    && (peep2_regno_dead_p (3, REGNO (operands[1]))\n\
      || (REGNO (operands[1]) == REGNO (operands[4]))))",
    __builtin_constant_p 
#line 1212 "../../gcc/config/arm/ldmstm.md"
(((((REGNO (operands[6]) == REGNO (operands[0]))
         && (REGNO (operands[7]) == REGNO (operands[1])))
      || ((REGNO (operands[7]) == REGNO (operands[0]))
         && (REGNO (operands[6]) == REGNO (operands[1]))))
    && (peep2_regno_dead_p (3, REGNO (operands[0]))
      || (REGNO (operands[0]) == REGNO (operands[4])))
    && (peep2_regno_dead_p (3, REGNO (operands[1]))
      || (REGNO (operands[1]) == REGNO (operands[4])))))
    ? (int) 
#line 1212 "../../gcc/config/arm/ldmstm.md"
(((((REGNO (operands[6]) == REGNO (operands[0]))
         && (REGNO (operands[7]) == REGNO (operands[1])))
      || ((REGNO (operands[7]) == REGNO (operands[0]))
         && (REGNO (operands[6]) == REGNO (operands[1]))))
    && (peep2_regno_dead_p (3, REGNO (operands[0]))
      || (REGNO (operands[0]) == REGNO (operands[4])))
    && (peep2_regno_dead_p (3, REGNO (operands[1]))
      || (REGNO (operands[1]) == REGNO (operands[4])))))
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode)))
    : -1 },
#line 3074 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !TARGET_IWMMXT && reload_completed\n\
   && !(IS_VFP_REGNUM (REGNO (operands[0])))",
    __builtin_constant_p 
#line 3074 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_IWMMXT && reload_completed
   && !(IS_VFP_REGNUM (REGNO (operands[0]))))
    ? (int) 
#line 3074 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_IWMMXT && reload_completed
   && !(IS_VFP_REGNUM (REGNO (operands[0]))))
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V2SImode)\n\
       || register_operand (operands[1], V2SImode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2SImode)
       || register_operand (operands[1], V2SImode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2SImode)
       || register_operand (operands[1], V2SImode)))
    : -1 },
#line 11225 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))\n\
     && (operands_ok_ldrd_strd (operands[0], operands[3],\n\
                                  operands[1], INTVAL (operands[2]),\n\
                                  false, true))",
    __builtin_constant_p 
#line 11225 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))
     && (operands_ok_ldrd_strd (operands[0], operands[3],
                                  operands[1], INTVAL (operands[2]),
                                  false, true)))
    ? (int) 
#line 11225 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[2]) + 4) == INTVAL (operands[4]))
     && (operands_ok_ldrd_strd (operands[0], operands[3],
                                  operands[1], INTVAL (operands[2]),
                                  false, true)))
    : -1 },
  { "(TARGET_32BIT && !TARGET_NEON) && ( reload_completed)",
    __builtin_constant_p (
#line 1011 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_NEON) && 
#line 1013 "../../gcc/config/arm/arm.md"
( reload_completed))
    ? (int) (
#line 1011 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_NEON) && 
#line 1013 "../../gcc/config/arm/arm.md"
( reload_completed))
    : -1 },
#line 839 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], SFmode)\n\
       || register_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 839 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], SFmode)
       || register_operand (operands[1], SFmode)))
    ? (int) 
#line 839 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], SFmode)
       || register_operand (operands[1], SFmode)))
    : -1 },
#line 2331 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM\n\
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32\n\
       && INTVAL (operands[2]) > 0 \n\
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8\n\
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32)\n\
   && !reg_overlap_mentioned_p (operands[0], operands[4])",
    __builtin_constant_p 
#line 2331 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32
       && INTVAL (operands[2]) > 0 
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32)
   && !reg_overlap_mentioned_p (operands[0], operands[4]))
    ? (int) 
#line 2331 "../../gcc/config/arm/arm.md"
(TARGET_ARM
   && (INTVAL (operands[3]) >= 0 && INTVAL (operands[3]) < 32
       && INTVAL (operands[2]) > 0 
       && INTVAL (operands[2]) + (INTVAL (operands[3]) & 1) <= 8
       && INTVAL (operands[2]) + INTVAL (operands[3]) <= 32)
   && !reg_overlap_mentioned_p (operands[0], operands[4]))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8\n\
    && (   register_operand (operands[0], DImode)\n\
        || register_operand (operands[1], DImode))\n\
    && !(TARGET_NEON && CONST_INT_P (operands[1])\n\
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 166 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8
    && (   register_operand (operands[0], DImode)
        || register_operand (operands[1], DImode))
    && !(TARGET_NEON && CONST_INT_P (operands[1])
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 166 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP && arm_tune == cortexa8
    && (   register_operand (operands[0], DImode)
        || register_operand (operands[1], DImode))
    && !(TARGET_NEON && CONST_INT_P (operands[1])
	 && neon_immediate_valid_for_move (operands[1], DImode, NULL, NULL))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)\n\
   && (	  s_register_operand (operands[0], HFmode)\n\
       || s_register_operand (operands[1], HFmode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6551 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 6551 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !(TARGET_HARD_FLOAT && TARGET_FP16)
   && (	  s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode))))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && (reload_in_progress || reload_completed))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10622 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (reload_in_progress || reload_completed)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10622 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (reload_in_progress || reload_completed)))
    : -1 },
  { "(TARGET_THUMB1) && ( reload_completed && CONST_INT_P (operands[2])\n\
   && ((operands[1] != stack_pointer_rtx\n\
        && (INTVAL (operands[2]) > 255 || INTVAL (operands[2]) < -255))\n\
       || (operands[1] == stack_pointer_rtx\n\
 	   && INTVAL (operands[2]) > 1020)))",
    __builtin_constant_p (
#line 62 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1) && 
#line 83 "../../gcc/config/arm/thumb1.md"
( reload_completed && CONST_INT_P (operands[2])
   && ((operands[1] != stack_pointer_rtx
        && (INTVAL (operands[2]) > 255 || INTVAL (operands[2]) < -255))
       || (operands[1] == stack_pointer_rtx
 	   && INTVAL (operands[2]) > 1020))))
    ? (int) (
#line 62 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1) && 
#line 83 "../../gcc/config/arm/thumb1.md"
( reload_completed && CONST_INT_P (operands[2])
   && ((operands[1] != stack_pointer_rtx
        && (INTVAL (operands[2]) > 255 || INTVAL (operands[2]) < -255))
       || (operands[1] == stack_pointer_rtx
 	   && INTVAL (operands[2]) > 1020))))
    : -1 },
#line 1295 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math",
    __builtin_constant_p 
#line 1295 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math)
    ? (int) 
#line 1295 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math)
    : -1 },
#line 1038 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_ARM && XVECLEN (operands[0], 0) == 2",
    __builtin_constant_p 
#line 1038 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 2)
    ? (int) 
#line 1038 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 2)
    : -1 },
#line 565 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT &&\n\
   !(const_ok_for_arm (INTVAL (operands[2]))\n\
     || const_ok_for_arm (-INTVAL (operands[2])))\n\
    && const_ok_for_arm (~INTVAL (operands[2]))",
    __builtin_constant_p 
#line 565 "../../gcc/config/arm/arm.md"
(TARGET_32BIT &&
   !(const_ok_for_arm (INTVAL (operands[2]))
     || const_ok_for_arm (-INTVAL (operands[2])))
    && const_ok_for_arm (~INTVAL (operands[2])))
    ? (int) 
#line 565 "../../gcc/config/arm/arm.md"
(TARGET_32BIT &&
   !(const_ok_for_arm (INTVAL (operands[2]))
     || const_ok_for_arm (-INTVAL (operands[2])))
    && const_ok_for_arm (~INTVAL (operands[2])))
    : -1 },
#line 1011 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !TARGET_NEON",
    __builtin_constant_p 
#line 1011 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_NEON)
    ? (int) 
#line 1011 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !TARGET_NEON)
    : -1 },
#line 1068 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && arm_arch6",
    __builtin_constant_p 
#line 1068 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_arch6)
    ? (int) 
#line 1068 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_arch6)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1295 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1295 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_VFP3 && !flag_rounding_math))
    : -1 },
#line 11040 "../../gcc/config/arm/arm.md"
  { "TARGET_THUMB",
    __builtin_constant_p 
#line 11040 "../../gcc/config/arm/arm.md"
(TARGET_THUMB)
    ? (int) 
#line 11040 "../../gcc/config/arm/arm.md"
(TARGET_THUMB)
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2DImode)))
    : -1 },
#line 543 "../../gcc/config/arm/vfp.md"
  { "TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE",
    __builtin_constant_p 
#line 543 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE)
    ? (int) 
#line 543 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP_DOUBLE)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 451 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXBH && TARGET_HAVE_MEMORY_BARRIER))
    : -1 },
  { "(TARGET_THUMB2 && arm_restrict_it) && ( reload_completed)",
    __builtin_constant_p (
#line 788 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_restrict_it) && 
#line 790 "../../gcc/config/arm/thumb2.md"
( reload_completed))
    ? (int) (
#line 788 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_restrict_it) && 
#line 790 "../../gcc/config/arm/thumb2.md"
( reload_completed))
    : -1 },
  { "(TARGET_THUMB2) && ( reload_completed)",
    __builtin_constant_p (
#line 212 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2) && 
#line 217 "../../gcc/config/arm/thumb2.md"
( reload_completed))
    ? (int) (
#line 212 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2) && 
#line 217 "../../gcc/config/arm/thumb2.md"
( reload_completed))
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V2SFmode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V2SFmode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V2SFmode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
#line 11320 "../../gcc/config/arm/arm.md"
  { "TARGET_CRC32",
    __builtin_constant_p 
#line 11320 "../../gcc/config/arm/arm.md"
(TARGET_CRC32)
    ? (int) 
#line 11320 "../../gcc/config/arm/arm.md"
(TARGET_CRC32)
    : -1 },
#line 266 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && (reload_in_progress || reload_completed)",
    __builtin_constant_p 
#line 266 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && (reload_in_progress || reload_completed))
    ? (int) 
#line 266 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && (reload_in_progress || reload_completed))
    : -1 },
#line 1597 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && (!false || flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 1597 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!false || flag_unsafe_math_optimizations))
    ? (int) 
#line 1597 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!false || flag_unsafe_math_optimizations))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && !arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1396 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1396 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_arch6))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[1], operands[2],\n\
                                  operands[0], 0, false, false)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11290 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], 0, false, false))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11290 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[1], operands[2],
                                  operands[0], 0, false, false))))
    : -1 },
#line 6633 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && TARGET_SOFT_FLOAT\n\
   && (!MEM_P (operands[0])\n\
       || register_operand (operands[1], SFmode))",
    __builtin_constant_p 
#line 6633 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_SOFT_FLOAT
   && (!MEM_P (operands[0])
       || register_operand (operands[1], SFmode)))
    ? (int) 
#line 6633 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && TARGET_SOFT_FLOAT
   && (!MEM_P (operands[0])
       || register_operand (operands[1], SFmode)))
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && XVECLEN (operands[0], 0) == 3)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1051 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 3))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1051 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 3))
    : -1 },
#line 5325 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && arm_arch4 && !arm_arch6",
    __builtin_constant_p 
#line 5325 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4 && !arm_arch6)
    ? (int) 
#line 5325 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4 && !arm_arch6)
    : -1 },
#line 5548 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && reload_completed\n\
   && arm_const_double_by_parts (operands[1])",
    __builtin_constant_p 
#line 5548 "../../gcc/config/arm/arm.md"
(TARGET_ARM && reload_completed
   && arm_const_double_by_parts (operands[1]))
    ? (int) 
#line 5548 "../../gcc/config/arm/arm.md"
(TARGET_ARM && reload_completed
   && arm_const_double_by_parts (operands[1]))
    : -1 },
#line 1228 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
   && peep2_reg_dead_p (1, operands[1])\n\
   && satisfies_constraint_Pw (operands[2])",
    __builtin_constant_p 
#line 1228 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && peep2_reg_dead_p (1, operands[1])
   && satisfies_constraint_Pw (operands[2]))
    ? (int) 
#line 1228 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && peep2_reg_dead_p (1, operands[1])
   && satisfies_constraint_Pw (operands[2]))
    : -1 },
#line 8331 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && GET_CODE (operands[2]) != MULT",
    __builtin_constant_p 
#line 8331 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && GET_CODE (operands[2]) != MULT)
    ? (int) 
#line 8331 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && GET_CODE (operands[2]) != MULT)
    : -1 },
#line 2232 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !(GET_MODE_CLASS (V2SImode) == MODE_VECTOR_FLOAT\n\
                    && !flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V2SImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    ? (int) 
#line 2232 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !(GET_MODE_CLASS (V2SImode) == MODE_VECTOR_FLOAT
                    && !flag_unsafe_math_optimizations))
    : -1 },
#line 7942 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM   && USE_RETURN_INSN (TRUE)",
    __builtin_constant_p 
#line 7942 "../../gcc/config/arm/arm.md"
(TARGET_ARM   && USE_RETURN_INSN (TRUE))
    ? (int) 
#line 7942 "../../gcc/config/arm/arm.md"
(TARGET_ARM   && USE_RETURN_INSN (TRUE))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V8HImode)\n\
       || register_operand (operands[1], V8HImode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8HImode)
       || register_operand (operands[1], V8HImode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V8HImode)
       || register_operand (operands[1], V8HImode)))
    : -1 },
#line 5564 "../../gcc/config/arm/arm.md"
  { "TARGET_EITHER && reload_completed",
    __builtin_constant_p 
#line 5564 "../../gcc/config/arm/arm.md"
(TARGET_EITHER && reload_completed)
    ? (int) 
#line 5564 "../../gcc/config/arm/arm.md"
(TARGET_EITHER && reload_completed)
    : -1 },
#line 1763 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1",
    __builtin_constant_p 
#line 1763 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1)
    ? (int) 
#line 1763 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1)
    : -1 },
#line 217 "../../gcc/config/arm/iwmmxt.md"
  { "TARGET_REALLY_IWMMXT\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 217 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    ? (int) 
#line 217 "../../gcc/config/arm/iwmmxt.md"
(TARGET_REALLY_IWMMXT
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_DSP_MULTIPLY)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1870 "../../gcc/config/arm/arm.md"
(TARGET_DSP_MULTIPLY))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1870 "../../gcc/config/arm/arm.md"
(TARGET_DSP_MULTIPLY))
    : -1 },
#line 271 "../../gcc/config/arm/vfp.md"
  { "TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16 && !TARGET_NEON_FP16\n\
   && (   s_register_operand (operands[0], HFmode)\n\
       || s_register_operand (operands[1], HFmode))",
    __builtin_constant_p 
#line 271 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16 && !TARGET_NEON_FP16
   && (   s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    ? (int) 
#line 271 "../../gcc/config/arm/vfp.md"
(TARGET_32BIT && TARGET_HARD_FLOAT && TARGET_FP16 && !TARGET_NEON_FP16
   && (   s_register_operand (operands[0], HFmode)
       || s_register_operand (operands[1], HFmode)))
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V8HImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V8HImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8HImode != V2SFmode && V8HImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V8HImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && adjacent_mem_locations (operands[2], operands[3]))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10086 "../../gcc/config/arm/arm.md"
(TARGET_ARM && adjacent_mem_locations (operands[2], operands[3])))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 10086 "../../gcc/config/arm/arm.md"
(TARGET_ARM && adjacent_mem_locations (operands[2], operands[3])))
    : -1 },
#line 5058 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && !arm_arch6",
    __builtin_constant_p 
#line 5058 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch6)
    ? (int) 
#line 5058 "../../gcc/config/arm/arm.md"
(TARGET_ARM && !arm_arch6)
    : -1 },
#line 1342 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && optimize_size",
    __builtin_constant_p 
#line 1342 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size)
    ? (int) 
#line 1342 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && optimize_size)
    : -1 },
  { "(TARGET_ARM) && ( reload_completed)",
    __builtin_constant_p (
#line 4624 "../../gcc/config/arm/arm.md"
(TARGET_ARM) && 
#line 4626 "../../gcc/config/arm/arm.md"
( reload_completed))
    ? (int) (
#line 4624 "../../gcc/config/arm/arm.md"
(TARGET_ARM) && 
#line 4626 "../../gcc/config/arm/arm.md"
( reload_completed))
    : -1 },
#line 1597 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && (!true || flag_unsafe_math_optimizations)",
    __builtin_constant_p 
#line 1597 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!true || flag_unsafe_math_optimizations))
    ? (int) 
#line 1597 "../../gcc/config/arm/neon.md"
(TARGET_NEON && (!true || flag_unsafe_math_optimizations))
    : -1 },
#line 10086 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && adjacent_mem_locations (operands[2], operands[3])",
    __builtin_constant_p 
#line 10086 "../../gcc/config/arm/arm.md"
(TARGET_ARM && adjacent_mem_locations (operands[2], operands[3]))
    ? (int) 
#line 10086 "../../gcc/config/arm/arm.md"
(TARGET_ARM && adjacent_mem_locations (operands[2], operands[3]))
    : -1 },
#line 3549 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && optimize_function_for_size_p (cfun) && !arm_restrict_it",
    __builtin_constant_p 
#line 3549 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && optimize_function_for_size_p (cfun) && !arm_restrict_it)
    ? (int) 
#line 3549 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && optimize_function_for_size_p (cfun) && !arm_restrict_it)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_HAVE_LDACQ)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 494 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 494 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDACQ))
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V2SImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V2SImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V2SImode != V2SFmode && V2SImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V2SImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))\n\
     && (operands_ok_ldrd_strd (operands[2], operands[4],\n\
                                  operands[0], INTVAL (operands[1]),\n\
                                  false, false)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11273 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))
     && (operands_ok_ldrd_strd (operands[2], operands[4],
                                  operands[0], INTVAL (operands[1]),
                                  false, false))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11273 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && ((INTVAL (operands[1]) + 4) == INTVAL (operands[3]))
     && (operands_ok_ldrd_strd (operands[2], operands[4],
                                  operands[0], INTVAL (operands[1]),
                                  false, false))))
    : -1 },
#line 4343 "../../gcc/config/arm/arm.md"
  { "TARGET_IDIV",
    __builtin_constant_p 
#line 4343 "../../gcc/config/arm/arm.md"
(TARGET_IDIV)
    ? (int) 
#line 4343 "../../gcc/config/arm/arm.md"
(TARGET_IDIV)
    : -1 },
#line 27 "../../gcc/config/arm/vfp.md"
  { "TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT\n\
   && (   s_register_operand (operands[0], SImode)\n\
       || s_register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 27 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode)))
    ? (int) 
#line 27 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_VFP && TARGET_HARD_FLOAT
   && (   s_register_operand (operands[0], SImode)
       || s_register_operand (operands[1], SImode)))
    : -1 },
#line 1982 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && operands[0] != operands[1] && reload_completed",
    __builtin_constant_p 
#line 1982 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && operands[0] != operands[1] && reload_completed)
    ? (int) 
#line 1982 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && operands[0] != operands[1] && reload_completed)
    : -1 },
#line 429 "../../gcc/config/arm/sync.md"
  { "TARGET_HAVE_LDREXD",
    __builtin_constant_p 
#line 429 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD)
    ? (int) 
#line 429 "../../gcc/config/arm/sync.md"
(TARGET_HAVE_LDREXD)
    : -1 },
#line 462 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && reload_completed\n\
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0])))",
    __builtin_constant_p 
#line 462 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0]))))
    ? (int) 
#line 462 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && reload_completed
   && ! (TARGET_NEON && IS_VFP_REGNUM (REGNO (operands[0]))))
    : -1 },
#line 76 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V16QImode)\n\
       || register_operand (operands[1], V16QImode))",
    __builtin_constant_p 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V16QImode)
       || register_operand (operands[1], V16QImode)))
    ? (int) 
#line 76 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V16QImode)
       || register_operand (operands[1], V16QImode)))
    : -1 },
#line 1684 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && GET_CODE (operands[1]) == SYMBOL_REF\n\
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1]))",
    __builtin_constant_p 
#line 1684 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (operands[1]) == SYMBOL_REF
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1])))
    ? (int) 
#line 1684 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (operands[1]) == SYMBOL_REF
   && !arm_is_long_call_p (SYMBOL_REF_DECL (operands[1])))
    : -1 },
#line 399 "../../gcc/config/arm/vfp.md"
  { "TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 399 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    ? (int) 
#line 399 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    : -1 },
#line 7942 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM   && use_simple_return_p ()",
    __builtin_constant_p 
#line 7942 "../../gcc/config/arm/arm.md"
(TARGET_ARM   && use_simple_return_p ())
    ? (int) 
#line 7942 "../../gcc/config/arm/arm.md"
(TARGET_ARM   && use_simple_return_p ())
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5338 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5338 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch6))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && (reload_in_progress || reload_completed))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 266 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && (reload_in_progress || reload_completed)))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 266 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && (reload_in_progress || reload_completed)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[0], operands[2],\n\
                                  operands[1], -4, false, true)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11257 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], -4, false, true))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11257 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], -4, false, true))))
    : -1 },
#line 1581 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2\n\
   && (INTVAL (operands[2]) > 0 && INTVAL (operands[2]) < 32)\n\
   && peep2_reg_dead_p (2, operands[0])",
    __builtin_constant_p 
#line 1581 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && (INTVAL (operands[2]) > 0 && INTVAL (operands[2]) < 32)
   && peep2_reg_dead_p (2, operands[0]))
    ? (int) 
#line 1581 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2
   && (INTVAL (operands[2]) > 0 && INTVAL (operands[2]) < 32)
   && peep2_reg_dead_p (2, operands[0]))
    : -1 },
#line 5315 "../../gcc/config/arm/arm.md"
  { "!arm_arch6",
    __builtin_constant_p 
#line 5315 "../../gcc/config/arm/arm.md"
(!arm_arch6)
    ? (int) 
#line 5315 "../../gcc/config/arm/arm.md"
(!arm_arch6)
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V2SImode)))
    : -1 },
#line 788 "../../gcc/config/arm/thumb2.md"
  { "TARGET_THUMB2 && arm_restrict_it",
    __builtin_constant_p 
#line 788 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_restrict_it)
    ? (int) 
#line 788 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && arm_restrict_it)
    : -1 },
#line 11257 "../../gcc/config/arm/arm.md"
  { "TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[0], operands[2],\n\
                                  operands[1], -4, false, true))",
    __builtin_constant_p 
#line 11257 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], -4, false, true)))
    ? (int) 
#line 11257 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], -4, false, true)))
    : -1 },
#line 5492 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && !(TARGET_HARD_FLOAT && TARGET_VFP)\n\
   && !TARGET_IWMMXT\n\
   && (   register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 5492 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && !TARGET_IWMMXT
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 5492 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && !TARGET_IWMMXT
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
#line 5103 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && (!MEM_P (operands[1])) && BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 5103 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (!MEM_P (operands[1])) && BYTES_BIG_ENDIAN)
    ? (int) 
#line 5103 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && (!MEM_P (operands[1])) && BYTES_BIG_ENDIAN)
    : -1 },
#line 1051 "../../gcc/config/arm/ldmstm.md"
  { "TARGET_ARM && XVECLEN (operands[0], 0) == 3",
    __builtin_constant_p 
#line 1051 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 3)
    ? (int) 
#line 1051 "../../gcc/config/arm/ldmstm.md"
(TARGET_ARM && XVECLEN (operands[0], 0) == 3)
    : -1 },
  { "(TARGET_ARM) && ( reload_completed\n\
   && REGNO (operands [0]) != REGNO (operands[3]))",
    __builtin_constant_p (
#line 8475 "../../gcc/config/arm/arm.md"
(TARGET_ARM) && 
#line 8479 "../../gcc/config/arm/arm.md"
( reload_completed
   && REGNO (operands [0]) != REGNO (operands[3])))
    ? (int) (
#line 8475 "../../gcc/config/arm/arm.md"
(TARGET_ARM) && 
#line 8479 "../../gcc/config/arm/arm.md"
( reload_completed
   && REGNO (operands [0]) != REGNO (operands[3])))
    : -1 },
#line 5575 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && !BYTES_BIG_ENDIAN",
    __builtin_constant_p 
#line 5575 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !BYTES_BIG_ENDIAN)
    ? (int) 
#line 5575 "../../gcc/config/arm/neon.md"
(TARGET_NEON && !BYTES_BIG_ENDIAN)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && arm_arch3m && !arm_arch6)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1704 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch3m && !arm_arch6))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1704 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch3m && !arm_arch6))
    : -1 },
#line 2409 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON && TARGET_FPU_ARMV8",
    __builtin_constant_p 
#line 2409 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FPU_ARMV8)
    ? (int) 
#line 2409 "../../gcc/config/arm/neon.md"
(TARGET_NEON && TARGET_FPU_ARMV8)
    : -1 },
#line 545 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && GET_CODE (XEXP (operands[4], 0)) == PLUS\n\
   && rtx_equal_p (operands[0], XEXP (XEXP (operands[4], 0), 0))\n\
   && rtx_equal_p (operands[2], XEXP (XEXP (operands[4], 0), 1))\n\
   && (peep2_reg_dead_p (3, operands[0])\n\
       || rtx_equal_p (operands[0], operands[3]))\n\
   && (peep2_reg_dead_p (3, operands[2])\n\
       || rtx_equal_p (operands[2], operands[3]))",
    __builtin_constant_p 
#line 545 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (XEXP (operands[4], 0)) == PLUS
   && rtx_equal_p (operands[0], XEXP (XEXP (operands[4], 0), 0))
   && rtx_equal_p (operands[2], XEXP (XEXP (operands[4], 0), 1))
   && (peep2_reg_dead_p (3, operands[0])
       || rtx_equal_p (operands[0], operands[3]))
   && (peep2_reg_dead_p (3, operands[2])
       || rtx_equal_p (operands[2], operands[3])))
    ? (int) 
#line 545 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && GET_CODE (XEXP (operands[4], 0)) == PLUS
   && rtx_equal_p (operands[0], XEXP (XEXP (operands[4], 0), 0))
   && rtx_equal_p (operands[2], XEXP (XEXP (operands[4], 0), 1))
   && (peep2_reg_dead_p (3, operands[0])
       || rtx_equal_p (operands[0], operands[3]))
   && (peep2_reg_dead_p (3, operands[2])
       || rtx_equal_p (operands[2], operands[3])))
    : -1 },
#line 6618 "../../gcc/config/arm/arm.md"
  { "TARGET_EITHER\n\
   && reload_completed\n\
   && CONST_DOUBLE_P (operands[1])",
    __builtin_constant_p 
#line 6618 "../../gcc/config/arm/arm.md"
(TARGET_EITHER
   && reload_completed
   && CONST_DOUBLE_P (operands[1]))
    ? (int) 
#line 6618 "../../gcc/config/arm/arm.md"
(TARGET_EITHER
   && reload_completed
   && CONST_DOUBLE_P (operands[1]))
    : -1 },
#line 97 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode))",
    __builtin_constant_p 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode)))
    ? (int) 
#line 97 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V8QImode != V2SFmode && V8QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V8QImode)))
    : -1 },
#line 662 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && reload_completed && !satisfies_constraint_J (operands[1])",
    __builtin_constant_p 
#line 662 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && reload_completed && !satisfies_constraint_J (operands[1]))
    ? (int) 
#line 662 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && reload_completed && !satisfies_constraint_J (operands[1]))
    : -1 },
#line 8660 "../../gcc/config/arm/arm.md"
  { "arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM)\n\
  && !(TARGET_THUMB2 && optimize_insn_for_size_p ())",
    __builtin_constant_p 
#line 8660 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM)
  && !(TARGET_THUMB2 && optimize_insn_for_size_p ()))
    ? (int) 
#line 8660 "../../gcc/config/arm/arm.md"
(arm_arch5 && TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM)
  && !(TARGET_THUMB2 && optimize_insn_for_size_p ()))
    : -1 },
#line 3346 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
   && GET_CODE (operands[1]) == GET_CODE (operands[9])\n\
   && INTVAL (operands[3]) == 32 - INTVAL (operands[6])",
    __builtin_constant_p 
#line 3346 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && GET_CODE (operands[1]) == GET_CODE (operands[9])
   && INTVAL (operands[3]) == 32 - INTVAL (operands[6]))
    ? (int) 
#line 3346 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && GET_CODE (operands[1]) == GET_CODE (operands[9])
   && INTVAL (operands[3]) == 32 - INTVAL (operands[6]))
    : -1 },
#line 187 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_32BIT && arm_arch3m",
    __builtin_constant_p 
#line 187 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch3m)
    ? (int) 
#line 187 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && arm_arch3m)
    : -1 },
#line 1638 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1 && arm_arch5",
    __builtin_constant_p 
#line 1638 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch5)
    ? (int) 
#line 1638 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1 && arm_arch5)
    : -1 },
#line 31 "../../gcc/config/arm/neon.md"
  { "TARGET_NEON\n\
   && (register_operand (operands[0], V2SFmode)\n\
       || register_operand (operands[1], V2SFmode))",
    __builtin_constant_p 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2SFmode)
       || register_operand (operands[1], V2SFmode)))
    ? (int) 
#line 31 "../../gcc/config/arm/neon.md"
(TARGET_NEON
   && (register_operand (operands[0], V2SFmode)
       || register_operand (operands[1], V2SFmode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_32BIT && XVECLEN (operands[0], 0) == 3)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1106 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 3))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1106 "../../gcc/config/arm/ldmstm.md"
(TARGET_32BIT && XVECLEN (operands[0], 0) == 3))
    : -1 },
  { "(flag_pic) && ( reload_completed)",
    __builtin_constant_p (
#line 5849 "../../gcc/config/arm/arm.md"
(flag_pic) && 
#line 5851 "../../gcc/config/arm/arm.md"
( reload_completed))
    ? (int) (
#line 5849 "../../gcc/config/arm/arm.md"
(flag_pic) && 
#line 5851 "../../gcc/config/arm/arm.md"
( reload_completed))
    : -1 },
#line 365 "../../gcc/config/arm/arm-fixed.md"
  { "TARGET_32BIT && TARGET_DSP_MULTIPLY && arm_arch6",
    __builtin_constant_p 
#line 365 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && TARGET_DSP_MULTIPLY && arm_arch6)
    ? (int) 
#line 365 "../../gcc/config/arm/arm-fixed.md"
(TARGET_32BIT && TARGET_DSP_MULTIPLY && arm_arch6)
    : -1 },
#line 595 "../../gcc/config/arm/thumb1.md"
  { "TARGET_THUMB1\n\
   && (   register_operand (operands[0], DImode)\n\
       || register_operand (operands[1], DImode))",
    __builtin_constant_p 
#line 595 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    ? (int) 
#line 595 "../../gcc/config/arm/thumb1.md"
(TARGET_THUMB1
   && (   register_operand (operands[0], DImode)
       || register_operand (operands[1], DImode)))
    : -1 },
#line 68 "../../gcc/config/arm/vec-common.md"
  { "(TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)\n\
		    || flag_unsafe_math_optimizations))\n\
   || (V16QImode == V4HImode && TARGET_REALLY_IWMMXT)",
    __builtin_constant_p 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V16QImode == V4HImode && TARGET_REALLY_IWMMXT))
    ? (int) 
#line 68 "../../gcc/config/arm/vec-common.md"
((TARGET_NEON && ((V16QImode != V2SFmode && V16QImode != V4SFmode)
		    || flag_unsafe_math_optimizations))
   || (V16QImode == V4HImode && TARGET_REALLY_IWMMXT))
    : -1 },
#line 7921 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && USE_RETURN_INSN (FALSE)",
    __builtin_constant_p 
#line 7921 "../../gcc/config/arm/arm.md"
(TARGET_ARM && USE_RETURN_INSN (FALSE))
    ? (int) 
#line 7921 "../../gcc/config/arm/arm.md"
(TARGET_ARM && USE_RETURN_INSN (FALSE))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_LDRD && TARGET_THUMB2 && reload_completed\n\
     && current_tune->prefer_ldrd_strd\n\
     && (operands_ok_ldrd_strd (operands[0], operands[2],\n\
                                  operands[1], 0, false, true)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11242 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], 0, false, true))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 11242 "../../gcc/config/arm/arm.md"
(TARGET_LDRD && TARGET_THUMB2 && reload_completed
     && current_tune->prefer_ldrd_strd
     && (operands_ok_ldrd_strd (operands[0], operands[2],
                                  operands[1], 0, false, true))))
    : -1 },
#line 1396 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && !arm_arch6",
    __builtin_constant_p 
#line 1396 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_arch6)
    ? (int) 
#line 1396 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && !arm_arch6)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_THUMB2 && reload_completed\n\
   && GET_CODE(operands[3]) != PLUS\n\
   && GET_CODE(operands[3]) != MINUS)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1145 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && GET_CODE(operands[3]) != PLUS
   && GET_CODE(operands[3]) != MINUS))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 1145 "../../gcc/config/arm/thumb2.md"
(TARGET_THUMB2 && reload_completed
   && GET_CODE(operands[3]) != PLUS
   && GET_CODE(operands[3]) != MINUS))
    : -1 },
#line 5705 "../../gcc/config/arm/arm.md"
  { "arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2])",
    __builtin_constant_p 
#line 5705 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2]))
    ? (int) 
#line 5705 "../../gcc/config/arm/arm.md"
(arm_arch_thumb2 && arm_valid_symbolic_address_p (operands[2]))
    : -1 },
#line 5716 "../../gcc/config/arm/arm.md"
  { "TARGET_ARM && ! TARGET_IWMMXT\n\
   && !(TARGET_HARD_FLOAT && TARGET_VFP)\n\
   && (   register_operand (operands[0], SImode)\n\
       || register_operand (operands[1], SImode))",
    __builtin_constant_p 
#line 5716 "../../gcc/config/arm/arm.md"
(TARGET_ARM && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    ? (int) 
#line 5716 "../../gcc/config/arm/arm.md"
(TARGET_ARM && ! TARGET_IWMMXT
   && !(TARGET_HARD_FLOAT && TARGET_VFP)
   && (   register_operand (operands[0], SImode)
       || register_operand (operands[1], SImode)))
    : -1 },
#line 5736 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT\n\
  && (!(const_ok_for_arm (INTVAL (operands[1]))\n\
        || const_ok_for_arm (~INTVAL (operands[1]))))",
    __builtin_constant_p 
#line 5736 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (!(const_ok_for_arm (INTVAL (operands[1]))
        || const_ok_for_arm (~INTVAL (operands[1])))))
    ? (int) 
#line 5736 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
  && (!(const_ok_for_arm (INTVAL (operands[1]))
        || const_ok_for_arm (~INTVAL (operands[1])))))
    : -1 },
#line 117 "../../gcc/config/arm/vec-common.md"
  { "TARGET_NEON\n\
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode))",
    __builtin_constant_p 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode)))
    ? (int) 
#line 117 "../../gcc/config/arm/vec-common.md"
(TARGET_NEON
   || (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (V4SFmode)))
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && arm_arch4)",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5288 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 5288 "../../gcc/config/arm/arm.md"
(TARGET_ARM && arm_arch4))
    : -1 },
#line 6717 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && TARGET_SOFT_FLOAT\n\
   && (   register_operand (operands[0], DFmode)\n\
       || register_operand (operands[1], DFmode))",
    __builtin_constant_p 
#line 6717 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_SOFT_FLOAT
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    ? (int) 
#line 6717 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && TARGET_SOFT_FLOAT
   && (   register_operand (operands[0], DFmode)
       || register_operand (operands[1], DFmode)))
    : -1 },
#line 8681 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM)",
    __builtin_constant_p 
#line 8681 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM))
    ? (int) 
#line 8681 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && peep2_regno_dead_p (3, CC_REGNUM))
    : -1 },
#line 1704 "../../gcc/config/arm/arm.md"
  { "TARGET_32BIT && arm_arch3m && !arm_arch6",
    __builtin_constant_p 
#line 1704 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch3m && !arm_arch6)
    ? (int) 
#line 1704 "../../gcc/config/arm/arm.md"
(TARGET_32BIT && arm_arch3m && !arm_arch6)
    : -1 },
  { "(TARGET_32BIT\n\
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && (TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP\n\
   && (   s_register_operand (operands[0], SFmode)\n\
       || s_register_operand (operands[1], SFmode)))",
    __builtin_constant_p (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 324 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode))))
    ? (int) (
#line 10856 "../../gcc/config/arm/arm.md"
(TARGET_32BIT
   && (!TARGET_NO_VOLATILE_CE || !volatile_refs_p (PATTERN (insn)))) && 
#line 324 "../../gcc/config/arm/vfp.md"
(TARGET_ARM && TARGET_HARD_FLOAT && TARGET_VFP
   && (   s_register_operand (operands[0], SFmode)
       || s_register_operand (operands[1], SFmode))))
    : -1 },
#line 83 "../../gcc/config/arm/crypto.md"
  { "TARGET_CRYPTO",
    __builtin_constant_p 
#line 83 "../../gcc/config/arm/crypto.md"
(TARGET_CRYPTO)
    ? (int) 
#line 83 "../../gcc/config/arm/crypto.md"
(TARGET_CRYPTO)
    : -1 },
#line 199 "../../gcc/config/arm/ldrdstrd.md"
  { "TARGET_LDRD && TARGET_ARM\n\
   && current_tune->prefer_ldrd_strd\n\
   && !optimize_function_for_size_p (cfun)\n\
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))\n\
        ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))\n\
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))\n\
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4]))",
    __builtin_constant_p 
#line 199 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD && TARGET_ARM
   && current_tune->prefer_ldrd_strd
   && !optimize_function_for_size_p (cfun)
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))
        ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4])))
    ? (int) 
#line 199 "../../gcc/config/arm/ldrdstrd.md"
(TARGET_LDRD && TARGET_ARM
   && current_tune->prefer_ldrd_strd
   && !optimize_function_for_size_p (cfun)
   && (  ((rtx_equal_p(operands[0], operands[6])) && (rtx_equal_p(operands[1], operands[7])))
        ||((rtx_equal_p(operands[0], operands[7])) && (rtx_equal_p(operands[1], operands[6]))))
   && (peep2_reg_dead_p (3, operands[0]) || rtx_equal_p (operands[0], operands[4]))
   && (peep2_reg_dead_p (3, operands[1]) || rtx_equal_p (operands[1], operands[4])))
    : -1 },

};
#endif /* gcc >= 3.0.1 */

int
main(void)
{
  unsigned int i;
  const char *p;
  puts ("(define_conditions [");
#if GCC_VERSION >= 3001
  for (i = 0; i < ARRAY_SIZE (insn_conditions); i++)
    {
      printf ("  (%d \"", insn_conditions[i].value);
      for (p = insn_conditions[i].expr; *p; p++)
        {
          switch (*p)
	     {
	     case '\\':
	     case '\"': putchar ('\\'); break;
	     default: break;
	     }
          putchar (*p);
        }
      puts ("\")");
    }
#endif /* gcc >= 3.0.1 */
  puts ("])");
  fflush (stdout);
return ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE;
}
