/* Generated automatically by the program `genopinit'
   from the machine description file `md'.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "predict.h"
#include "tree.h"
#include "rtl.h"
#include "alias.h"
#include "varasm.h"
#include "stor-layout.h"
#include "calls.h"
#include "tm_p.h"
#include "flags.h"
#include "insn-config.h"
#include "expmed.h"
#include "dojump.h"
#include "explow.h"
#include "emit-rtl.h"
#include "stmt.h"
#include "expr.h"
#include "insn-codes.h"
#include "optabs.h"

struct optab_pat {
  unsigned scode;
  enum insn_code icode;
};

static const struct optab_pat pats[NUM_OPTAB_PATTERNS] = {
  { 0x011718, CODE_FOR_extendqihi2 },
  { 0x011719, CODE_FOR_extendqisi2 },
  { 0x01171a, CODE_FOR_extendqidi2 },
  { 0x011819, CODE_FOR_extendhisi2 },
  { 0x01181a, CODE_FOR_extendhidi2 },
  { 0x01191a, CODE_FOR_extendsidi2 },
  { 0x013233, CODE_FOR_extendhfsf2 },
  { 0x013234, CODE_FOR_extendhfdf2 },
  { 0x013334, CODE_FOR_extendsfdf2 },
  { 0x023332, CODE_FOR_truncsfhf2 },
  { 0x023432, CODE_FOR_truncdfhf2 },
  { 0x023433, CODE_FOR_truncdfsf2 },
  { 0x031719, CODE_FOR_zero_extendqisi2 },
  { 0x03171a, CODE_FOR_zero_extendqidi2 },
  { 0x031819, CODE_FOR_zero_extendhisi2 },
  { 0x03181a, CODE_FOR_zero_extendhidi2 },
  { 0x03191a, CODE_FOR_zero_extendsidi2 },
  { 0x061932, CODE_FOR_floatsihf2 },
  { 0x061933, CODE_FOR_floatsisf2 },
  { 0x061934, CODE_FOR_floatsidf2 },
  { 0x061a32, CODE_FOR_floatdihf2 },
  { 0x064854, CODE_FOR_floatv2siv2sf2 },
  { 0x064b56, CODE_FOR_floatv4siv4sf2 },
  { 0x071933, CODE_FOR_floatunssisf2 },
  { 0x071934, CODE_FOR_floatunssidf2 },
  { 0x074854, CODE_FOR_floatunsv2siv2sf2 },
  { 0x074b56, CODE_FOR_floatunsv4siv4sf2 },
  { 0x093319, CODE_FOR_lroundsfsi2 },
  { 0x093419, CODE_FOR_lrounddfsi2 },
  { 0x0a3319, CODE_FOR_lfloorsfsi2 },
  { 0x0a3419, CODE_FOR_lfloordfsi2 },
  { 0x0b3319, CODE_FOR_lceilsfsi2 },
  { 0x0b3419, CODE_FOR_lceildfsi2 },
  { 0x103219, CODE_FOR_fix_trunchfsi2 },
  { 0x10321a, CODE_FOR_fix_trunchfdi2 },
  { 0x103319, CODE_FOR_fix_truncsfsi2 },
  { 0x103419, CODE_FOR_fix_truncdfsi2 },
  { 0x105448, CODE_FOR_fix_truncv2sfv2si2 },
  { 0x10564b, CODE_FOR_fix_truncv4sfv4si2 },
  { 0x113319, CODE_FOR_fixuns_truncsfsi2 },
  { 0x113419, CODE_FOR_fixuns_truncdfsi2 },
  { 0x115448, CODE_FOR_fixuns_truncv2sfv2si2 },
  { 0x11564b, CODE_FOR_fixuns_truncv4sfv4si2 },
  { 0x121819, CODE_FOR_mulhisi3 },
  { 0x12191a, CODE_FOR_mulsidi3 },
  { 0x13191a, CODE_FOR_umulsidi3 },
  { 0x151819, CODE_FOR_maddhisi4 },
  { 0x15181a, CODE_FOR_maddhidi4 },
  { 0x15191a, CODE_FOR_maddsidi4 },
  { 0x16191a, CODE_FOR_umaddsidi4 },
  { 0x1d1a1a, CODE_FOR_vec_load_lanesdidi },
  { 0x1d1a1b, CODE_FOR_vec_load_lanestidi },
  { 0x1d1a1c, CODE_FOR_vec_load_laneseidi },
  { 0x1d1a1d, CODE_FOR_vec_load_lanesoidi },
  { 0x1d461b, CODE_FOR_vec_load_lanestiv8qi },
  { 0x1d461c, CODE_FOR_vec_load_laneseiv8qi },
  { 0x1d461d, CODE_FOR_vec_load_lanesoiv8qi },
  { 0x1d4646, CODE_FOR_vec_load_lanesv8qiv8qi },
  { 0x1d471b, CODE_FOR_vec_load_lanestiv4hi },
  { 0x1d471c, CODE_FOR_vec_load_laneseiv4hi },
  { 0x1d471d, CODE_FOR_vec_load_lanesoiv4hi },
  { 0x1d4747, CODE_FOR_vec_load_lanesv4hiv4hi },
  { 0x1d481b, CODE_FOR_vec_load_lanestiv2si },
  { 0x1d481c, CODE_FOR_vec_load_laneseiv2si },
  { 0x1d481d, CODE_FOR_vec_load_lanesoiv2si },
  { 0x1d4848, CODE_FOR_vec_load_lanesv2siv2si },
  { 0x1d491d, CODE_FOR_vec_load_lanesoiv16qi },
  { 0x1d491e, CODE_FOR_vec_load_lanesciv16qi },
  { 0x1d491f, CODE_FOR_vec_load_lanesxiv16qi },
  { 0x1d4949, CODE_FOR_vec_load_lanesv16qiv16qi },
  { 0x1d4a1d, CODE_FOR_vec_load_lanesoiv8hi },
  { 0x1d4a1e, CODE_FOR_vec_load_lanesciv8hi },
  { 0x1d4a1f, CODE_FOR_vec_load_lanesxiv8hi },
  { 0x1d4a4a, CODE_FOR_vec_load_lanesv8hiv8hi },
  { 0x1d4b1d, CODE_FOR_vec_load_lanesoiv4si },
  { 0x1d4b1e, CODE_FOR_vec_load_lanesciv4si },
  { 0x1d4b1f, CODE_FOR_vec_load_lanesxiv4si },
  { 0x1d4b4b, CODE_FOR_vec_load_lanesv4siv4si },
  { 0x1d4c4c, CODE_FOR_vec_load_lanesv2div2di },
  { 0x1d531b, CODE_FOR_vec_load_lanestiv4hf },
  { 0x1d531c, CODE_FOR_vec_load_laneseiv4hf },
  { 0x1d531d, CODE_FOR_vec_load_lanesoiv4hf },
  { 0x1d5353, CODE_FOR_vec_load_lanesv4hfv4hf },
  { 0x1d541b, CODE_FOR_vec_load_lanestiv2sf },
  { 0x1d541c, CODE_FOR_vec_load_laneseiv2sf },
  { 0x1d541d, CODE_FOR_vec_load_lanesoiv2sf },
  { 0x1d5454, CODE_FOR_vec_load_lanesv2sfv2sf },
  { 0x1d551d, CODE_FOR_vec_load_lanesoiv8hf },
  { 0x1d551e, CODE_FOR_vec_load_lanesciv8hf },
  { 0x1d551f, CODE_FOR_vec_load_lanesxiv8hf },
  { 0x1d5555, CODE_FOR_vec_load_lanesv8hfv8hf },
  { 0x1d561d, CODE_FOR_vec_load_lanesoiv4sf },
  { 0x1d561e, CODE_FOR_vec_load_lanesciv4sf },
  { 0x1d561f, CODE_FOR_vec_load_lanesxiv4sf },
  { 0x1d5656, CODE_FOR_vec_load_lanesv4sfv4sf },
  { 0x1e1a1a, CODE_FOR_vec_store_lanesdidi },
  { 0x1e1a1b, CODE_FOR_vec_store_lanestidi },
  { 0x1e1a1c, CODE_FOR_vec_store_laneseidi },
  { 0x1e1a1d, CODE_FOR_vec_store_lanesoidi },
  { 0x1e461b, CODE_FOR_vec_store_lanestiv8qi },
  { 0x1e461c, CODE_FOR_vec_store_laneseiv8qi },
  { 0x1e461d, CODE_FOR_vec_store_lanesoiv8qi },
  { 0x1e4646, CODE_FOR_vec_store_lanesv8qiv8qi },
  { 0x1e471b, CODE_FOR_vec_store_lanestiv4hi },
  { 0x1e471c, CODE_FOR_vec_store_laneseiv4hi },
  { 0x1e471d, CODE_FOR_vec_store_lanesoiv4hi },
  { 0x1e4747, CODE_FOR_vec_store_lanesv4hiv4hi },
  { 0x1e481b, CODE_FOR_vec_store_lanestiv2si },
  { 0x1e481c, CODE_FOR_vec_store_laneseiv2si },
  { 0x1e481d, CODE_FOR_vec_store_lanesoiv2si },
  { 0x1e4848, CODE_FOR_vec_store_lanesv2siv2si },
  { 0x1e491d, CODE_FOR_vec_store_lanesoiv16qi },
  { 0x1e491e, CODE_FOR_vec_store_lanesciv16qi },
  { 0x1e491f, CODE_FOR_vec_store_lanesxiv16qi },
  { 0x1e4949, CODE_FOR_vec_store_lanesv16qiv16qi },
  { 0x1e4a1d, CODE_FOR_vec_store_lanesoiv8hi },
  { 0x1e4a1e, CODE_FOR_vec_store_lanesciv8hi },
  { 0x1e4a1f, CODE_FOR_vec_store_lanesxiv8hi },
  { 0x1e4a4a, CODE_FOR_vec_store_lanesv8hiv8hi },
  { 0x1e4b1d, CODE_FOR_vec_store_lanesoiv4si },
  { 0x1e4b1e, CODE_FOR_vec_store_lanesciv4si },
  { 0x1e4b1f, CODE_FOR_vec_store_lanesxiv4si },
  { 0x1e4b4b, CODE_FOR_vec_store_lanesv4siv4si },
  { 0x1e4c4c, CODE_FOR_vec_store_lanesv2div2di },
  { 0x1e531b, CODE_FOR_vec_store_lanestiv4hf },
  { 0x1e531c, CODE_FOR_vec_store_laneseiv4hf },
  { 0x1e531d, CODE_FOR_vec_store_lanesoiv4hf },
  { 0x1e5353, CODE_FOR_vec_store_lanesv4hfv4hf },
  { 0x1e541b, CODE_FOR_vec_store_lanestiv2sf },
  { 0x1e541c, CODE_FOR_vec_store_laneseiv2sf },
  { 0x1e541d, CODE_FOR_vec_store_lanesoiv2sf },
  { 0x1e5454, CODE_FOR_vec_store_lanesv2sfv2sf },
  { 0x1e551d, CODE_FOR_vec_store_lanesoiv8hf },
  { 0x1e551e, CODE_FOR_vec_store_lanesciv8hf },
  { 0x1e551f, CODE_FOR_vec_store_lanesxiv8hf },
  { 0x1e5555, CODE_FOR_vec_store_lanesv8hfv8hf },
  { 0x1e561d, CODE_FOR_vec_store_lanesoiv4sf },
  { 0x1e561e, CODE_FOR_vec_store_lanesciv4sf },
  { 0x1e561f, CODE_FOR_vec_store_lanesxiv4sf },
  { 0x1e5656, CODE_FOR_vec_store_lanesv4sfv4sf },
  { 0x1f4646, CODE_FOR_vcondv8qiv8qi },
  { 0x1f4747, CODE_FOR_vcondv4hiv4hi },
  { 0x1f4848, CODE_FOR_vcondv2siv2si },
  { 0x1f4949, CODE_FOR_vcondv16qiv16qi },
  { 0x1f4a4a, CODE_FOR_vcondv8hiv8hi },
  { 0x1f4b4b, CODE_FOR_vcondv4siv4si },
  { 0x1f5454, CODE_FOR_vcondv2sfv2sf },
  { 0x1f5656, CODE_FOR_vcondv4sfv4sf },
  { 0x204646, CODE_FOR_vconduv8qiv8qi },
  { 0x204747, CODE_FOR_vconduv4hiv4hi },
  { 0x204848, CODE_FOR_vconduv2siv2si },
  { 0x204949, CODE_FOR_vconduv16qiv16qi },
  { 0x204a4a, CODE_FOR_vconduv8hiv8hi },
  { 0x204b4b, CODE_FOR_vconduv4siv4si },
  { 0x260019, CODE_FOR_addsi3 },
  { 0x26001a, CODE_FOR_adddi3 },
  { 0x260020, CODE_FOR_addqq3 },
  { 0x260021, CODE_FOR_addhq3 },
  { 0x260022, CODE_FOR_addsq3 },
  { 0x260025, CODE_FOR_adduqq3 },
  { 0x260026, CODE_FOR_adduhq3 },
  { 0x260027, CODE_FOR_addusq3 },
  { 0x26002a, CODE_FOR_addha3 },
  { 0x26002b, CODE_FOR_addsa3 },
  { 0x26002e, CODE_FOR_adduha3 },
  { 0x26002f, CODE_FOR_addusa3 },
  { 0x260033, CODE_FOR_addsf3 },
  { 0x260034, CODE_FOR_adddf3 },
  { 0x260046, CODE_FOR_addv8qi3 },
  { 0x260047, CODE_FOR_addv4hi3 },
  { 0x260048, CODE_FOR_addv2si3 },
  { 0x260049, CODE_FOR_addv16qi3 },
  { 0x26004a, CODE_FOR_addv8hi3 },
  { 0x26004b, CODE_FOR_addv4si3 },
  { 0x26004c, CODE_FOR_addv2di3 },
  { 0x26004d, CODE_FOR_addv4qq3 },
  { 0x26004e, CODE_FOR_addv2hq3 },
  { 0x260051, CODE_FOR_addv2ha3 },
  { 0x260054, CODE_FOR_addv2sf3 },
  { 0x260056, CODE_FOR_addv4sf3 },
  { 0x280020, CODE_FOR_ssaddqq3 },
  { 0x280021, CODE_FOR_ssaddhq3 },
  { 0x280022, CODE_FOR_ssaddsq3 },
  { 0x28002a, CODE_FOR_ssaddha3 },
  { 0x28002b, CODE_FOR_ssaddsa3 },
  { 0x28004d, CODE_FOR_ssaddv4qq3 },
  { 0x28004e, CODE_FOR_ssaddv2hq3 },
  { 0x280051, CODE_FOR_ssaddv2ha3 },
  { 0x290025, CODE_FOR_usadduqq3 },
  { 0x290026, CODE_FOR_usadduhq3 },
  { 0x29002e, CODE_FOR_usadduha3 },
  { 0x29004f, CODE_FOR_usaddv4uqq3 },
  { 0x290050, CODE_FOR_usaddv2uhq3 },
  { 0x290052, CODE_FOR_usaddv2uha3 },
  { 0x2a0019, CODE_FOR_subsi3 },
  { 0x2a001a, CODE_FOR_subdi3 },
  { 0x2a0020, CODE_FOR_subqq3 },
  { 0x2a0021, CODE_FOR_subhq3 },
  { 0x2a0022, CODE_FOR_subsq3 },
  { 0x2a0025, CODE_FOR_subuqq3 },
  { 0x2a0026, CODE_FOR_subuhq3 },
  { 0x2a0027, CODE_FOR_subusq3 },
  { 0x2a002a, CODE_FOR_subha3 },
  { 0x2a002b, CODE_FOR_subsa3 },
  { 0x2a002e, CODE_FOR_subuha3 },
  { 0x2a002f, CODE_FOR_subusa3 },
  { 0x2a0033, CODE_FOR_subsf3 },
  { 0x2a0034, CODE_FOR_subdf3 },
  { 0x2a0046, CODE_FOR_subv8qi3 },
  { 0x2a0047, CODE_FOR_subv4hi3 },
  { 0x2a0048, CODE_FOR_subv2si3 },
  { 0x2a0049, CODE_FOR_subv16qi3 },
  { 0x2a004a, CODE_FOR_subv8hi3 },
  { 0x2a004b, CODE_FOR_subv4si3 },
  { 0x2a004c, CODE_FOR_subv2di3 },
  { 0x2a004d, CODE_FOR_subv4qq3 },
  { 0x2a004e, CODE_FOR_subv2hq3 },
  { 0x2a0051, CODE_FOR_subv2ha3 },
  { 0x2a0054, CODE_FOR_subv2sf3 },
  { 0x2a0056, CODE_FOR_subv4sf3 },
  { 0x2c0020, CODE_FOR_sssubqq3 },
  { 0x2c0021, CODE_FOR_sssubhq3 },
  { 0x2c0022, CODE_FOR_sssubsq3 },
  { 0x2c002a, CODE_FOR_sssubha3 },
  { 0x2c002b, CODE_FOR_sssubsa3 },
  { 0x2c004d, CODE_FOR_sssubv4qq3 },
  { 0x2c004e, CODE_FOR_sssubv2hq3 },
  { 0x2c0051, CODE_FOR_sssubv2ha3 },
  { 0x2d0025, CODE_FOR_ussubuqq3 },
  { 0x2d0026, CODE_FOR_ussubuhq3 },
  { 0x2d002e, CODE_FOR_ussubuha3 },
  { 0x2d004f, CODE_FOR_ussubv4uqq3 },
  { 0x2d0050, CODE_FOR_ussubv2uhq3 },
  { 0x2d0052, CODE_FOR_ussubv2uha3 },
  { 0x2e0018, CODE_FOR_mulhi3 },
  { 0x2e0019, CODE_FOR_mulsi3 },
  { 0x2e0020, CODE_FOR_mulqq3 },
  { 0x2e0021, CODE_FOR_mulhq3 },
  { 0x2e0022, CODE_FOR_mulsq3 },
  { 0x2e002a, CODE_FOR_mulha3 },
  { 0x2e002b, CODE_FOR_mulsa3 },
  { 0x2e002e, CODE_FOR_muluha3 },
  { 0x2e002f, CODE_FOR_mulusa3 },
  { 0x2e0033, CODE_FOR_mulsf3 },
  { 0x2e0034, CODE_FOR_muldf3 },
  { 0x2e0046, CODE_FOR_mulv8qi3 },
  { 0x2e0047, CODE_FOR_mulv4hi3 },
  { 0x2e0048, CODE_FOR_mulv2si3 },
  { 0x2e0049, CODE_FOR_mulv16qi3 },
  { 0x2e004a, CODE_FOR_mulv8hi3 },
  { 0x2e004b, CODE_FOR_mulv4si3 },
  { 0x2e0054, CODE_FOR_mulv2sf3 },
  { 0x2e0056, CODE_FOR_mulv4sf3 },
  { 0x30002a, CODE_FOR_ssmulha3 },
  { 0x30002b, CODE_FOR_ssmulsa3 },
  { 0x31002e, CODE_FOR_usmuluha3 },
  { 0x31002f, CODE_FOR_usmulusa3 },
  { 0x320019, CODE_FOR_divsi3 },
  { 0x320033, CODE_FOR_divsf3 },
  { 0x320034, CODE_FOR_divdf3 },
  { 0x350019, CODE_FOR_udivsi3 },
  { 0x390019, CODE_FOR_modsi3 },
  { 0x3c0019, CODE_FOR_andsi3 },
  { 0x3c001a, CODE_FOR_anddi3 },
  { 0x3c0046, CODE_FOR_andv8qi3 },
  { 0x3c0047, CODE_FOR_andv4hi3 },
  { 0x3c0048, CODE_FOR_andv2si3 },
  { 0x3c0049, CODE_FOR_andv16qi3 },
  { 0x3c004a, CODE_FOR_andv8hi3 },
  { 0x3c004b, CODE_FOR_andv4si3 },
  { 0x3c004c, CODE_FOR_andv2di3 },
  { 0x3c0053, CODE_FOR_andv4hf3 },
  { 0x3c0054, CODE_FOR_andv2sf3 },
  { 0x3c0055, CODE_FOR_andv8hf3 },
  { 0x3c0056, CODE_FOR_andv4sf3 },
  { 0x3d0019, CODE_FOR_iorsi3 },
  { 0x3d001a, CODE_FOR_iordi3 },
  { 0x3d0046, CODE_FOR_iorv8qi3 },
  { 0x3d0047, CODE_FOR_iorv4hi3 },
  { 0x3d0048, CODE_FOR_iorv2si3 },
  { 0x3d0049, CODE_FOR_iorv16qi3 },
  { 0x3d004a, CODE_FOR_iorv8hi3 },
  { 0x3d004b, CODE_FOR_iorv4si3 },
  { 0x3d004c, CODE_FOR_iorv2di3 },
  { 0x3d0053, CODE_FOR_iorv4hf3 },
  { 0x3d0054, CODE_FOR_iorv2sf3 },
  { 0x3d0055, CODE_FOR_iorv8hf3 },
  { 0x3d0056, CODE_FOR_iorv4sf3 },
  { 0x3e0019, CODE_FOR_xorsi3 },
  { 0x3e001a, CODE_FOR_xordi3 },
  { 0x3e0046, CODE_FOR_xorv8qi3 },
  { 0x3e0047, CODE_FOR_xorv4hi3 },
  { 0x3e0048, CODE_FOR_xorv2si3 },
  { 0x3e0049, CODE_FOR_xorv16qi3 },
  { 0x3e004a, CODE_FOR_xorv8hi3 },
  { 0x3e004b, CODE_FOR_xorv4si3 },
  { 0x3e004c, CODE_FOR_xorv2di3 },
  { 0x3e0053, CODE_FOR_xorv4hf3 },
  { 0x3e0054, CODE_FOR_xorv2sf3 },
  { 0x3e0055, CODE_FOR_xorv8hf3 },
  { 0x3e0056, CODE_FOR_xorv4sf3 },
  { 0x3f0019, CODE_FOR_ashlsi3 },
  { 0x3f001a, CODE_FOR_ashldi3 },
  { 0x420019, CODE_FOR_ashrsi3 },
  { 0x42001a, CODE_FOR_ashrdi3 },
  { 0x430019, CODE_FOR_lshrsi3 },
  { 0x43001a, CODE_FOR_lshrdi3 },
  { 0x440019, CODE_FOR_rotlsi3 },
  { 0x450019, CODE_FOR_rotrsi3 },
  { 0x460046, CODE_FOR_vashlv8qi3 },
  { 0x460047, CODE_FOR_vashlv4hi3 },
  { 0x460048, CODE_FOR_vashlv2si3 },
  { 0x460049, CODE_FOR_vashlv16qi3 },
  { 0x46004a, CODE_FOR_vashlv8hi3 },
  { 0x46004b, CODE_FOR_vashlv4si3 },
  { 0x470046, CODE_FOR_vashrv8qi3 },
  { 0x470047, CODE_FOR_vashrv4hi3 },
  { 0x470048, CODE_FOR_vashrv2si3 },
  { 0x470049, CODE_FOR_vashrv16qi3 },
  { 0x47004a, CODE_FOR_vashrv8hi3 },
  { 0x47004b, CODE_FOR_vashrv4si3 },
  { 0x480046, CODE_FOR_vlshrv8qi3 },
  { 0x480047, CODE_FOR_vlshrv4hi3 },
  { 0x480048, CODE_FOR_vlshrv2si3 },
  { 0x480049, CODE_FOR_vlshrv16qi3 },
  { 0x48004a, CODE_FOR_vlshrv8hi3 },
  { 0x48004b, CODE_FOR_vlshrv4si3 },
  { 0x4b0019, CODE_FOR_sminsi3 },
  { 0x4b0033, CODE_FOR_sminsf3 },
  { 0x4b0034, CODE_FOR_smindf3 },
  { 0x4b0046, CODE_FOR_sminv8qi3 },
  { 0x4b0047, CODE_FOR_sminv4hi3 },
  { 0x4b0048, CODE_FOR_sminv2si3 },
  { 0x4b0049, CODE_FOR_sminv16qi3 },
  { 0x4b004a, CODE_FOR_sminv8hi3 },
  { 0x4b004b, CODE_FOR_sminv4si3 },
  { 0x4b0054, CODE_FOR_sminv2sf3 },
  { 0x4b0056, CODE_FOR_sminv4sf3 },
  { 0x4c0019, CODE_FOR_smaxsi3 },
  { 0x4c0033, CODE_FOR_smaxsf3 },
  { 0x4c0034, CODE_FOR_smaxdf3 },
  { 0x4c0046, CODE_FOR_smaxv8qi3 },
  { 0x4c0047, CODE_FOR_smaxv4hi3 },
  { 0x4c0048, CODE_FOR_smaxv2si3 },
  { 0x4c0049, CODE_FOR_smaxv16qi3 },
  { 0x4c004a, CODE_FOR_smaxv8hi3 },
  { 0x4c004b, CODE_FOR_smaxv4si3 },
  { 0x4c0054, CODE_FOR_smaxv2sf3 },
  { 0x4c0056, CODE_FOR_smaxv4sf3 },
  { 0x4d0019, CODE_FOR_uminsi3 },
  { 0x4d0046, CODE_FOR_uminv8qi3 },
  { 0x4d0047, CODE_FOR_uminv4hi3 },
  { 0x4d0048, CODE_FOR_uminv2si3 },
  { 0x4d0049, CODE_FOR_uminv16qi3 },
  { 0x4d004a, CODE_FOR_uminv8hi3 },
  { 0x4d004b, CODE_FOR_uminv4si3 },
  { 0x4e0019, CODE_FOR_umaxsi3 },
  { 0x4e0046, CODE_FOR_umaxv8qi3 },
  { 0x4e0047, CODE_FOR_umaxv4hi3 },
  { 0x4e0048, CODE_FOR_umaxv2si3 },
  { 0x4e0049, CODE_FOR_umaxv16qi3 },
  { 0x4e004a, CODE_FOR_umaxv8hi3 },
  { 0x4e004b, CODE_FOR_umaxv4si3 },
  { 0x4f0019, CODE_FOR_negsi2 },
  { 0x4f001a, CODE_FOR_negdi2 },
  { 0x4f0033, CODE_FOR_negsf2 },
  { 0x4f0034, CODE_FOR_negdf2 },
  { 0x4f0046, CODE_FOR_negv8qi2 },
  { 0x4f0047, CODE_FOR_negv4hi2 },
  { 0x4f0048, CODE_FOR_negv2si2 },
  { 0x4f0049, CODE_FOR_negv16qi2 },
  { 0x4f004a, CODE_FOR_negv8hi2 },
  { 0x4f004b, CODE_FOR_negv4si2 },
  { 0x4f0054, CODE_FOR_negv2sf2 },
  { 0x4f0056, CODE_FOR_negv4sf2 },
  { 0x530019, CODE_FOR_abssi2 },
  { 0x530033, CODE_FOR_abssf2 },
  { 0x530034, CODE_FOR_absdf2 },
  { 0x530046, CODE_FOR_absv8qi2 },
  { 0x530047, CODE_FOR_absv4hi2 },
  { 0x530048, CODE_FOR_absv2si2 },
  { 0x530049, CODE_FOR_absv16qi2 },
  { 0x53004a, CODE_FOR_absv8hi2 },
  { 0x53004b, CODE_FOR_absv4si2 },
  { 0x530054, CODE_FOR_absv2sf2 },
  { 0x530056, CODE_FOR_absv4sf2 },
  { 0x550019, CODE_FOR_one_cmplsi2 },
  { 0x55001a, CODE_FOR_one_cmpldi2 },
  { 0x550046, CODE_FOR_one_cmplv8qi2 },
  { 0x550047, CODE_FOR_one_cmplv4hi2 },
  { 0x550048, CODE_FOR_one_cmplv2si2 },
  { 0x550049, CODE_FOR_one_cmplv16qi2 },
  { 0x55004a, CODE_FOR_one_cmplv8hi2 },
  { 0x55004b, CODE_FOR_one_cmplv4si2 },
  { 0x55004c, CODE_FOR_one_cmplv2di2 },
  { 0x550053, CODE_FOR_one_cmplv4hf2 },
  { 0x550054, CODE_FOR_one_cmplv2sf2 },
  { 0x550055, CODE_FOR_one_cmplv8hf2 },
  { 0x550056, CODE_FOR_one_cmplv4sf2 },
  { 0x560018, CODE_FOR_bswaphi2 },
  { 0x560019, CODE_FOR_bswapsi2 },
  { 0x580019, CODE_FOR_clzsi2 },
  { 0x580046, CODE_FOR_clzv8qi2 },
  { 0x580047, CODE_FOR_clzv4hi2 },
  { 0x580048, CODE_FOR_clzv2si2 },
  { 0x580049, CODE_FOR_clzv16qi2 },
  { 0x58004a, CODE_FOR_clzv8hi2 },
  { 0x58004b, CODE_FOR_clzv4si2 },
  { 0x590019, CODE_FOR_ctzsi2 },
  { 0x5b0046, CODE_FOR_popcountv8qi2 },
  { 0x5b0049, CODE_FOR_popcountv16qi2 },
  { 0x670033, CODE_FOR_sqrtsf2 },
  { 0x670034, CODE_FOR_sqrtdf2 },
  { 0x760017, CODE_FOR_movqi },
  { 0x760018, CODE_FOR_movhi },
  { 0x760019, CODE_FOR_movsi },
  { 0x76001a, CODE_FOR_movdi },
  { 0x76001b, CODE_FOR_movti },
  { 0x76001c, CODE_FOR_movei },
  { 0x76001d, CODE_FOR_movoi },
  { 0x76001e, CODE_FOR_movci },
  { 0x76001f, CODE_FOR_movxi },
  { 0x760032, CODE_FOR_movhf },
  { 0x760033, CODE_FOR_movsf },
  { 0x760034, CODE_FOR_movdf },
  { 0x760046, CODE_FOR_movv8qi },
  { 0x760047, CODE_FOR_movv4hi },
  { 0x760048, CODE_FOR_movv2si },
  { 0x760049, CODE_FOR_movv16qi },
  { 0x76004a, CODE_FOR_movv8hi },
  { 0x76004b, CODE_FOR_movv4si },
  { 0x76004c, CODE_FOR_movv2di },
  { 0x760053, CODE_FOR_movv4hf },
  { 0x760054, CODE_FOR_movv2sf },
  { 0x760055, CODE_FOR_movv8hf },
  { 0x760056, CODE_FOR_movv4sf },
  { 0x780018, CODE_FOR_movmisalignhi },
  { 0x780019, CODE_FOR_movmisalignsi },
  { 0x78001a, CODE_FOR_movmisaligndi },
  { 0x780046, CODE_FOR_movmisalignv8qi },
  { 0x780047, CODE_FOR_movmisalignv4hi },
  { 0x780048, CODE_FOR_movmisalignv2si },
  { 0x780049, CODE_FOR_movmisalignv16qi },
  { 0x78004a, CODE_FOR_movmisalignv8hi },
  { 0x78004b, CODE_FOR_movmisalignv4si },
  { 0x78004c, CODE_FOR_movmisalignv2di },
  { 0x780053, CODE_FOR_movmisalignv4hf },
  { 0x780054, CODE_FOR_movmisalignv2sf },
  { 0x780055, CODE_FOR_movmisalignv8hf },
  { 0x780056, CODE_FOR_movmisalignv4sf },
  { 0x810018, CODE_FOR_reload_inhi },
  { 0x820018, CODE_FOR_reload_outhi },
  { 0x820034, CODE_FOR_reload_outdf },
  { 0x830017, CODE_FOR_cbranchqi4 },
  { 0x830019, CODE_FOR_cbranchsi4 },
  { 0x83001a, CODE_FOR_cbranchdi4 },
  { 0x830033, CODE_FOR_cbranchsf4 },
  { 0x830034, CODE_FOR_cbranchdf4 },
  { 0x870019, CODE_FOR_movsicc },
  { 0x870033, CODE_FOR_movsfcc },
  { 0x870034, CODE_FOR_movdfcc },
  { 0x890019, CODE_FOR_cstoresi4 },
  { 0x89001a, CODE_FOR_cstoredi4 },
  { 0x890033, CODE_FOR_cstoresf4 },
  { 0x890034, CODE_FOR_cstoredf4 },
  { 0x930019, CODE_FOR_smulsi3_highpart },
  { 0x930047, CODE_FOR_smulv4hi3_highpart },
  { 0x940019, CODE_FOR_umulsi3_highpart },
  { 0x940047, CODE_FOR_umulv4hi3_highpart },
  { 0x980017, CODE_FOR_movmemqi },
  { 0x990019, CODE_FOR_setmemsi },
  { 0x9b0033, CODE_FOR_fmasf4 },
  { 0x9b0034, CODE_FOR_fmadf4 },
  { 0x9b0054, CODE_FOR_fmav2sf4 },
  { 0x9b0056, CODE_FOR_fmav4sf4 },
  { 0x9f0033, CODE_FOR_rintsf2 },
  { 0x9f0034, CODE_FOR_rintdf2 },
  { 0xa00033, CODE_FOR_roundsf2 },
  { 0xa00034, CODE_FOR_rounddf2 },
  { 0xa10033, CODE_FOR_floorsf2 },
  { 0xa10034, CODE_FOR_floordf2 },
  { 0xa20033, CODE_FOR_ceilsf2 },
  { 0xa20034, CODE_FOR_ceildf2 },
  { 0xa30033, CODE_FOR_btruncsf2 },
  { 0xa30034, CODE_FOR_btruncdf2 },
  { 0xa40033, CODE_FOR_nearbyintsf2 },
  { 0xa40034, CODE_FOR_nearbyintdf2 },
  { 0xa90033, CODE_FOR_copysignsf3 },
  { 0xa90034, CODE_FOR_copysigndf3 },
  { 0xc10033, CODE_FOR_fmaxsf3 },
  { 0xc10034, CODE_FOR_fmaxdf3 },
  { 0xc10054, CODE_FOR_fmaxv2sf3 },
  { 0xc10056, CODE_FOR_fmaxv4sf3 },
  { 0xc20033, CODE_FOR_fminsf3 },
  { 0xc20034, CODE_FOR_fmindf3 },
  { 0xc20054, CODE_FOR_fminv2sf3 },
  { 0xc20056, CODE_FOR_fminv4sf3 },
  { 0xc30046, CODE_FOR_reduc_smax_scal_v8qi },
  { 0xc30047, CODE_FOR_reduc_smax_scal_v4hi },
  { 0xc30048, CODE_FOR_reduc_smax_scal_v2si },
  { 0xc30049, CODE_FOR_reduc_smax_scal_v16qi },
  { 0xc3004a, CODE_FOR_reduc_smax_scal_v8hi },
  { 0xc3004b, CODE_FOR_reduc_smax_scal_v4si },
  { 0xc30054, CODE_FOR_reduc_smax_scal_v2sf },
  { 0xc30056, CODE_FOR_reduc_smax_scal_v4sf },
  { 0xc40046, CODE_FOR_reduc_smin_scal_v8qi },
  { 0xc40047, CODE_FOR_reduc_smin_scal_v4hi },
  { 0xc40048, CODE_FOR_reduc_smin_scal_v2si },
  { 0xc40049, CODE_FOR_reduc_smin_scal_v16qi },
  { 0xc4004a, CODE_FOR_reduc_smin_scal_v8hi },
  { 0xc4004b, CODE_FOR_reduc_smin_scal_v4si },
  { 0xc40054, CODE_FOR_reduc_smin_scal_v2sf },
  { 0xc40056, CODE_FOR_reduc_smin_scal_v4sf },
  { 0xc50046, CODE_FOR_reduc_plus_scal_v8qi },
  { 0xc50047, CODE_FOR_reduc_plus_scal_v4hi },
  { 0xc50048, CODE_FOR_reduc_plus_scal_v2si },
  { 0xc50049, CODE_FOR_reduc_plus_scal_v16qi },
  { 0xc5004a, CODE_FOR_reduc_plus_scal_v8hi },
  { 0xc5004b, CODE_FOR_reduc_plus_scal_v4si },
  { 0xc5004c, CODE_FOR_reduc_plus_scal_v2di },
  { 0xc50054, CODE_FOR_reduc_plus_scal_v2sf },
  { 0xc50056, CODE_FOR_reduc_plus_scal_v4sf },
  { 0xc60046, CODE_FOR_reduc_umax_scal_v8qi },
  { 0xc60047, CODE_FOR_reduc_umax_scal_v4hi },
  { 0xc60048, CODE_FOR_reduc_umax_scal_v2si },
  { 0xc60049, CODE_FOR_reduc_umax_scal_v16qi },
  { 0xc6004a, CODE_FOR_reduc_umax_scal_v8hi },
  { 0xc6004b, CODE_FOR_reduc_umax_scal_v4si },
  { 0xc70046, CODE_FOR_reduc_umin_scal_v8qi },
  { 0xc70047, CODE_FOR_reduc_umin_scal_v4hi },
  { 0xc70048, CODE_FOR_reduc_umin_scal_v2si },
  { 0xc70049, CODE_FOR_reduc_umin_scal_v16qi },
  { 0xc7004a, CODE_FOR_reduc_umin_scal_v8hi },
  { 0xc7004b, CODE_FOR_reduc_umin_scal_v4si },
  { 0xc90046, CODE_FOR_widen_ssumv8qi3 },
  { 0xc90047, CODE_FOR_widen_ssumv4hi3 },
  { 0xc90048, CODE_FOR_widen_ssumv2si3 },
  { 0xcb0046, CODE_FOR_widen_usumv8qi3 },
  { 0xcb0047, CODE_FOR_widen_usumv4hi3 },
  { 0xcb0048, CODE_FOR_widen_usumv2si3 },
  { 0xce0046, CODE_FOR_vec_extractv8qi },
  { 0xce0047, CODE_FOR_vec_extractv4hi },
  { 0xce0048, CODE_FOR_vec_extractv2si },
  { 0xce0049, CODE_FOR_vec_extractv16qi },
  { 0xce004a, CODE_FOR_vec_extractv8hi },
  { 0xce004b, CODE_FOR_vec_extractv4si },
  { 0xce004c, CODE_FOR_vec_extractv2di },
  { 0xce0053, CODE_FOR_vec_extractv4hf },
  { 0xce0054, CODE_FOR_vec_extractv2sf },
  { 0xce0055, CODE_FOR_vec_extractv8hf },
  { 0xce0056, CODE_FOR_vec_extractv4sf },
  { 0xcf0046, CODE_FOR_vec_initv8qi },
  { 0xcf0047, CODE_FOR_vec_initv4hi },
  { 0xcf0048, CODE_FOR_vec_initv2si },
  { 0xcf0049, CODE_FOR_vec_initv16qi },
  { 0xcf004a, CODE_FOR_vec_initv8hi },
  { 0xcf004b, CODE_FOR_vec_initv4si },
  { 0xcf004c, CODE_FOR_vec_initv2di },
  { 0xcf0053, CODE_FOR_vec_initv4hf },
  { 0xcf0054, CODE_FOR_vec_initv2sf },
  { 0xcf0055, CODE_FOR_vec_initv8hf },
  { 0xcf0056, CODE_FOR_vec_initv4sf },
  { 0xd2001a, CODE_FOR_vec_pack_trunc_di },
  { 0xd20047, CODE_FOR_vec_pack_trunc_v4hi },
  { 0xd20048, CODE_FOR_vec_pack_trunc_v2si },
  { 0xd2004a, CODE_FOR_vec_pack_trunc_v8hi },
  { 0xd2004b, CODE_FOR_vec_pack_trunc_v4si },
  { 0xd2004c, CODE_FOR_vec_pack_trunc_v2di },
  { 0xd50046, CODE_FOR_vec_perm_constv8qi },
  { 0xd50047, CODE_FOR_vec_perm_constv4hi },
  { 0xd50048, CODE_FOR_vec_perm_constv2si },
  { 0xd50049, CODE_FOR_vec_perm_constv16qi },
  { 0xd5004a, CODE_FOR_vec_perm_constv8hi },
  { 0xd5004b, CODE_FOR_vec_perm_constv4si },
  { 0xd5004c, CODE_FOR_vec_perm_constv2di },
  { 0xd50054, CODE_FOR_vec_perm_constv2sf },
  { 0xd50056, CODE_FOR_vec_perm_constv4sf },
  { 0xd60046, CODE_FOR_vec_permv8qi },
  { 0xd60049, CODE_FOR_vec_permv16qi },
  { 0xd80046, CODE_FOR_vec_setv8qi },
  { 0xd80047, CODE_FOR_vec_setv4hi },
  { 0xd80048, CODE_FOR_vec_setv2si },
  { 0xd80049, CODE_FOR_vec_setv16qi },
  { 0xd8004a, CODE_FOR_vec_setv8hi },
  { 0xd8004b, CODE_FOR_vec_setv4si },
  { 0xd8004c, CODE_FOR_vec_setv2di },
  { 0xd80053, CODE_FOR_vec_setv4hf },
  { 0xd80054, CODE_FOR_vec_setv2sf },
  { 0xd80055, CODE_FOR_vec_setv8hf },
  { 0xd80056, CODE_FOR_vec_setv4sf },
  { 0xdc0046, CODE_FOR_vec_unpacks_hi_v8qi },
  { 0xdc0047, CODE_FOR_vec_unpacks_hi_v4hi },
  { 0xdc0048, CODE_FOR_vec_unpacks_hi_v2si },
  { 0xdc0049, CODE_FOR_vec_unpacks_hi_v16qi },
  { 0xdc004a, CODE_FOR_vec_unpacks_hi_v8hi },
  { 0xdc004b, CODE_FOR_vec_unpacks_hi_v4si },
  { 0xdd0046, CODE_FOR_vec_unpacks_lo_v8qi },
  { 0xdd0047, CODE_FOR_vec_unpacks_lo_v4hi },
  { 0xdd0048, CODE_FOR_vec_unpacks_lo_v2si },
  { 0xdd0049, CODE_FOR_vec_unpacks_lo_v16qi },
  { 0xdd004a, CODE_FOR_vec_unpacks_lo_v8hi },
  { 0xdd004b, CODE_FOR_vec_unpacks_lo_v4si },
  { 0xe00046, CODE_FOR_vec_unpacku_hi_v8qi },
  { 0xe00047, CODE_FOR_vec_unpacku_hi_v4hi },
  { 0xe00048, CODE_FOR_vec_unpacku_hi_v2si },
  { 0xe00049, CODE_FOR_vec_unpacku_hi_v16qi },
  { 0xe0004a, CODE_FOR_vec_unpacku_hi_v8hi },
  { 0xe0004b, CODE_FOR_vec_unpacku_hi_v4si },
  { 0xe10046, CODE_FOR_vec_unpacku_lo_v8qi },
  { 0xe10047, CODE_FOR_vec_unpacku_lo_v4hi },
  { 0xe10048, CODE_FOR_vec_unpacku_lo_v2si },
  { 0xe10049, CODE_FOR_vec_unpacku_lo_v16qi },
  { 0xe1004a, CODE_FOR_vec_unpacku_lo_v8hi },
  { 0xe1004b, CODE_FOR_vec_unpacku_lo_v4si },
  { 0xe30046, CODE_FOR_vec_widen_smult_hi_v8qi },
  { 0xe30047, CODE_FOR_vec_widen_smult_hi_v4hi },
  { 0xe30048, CODE_FOR_vec_widen_smult_hi_v2si },
  { 0xe30049, CODE_FOR_vec_widen_smult_hi_v16qi },
  { 0xe3004a, CODE_FOR_vec_widen_smult_hi_v8hi },
  { 0xe3004b, CODE_FOR_vec_widen_smult_hi_v4si },
  { 0xe40046, CODE_FOR_vec_widen_smult_lo_v8qi },
  { 0xe40047, CODE_FOR_vec_widen_smult_lo_v4hi },
  { 0xe40048, CODE_FOR_vec_widen_smult_lo_v2si },
  { 0xe40049, CODE_FOR_vec_widen_smult_lo_v16qi },
  { 0xe4004a, CODE_FOR_vec_widen_smult_lo_v8hi },
  { 0xe4004b, CODE_FOR_vec_widen_smult_lo_v4si },
  { 0xe60046, CODE_FOR_vec_widen_sshiftl_hi_v8qi },
  { 0xe60047, CODE_FOR_vec_widen_sshiftl_hi_v4hi },
  { 0xe60048, CODE_FOR_vec_widen_sshiftl_hi_v2si },
  { 0xe60049, CODE_FOR_vec_widen_sshiftl_hi_v16qi },
  { 0xe6004a, CODE_FOR_vec_widen_sshiftl_hi_v8hi },
  { 0xe6004b, CODE_FOR_vec_widen_sshiftl_hi_v4si },
  { 0xe70046, CODE_FOR_vec_widen_sshiftl_lo_v8qi },
  { 0xe70047, CODE_FOR_vec_widen_sshiftl_lo_v4hi },
  { 0xe70048, CODE_FOR_vec_widen_sshiftl_lo_v2si },
  { 0xe70049, CODE_FOR_vec_widen_sshiftl_lo_v16qi },
  { 0xe7004a, CODE_FOR_vec_widen_sshiftl_lo_v8hi },
  { 0xe7004b, CODE_FOR_vec_widen_sshiftl_lo_v4si },
  { 0xe90046, CODE_FOR_vec_widen_umult_hi_v8qi },
  { 0xe90047, CODE_FOR_vec_widen_umult_hi_v4hi },
  { 0xe90048, CODE_FOR_vec_widen_umult_hi_v2si },
  { 0xe90049, CODE_FOR_vec_widen_umult_hi_v16qi },
  { 0xe9004a, CODE_FOR_vec_widen_umult_hi_v8hi },
  { 0xe9004b, CODE_FOR_vec_widen_umult_hi_v4si },
  { 0xea0046, CODE_FOR_vec_widen_umult_lo_v8qi },
  { 0xea0047, CODE_FOR_vec_widen_umult_lo_v4hi },
  { 0xea0048, CODE_FOR_vec_widen_umult_lo_v2si },
  { 0xea0049, CODE_FOR_vec_widen_umult_lo_v16qi },
  { 0xea004a, CODE_FOR_vec_widen_umult_lo_v8hi },
  { 0xea004b, CODE_FOR_vec_widen_umult_lo_v4si },
  { 0xec0046, CODE_FOR_vec_widen_ushiftl_hi_v8qi },
  { 0xec0047, CODE_FOR_vec_widen_ushiftl_hi_v4hi },
  { 0xec0048, CODE_FOR_vec_widen_ushiftl_hi_v2si },
  { 0xec0049, CODE_FOR_vec_widen_ushiftl_hi_v16qi },
  { 0xec004a, CODE_FOR_vec_widen_ushiftl_hi_v8hi },
  { 0xec004b, CODE_FOR_vec_widen_ushiftl_hi_v4si },
  { 0xed0046, CODE_FOR_vec_widen_ushiftl_lo_v8qi },
  { 0xed0047, CODE_FOR_vec_widen_ushiftl_lo_v4hi },
  { 0xed0048, CODE_FOR_vec_widen_ushiftl_lo_v2si },
  { 0xed0049, CODE_FOR_vec_widen_ushiftl_lo_v16qi },
  { 0xed004a, CODE_FOR_vec_widen_ushiftl_lo_v8hi },
  { 0xed004b, CODE_FOR_vec_widen_ushiftl_lo_v4si },
  { 0xf50017, CODE_FOR_atomic_add_fetchqi },
  { 0xf50018, CODE_FOR_atomic_add_fetchhi },
  { 0xf50019, CODE_FOR_atomic_add_fetchsi },
  { 0xf5001a, CODE_FOR_atomic_add_fetchdi },
  { 0xf60017, CODE_FOR_atomic_addqi },
  { 0xf60018, CODE_FOR_atomic_addhi },
  { 0xf60019, CODE_FOR_atomic_addsi },
  { 0xf6001a, CODE_FOR_atomic_adddi },
  { 0xf70017, CODE_FOR_atomic_and_fetchqi },
  { 0xf70018, CODE_FOR_atomic_and_fetchhi },
  { 0xf70019, CODE_FOR_atomic_and_fetchsi },
  { 0xf7001a, CODE_FOR_atomic_and_fetchdi },
  { 0xf80017, CODE_FOR_atomic_andqi },
  { 0xf80018, CODE_FOR_atomic_andhi },
  { 0xf80019, CODE_FOR_atomic_andsi },
  { 0xf8001a, CODE_FOR_atomic_anddi },
  { 0xf90017, CODE_FOR_atomic_compare_and_swapqi },
  { 0xf90018, CODE_FOR_atomic_compare_and_swaphi },
  { 0xf90019, CODE_FOR_atomic_compare_and_swapsi },
  { 0xf9001a, CODE_FOR_atomic_compare_and_swapdi },
  { 0xfa0017, CODE_FOR_atomic_exchangeqi },
  { 0xfa0018, CODE_FOR_atomic_exchangehi },
  { 0xfa0019, CODE_FOR_atomic_exchangesi },
  { 0xfa001a, CODE_FOR_atomic_exchangedi },
  { 0xfb0017, CODE_FOR_atomic_fetch_addqi },
  { 0xfb0018, CODE_FOR_atomic_fetch_addhi },
  { 0xfb0019, CODE_FOR_atomic_fetch_addsi },
  { 0xfb001a, CODE_FOR_atomic_fetch_adddi },
  { 0xfc0017, CODE_FOR_atomic_fetch_andqi },
  { 0xfc0018, CODE_FOR_atomic_fetch_andhi },
  { 0xfc0019, CODE_FOR_atomic_fetch_andsi },
  { 0xfc001a, CODE_FOR_atomic_fetch_anddi },
  { 0xfd0017, CODE_FOR_atomic_fetch_nandqi },
  { 0xfd0018, CODE_FOR_atomic_fetch_nandhi },
  { 0xfd0019, CODE_FOR_atomic_fetch_nandsi },
  { 0xfd001a, CODE_FOR_atomic_fetch_nanddi },
  { 0xfe0017, CODE_FOR_atomic_fetch_orqi },
  { 0xfe0018, CODE_FOR_atomic_fetch_orhi },
  { 0xfe0019, CODE_FOR_atomic_fetch_orsi },
  { 0xfe001a, CODE_FOR_atomic_fetch_ordi },
  { 0xff0017, CODE_FOR_atomic_fetch_subqi },
  { 0xff0018, CODE_FOR_atomic_fetch_subhi },
  { 0xff0019, CODE_FOR_atomic_fetch_subsi },
  { 0xff001a, CODE_FOR_atomic_fetch_subdi },
  { 0x1000017, CODE_FOR_atomic_fetch_xorqi },
  { 0x1000018, CODE_FOR_atomic_fetch_xorhi },
  { 0x1000019, CODE_FOR_atomic_fetch_xorsi },
  { 0x100001a, CODE_FOR_atomic_fetch_xordi },
  { 0x1010017, CODE_FOR_atomic_loadqi },
  { 0x1010018, CODE_FOR_atomic_loadhi },
  { 0x1010019, CODE_FOR_atomic_loadsi },
  { 0x101001a, CODE_FOR_atomic_loaddi },
  { 0x1020017, CODE_FOR_atomic_nand_fetchqi },
  { 0x1020018, CODE_FOR_atomic_nand_fetchhi },
  { 0x1020019, CODE_FOR_atomic_nand_fetchsi },
  { 0x102001a, CODE_FOR_atomic_nand_fetchdi },
  { 0x1030017, CODE_FOR_atomic_nandqi },
  { 0x1030018, CODE_FOR_atomic_nandhi },
  { 0x1030019, CODE_FOR_atomic_nandsi },
  { 0x103001a, CODE_FOR_atomic_nanddi },
  { 0x1040017, CODE_FOR_atomic_or_fetchqi },
  { 0x1040018, CODE_FOR_atomic_or_fetchhi },
  { 0x1040019, CODE_FOR_atomic_or_fetchsi },
  { 0x104001a, CODE_FOR_atomic_or_fetchdi },
  { 0x1050017, CODE_FOR_atomic_orqi },
  { 0x1050018, CODE_FOR_atomic_orhi },
  { 0x1050019, CODE_FOR_atomic_orsi },
  { 0x105001a, CODE_FOR_atomic_ordi },
  { 0x1060017, CODE_FOR_atomic_storeqi },
  { 0x1060018, CODE_FOR_atomic_storehi },
  { 0x1060019, CODE_FOR_atomic_storesi },
  { 0x1070017, CODE_FOR_atomic_sub_fetchqi },
  { 0x1070018, CODE_FOR_atomic_sub_fetchhi },
  { 0x1070019, CODE_FOR_atomic_sub_fetchsi },
  { 0x107001a, CODE_FOR_atomic_sub_fetchdi },
  { 0x1080017, CODE_FOR_atomic_subqi },
  { 0x1080018, CODE_FOR_atomic_subhi },
  { 0x1080019, CODE_FOR_atomic_subsi },
  { 0x108001a, CODE_FOR_atomic_subdi },
  { 0x1090017, CODE_FOR_atomic_xor_fetchqi },
  { 0x1090018, CODE_FOR_atomic_xor_fetchhi },
  { 0x1090019, CODE_FOR_atomic_xor_fetchsi },
  { 0x109001a, CODE_FOR_atomic_xor_fetchdi },
  { 0x10a0017, CODE_FOR_atomic_xorqi },
  { 0x10a0018, CODE_FOR_atomic_xorhi },
  { 0x10a0019, CODE_FOR_atomic_xorsi },
  { 0x10a001a, CODE_FOR_atomic_xordi },
  { 0x10b0019, CODE_FOR_get_thread_pointersi },
};

void
init_all_optabs (struct target_optabs *optabs)
{
  bool *ena = optabs->pat_enable;
  ena[0] = HAVE_extendqihi2;
  ena[1] = HAVE_extendqisi2;
  ena[2] = HAVE_extendqidi2;
  ena[3] = HAVE_extendhisi2;
  ena[4] = HAVE_extendhidi2;
  ena[5] = HAVE_extendsidi2;
  ena[6] = HAVE_extendhfsf2;
  ena[7] = HAVE_extendhfdf2;
  ena[8] = HAVE_extendsfdf2;
  ena[9] = HAVE_truncsfhf2;
  ena[10] = HAVE_truncdfhf2;
  ena[11] = HAVE_truncdfsf2;
  ena[12] = HAVE_zero_extendqisi2;
  ena[13] = HAVE_zero_extendqidi2;
  ena[14] = HAVE_zero_extendhisi2;
  ena[15] = HAVE_zero_extendhidi2;
  ena[16] = HAVE_zero_extendsidi2;
  ena[17] = HAVE_floatsihf2;
  ena[18] = HAVE_floatsisf2;
  ena[19] = HAVE_floatsidf2;
  ena[20] = HAVE_floatdihf2;
  ena[21] = HAVE_floatv2siv2sf2;
  ena[22] = HAVE_floatv4siv4sf2;
  ena[23] = HAVE_floatunssisf2;
  ena[24] = HAVE_floatunssidf2;
  ena[25] = HAVE_floatunsv2siv2sf2;
  ena[26] = HAVE_floatunsv4siv4sf2;
  ena[27] = HAVE_lroundsfsi2;
  ena[28] = HAVE_lrounddfsi2;
  ena[29] = HAVE_lfloorsfsi2;
  ena[30] = HAVE_lfloordfsi2;
  ena[31] = HAVE_lceilsfsi2;
  ena[32] = HAVE_lceildfsi2;
  ena[33] = HAVE_fix_trunchfsi2;
  ena[34] = HAVE_fix_trunchfdi2;
  ena[35] = HAVE_fix_truncsfsi2;
  ena[36] = HAVE_fix_truncdfsi2;
  ena[37] = HAVE_fix_truncv2sfv2si2;
  ena[38] = HAVE_fix_truncv4sfv4si2;
  ena[39] = HAVE_fixuns_truncsfsi2;
  ena[40] = HAVE_fixuns_truncdfsi2;
  ena[41] = HAVE_fixuns_truncv2sfv2si2;
  ena[42] = HAVE_fixuns_truncv4sfv4si2;
  ena[43] = HAVE_mulhisi3;
  ena[44] = HAVE_mulsidi3;
  ena[45] = HAVE_umulsidi3;
  ena[46] = HAVE_maddhisi4;
  ena[47] = HAVE_maddhidi4;
  ena[48] = HAVE_maddsidi4;
  ena[49] = HAVE_umaddsidi4;
  ena[50] = HAVE_vec_load_lanesdidi;
  ena[51] = HAVE_vec_load_lanestidi;
  ena[52] = HAVE_vec_load_laneseidi;
  ena[53] = HAVE_vec_load_lanesoidi;
  ena[54] = HAVE_vec_load_lanestiv8qi;
  ena[55] = HAVE_vec_load_laneseiv8qi;
  ena[56] = HAVE_vec_load_lanesoiv8qi;
  ena[57] = HAVE_vec_load_lanesv8qiv8qi;
  ena[58] = HAVE_vec_load_lanestiv4hi;
  ena[59] = HAVE_vec_load_laneseiv4hi;
  ena[60] = HAVE_vec_load_lanesoiv4hi;
  ena[61] = HAVE_vec_load_lanesv4hiv4hi;
  ena[62] = HAVE_vec_load_lanestiv2si;
  ena[63] = HAVE_vec_load_laneseiv2si;
  ena[64] = HAVE_vec_load_lanesoiv2si;
  ena[65] = HAVE_vec_load_lanesv2siv2si;
  ena[66] = HAVE_vec_load_lanesoiv16qi;
  ena[67] = HAVE_vec_load_lanesciv16qi;
  ena[68] = HAVE_vec_load_lanesxiv16qi;
  ena[69] = HAVE_vec_load_lanesv16qiv16qi;
  ena[70] = HAVE_vec_load_lanesoiv8hi;
  ena[71] = HAVE_vec_load_lanesciv8hi;
  ena[72] = HAVE_vec_load_lanesxiv8hi;
  ena[73] = HAVE_vec_load_lanesv8hiv8hi;
  ena[74] = HAVE_vec_load_lanesoiv4si;
  ena[75] = HAVE_vec_load_lanesciv4si;
  ena[76] = HAVE_vec_load_lanesxiv4si;
  ena[77] = HAVE_vec_load_lanesv4siv4si;
  ena[78] = HAVE_vec_load_lanesv2div2di;
  ena[79] = HAVE_vec_load_lanestiv4hf;
  ena[80] = HAVE_vec_load_laneseiv4hf;
  ena[81] = HAVE_vec_load_lanesoiv4hf;
  ena[82] = HAVE_vec_load_lanesv4hfv4hf;
  ena[83] = HAVE_vec_load_lanestiv2sf;
  ena[84] = HAVE_vec_load_laneseiv2sf;
  ena[85] = HAVE_vec_load_lanesoiv2sf;
  ena[86] = HAVE_vec_load_lanesv2sfv2sf;
  ena[87] = HAVE_vec_load_lanesoiv8hf;
  ena[88] = HAVE_vec_load_lanesciv8hf;
  ena[89] = HAVE_vec_load_lanesxiv8hf;
  ena[90] = HAVE_vec_load_lanesv8hfv8hf;
  ena[91] = HAVE_vec_load_lanesoiv4sf;
  ena[92] = HAVE_vec_load_lanesciv4sf;
  ena[93] = HAVE_vec_load_lanesxiv4sf;
  ena[94] = HAVE_vec_load_lanesv4sfv4sf;
  ena[95] = HAVE_vec_store_lanesdidi;
  ena[96] = HAVE_vec_store_lanestidi;
  ena[97] = HAVE_vec_store_laneseidi;
  ena[98] = HAVE_vec_store_lanesoidi;
  ena[99] = HAVE_vec_store_lanestiv8qi;
  ena[100] = HAVE_vec_store_laneseiv8qi;
  ena[101] = HAVE_vec_store_lanesoiv8qi;
  ena[102] = HAVE_vec_store_lanesv8qiv8qi;
  ena[103] = HAVE_vec_store_lanestiv4hi;
  ena[104] = HAVE_vec_store_laneseiv4hi;
  ena[105] = HAVE_vec_store_lanesoiv4hi;
  ena[106] = HAVE_vec_store_lanesv4hiv4hi;
  ena[107] = HAVE_vec_store_lanestiv2si;
  ena[108] = HAVE_vec_store_laneseiv2si;
  ena[109] = HAVE_vec_store_lanesoiv2si;
  ena[110] = HAVE_vec_store_lanesv2siv2si;
  ena[111] = HAVE_vec_store_lanesoiv16qi;
  ena[112] = HAVE_vec_store_lanesciv16qi;
  ena[113] = HAVE_vec_store_lanesxiv16qi;
  ena[114] = HAVE_vec_store_lanesv16qiv16qi;
  ena[115] = HAVE_vec_store_lanesoiv8hi;
  ena[116] = HAVE_vec_store_lanesciv8hi;
  ena[117] = HAVE_vec_store_lanesxiv8hi;
  ena[118] = HAVE_vec_store_lanesv8hiv8hi;
  ena[119] = HAVE_vec_store_lanesoiv4si;
  ena[120] = HAVE_vec_store_lanesciv4si;
  ena[121] = HAVE_vec_store_lanesxiv4si;
  ena[122] = HAVE_vec_store_lanesv4siv4si;
  ena[123] = HAVE_vec_store_lanesv2div2di;
  ena[124] = HAVE_vec_store_lanestiv4hf;
  ena[125] = HAVE_vec_store_laneseiv4hf;
  ena[126] = HAVE_vec_store_lanesoiv4hf;
  ena[127] = HAVE_vec_store_lanesv4hfv4hf;
  ena[128] = HAVE_vec_store_lanestiv2sf;
  ena[129] = HAVE_vec_store_laneseiv2sf;
  ena[130] = HAVE_vec_store_lanesoiv2sf;
  ena[131] = HAVE_vec_store_lanesv2sfv2sf;
  ena[132] = HAVE_vec_store_lanesoiv8hf;
  ena[133] = HAVE_vec_store_lanesciv8hf;
  ena[134] = HAVE_vec_store_lanesxiv8hf;
  ena[135] = HAVE_vec_store_lanesv8hfv8hf;
  ena[136] = HAVE_vec_store_lanesoiv4sf;
  ena[137] = HAVE_vec_store_lanesciv4sf;
  ena[138] = HAVE_vec_store_lanesxiv4sf;
  ena[139] = HAVE_vec_store_lanesv4sfv4sf;
  ena[140] = HAVE_vcondv8qiv8qi;
  ena[141] = HAVE_vcondv4hiv4hi;
  ena[142] = HAVE_vcondv2siv2si;
  ena[143] = HAVE_vcondv16qiv16qi;
  ena[144] = HAVE_vcondv8hiv8hi;
  ena[145] = HAVE_vcondv4siv4si;
  ena[146] = HAVE_vcondv2sfv2sf;
  ena[147] = HAVE_vcondv4sfv4sf;
  ena[148] = HAVE_vconduv8qiv8qi;
  ena[149] = HAVE_vconduv4hiv4hi;
  ena[150] = HAVE_vconduv2siv2si;
  ena[151] = HAVE_vconduv16qiv16qi;
  ena[152] = HAVE_vconduv8hiv8hi;
  ena[153] = HAVE_vconduv4siv4si;
  ena[154] = HAVE_addsi3;
  ena[155] = HAVE_adddi3;
  ena[156] = HAVE_addqq3;
  ena[157] = HAVE_addhq3;
  ena[158] = HAVE_addsq3;
  ena[159] = HAVE_adduqq3;
  ena[160] = HAVE_adduhq3;
  ena[161] = HAVE_addusq3;
  ena[162] = HAVE_addha3;
  ena[163] = HAVE_addsa3;
  ena[164] = HAVE_adduha3;
  ena[165] = HAVE_addusa3;
  ena[166] = HAVE_addsf3;
  ena[167] = HAVE_adddf3;
  ena[168] = HAVE_addv8qi3;
  ena[169] = HAVE_addv4hi3;
  ena[170] = HAVE_addv2si3;
  ena[171] = HAVE_addv16qi3;
  ena[172] = HAVE_addv8hi3;
  ena[173] = HAVE_addv4si3;
  ena[174] = HAVE_addv2di3;
  ena[175] = HAVE_addv4qq3;
  ena[176] = HAVE_addv2hq3;
  ena[177] = HAVE_addv2ha3;
  ena[178] = HAVE_addv2sf3;
  ena[179] = HAVE_addv4sf3;
  ena[180] = HAVE_ssaddqq3;
  ena[181] = HAVE_ssaddhq3;
  ena[182] = HAVE_ssaddsq3;
  ena[183] = HAVE_ssaddha3;
  ena[184] = HAVE_ssaddsa3;
  ena[185] = HAVE_ssaddv4qq3;
  ena[186] = HAVE_ssaddv2hq3;
  ena[187] = HAVE_ssaddv2ha3;
  ena[188] = HAVE_usadduqq3;
  ena[189] = HAVE_usadduhq3;
  ena[190] = HAVE_usadduha3;
  ena[191] = HAVE_usaddv4uqq3;
  ena[192] = HAVE_usaddv2uhq3;
  ena[193] = HAVE_usaddv2uha3;
  ena[194] = HAVE_subsi3;
  ena[195] = HAVE_subdi3;
  ena[196] = HAVE_subqq3;
  ena[197] = HAVE_subhq3;
  ena[198] = HAVE_subsq3;
  ena[199] = HAVE_subuqq3;
  ena[200] = HAVE_subuhq3;
  ena[201] = HAVE_subusq3;
  ena[202] = HAVE_subha3;
  ena[203] = HAVE_subsa3;
  ena[204] = HAVE_subuha3;
  ena[205] = HAVE_subusa3;
  ena[206] = HAVE_subsf3;
  ena[207] = HAVE_subdf3;
  ena[208] = HAVE_subv8qi3;
  ena[209] = HAVE_subv4hi3;
  ena[210] = HAVE_subv2si3;
  ena[211] = HAVE_subv16qi3;
  ena[212] = HAVE_subv8hi3;
  ena[213] = HAVE_subv4si3;
  ena[214] = HAVE_subv2di3;
  ena[215] = HAVE_subv4qq3;
  ena[216] = HAVE_subv2hq3;
  ena[217] = HAVE_subv2ha3;
  ena[218] = HAVE_subv2sf3;
  ena[219] = HAVE_subv4sf3;
  ena[220] = HAVE_sssubqq3;
  ena[221] = HAVE_sssubhq3;
  ena[222] = HAVE_sssubsq3;
  ena[223] = HAVE_sssubha3;
  ena[224] = HAVE_sssubsa3;
  ena[225] = HAVE_sssubv4qq3;
  ena[226] = HAVE_sssubv2hq3;
  ena[227] = HAVE_sssubv2ha3;
  ena[228] = HAVE_ussubuqq3;
  ena[229] = HAVE_ussubuhq3;
  ena[230] = HAVE_ussubuha3;
  ena[231] = HAVE_ussubv4uqq3;
  ena[232] = HAVE_ussubv2uhq3;
  ena[233] = HAVE_ussubv2uha3;
  ena[234] = HAVE_mulhi3;
  ena[235] = HAVE_mulsi3;
  ena[236] = HAVE_mulqq3;
  ena[237] = HAVE_mulhq3;
  ena[238] = HAVE_mulsq3;
  ena[239] = HAVE_mulha3;
  ena[240] = HAVE_mulsa3;
  ena[241] = HAVE_muluha3;
  ena[242] = HAVE_mulusa3;
  ena[243] = HAVE_mulsf3;
  ena[244] = HAVE_muldf3;
  ena[245] = HAVE_mulv8qi3;
  ena[246] = HAVE_mulv4hi3;
  ena[247] = HAVE_mulv2si3;
  ena[248] = HAVE_mulv16qi3;
  ena[249] = HAVE_mulv8hi3;
  ena[250] = HAVE_mulv4si3;
  ena[251] = HAVE_mulv2sf3;
  ena[252] = HAVE_mulv4sf3;
  ena[253] = HAVE_ssmulha3;
  ena[254] = HAVE_ssmulsa3;
  ena[255] = HAVE_usmuluha3;
  ena[256] = HAVE_usmulusa3;
  ena[257] = HAVE_divsi3;
  ena[258] = HAVE_divsf3;
  ena[259] = HAVE_divdf3;
  ena[260] = HAVE_udivsi3;
  ena[261] = HAVE_modsi3;
  ena[262] = HAVE_andsi3;
  ena[263] = HAVE_anddi3;
  ena[264] = HAVE_andv8qi3;
  ena[265] = HAVE_andv4hi3;
  ena[266] = HAVE_andv2si3;
  ena[267] = HAVE_andv16qi3;
  ena[268] = HAVE_andv8hi3;
  ena[269] = HAVE_andv4si3;
  ena[270] = HAVE_andv2di3;
  ena[271] = HAVE_andv4hf3;
  ena[272] = HAVE_andv2sf3;
  ena[273] = HAVE_andv8hf3;
  ena[274] = HAVE_andv4sf3;
  ena[275] = HAVE_iorsi3;
  ena[276] = HAVE_iordi3;
  ena[277] = HAVE_iorv8qi3;
  ena[278] = HAVE_iorv4hi3;
  ena[279] = HAVE_iorv2si3;
  ena[280] = HAVE_iorv16qi3;
  ena[281] = HAVE_iorv8hi3;
  ena[282] = HAVE_iorv4si3;
  ena[283] = HAVE_iorv2di3;
  ena[284] = HAVE_iorv4hf3;
  ena[285] = HAVE_iorv2sf3;
  ena[286] = HAVE_iorv8hf3;
  ena[287] = HAVE_iorv4sf3;
  ena[288] = HAVE_xorsi3;
  ena[289] = HAVE_xordi3;
  ena[290] = HAVE_xorv8qi3;
  ena[291] = HAVE_xorv4hi3;
  ena[292] = HAVE_xorv2si3;
  ena[293] = HAVE_xorv16qi3;
  ena[294] = HAVE_xorv8hi3;
  ena[295] = HAVE_xorv4si3;
  ena[296] = HAVE_xorv2di3;
  ena[297] = HAVE_xorv4hf3;
  ena[298] = HAVE_xorv2sf3;
  ena[299] = HAVE_xorv8hf3;
  ena[300] = HAVE_xorv4sf3;
  ena[301] = HAVE_ashlsi3;
  ena[302] = HAVE_ashldi3;
  ena[303] = HAVE_ashrsi3;
  ena[304] = HAVE_ashrdi3;
  ena[305] = HAVE_lshrsi3;
  ena[306] = HAVE_lshrdi3;
  ena[307] = HAVE_rotlsi3;
  ena[308] = HAVE_rotrsi3;
  ena[309] = HAVE_vashlv8qi3;
  ena[310] = HAVE_vashlv4hi3;
  ena[311] = HAVE_vashlv2si3;
  ena[312] = HAVE_vashlv16qi3;
  ena[313] = HAVE_vashlv8hi3;
  ena[314] = HAVE_vashlv4si3;
  ena[315] = HAVE_vashrv8qi3;
  ena[316] = HAVE_vashrv4hi3;
  ena[317] = HAVE_vashrv2si3;
  ena[318] = HAVE_vashrv16qi3;
  ena[319] = HAVE_vashrv8hi3;
  ena[320] = HAVE_vashrv4si3;
  ena[321] = HAVE_vlshrv8qi3;
  ena[322] = HAVE_vlshrv4hi3;
  ena[323] = HAVE_vlshrv2si3;
  ena[324] = HAVE_vlshrv16qi3;
  ena[325] = HAVE_vlshrv8hi3;
  ena[326] = HAVE_vlshrv4si3;
  ena[327] = HAVE_sminsi3;
  ena[328] = HAVE_sminsf3;
  ena[329] = HAVE_smindf3;
  ena[330] = HAVE_sminv8qi3;
  ena[331] = HAVE_sminv4hi3;
  ena[332] = HAVE_sminv2si3;
  ena[333] = HAVE_sminv16qi3;
  ena[334] = HAVE_sminv8hi3;
  ena[335] = HAVE_sminv4si3;
  ena[336] = HAVE_sminv2sf3;
  ena[337] = HAVE_sminv4sf3;
  ena[338] = HAVE_smaxsi3;
  ena[339] = HAVE_smaxsf3;
  ena[340] = HAVE_smaxdf3;
  ena[341] = HAVE_smaxv8qi3;
  ena[342] = HAVE_smaxv4hi3;
  ena[343] = HAVE_smaxv2si3;
  ena[344] = HAVE_smaxv16qi3;
  ena[345] = HAVE_smaxv8hi3;
  ena[346] = HAVE_smaxv4si3;
  ena[347] = HAVE_smaxv2sf3;
  ena[348] = HAVE_smaxv4sf3;
  ena[349] = HAVE_uminsi3;
  ena[350] = HAVE_uminv8qi3;
  ena[351] = HAVE_uminv4hi3;
  ena[352] = HAVE_uminv2si3;
  ena[353] = HAVE_uminv16qi3;
  ena[354] = HAVE_uminv8hi3;
  ena[355] = HAVE_uminv4si3;
  ena[356] = HAVE_umaxsi3;
  ena[357] = HAVE_umaxv8qi3;
  ena[358] = HAVE_umaxv4hi3;
  ena[359] = HAVE_umaxv2si3;
  ena[360] = HAVE_umaxv16qi3;
  ena[361] = HAVE_umaxv8hi3;
  ena[362] = HAVE_umaxv4si3;
  ena[363] = HAVE_negsi2;
  ena[364] = HAVE_negdi2;
  ena[365] = HAVE_negsf2;
  ena[366] = HAVE_negdf2;
  ena[367] = HAVE_negv8qi2;
  ena[368] = HAVE_negv4hi2;
  ena[369] = HAVE_negv2si2;
  ena[370] = HAVE_negv16qi2;
  ena[371] = HAVE_negv8hi2;
  ena[372] = HAVE_negv4si2;
  ena[373] = HAVE_negv2sf2;
  ena[374] = HAVE_negv4sf2;
  ena[375] = HAVE_abssi2;
  ena[376] = HAVE_abssf2;
  ena[377] = HAVE_absdf2;
  ena[378] = HAVE_absv8qi2;
  ena[379] = HAVE_absv4hi2;
  ena[380] = HAVE_absv2si2;
  ena[381] = HAVE_absv16qi2;
  ena[382] = HAVE_absv8hi2;
  ena[383] = HAVE_absv4si2;
  ena[384] = HAVE_absv2sf2;
  ena[385] = HAVE_absv4sf2;
  ena[386] = HAVE_one_cmplsi2;
  ena[387] = HAVE_one_cmpldi2;
  ena[388] = HAVE_one_cmplv8qi2;
  ena[389] = HAVE_one_cmplv4hi2;
  ena[390] = HAVE_one_cmplv2si2;
  ena[391] = HAVE_one_cmplv16qi2;
  ena[392] = HAVE_one_cmplv8hi2;
  ena[393] = HAVE_one_cmplv4si2;
  ena[394] = HAVE_one_cmplv2di2;
  ena[395] = HAVE_one_cmplv4hf2;
  ena[396] = HAVE_one_cmplv2sf2;
  ena[397] = HAVE_one_cmplv8hf2;
  ena[398] = HAVE_one_cmplv4sf2;
  ena[399] = HAVE_bswaphi2;
  ena[400] = HAVE_bswapsi2;
  ena[401] = HAVE_clzsi2;
  ena[402] = HAVE_clzv8qi2;
  ena[403] = HAVE_clzv4hi2;
  ena[404] = HAVE_clzv2si2;
  ena[405] = HAVE_clzv16qi2;
  ena[406] = HAVE_clzv8hi2;
  ena[407] = HAVE_clzv4si2;
  ena[408] = HAVE_ctzsi2;
  ena[409] = HAVE_popcountv8qi2;
  ena[410] = HAVE_popcountv16qi2;
  ena[411] = HAVE_sqrtsf2;
  ena[412] = HAVE_sqrtdf2;
  ena[413] = HAVE_movqi;
  ena[414] = HAVE_movhi;
  ena[415] = HAVE_movsi;
  ena[416] = HAVE_movdi;
  ena[417] = HAVE_movti;
  ena[418] = HAVE_movei;
  ena[419] = HAVE_movoi;
  ena[420] = HAVE_movci;
  ena[421] = HAVE_movxi;
  ena[422] = HAVE_movhf;
  ena[423] = HAVE_movsf;
  ena[424] = HAVE_movdf;
  ena[425] = HAVE_movv8qi;
  ena[426] = HAVE_movv4hi;
  ena[427] = HAVE_movv2si;
  ena[428] = HAVE_movv16qi;
  ena[429] = HAVE_movv8hi;
  ena[430] = HAVE_movv4si;
  ena[431] = HAVE_movv2di;
  ena[432] = HAVE_movv4hf;
  ena[433] = HAVE_movv2sf;
  ena[434] = HAVE_movv8hf;
  ena[435] = HAVE_movv4sf;
  ena[436] = HAVE_movmisalignhi;
  ena[437] = HAVE_movmisalignsi;
  ena[438] = HAVE_movmisaligndi;
  ena[439] = HAVE_movmisalignv8qi;
  ena[440] = HAVE_movmisalignv4hi;
  ena[441] = HAVE_movmisalignv2si;
  ena[442] = HAVE_movmisalignv16qi;
  ena[443] = HAVE_movmisalignv8hi;
  ena[444] = HAVE_movmisalignv4si;
  ena[445] = HAVE_movmisalignv2di;
  ena[446] = HAVE_movmisalignv4hf;
  ena[447] = HAVE_movmisalignv2sf;
  ena[448] = HAVE_movmisalignv8hf;
  ena[449] = HAVE_movmisalignv4sf;
  ena[450] = HAVE_reload_inhi;
  ena[451] = HAVE_reload_outhi;
  ena[452] = HAVE_reload_outdf;
  ena[453] = HAVE_cbranchqi4;
  ena[454] = HAVE_cbranchsi4;
  ena[455] = HAVE_cbranchdi4;
  ena[456] = HAVE_cbranchsf4;
  ena[457] = HAVE_cbranchdf4;
  ena[458] = HAVE_movsicc;
  ena[459] = HAVE_movsfcc;
  ena[460] = HAVE_movdfcc;
  ena[461] = HAVE_cstoresi4;
  ena[462] = HAVE_cstoredi4;
  ena[463] = HAVE_cstoresf4;
  ena[464] = HAVE_cstoredf4;
  ena[465] = HAVE_smulsi3_highpart;
  ena[466] = HAVE_smulv4hi3_highpart;
  ena[467] = HAVE_umulsi3_highpart;
  ena[468] = HAVE_umulv4hi3_highpart;
  ena[469] = HAVE_movmemqi;
  ena[470] = HAVE_setmemsi;
  ena[471] = HAVE_fmasf4;
  ena[472] = HAVE_fmadf4;
  ena[473] = HAVE_fmav2sf4;
  ena[474] = HAVE_fmav4sf4;
  ena[475] = HAVE_rintsf2;
  ena[476] = HAVE_rintdf2;
  ena[477] = HAVE_roundsf2;
  ena[478] = HAVE_rounddf2;
  ena[479] = HAVE_floorsf2;
  ena[480] = HAVE_floordf2;
  ena[481] = HAVE_ceilsf2;
  ena[482] = HAVE_ceildf2;
  ena[483] = HAVE_btruncsf2;
  ena[484] = HAVE_btruncdf2;
  ena[485] = HAVE_nearbyintsf2;
  ena[486] = HAVE_nearbyintdf2;
  ena[487] = HAVE_copysignsf3;
  ena[488] = HAVE_copysigndf3;
  ena[489] = HAVE_fmaxsf3;
  ena[490] = HAVE_fmaxdf3;
  ena[491] = HAVE_fmaxv2sf3;
  ena[492] = HAVE_fmaxv4sf3;
  ena[493] = HAVE_fminsf3;
  ena[494] = HAVE_fmindf3;
  ena[495] = HAVE_fminv2sf3;
  ena[496] = HAVE_fminv4sf3;
  ena[497] = HAVE_reduc_smax_scal_v8qi;
  ena[498] = HAVE_reduc_smax_scal_v4hi;
  ena[499] = HAVE_reduc_smax_scal_v2si;
  ena[500] = HAVE_reduc_smax_scal_v16qi;
  ena[501] = HAVE_reduc_smax_scal_v8hi;
  ena[502] = HAVE_reduc_smax_scal_v4si;
  ena[503] = HAVE_reduc_smax_scal_v2sf;
  ena[504] = HAVE_reduc_smax_scal_v4sf;
  ena[505] = HAVE_reduc_smin_scal_v8qi;
  ena[506] = HAVE_reduc_smin_scal_v4hi;
  ena[507] = HAVE_reduc_smin_scal_v2si;
  ena[508] = HAVE_reduc_smin_scal_v16qi;
  ena[509] = HAVE_reduc_smin_scal_v8hi;
  ena[510] = HAVE_reduc_smin_scal_v4si;
  ena[511] = HAVE_reduc_smin_scal_v2sf;
  ena[512] = HAVE_reduc_smin_scal_v4sf;
  ena[513] = HAVE_reduc_plus_scal_v8qi;
  ena[514] = HAVE_reduc_plus_scal_v4hi;
  ena[515] = HAVE_reduc_plus_scal_v2si;
  ena[516] = HAVE_reduc_plus_scal_v16qi;
  ena[517] = HAVE_reduc_plus_scal_v8hi;
  ena[518] = HAVE_reduc_plus_scal_v4si;
  ena[519] = HAVE_reduc_plus_scal_v2di;
  ena[520] = HAVE_reduc_plus_scal_v2sf;
  ena[521] = HAVE_reduc_plus_scal_v4sf;
  ena[522] = HAVE_reduc_umax_scal_v8qi;
  ena[523] = HAVE_reduc_umax_scal_v4hi;
  ena[524] = HAVE_reduc_umax_scal_v2si;
  ena[525] = HAVE_reduc_umax_scal_v16qi;
  ena[526] = HAVE_reduc_umax_scal_v8hi;
  ena[527] = HAVE_reduc_umax_scal_v4si;
  ena[528] = HAVE_reduc_umin_scal_v8qi;
  ena[529] = HAVE_reduc_umin_scal_v4hi;
  ena[530] = HAVE_reduc_umin_scal_v2si;
  ena[531] = HAVE_reduc_umin_scal_v16qi;
  ena[532] = HAVE_reduc_umin_scal_v8hi;
  ena[533] = HAVE_reduc_umin_scal_v4si;
  ena[534] = HAVE_widen_ssumv8qi3;
  ena[535] = HAVE_widen_ssumv4hi3;
  ena[536] = HAVE_widen_ssumv2si3;
  ena[537] = HAVE_widen_usumv8qi3;
  ena[538] = HAVE_widen_usumv4hi3;
  ena[539] = HAVE_widen_usumv2si3;
  ena[540] = HAVE_vec_extractv8qi;
  ena[541] = HAVE_vec_extractv4hi;
  ena[542] = HAVE_vec_extractv2si;
  ena[543] = HAVE_vec_extractv16qi;
  ena[544] = HAVE_vec_extractv8hi;
  ena[545] = HAVE_vec_extractv4si;
  ena[546] = HAVE_vec_extractv2di;
  ena[547] = HAVE_vec_extractv4hf;
  ena[548] = HAVE_vec_extractv2sf;
  ena[549] = HAVE_vec_extractv8hf;
  ena[550] = HAVE_vec_extractv4sf;
  ena[551] = HAVE_vec_initv8qi;
  ena[552] = HAVE_vec_initv4hi;
  ena[553] = HAVE_vec_initv2si;
  ena[554] = HAVE_vec_initv16qi;
  ena[555] = HAVE_vec_initv8hi;
  ena[556] = HAVE_vec_initv4si;
  ena[557] = HAVE_vec_initv2di;
  ena[558] = HAVE_vec_initv4hf;
  ena[559] = HAVE_vec_initv2sf;
  ena[560] = HAVE_vec_initv8hf;
  ena[561] = HAVE_vec_initv4sf;
  ena[562] = HAVE_vec_pack_trunc_di;
  ena[563] = HAVE_vec_pack_trunc_v4hi;
  ena[564] = HAVE_vec_pack_trunc_v2si;
  ena[565] = HAVE_vec_pack_trunc_v8hi;
  ena[566] = HAVE_vec_pack_trunc_v4si;
  ena[567] = HAVE_vec_pack_trunc_v2di;
  ena[568] = HAVE_vec_perm_constv8qi;
  ena[569] = HAVE_vec_perm_constv4hi;
  ena[570] = HAVE_vec_perm_constv2si;
  ena[571] = HAVE_vec_perm_constv16qi;
  ena[572] = HAVE_vec_perm_constv8hi;
  ena[573] = HAVE_vec_perm_constv4si;
  ena[574] = HAVE_vec_perm_constv2di;
  ena[575] = HAVE_vec_perm_constv2sf;
  ena[576] = HAVE_vec_perm_constv4sf;
  ena[577] = HAVE_vec_permv8qi;
  ena[578] = HAVE_vec_permv16qi;
  ena[579] = HAVE_vec_setv8qi;
  ena[580] = HAVE_vec_setv4hi;
  ena[581] = HAVE_vec_setv2si;
  ena[582] = HAVE_vec_setv16qi;
  ena[583] = HAVE_vec_setv8hi;
  ena[584] = HAVE_vec_setv4si;
  ena[585] = HAVE_vec_setv2di;
  ena[586] = HAVE_vec_setv4hf;
  ena[587] = HAVE_vec_setv2sf;
  ena[588] = HAVE_vec_setv8hf;
  ena[589] = HAVE_vec_setv4sf;
  ena[590] = HAVE_vec_unpacks_hi_v8qi;
  ena[591] = HAVE_vec_unpacks_hi_v4hi;
  ena[592] = HAVE_vec_unpacks_hi_v2si;
  ena[593] = HAVE_vec_unpacks_hi_v16qi;
  ena[594] = HAVE_vec_unpacks_hi_v8hi;
  ena[595] = HAVE_vec_unpacks_hi_v4si;
  ena[596] = HAVE_vec_unpacks_lo_v8qi;
  ena[597] = HAVE_vec_unpacks_lo_v4hi;
  ena[598] = HAVE_vec_unpacks_lo_v2si;
  ena[599] = HAVE_vec_unpacks_lo_v16qi;
  ena[600] = HAVE_vec_unpacks_lo_v8hi;
  ena[601] = HAVE_vec_unpacks_lo_v4si;
  ena[602] = HAVE_vec_unpacku_hi_v8qi;
  ena[603] = HAVE_vec_unpacku_hi_v4hi;
  ena[604] = HAVE_vec_unpacku_hi_v2si;
  ena[605] = HAVE_vec_unpacku_hi_v16qi;
  ena[606] = HAVE_vec_unpacku_hi_v8hi;
  ena[607] = HAVE_vec_unpacku_hi_v4si;
  ena[608] = HAVE_vec_unpacku_lo_v8qi;
  ena[609] = HAVE_vec_unpacku_lo_v4hi;
  ena[610] = HAVE_vec_unpacku_lo_v2si;
  ena[611] = HAVE_vec_unpacku_lo_v16qi;
  ena[612] = HAVE_vec_unpacku_lo_v8hi;
  ena[613] = HAVE_vec_unpacku_lo_v4si;
  ena[614] = HAVE_vec_widen_smult_hi_v8qi;
  ena[615] = HAVE_vec_widen_smult_hi_v4hi;
  ena[616] = HAVE_vec_widen_smult_hi_v2si;
  ena[617] = HAVE_vec_widen_smult_hi_v16qi;
  ena[618] = HAVE_vec_widen_smult_hi_v8hi;
  ena[619] = HAVE_vec_widen_smult_hi_v4si;
  ena[620] = HAVE_vec_widen_smult_lo_v8qi;
  ena[621] = HAVE_vec_widen_smult_lo_v4hi;
  ena[622] = HAVE_vec_widen_smult_lo_v2si;
  ena[623] = HAVE_vec_widen_smult_lo_v16qi;
  ena[624] = HAVE_vec_widen_smult_lo_v8hi;
  ena[625] = HAVE_vec_widen_smult_lo_v4si;
  ena[626] = HAVE_vec_widen_sshiftl_hi_v8qi;
  ena[627] = HAVE_vec_widen_sshiftl_hi_v4hi;
  ena[628] = HAVE_vec_widen_sshiftl_hi_v2si;
  ena[629] = HAVE_vec_widen_sshiftl_hi_v16qi;
  ena[630] = HAVE_vec_widen_sshiftl_hi_v8hi;
  ena[631] = HAVE_vec_widen_sshiftl_hi_v4si;
  ena[632] = HAVE_vec_widen_sshiftl_lo_v8qi;
  ena[633] = HAVE_vec_widen_sshiftl_lo_v4hi;
  ena[634] = HAVE_vec_widen_sshiftl_lo_v2si;
  ena[635] = HAVE_vec_widen_sshiftl_lo_v16qi;
  ena[636] = HAVE_vec_widen_sshiftl_lo_v8hi;
  ena[637] = HAVE_vec_widen_sshiftl_lo_v4si;
  ena[638] = HAVE_vec_widen_umult_hi_v8qi;
  ena[639] = HAVE_vec_widen_umult_hi_v4hi;
  ena[640] = HAVE_vec_widen_umult_hi_v2si;
  ena[641] = HAVE_vec_widen_umult_hi_v16qi;
  ena[642] = HAVE_vec_widen_umult_hi_v8hi;
  ena[643] = HAVE_vec_widen_umult_hi_v4si;
  ena[644] = HAVE_vec_widen_umult_lo_v8qi;
  ena[645] = HAVE_vec_widen_umult_lo_v4hi;
  ena[646] = HAVE_vec_widen_umult_lo_v2si;
  ena[647] = HAVE_vec_widen_umult_lo_v16qi;
  ena[648] = HAVE_vec_widen_umult_lo_v8hi;
  ena[649] = HAVE_vec_widen_umult_lo_v4si;
  ena[650] = HAVE_vec_widen_ushiftl_hi_v8qi;
  ena[651] = HAVE_vec_widen_ushiftl_hi_v4hi;
  ena[652] = HAVE_vec_widen_ushiftl_hi_v2si;
  ena[653] = HAVE_vec_widen_ushiftl_hi_v16qi;
  ena[654] = HAVE_vec_widen_ushiftl_hi_v8hi;
  ena[655] = HAVE_vec_widen_ushiftl_hi_v4si;
  ena[656] = HAVE_vec_widen_ushiftl_lo_v8qi;
  ena[657] = HAVE_vec_widen_ushiftl_lo_v4hi;
  ena[658] = HAVE_vec_widen_ushiftl_lo_v2si;
  ena[659] = HAVE_vec_widen_ushiftl_lo_v16qi;
  ena[660] = HAVE_vec_widen_ushiftl_lo_v8hi;
  ena[661] = HAVE_vec_widen_ushiftl_lo_v4si;
  ena[662] = HAVE_atomic_add_fetchqi;
  ena[663] = HAVE_atomic_add_fetchhi;
  ena[664] = HAVE_atomic_add_fetchsi;
  ena[665] = HAVE_atomic_add_fetchdi;
  ena[666] = HAVE_atomic_addqi;
  ena[667] = HAVE_atomic_addhi;
  ena[668] = HAVE_atomic_addsi;
  ena[669] = HAVE_atomic_adddi;
  ena[670] = HAVE_atomic_and_fetchqi;
  ena[671] = HAVE_atomic_and_fetchhi;
  ena[672] = HAVE_atomic_and_fetchsi;
  ena[673] = HAVE_atomic_and_fetchdi;
  ena[674] = HAVE_atomic_andqi;
  ena[675] = HAVE_atomic_andhi;
  ena[676] = HAVE_atomic_andsi;
  ena[677] = HAVE_atomic_anddi;
  ena[678] = HAVE_atomic_compare_and_swapqi;
  ena[679] = HAVE_atomic_compare_and_swaphi;
  ena[680] = HAVE_atomic_compare_and_swapsi;
  ena[681] = HAVE_atomic_compare_and_swapdi;
  ena[682] = HAVE_atomic_exchangeqi;
  ena[683] = HAVE_atomic_exchangehi;
  ena[684] = HAVE_atomic_exchangesi;
  ena[685] = HAVE_atomic_exchangedi;
  ena[686] = HAVE_atomic_fetch_addqi;
  ena[687] = HAVE_atomic_fetch_addhi;
  ena[688] = HAVE_atomic_fetch_addsi;
  ena[689] = HAVE_atomic_fetch_adddi;
  ena[690] = HAVE_atomic_fetch_andqi;
  ena[691] = HAVE_atomic_fetch_andhi;
  ena[692] = HAVE_atomic_fetch_andsi;
  ena[693] = HAVE_atomic_fetch_anddi;
  ena[694] = HAVE_atomic_fetch_nandqi;
  ena[695] = HAVE_atomic_fetch_nandhi;
  ena[696] = HAVE_atomic_fetch_nandsi;
  ena[697] = HAVE_atomic_fetch_nanddi;
  ena[698] = HAVE_atomic_fetch_orqi;
  ena[699] = HAVE_atomic_fetch_orhi;
  ena[700] = HAVE_atomic_fetch_orsi;
  ena[701] = HAVE_atomic_fetch_ordi;
  ena[702] = HAVE_atomic_fetch_subqi;
  ena[703] = HAVE_atomic_fetch_subhi;
  ena[704] = HAVE_atomic_fetch_subsi;
  ena[705] = HAVE_atomic_fetch_subdi;
  ena[706] = HAVE_atomic_fetch_xorqi;
  ena[707] = HAVE_atomic_fetch_xorhi;
  ena[708] = HAVE_atomic_fetch_xorsi;
  ena[709] = HAVE_atomic_fetch_xordi;
  ena[710] = HAVE_atomic_loadqi;
  ena[711] = HAVE_atomic_loadhi;
  ena[712] = HAVE_atomic_loadsi;
  ena[713] = HAVE_atomic_loaddi;
  ena[714] = HAVE_atomic_nand_fetchqi;
  ena[715] = HAVE_atomic_nand_fetchhi;
  ena[716] = HAVE_atomic_nand_fetchsi;
  ena[717] = HAVE_atomic_nand_fetchdi;
  ena[718] = HAVE_atomic_nandqi;
  ena[719] = HAVE_atomic_nandhi;
  ena[720] = HAVE_atomic_nandsi;
  ena[721] = HAVE_atomic_nanddi;
  ena[722] = HAVE_atomic_or_fetchqi;
  ena[723] = HAVE_atomic_or_fetchhi;
  ena[724] = HAVE_atomic_or_fetchsi;
  ena[725] = HAVE_atomic_or_fetchdi;
  ena[726] = HAVE_atomic_orqi;
  ena[727] = HAVE_atomic_orhi;
  ena[728] = HAVE_atomic_orsi;
  ena[729] = HAVE_atomic_ordi;
  ena[730] = HAVE_atomic_storeqi;
  ena[731] = HAVE_atomic_storehi;
  ena[732] = HAVE_atomic_storesi;
  ena[733] = HAVE_atomic_sub_fetchqi;
  ena[734] = HAVE_atomic_sub_fetchhi;
  ena[735] = HAVE_atomic_sub_fetchsi;
  ena[736] = HAVE_atomic_sub_fetchdi;
  ena[737] = HAVE_atomic_subqi;
  ena[738] = HAVE_atomic_subhi;
  ena[739] = HAVE_atomic_subsi;
  ena[740] = HAVE_atomic_subdi;
  ena[741] = HAVE_atomic_xor_fetchqi;
  ena[742] = HAVE_atomic_xor_fetchhi;
  ena[743] = HAVE_atomic_xor_fetchsi;
  ena[744] = HAVE_atomic_xor_fetchdi;
  ena[745] = HAVE_atomic_xorqi;
  ena[746] = HAVE_atomic_xorhi;
  ena[747] = HAVE_atomic_xorsi;
  ena[748] = HAVE_atomic_xordi;
  ena[749] = HAVE_get_thread_pointersi;
}

static int
lookup_handler (unsigned scode)
{
  int l = 0, h = ARRAY_SIZE (pats), m;
  while (h > l)
    {
      m = (h + l) / 2;
      if (scode == pats[m].scode)
        return m;
      else if (scode < pats[m].scode)
        h = m;
      else
        l = m + 1;
    }
  return -1;
}

enum insn_code
raw_optab_handler (unsigned scode)
{
  int i = lookup_handler (scode);
  return (i >= 0 && this_fn_optabs->pat_enable[i]
          ? pats[i].icode : CODE_FOR_nothing);
}

bool
swap_optab_enable (optab op, machine_mode m, bool set)
{
  unsigned scode = (op << 16) | m;
  int i = lookup_handler (scode);
  if (i >= 0)
    {
      bool ret = this_fn_optabs->pat_enable[i];
      this_fn_optabs->pat_enable[i] = set;
      return ret;
    }
  else
    {
      gcc_assert (!set);
      return false;
    }
}

const struct convert_optab_libcall_d convlib_def[NUM_CONVLIB_OPTABS] = {
  { "extend", gen_extend_conv_libfunc },
  { "trunc", gen_trunc_conv_libfunc },
  { NULL, NULL },
  { "fix", gen_fp_to_int_conv_libfunc },
  { "fixuns", gen_fp_to_int_conv_libfunc },
  { "float", gen_int_to_fp_conv_libfunc },
  { NULL, gen_ufloat_conv_libfunc },
  { "lrint", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lround", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lfloor", gen_int_to_fp_nondecimal_conv_libfunc },
  { "lceil", gen_int_to_fp_nondecimal_conv_libfunc },
  { "fract", gen_fract_conv_libfunc },
  { "fractuns", gen_fractuns_conv_libfunc },
  { "satfract", gen_satfract_conv_libfunc },
  { "satfractuns", gen_satfractuns_conv_libfunc },
};

const struct optab_libcall_d normlib_def[NUM_NORMLIB_OPTABS] = {
  { '3', "add", gen_int_fp_fixed_libfunc },
  { '3', "add", gen_intv_fp_libfunc },
  { '3', "ssadd", gen_signed_fixed_libfunc },
  { '3', "usadd", gen_unsigned_fixed_libfunc },
  { '3', "sub", gen_int_fp_fixed_libfunc },
  { '3', "sub", gen_intv_fp_libfunc },
  { '3', "sssub", gen_signed_fixed_libfunc },
  { '3', "ussub", gen_unsigned_fixed_libfunc },
  { '3', "mul", gen_int_fp_fixed_libfunc },
  { '3', "mul", gen_intv_fp_libfunc },
  { '3', "ssmul", gen_signed_fixed_libfunc },
  { '3', "usmul", gen_unsigned_fixed_libfunc },
  { '3', "div", gen_int_fp_signed_fixed_libfunc },
  { '3', "divv", gen_int_libfunc },
  { '3', "ssdiv", gen_signed_fixed_libfunc },
  { '3', "udiv", gen_int_unsigned_fixed_libfunc },
  { '3', "usdiv", gen_unsigned_fixed_libfunc },
  { '4', "divmod", gen_int_libfunc },
  { '4', "udivmod", gen_int_libfunc },
  { '3', "mod", gen_int_libfunc },
  { '3', "umod", gen_int_libfunc },
  { '2', "ftrunc", gen_fp_libfunc },
  { '3', "and", gen_int_libfunc },
  { '3', "ior", gen_int_libfunc },
  { '3', "xor", gen_int_libfunc },
  { '3', "ashl", gen_int_fixed_libfunc },
  { '3', "ssashl", gen_signed_fixed_libfunc },
  { '3', "usashl", gen_unsigned_fixed_libfunc },
  { '3', "ashr", gen_int_signed_fixed_libfunc },
  { '3', "lshr", gen_int_unsigned_fixed_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '3', "min", gen_int_fp_libfunc },
  { '3', "max", gen_int_fp_libfunc },
  { '3', "umin", gen_int_libfunc },
  { '3', "umax", gen_int_libfunc },
  { '2', "neg", gen_int_fp_fixed_libfunc },
  { '2', "neg", gen_intv_fp_libfunc },
  { '2', "ssneg", gen_signed_fixed_libfunc },
  { '2', "usneg", gen_unsigned_fixed_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '2', "one_cmpl", gen_int_libfunc },
  { '\0', NULL, NULL },
  { '2', "ffs", gen_int_libfunc },
  { '2', "clz", gen_int_libfunc },
  { '2', "ctz", gen_int_libfunc },
  { '2', "clrsb", gen_int_libfunc },
  { '2', "popcount", gen_int_libfunc },
  { '2', "parity", gen_int_libfunc },
  { '2', "cmp", gen_int_fp_fixed_libfunc },
  { '2', "ucmp", gen_int_libfunc },
  { '2', "eq", gen_fp_libfunc },
  { '2', "ne", gen_fp_libfunc },
  { '2', "gt", gen_fp_libfunc },
  { '2', "ge", gen_fp_libfunc },
  { '2', "lt", gen_fp_libfunc },
  { '2', "le", gen_fp_libfunc },
  { '2', "unord", gen_fp_libfunc },
  { '2', "powi", gen_fp_libfunc },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
  { '\0', NULL, NULL },
};

enum rtx_code const optab_to_code_[NUM_OPTABS] = {
  UNKNOWN,
  SIGN_EXTEND,
  TRUNCATE,
  ZERO_EXTEND,
  FIX,
  UNSIGNED_FIX,
  FLOAT,
  UNSIGNED_FLOAT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  FRACT_CONVERT,
  UNSIGNED_FRACT_CONVERT,
  SAT_FRACT,
  UNSIGNED_SAT_FRACT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  PLUS,
  PLUS,
  SS_PLUS,
  US_PLUS,
  MINUS,
  MINUS,
  SS_MINUS,
  US_MINUS,
  MULT,
  MULT,
  SS_MULT,
  US_MULT,
  DIV,
  DIV,
  SS_DIV,
  UDIV,
  US_DIV,
  UNKNOWN,
  UNKNOWN,
  MOD,
  UMOD,
  UNKNOWN,
  AND,
  IOR,
  XOR,
  ASHIFT,
  SS_ASHIFT,
  US_ASHIFT,
  ASHIFTRT,
  LSHIFTRT,
  ROTATE,
  ROTATERT,
  ASHIFT,
  ASHIFTRT,
  LSHIFTRT,
  ROTATE,
  ROTATERT,
  SMIN,
  SMAX,
  UMIN,
  UMAX,
  NEG,
  NEG,
  SS_NEG,
  US_NEG,
  ABS,
  ABS,
  NOT,
  BSWAP,
  FFS,
  CLZ,
  CTZ,
  CLRSB,
  POPCOUNT,
  PARITY,
  UNKNOWN,
  UNKNOWN,
  EQ,
  NE,
  GT,
  GE,
  LT,
  LE,
  UNORDERED,
  UNKNOWN,
  SQRT,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  SET,
  STRICT_LOW_PART,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  COMPARE,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  FMA,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
  UNKNOWN,
};

const optab code_to_optab_[NUM_RTX_CODE] = {
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  mov_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  movstrict_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  cbranch_optab,
  add_optab,
  sub_optab,
  neg_optab,
  smul_optab,
  ssmul_optab,
  usmul_optab,
  sdiv_optab,
  ssdiv_optab,
  usdiv_optab,
  smod_optab,
  udiv_optab,
  umod_optab,
  and_optab,
  ior_optab,
  xor_optab,
  one_cmpl_optab,
  ashl_optab,
  rotl_optab,
  ashr_optab,
  lshr_optab,
  rotr_optab,
  smin_optab,
  smax_optab,
  umin_optab,
  umax_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  ne_optab,
  eq_optab,
  ge_optab,
  gt_optab,
  le_optab,
  lt_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unord_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  abs_optab,
  sqrt_optab,
  bswap_optab,
  ffs_optab,
  clrsb_optab,
  clz_optab,
  ctz_optab,
  popcount_optab,
  parity_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  ssadd_optab,
  usadd_optab,
  sssub_optab,
  ssneg_optab,
  usneg_optab,
  unknown_optab,
  ssashl_optab,
  usashl_optab,
  ussub_optab,
  unknown_optab,
  unknown_optab,
  fma_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
  unknown_optab,
};

