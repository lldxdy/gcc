/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64 -O3 -Wno-psabi" } */

#include "riscv_vector.h"

size_t __attribute__ ((noinline))
normalize_vl (size_t vl)
{
  if (vl % 4 == 0)
    return vl;

  return ((vl / 4) + 1) * 4;
}

void
test_float_point_frm_static (float *out, vfloat32m1_t op1, vfloat32m1_t op2,
			     size_t vl)
{
  vl = normalize_vl (vl);

  vfloat32m1_t result = __riscv_vfadd_vv_f32m1_rm (op1, op2, 2, vl);

  *(vfloat32m1_t *)out = result;
}

/* { dg-final { scan-assembler-times {vfadd\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[fav]+[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {fsrm\s+[ax][0-9]+,\s*[ax][0-9]+} 1 } } */
