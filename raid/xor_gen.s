	.file	"xor_gen.c"
	.ignore	ld_st_style
	.ignore	strict_delay
.text
	.global	$xor_gen
	.type	$xor_gen, @function
	.align	8
$xor_gen:
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	  return	%ctpr3; ipd 2
	  sxt,1,sm	0x2, %r1, %g16
	  sxt,2,sm	0x2, %r0, %g17
	  adds,3,sm	0x0, %r1, %r10
	  adds,4,sm	0x0, %r0, %r5
	  sxt,5,sm	0x2, %r0, %g18
	}
	{
	  disp	%ctpr2, $.L70; ipd 2
	  cmpandedb,0,sm	%g16, 0x7, %pred1
	  cmplsb,1	%r0, 0x3, %pred0
	  shld,2,sm	%g17, 0x3, %g17
	  cmpesb,3,sm	%r1, 0x0, %pred2
	  shld,4,sm	%g18, 0x3, %g18
	  ldd,5,sm	%r2, 0x0, %g19
	}
	{
	  disp	%ctpr1, $.L185; ipd 2
	  subd,1,sm	%g17, 0x8, %g17
	  ldd,2,sm	%r2, 0x0, %g20
	  subs,3,sm	%r1, 0x1, %r9
	  subd,4,sm	%g18, 0x8, %g18
	  pass	%pred0, @p0
	  pass	%pred1, @p1
	  landp	~@p0, @p1, @p4
	  pass	@p4, %pred3
	  landp	~@p0, ~@p1, @p5
	  pass	@p5, %pred1
	  pass	%pred2, @p2
	  landp	@p5, @p2, @p6
	  pass	@p6, %pred4
	}
	{
	  ldd,0,sm	%r2, %g17, %r7
	  subd,1	0x0, 0x1, %r0 ? %pred0
	  ldd,3,sm	%r2, %g18, %r8
	  pass	%pred1, @p0
	  pass	%pred2, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred2
	}
	{
	  ct	%ctpr3 ? %pred0
	  shrd,0	%g16, 0x3, %r6 ? %pred3
	  adds,1	0x0, %r9, %r16 ? %pred1
	  addd,3,sm	%g19, _f16s,_lts0lo 0x308, %g16
	  addd,4,sm	0x8, %g19, %g17
	  addd,5	0x0, %g19, %r13 ? %pred3
	}
	{
	  disp	%ctpr3, $.L1386; ipd 2
	  cmpesb,0,sm	%r6, 0x0, %pred0
	  addd,1	0x0, %g20, %r15 ? %pred1
	  subs,2	%r6, 0x1, %r12 ? %pred3
	  addd,3,sm	%g19, _f16s,_lts0lo 0x300, %g18
	}
	{
	  ct	%ctpr2 ? %pred4
	  addd,0,sm	%r7, _f16s,_lts0lo 0x2f8, %g21
	  subd,1,sm	%r7, 0x8, %g22
	  addd,2,sm	%g20, _f16s,_lts0hi 0x61, %g23
	  addd,3	0x0, %r8, %r14 ? %pred1
	  addd,4,sm	%r8, _f16s,_lts1lo 0x5f, %g24
	  subd,5,sm	%r8, 0x1, %g25
	  pass	%pred3, @p0
	  pass	%pred0, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred1
	  landp	@p0, ~@p1, @p5
	  pass	@p5, %pred0
	}
	{
	  disp	%ctpr2, $.L1344; ipd 2
	  cmpledb,0,sm	%g16, %g21, %pred4
	  cmpledb,1,sm	%g16, %g22, %pred5
	  addd,2,sm	0x1, %g20, %g26
	  addd,3,sm	%r7, _f16s,_lts0lo 0x300, %g16
	  addd,4,sm	%g20, _f16s,_lts0hi 0x60, %g21
	  addd,5	0x0, %r7, %r11 ? %pred3
	}
	{
	  cmpledb,0,sm	%g17, %g22, %pred3
	  cmpledb,1,sm	%g23, %g24, %pred6
	  addd,2,sm	%r8, _f16s,_lts0lo 0x60, %g17
	  cmpledb,3,sm	%g23, %g25, %pred7
	  cmpledb,4,sm	%g16, %g18, %pred9
	  pass	%pred4, @p0
	  pass	%pred5, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred8
	  pass	%pred0, @p2
	  landp	@p2, @p0, @p5
	  pass	@p5, %pred4
	}
	{
	  ct	%ctpr1 ? %pred1
	  cmpledb,0,sm	%g26, %g25, %pred10
	  cmpledb,1,sm	%g17, %g21, %pred5
	  cmpledb,3,sm	%r7, %g18, %pred11
	  cmpledb,4,sm	%r7, %g19, %pred12
	  pass	%pred8, @p0
	  pass	%pred3, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred8
	  pass	%pred5, @p2
	  landp	@p2, @p1, @p5
	  pass	@p5, %pred3
	  pass	%pred4, @p3
	  landp	@p3, @p5, @p6
	  pass	@p6, %pred4
	}
	{
	  disp	%ctpr1, $.L1365; ipd 2
	  cmpledb,0,sm	%r8, %g21, %pred3
	  cmpledb,1,sm	%r8, %g20, %pred8
	  pass	%pred0, @p0
	  pass	%pred8, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred0
	  pass	%pred6, @p2
	  pass	%pred7, @p3
	  landp	@p2, @p3, @p5
	  pass	@p5, %pred1
	}
	{
	  pass	%pred1, @p0
	  pass	%pred10, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred1
	  pass	%pred0, @p2
	  pass	%pred9, @p3
	  landp	@p2, @p3, @p5
	  pass	@p5, %pred13
	  landp	@p2, ~@p3, @p6
	  pass	@p6, %pred0
	}
	{
	  ct	%ctpr2 ? %pred4
	  pass	%pred2, @p0
	  pass	%pred1, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred1
	  pass	%pred5, @p2
	  landp	@p4, @p2, @p5
	  pass	@p5, %pred5
	  pass	%pred6, @p3
	  landp	@p0, @p3, @p6
	  pass	@p6, %pred2
	}
	{
	  pass	%pred7, @p0
	  pass	%pred10, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred1
	  pass	%pred2, @p2
	  landp	@p2, @p4, @p5
	  pass	@p5, %pred2
	}
	{
	  ct	%ctpr3 ? %pred0
	  pass	%pred13, @p0
	  pass	%pred11, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred1
	  pass	%pred12, @p2
	  landp	@p4, @p2, @p5
	  pass	@p5, %pred4
	  landp	@p4, ~@p2, @p6
	  pass	@p6, %pred6
	}
	{
	  pass	%pred5, @p0
	  pass	%pred3, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred0
	  pass	%pred8, @p2
	  landp	@p4, @p2, @p5
	  pass	@p5, %pred1
	  landp	@p0, ~@p1, @p6
	  pass	@p6, %pred3
	}
	{
	  ct	%ctpr1 ? %pred2
	  pass	%pred13, @p0
	  pass	%pred11, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred0
	}
	{
	  ct	%ctpr2 ? %pred4
	}
	{
	  ct	%ctpr1 ? %pred1
	  disp	%ctpr2, $.L1499; ipd 2
	}
	{
	  ct	%ctpr3 ? %pred6
	}
	{
	  ct	%ctpr3 ? %pred0
	}
	{
	  ct	%ctpr2 ? %pred3
	}
