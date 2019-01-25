instrs = ["ADD", "LSL", "LSR", "AND", "LDR", "STR"]
num_regs = 9

for instr in instrs:
	print("if (instr->type == {0}) {{".format(instr))
	for dest in range(0, num_regs):
		print("    if (instr->dest == {0}) {{".format(dest))
		for src in range(0, num_regs):
			print("        if (instr->src == {0}) {{".format(src))
			print("            asm volatile(")
			print("                \"mov %[reg0],%[reg0]\\n\\tmov %[reg1],%[reg1]\\n\\tmov %[reg2],%[reg2]\\n\\tmov %[reg3],%[reg3]\\n\\tmov %[reg4],%[reg4]\\n\\tmov %[reg5],%[reg5]\\n\\tmov %[reg6],%[reg6]\\n\\tmov %[reg7],%[reg7]\\n\\tmov %[reg8],%[reg8]\\n\\tmrs %[f1],cpsr\\n\\t\"")
			if instr == "ADD":
				print("                \"adds %[reg{0}],%[reg{1}],%[imm]\\n\\t\"".format(dest,src))
			if instr == "LSL":
				print("                \"lsls %[reg{0}],%[reg{1}],%[imm]\\n\\t\"".format(dest,src))
			if instr == "LSR":
				print("                \"lsrs %[reg{0}],%[reg{1}],%[imm]\\n\\t\"".format(dest,src))
			if instr == "AND":
				print("                \"ands %[reg{0}],%[reg{1}],%[imm]\\n\\t\"".format(dest,src))
			if instr == "LDR":
				print("                \"ldr %[reg{0}],[%[reg{1}],%[imm]]\\n\\t\"".format(dest,src))
			if instr == "STR":
				print("                \"str %[reg{0}],[%[reg{1}],%[imm]]\\n\\t\"".format(dest,src))
			print("                \"mrs %[f2],cpsr\\n\\t\"")
			print("                : [f1] \"=r\" (s->cpsr),[f2] \"=r\" (cpsr_),[reg0] \"=r\" (r0_),[reg1] \"=r\" (r1_), [reg2] \"=r\" (r2_), [reg3] \"=r\" (r3_),[reg4] \"=r\" (r4_),[reg5] \"=r\" (r5_),[reg6] \"=r\" (r6_),[reg7] \"=r\" (r7_),[reg8] \"=r\" (r8_)")
			print("                : [imm] \"r\" (instr->imm),[reg0] \"r\" (r0_),[reg1] \"r\" (r1_),[reg2] \"r\" (r2_), [reg3] \"r\" (r3_), [reg4] \"r\" (r4_),[reg5] \"r\" (r5_),[reg6] \"r\" (r6_),[reg7] \"r\" (r7_),[reg8] \"r\" (r8_)")
			print("                : \"r0\", \"r1\", \"r2\", \"r3\", \"r4\", \"r5\", \"r6\", \"r7\", \"r8\"")
			print("            );")
			print("        }")
		print("    }")
	print("}")
