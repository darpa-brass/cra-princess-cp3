num_regs = 8
instrlist = [
"str %[reg3], [%[reg0], #0x000]",
"str %[reg7], [%[reg0], #0x040]",
"add %[reg3], %[reg0], #0x014",
# we cannot use ^ here
# "stmia %[reg3]!, {%[reg4]-%[reg7]}^",
"stmia %[reg3]!, {%[reg4]-%[reg7]}",
"add %[reg3], %[reg3], #0x008",
# vstmia instructions here
"add %[reg3], %[reg0], #0x010",
"pop {%[reg4]-%[reg5]}",
"stmda %[reg3]!, {%[reg4]-%[reg5]}"
]

for i in range(8):
	print("    // {0}".format(instrlist[i]))
	print("    if (num == {0}) {{".format(i+1))
	print("        asm volatile(")
	print("            \"mov %[reg0],%[reg0]\\n\\tmov %[reg1],%[reg1]\\n\\tmov %[reg2],%[reg2]\\n\\tmov %[reg3],%[reg3]\\n\\tmov %[reg4],%[reg4]\\n\\tmov %[reg5],%[reg5]\\n\\tmrs %[f1],cpsr\\n\\t\"")
	print("            \"{0}\\n\\t\"".format(instrlist[i]))
	print("            \"mrs %[f2],cpsr\\n\\t\"")
	print("            : [f1] \"=r\" (s->cpsr),[f2] \"=r\" (cpsr_),[reg0] \"=r\" (r0_),[reg1] \"=r\" (r1_), [reg2] \"=r\" (r2_), [reg3] \"=r\" (r3_),[reg4] \"=r\" (r4_),[reg5] \"=r\" (r5_)")
	print("            : [reg0] \"r\" (r0_),[reg1] \"r\" (r1_),[reg2] \"r\" (r2_), [reg3] \"r\" (r3_), [reg4] \"r\" (r4_),[reg5] \"r\" (r5_),[reg7] \"r\" (r7_)")
	print("            : \"r0\", \"r1\", \"r2\", \"r3\", \"r4\", \"r5\", \"r7\"")
	print("            );")
	print("    }")