$.L1499:
	{
	  setwd	wsz = 0xe, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x4, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L1232; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1,sm	%r16, 0x1, %g16
	  subs,2	0x0, 0x1, %r1
	  addd,3,sm	0x0, %r14, %r0
	}
	{
	  disp	%ctpr3, $.L70; ipd 2
	  cmpesb,0,sm	%g16, %r1, %pred1
	  subs,1,sm	%r16, 0x2, %b[3]
	  addd,2,sm	0x0, %r15, %b[6]
	}
	{
	  ldb,0,sm	%b[6], 0x0, %b[9], mas=0x4
	  addd,1,sm	%b[6], 0x1, %b[4]
	  addd,2,sm	%b[6], 0x2, %b[2]
	}
	{
	  nop 1
	  ldb,0,sm	%b[4], 0x0, %b[7], mas=0x4
	}
$.L1232:
	{
	  loop_mode
	  cmpesb,3,sm	%b[3], %r1, %pred0
	  subs,4,sm	%b[3], 0x1, %b[1]
	  ldb,5	%b[6], 0x0, %b[9], mas=0x3 ? %pcnt0
	}
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[2], 0x1, %b[0]
	  ldb,3,sm	%b[2], 0x0, %b[5], mas=0x4
	  addd,4,sm	%r0, 0x1, %r0
	  stb,5	%r0, 0x0, %b[9]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	  addd,0	0x0, 0x0, %g16
	}
	{
	  ct	%ctpr3
	  mmurw,2	%g16, %dam_inv
	}
