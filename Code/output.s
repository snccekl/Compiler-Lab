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

fact:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $t0, -4($gp)
  li $t0, 1
  sw $t0, -4($gp)
  lw $t1, 8($gp)
  lw $t2, -4($gp)
  beq $t1, $t2, label1
  j label2
label1:
  lw $t3, 8($gp)
  move $v0, $t3
  jr $ra
  j label3
label2:
  lw $t4, -8($gp)
  li $t4, 1
  sw $t4, -8($gp)
  lw $t5, -12($gp)
  lw $t6, -8($gp)
  lw $t7, 8($gp)
  sub $t5, $t7, $t6
  sw $t5, -12($gp)
  lw $s0, -16($gp)
  addi $sp, $sp, -72
  sw $t0, 0($sp)
  sw $t1, 4($sp)
  sw $t2, 8($sp)
  sw $t3, 12($sp)
  sw $t4, 16($sp)
  sw $t5, 20($sp)
  sw $t6, 24($sp)
  sw $t7, 28($sp)
  sw $s0, 32($sp)
  sw $s1, 36($sp)
  sw $s2, 40($sp)
  sw $s3, 44($sp)
  sw $s4, 48($sp)
  sw $s5, 52($sp)
  sw $s6, 56($sp)
  sw $s7, 60($sp)
  sw $t8, 64($sp)
  sw $t9, 68($sp)
  addi $sp, $sp, -4
  lw $s1, -12($gp)
  sw $s1, 0($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal fact
  move $sp, $gp
  lw $ra, 0($sp)
  lw $gp, 4($sp)
  addi $sp, $sp, 12
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  lw $t3, 12($sp)
  lw $t4, 16($sp)
  lw $t5, 20($sp)
  lw $t6, 24($sp)
  lw $t7, 28($sp)
  lw $s0, 32($sp)
  lw $s1, 36($sp)
  lw $s2, 40($sp)
  lw $s3, 44($sp)
  lw $s4, 48($sp)
  lw $s5, 52($sp)
  lw $s6, 56($sp)
  lw $s7, 60($sp)
  lw $t8, 64($sp)
  lw $t9, 68($sp)
  addi $sp, $sp, 72
  move $s0, $v0
  sw $s0, -16($gp)
  lw $s2, -20($gp)
  lw $s3, -16($gp)
  lw $s4, 8($gp)
  mul $s2, $s4, $s3
  sw $s2, -20($gp)
  lw $s5, -20($gp)
  move $v0, $s5
  jr $ra
label3:

main:
  move $gp, $sp
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal read
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t0, -4($gp)
  move $t0, $v0
  sw $t0, -4($gp)
  lw $t1, -8($gp)
  lw $t2, -4($gp)
  move $t1, $t2
  sw $t1, -8($gp)
  lw $t3, -12($gp)
  li $t3, 1
  sw $t3, -12($gp)
  lw $t4, -8($gp)
  lw $t5, -12($gp)
  bgt $t4, $t5, label4
  j label5
label4:
  lw $t6, -16($gp)
  addi $sp, $sp, -72
  sw $t0, 0($sp)
  sw $t1, 4($sp)
  sw $t2, 8($sp)
  sw $t3, 12($sp)
  sw $t4, 16($sp)
  sw $t5, 20($sp)
  sw $t6, 24($sp)
  sw $t7, 28($sp)
  sw $s0, 32($sp)
  sw $s1, 36($sp)
  sw $s2, 40($sp)
  sw $s3, 44($sp)
  sw $s4, 48($sp)
  sw $s5, 52($sp)
  sw $s6, 56($sp)
  sw $s7, 60($sp)
  sw $t8, 64($sp)
  sw $t9, 68($sp)
  addi $sp, $sp, -4
  lw $t7, -8($gp)
  sw $t7, 0($sp)
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $gp, 4($sp)
  jal fact
  move $sp, $gp
  lw $ra, 0($sp)
  lw $gp, 4($sp)
  addi $sp, $sp, 12
  lw $t0, 0($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)
  lw $t3, 12($sp)
  lw $t4, 16($sp)
  lw $t5, 20($sp)
  lw $t6, 24($sp)
  lw $t7, 28($sp)
  lw $s0, 32($sp)
  lw $s1, 36($sp)
  lw $s2, 40($sp)
  lw $s3, 44($sp)
  lw $s4, 48($sp)
  lw $s5, 52($sp)
  lw $s6, 56($sp)
  lw $s7, 60($sp)
  lw $t8, 64($sp)
  lw $t9, 68($sp)
  addi $sp, $sp, 72
  move $t6, $v0
  sw $t6, -16($gp)
  lw $s0, -20($gp)
  lw $s1, -16($gp)
  move $s0, $s1
  sw $s0, -20($gp)
  j label6
label5:
  lw $s2, -24($gp)
  li $s2, 1
  sw $s2, -24($gp)
  lw $s3, -20($gp)
  lw $s4, -24($gp)
  move $s3, $s4
  sw $s3, -20($gp)
label6:
  addi $sp, $sp, -8
  sw $a0, 0($sp)
  sw $ra, 4($sp)
  lw $s5, -20($gp)
  move $a0, $s5
  jal write
  lw $a0, 0($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  lw $s6, -32($gp)
  li $s6, 0
  sw $s6, -32($gp)
  lw $s7, -32($gp)
  move $v0, $s7
  jr $ra
