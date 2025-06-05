.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

main:
  move $gp, $sp
  addi $sp, $sp, -40
  lw $t0, -4($gp)
  li $t0, 5
  sw $t0, -4($gp)
  lw $t1, -8($gp)
  li $t1, 5
  sw $t1, -8($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t2, -8($gp)
  move $a0, $t2
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $t3, -12($gp)
  li $t3, 0
  sw $t3, -12($gp)
  lw $t4, -12($gp)
  bne $t4, $0, label1
  j label2
label1:
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  li $t5, 114
  move $a0, $t5
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  j label3
label2:
  lw $t6, -16($gp)
  lw $t7, -4($gp)
  addi $t6, $t7, 1
  sw $t6, -16($gp)
  lw $s0, -4($gp)
  lw $s1, -16($gp)
  move $s0, $s1
  sw $s0, -4($gp)
  lw $s2, -8($gp)
  lw $s3, -16($gp)
  move $s2, $s3
  sw $s2, -8($gp)
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $s4, -8($gp)
  move $a0, $s4
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $s5, -28($gp)
  li $s5, 0
  sw $s5, -28($gp)
  lw $s6, -28($gp)
  bne $s6, $0, label4
  j label5
label4:
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  li $s7, 514
  move $a0, $s7
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  j label6
label5:
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t8, -32($gp)
  move $t8, $v0
  sw $t8, -32($gp)
  lw $t9, -4($gp)
  lw $t0, -32($gp)
  move $t9, $t0
  sw $t9, -4($gp)
  lw $t1, -40($gp)
  lw $t2, -32($gp)
  move $t1, $t2
  sw $t1, -40($gp)
  lw $t3, -40($gp)
  bne $t3, $0, label7
  j label8
label7:
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $t4, -4($gp)
  move $a0, $t4
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  j label9
label8:
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  li $t5, 996
  move $a0, $t5
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
label9:
label6:
label3:
  move $v0, $0
  jr $ra