$.L1344:
	{
	  setwd	wsz = 0x13, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x9, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x3
	  disp	%ctpr1, $.L163; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1,sm	%r12, 0x3, %g16
	  subs,2	0x0, 0x1, %r0
	  subs,3,sm	%r12, 0x2, %g17
	  subs,4,sm	%r12, 0x1, %g18
	}
	{
	  cmpesb,1,sm	%g16, %r0, %pred1
	  ldd,2,sm	%r13, 0x0, %b[9]
	  ldd,3,sm	%r13, 0x8, %b[7]
	  addd,4,sm	%r13, _f16s,_lts0hi 0x28, %b[16]
	  ldd,5,sm	%r13, _f16s,_lts0lo 0x10, %b[5]
	}
	{
	  ldd,0,sm	%r13, _f16s,_lts0lo 0x18, %b[3]
	  cmpesb,1,sm	%g17, %r0, %pred2
	  subs,2,sm	%r12, 0x5, %b[13]
	  addd,3,sm	%r13, _f16s,_lts0hi 0x20, %b[18]
	  cmpesb,4,sm	%g18, %r0, %pred3
	  subs,5,sm	%r12, 0x4, %b[15]
	}
	{
	  nop 1
	  addd,0,sm	%r11, 0x8, %b[10]
	  addd,1,sm	0x0, %r11, %b[12]
	}
$.L163:
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred3 && %NOT_LOOP_END
	  ldd,0,sm	%b[18], 0x0, %b[1]
	  cmpesb,1,sm	%b[15], %r0, %pred0
	  std,2	%b[12], 0x0, %b[9]
	  addd,3,sm	%b[16], 0x8, %b[14]
	  subs,4,sm	%b[13], 0x1, %b[11]
	  addd,5,sm	%b[10], 0x8, %b[8]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	}
$.L185:
	{
	  return	%ctpr3; ipd 2
	  cmpesb,0,sm	%r6, 0x0, %pred0
	  adds,1	0x1, 0x0, %r4
	  subs,2	%r5, 0x1, %r12
	  subd,3,sm	%r7, 0x8, %r10
	  addd,4,sm	%r7, _f16s,_lts0lo 0x2f8, %r11
	  addd,5,sm	%r7, _f16s,_lts0hi 0x300, %r8
	}
	{
	  cmplsb,0	0x1, %r12, %pred1
	  subs,1,sm	%r6, 0x1, %r9
	}
	{
	  nop 1
	  pass	%pred1, @p0
	  pass	%pred0, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred0
	}
	{
	  nop 1
	  addd,0	0x0, 0x0, %r0 ? ~%pred0
	}
	{
	  ct	%ctpr3 ? ~%pred0
	}
	{
	  ldd,0,sm	0x8, %r2, %g16, mas=0x20
	  addd,1	0x0, %r2, %g17
	  addd,2,sm	%r2, 0x8, %g18
	}
	{
	  nop 7
	  ldd,0	0x8, %g17, %r1
	  ldb,2,sm	0x8, %g18, %empty, mas=0x20
	}
	{
	  ldb,0,sm	%g16, 0x0, %empty, mas=0x20
	}
