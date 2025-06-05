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
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  addi $sp, $sp, -4
  lw $0, -8($fp)
  li $0, 1
  sw $0, -8($fp)
  lw $at, -388($fp)
  lw $v0, -8($fp)
  move $at, $v0
  sw $at, -388($fp)
  lw $v1, -16($fp)
  li $v1, 2
  sw $v1, -16($fp)
  lw $a0, -392($fp)
  lw $a1, -16($fp)
  move $a0, $a1
  sw $a0, -392($fp)
  lw $a2, -20($fp)
  lw $a3, -392($fp)
  lw $t0, -388($fp)
  add $a2, $t0, $a3
  sw $a2, -20($fp)
  lw $t1, -388($fp)
  lw $t2, -20($fp)
  move $t1, $t2
  sw $t1, -388($fp)
  lw $t3, -36($fp)
  li $t3, 0
  sw $t3, -36($fp)
  lw $t4, -36($fp)
  move $v0, $t4
  jr $ra