$.L880:
	{
	  disp	%ctpr3, $.L1407; ipd 2
	  addd,0,sm	%r2, _f16s,_lts0lo 0x10, %g18
	  addd,1	0x0, %r7, %r5
	  ldd,2,sm	%r2, _lit16_ref,_lts0lo 0x10, %g16, mas=0x20
	  adds,3	0x0, %r9, %r6
	  addd,5	0x8, %r1, %g17
	}
	{
	  disp	%ctpr2, $.L1430; ipd 2
	  ldb,0,sm	0x8, %g18, %empty, mas=0x20
	  cmpledb,1,sm	%r7, %r1, %pred1
	  addd,2	%r1, _f16s,_lts0lo 0x300, %g19
	  addd,3	%r2, 0x8, %r2
	  cmpledb,4,sm	%g17, %r10, %pred0
	  addd,5	%r1, _f16s,_lts0hi 0x308, %g20
	}
	{
	  cmpledb,0,sm	%r8, %g19, %pred2
	  cmpledb,1,sm	%r7, %g19, %pred5
	  cmpledb,3,sm	%g20, %r10, %pred3
	  cmpledb,4	%g20, %r11, %pred4
	}
	{
	  pass	%pred4, @p0
	  pass	%pred3, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred3
	  pass	%pred0, @p2
	  landp	@p4, @p2, @p5
	  pass	@p5, %pred0
	}
	{
	  pass	%pred2, @p0
	  pass	%pred5, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred3
	  pass	%pred1, @p2
	  landp	@p4, @p2, @p5
	  pass	@p5, %pred1
	  pass	%pred0, @p3
	  landp	~@p3, ~@p0, @p6
	  pass	@p6, %pred2
	}
	{
	  nop 3
	  pass	%pred0, @p0
	  pass	%pred1, @p1
	  landp	~@p0, @p1, @p4
	  pass	@p4, %pred1
	  landp	~@p0, ~@p4, @p5
	  pass	@p5, %pred0
	}
	{
	  ct	%ctpr3 ? ~%pred0
	  ldb,0,sm	%g16, 0x0, %empty, mas=0x20
	}
	{
	  ct	%ctpr2 ? %pred2
	}
$.L1430:
	{
	  setwd	wsz = 0x12, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x8, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L948; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1,sm	%r6, 0x1, %g16
	  subs,2	0x0, 0x1, %r0
	}
	{
	  disp	%ctpr3, $.L892; ipd 2
	  cmpesb,0,sm	%g16, %r0, %pred1
	  addd,1,sm	%r1, 0x8, %g17
	  subs,2,sm	%r6, 0x2, %b[15]
	  ldd,3,sm	%r5, 0x0, %b[12]
	  addd,4,sm	%r5, _f16s,_lts0lo 0x10, %b[2]
	  ldd,5,sm	%r5, 0x8, %b[10]
	}
	{
	  ldd,0,sm	%r1, 0x0, %b[11], mas=0x4
	  addd,1,sm	%r1, _f16s,_lts0lo 0x10, %b[3]
	  addd,2,sm	0x0, %r1, %b[7]
	  addd,3,sm	%r5, 0x8, %b[4]
	  addd,4,sm	0x0, %r5, %b[6]
	}
	{
	  nop 2
	  ldd,0,sm	%g17, 0x0, %b[9], mas=0x4
	  addd,1,sm	0x0, %g17, %b[5]
	}
$.L948:
	{
	  loop_mode
	  rbranch	$.L2678
	  ldd,0,sm	%b[2], 0x0, %b[8]
	  addd,2,sm	%b[2], 0x8, %b[0]
	  cmpesb,3,sm	%b[15], %r0, %pred0
	  xord,4,sm	%b[12], %b[11], %b[14]
	  ldd,5	%b[7], 0x0, %b[11], mas=0x3 ? %pcnt0
	}
$.L2684:
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[3], 0x8, %b[1]
	  ldd,3,sm	%b[3], 0x0, %b[7], mas=0x4
	  subs,4,sm	%b[15], 0x1, %b[13]
	  std,5	%b[6], 0x0, %b[14]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	  addd,0	0x0, 0x0, %g16
	}
	{
	  ct	%ctpr3
	  mmurw,2	%g16, %dam_inv
	}
$.L1407:
	{
	  setwd	wsz = 0x11, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x7, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L921; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1	0x0, 0x1, %r0
	  subs,2,sm	%r6, 0x1, %g16
	}
	{
	  cmpesb,1,sm	%g16, %r0, %pred1
	  ldd,2,sm	%r1, 0x0, %b[9]
	  ldd,3,sm	%r1, 0x8, %b[7]
	  addd,4,sm	%r1, _f16s,_lts0lo 0x10, %b[13]
	  subs,5,sm	%r6, 0x2, %b[10]
	}
	{
	  nop 3
	  ldd,0,sm	%r5, 0x0, %b[5]
	  addd,1,sm	%r5, _f16s,_lts0lo 0x10, %b[2]
	  ldd,2,sm	%r5, 0x8, %b[3]
	  addd,3,sm	%r5, 0x8, %b[4]
	  addd,4,sm	0x0, %r5, %b[6]
	}
$.L921:
	{
	  loop_mode
	  ldd,0,sm	%b[2], 0x0, %b[1]
	  cmpesb,3,sm	%b[10], %r0, %pred0
	  xord,4,sm	%b[5], %b[9], %b[14]
	  addd,5,sm	%b[2], 0x8, %b[0]
	}
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[13], 0x8, %b[11]
	  ldd,3,sm	%b[13], 0x0, %b[5]
	  subs,4,sm	%b[10], 0x1, %b[8]
	  std,5	%b[6], 0x0, %b[14]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	}
$.L892:
	{
	  disp	%ctpr1, $.L880; ipd 2
	  adds,0	%r4, 0x1, %r4
	  addd,1,sm	0x0, %r2, %g16
	}
	{
	  nop 1
	  return	%ctpr3; ipd 2
	  ldd,0,sm	0x8, %g16, %r1
	  cmplsb,1	%r4, %r12, %pred0
	}
	{
	  addd,0	0x0, 0x0, %r0 ? ~%pred0
	}
	{
	  ct	%ctpr3 ? ~%pred0
	}
	{
	  ct	%ctpr1 ? %pred0
	}
$.L1386:
	{
	  setwd	wsz = 0xe, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x4, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L848; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1,sm	%r12, 0x1, %g16
	  subs,2	0x0, 0x1, %r1
	  addd,3,sm	0x0, %r11, %r0
	}
	{
	  disp	%ctpr3, $.L185; ipd 2
	  cmpesb,0,sm	%g16, %r1, %pred1
	  addd,1,sm	%r13, 0x8, %g17
	  subs,2,sm	%r12, 0x2, %b[3]
	}
	{
	  ldd,0,sm	%r13, 0x0, %b[9], mas=0x4
	  addd,1,sm	%r13, _f16s,_lts0lo 0x10, %b[2]
	  addd,2,sm	0x0, %r13, %b[6]
	}
	{
	  nop 1
	  ldd,0,sm	%g17, 0x0, %b[7], mas=0x4
	  addd,1,sm	0x0, %g17, %b[4]
	}
$.L848:
	{
	  loop_mode
	  cmpesb,3,sm	%b[3], %r1, %pred0
	  subs,4,sm	%b[3], 0x1, %b[1]
	  ldd,5	%b[6], 0x0, %b[9], mas=0x3 ? %pcnt0
	}
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[2], 0x8, %b[0]
	  ldd,3,sm	%b[2], 0x0, %b[5], mas=0x4
	  addd,4,sm	%r0, 0x8, %r0
	  std,5	%r0, 0x0, %b[9]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	  addd,0	0x0, 0x0, %g16
	}
	{
	  ct	%ctpr3
	  mmurw,2	%g16, %dam_inv
	}
$.L1365:
	{
	  setwd	wsz = 0x13, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x9, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x3
	  disp	%ctpr1, $.L48; ipd 2
	  ldb,0,sm	%r15, 0x0, %g16
	  subs,1,sm	%r16, 0x3, %g20
	  ldb,2,sm	%r15, 0x1, %g17
	  ldb,3,sm	%r15, 0x2, %g18
	  subs,4	0x0, 0x1, %r0
	  ldb,5,sm	%r15, 0x3, %g19
	}
	{
	  rwd,0	_f64,_lts0 0x20ff0000000000, %lsr
	  subs,1,sm	%r16, 0x2, %g21
	  subs,2,sm	%r16, 0x1, %g22
	  addd,3,sm	%r15, 0x5, %b[16]
	  subs,4,sm	%r16, 0x5, %b[13]
	  addd,5,sm	%r15, 0x4, %b[18]
	}
	{
	  cmpesb,0,sm	%g20, %r0, %pred1
	  cmpesb,1,sm	%g21, %r0, %pred2
	  subs,2,sm	%r16, 0x4, %b[15]
	  addd,3,sm	%r14, 0x1, %b[10]
	  addd,4,sm	0x0, %r14, %b[12]
	}
	{
	  nop 2
	  cmpesb,0,sm	%g22, %r0, %pred3
	  addd,1,sm	0x0, %g16, %b[9]
	  addd,2,sm	0x0, %g17, %b[7]
	  addd,3,sm	0x0, %g18, %b[5]
	  addd,4,sm	0x0, %g19, %b[3]
	}
$.L48:
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred3 && %NOT_LOOP_END
	  ldb,0,sm	%b[18], 0x0, %b[1]
	  cmpesb,1,sm	%b[15], %r0, %pred0
	  stb,2	%b[12], 0x0, %b[9]
	  addd,3,sm	%b[16], 0x1, %b[14]
	  subs,4,sm	%b[13], 0x1, %b[11]
	  addd,5,sm	%b[10], 0x1, %b[8]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	}
$.L70:
	{
	  return	%ctpr3; ipd 2
	  cmpesb,0,sm	%r10, 0x0, %pred0
	  adds,1	0x1, 0x0, %r1
	  subs,2	%r5, 0x1, %r13
	  addd,3,sm	%r8, _f16s,_lts0lo 0x5f, %r11
	  addd,4,sm	%r8, _f16s,_lts0hi 0x60, %r12
	  subd,5,sm	%r8, 0x1, %r10
	}
	{
	  cmplsb,0	0x1, %r13, %pred1
	}
	{
	  nop 1
	  pass	%pred1, @p0
	  pass	%pred0, @p1
	  landp	@p0, ~@p1, @p4
	  pass	@p4, %pred0
	}
	{
	  nop 1
	  addd,0	0x0, 0x0, %r0 ? ~%pred0
	}
	{
	  ct	%ctpr3 ? ~%pred0
	}
	{
	  ldd,0,sm	0x8, %r2, %g16, mas=0x20
	  addd,1,sm	%r2, 0x8, %g17
	  addd,2	0x0, %r2, %r4
	}
	{
	  nop 7
	  ldb,0,sm	0x8, %g17, %empty, mas=0x20
	}
	{
	  ldb,0,sm	%g16, 0x0, %empty, mas=0x20
	}
$.L974:
	{
	  disp	%ctpr3, $.L1453; ipd 2
	  ldd,0	0x8, %r4, %r4
	  addd,1	0x0, %r8, %g17
	  ldd,2,sm	%r2, _f16s,_lts0lo 0x10, %g16, mas=0x20
	  adds,3,sm	0x0, %r9, %r5
	}
	{
	  disp	%ctpr2, $.L1476; ipd 2
	  addd,0,sm	%r2, _f16s,_lts0lo 0x10, %g18
	  addd,1	%r2, 0x8, %r2
	  addd,2,sm	0x0, %g17, %r6
	}
	{
	  ldb,0,sm	0x8, %g18, %empty, mas=0x20
	  addd,1,sm	0x0, %g17, %r7
	}
	{
	  addd,0	%r4, _f16s,_lts0hi 0x60, %g18
	  addd,1	0x1, %r4, %g19
	  addd,2	%r4, _f16s,_lts0lo 0x61, %g17
	}
	{
	  cmpledb,0,sm	%g17, %r10, %pred0
	  cmpledb,1	%g17, %r11, %pred1
	  cmpledb,3,sm	%r8, %r4, %pred2
	}
	{
	  cmpledb,0,sm	%r12, %g18, %pred3
	  cmpledb,1,sm	%g19, %r10, %pred1
	  cmpledb,3,sm	%r8, %g18, %pred4
	  pass	%pred1, @p0
	  pass	%pred0, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred0
	}
	{
	  pass	%pred0, @p0
	  pass	%pred1, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred0
	  pass	%pred3, @p2
	  pass	%pred4, @p3
	  landp	@p2, @p3, @p5
	  pass	@p5, %pred1
	  landp	~@p4, ~@p2, @p6
	  pass	@p6, %pred3
	}
	{
	  nop 1
	  pass	%pred1, @p0
	  pass	%pred2, @p1
	  landp	@p0, @p1, @p4
	  pass	@p4, %pred1
	  pass	%pred0, @p2
	  landp	~@p2, @p4, @p5
	  pass	@p5, %pred2
	}
	{
	  ct	%ctpr3 ? %pred0
	  ldb,0,sm	%g16, 0x0, %empty, mas=0x20
	}
	{
	  ct	%ctpr3 ? %pred2
	}
	{
	  ct	%ctpr2 ? %pred3
	}
$.L1476:
	{
	  setwd	wsz = 0x12, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x8, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L1042; ipd 2
	  rwd,0	_f64,_lts1 0x20ff0000000000, %lsr
	  subs,1,sm	%r5, 0x1, %g18
	  ldb,2,sm	%r7, 0x0, %g16
	  ldb,3,sm	%r7, 0x1, %g17
	  subs,4	0x0, 0x1, %r0
	}
	{
	  disp	%ctpr3, $.L986; ipd 2
	  addd,1,sm	%r4, 0x1, %g19
	  subs,2,sm	%r5, 0x2, %b[15]
	  addd,3,sm	%r7, 0x2, %b[2]
	  addd,4,sm	%r7, 0x1, %b[4]
	  addd,5,sm	0x0, %r7, %b[6]
	}
	{
	  ldb,0,sm	%r4, 0x0, %b[11], mas=0x4
	  cmpesb,1,sm	%g18, %r0, %pred1
	  addd,2,sm	%r4, 0x2, %b[3]
	  addd,3,sm	0x0, %r4, %b[7]
	}
	{
	  nop 2
	  ldb,0,sm	%g19, 0x0, %b[9], mas=0x4
	  addd,1,sm	0x0, %g19, %b[5]
	  addd,2,sm	0x0, %g16, %b[12]
	  addd,3,sm	0x0, %g17, %b[10]
	}
$.L1042:
	{
	  loop_mode
	  rbranch	$.L2689
	  ldb,0,sm	%b[2], 0x0, %b[8]
	  addd,2,sm	%b[2], 0x1, %b[0]
	  cmpesb,3,sm	%b[15], %r0, %pred0
	  xors,4,sm	%b[12], %b[11], %b[14]
	  ldb,5	%b[7], 0x0, %b[11], mas=0x3 ? %pcnt0
	}
$.L2695:
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[3], 0x1, %b[1]
	  ldb,3,sm	%b[3], 0x0, %b[7], mas=0x4
	  subs,4,sm	%b[15], 0x1, %b[13]
	  stb,5	%b[6], 0x0, %b[14]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	  addd,0	0x0, 0x0, %g16
	}
	{
	  ct	%ctpr3
	  mmurw,2	%g16, %dam_inv
	}
$.L1453:
	{
	  setwd	wsz = 0x11, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x7, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x1
	  disp	%ctpr1, $.L1015; ipd 2
	  ldb,0,sm	%r4, 0x0, %g16
	  subs,1,sm	%r5, 0x1, %g20
	  ldb,2,sm	%r4, 0x1, %g17
	  ldb,3,sm	%r6, 0x0, %g18
	  subs,4	0x0, 0x1, %r0
	  ldb,5,sm	%r6, 0x1, %g19
	}
	{
	  rwd,0	_f64,_lts0 0x20ff0000000000, %lsr
	  addd,1,sm	%r4, 0x2, %b[13]
	  subs,2,sm	%r5, 0x2, %b[10]
	  addd,3,sm	%r6, 0x2, %b[2]
	  addd,4,sm	%r6, 0x1, %b[4]
	  addd,5,sm	0x0, %r6, %b[6]
	}
	{
	  cmpesb,0,sm	%g20, %r0, %pred1
	}
	{
	  nop 1
	  addd,0,sm	0x0, %g16, %b[9]
	  addd,1,sm	0x0, %g17, %b[7]
	  addd,3,sm	0x0, %g18, %b[5]
	  addd,4,sm	0x0, %g19, %b[3]
	}
$.L1015:
	{
	  loop_mode
	  ldb,0,sm	%b[2], 0x0, %b[1]
	  cmpesb,3,sm	%b[10], %r0, %pred0
	  xors,4,sm	%b[5], %b[9], %b[14]
	  addd,5,sm	%b[2], 0x1, %b[0]
	}
	{
	  loop_mode
	  alc	alcf=1, alct=1
	  abn	abnf=1, abnt=1
	  abp	abpf=1, abpt=1
	  ct	%ctpr1 ? ~%pred1 && %NOT_LOOP_END
	  addd,2,sm	%b[13], 0x1, %b[11]
	  ldb,3,sm	%b[13], 0x0, %b[5]
	  subs,4,sm	%b[10], 0x1, %b[8]
	  stb,5	%b[6], 0x0, %b[14]
	}
	{
	  setwd	wsz = 0xa, nfx = 0x1, dbl = 0x0
	  setbn	rsz = 0x0, rbs = 0x9, rcur = 0x0
	  setbp	psz = 0x0
	}
$.L986:
	{
	  disp	%ctpr1, $.L974; ipd 2
	  adds,0	%r1, 0x1, %r1
	  addd,1,sm	0x0, %r2, %r4
	}
	{
	  nop 1
	  return	%ctpr3; ipd 2
	  cmplsb,0	%r1, %r13, %pred0
	}
	{
	  addd,0	0x0, 0x0, %r0 ? ~%pred0
	}
	{
	  ct	%ctpr3 ? ~%pred0
	}
	{
	  ct	%ctpr1 ? %pred0
	}
$.L2678:
	{
	  ibranch	$.L2684
	  xord,0,sm	%b[12], %b[11], %b[14]
	}
$.L2689:
	{
	  ibranch	$.L2695
	  xors,0,sm	%b[12], %b[11], %b[14]
	}
	.size	$xor_gen, .- $xor_gen
	.weak	$elbrus_optimizing_compiler_v1.21.19_May_18_2017
	.set	$elbrus_optimizing_compiler_v1.21.19_May_18_2017, 0x0
