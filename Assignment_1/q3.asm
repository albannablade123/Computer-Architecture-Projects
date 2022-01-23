 # Hasan Al Banna 110510278 Question 3
.data 
	newLine: .asciiz " "
	prompt: .asciiz "Size of the array?: "
	promptArraySize: .asciiz "Size of the array: "
	resultLine: .asciiz "Your sorted array is: "
	point: .asciiz "."
	colon: .asciiz " : "
	nextline: .asciiz "\n"
	spacing: .asciiz ", "
	Intput: .asciiz "Input  :"
	array: .word 40
 .text
    .globl main
main:
    add $t3, $t3, $zero #Array size constant
    addi $t4, $t4, 1 #Loop counter
    
    li $v0, 4
    la $a0, prompt
    syscall
    
    li $v0, 5
    syscall 
    move $t3, $v0


    # ==== Modify Array Size ==============
    lw $a0, array
    
    la $a0, array 
    sll $a1, $t3, 2
    sw $a1 0($a0) 
	
    lw $a2, array
     
    move $s5, $a1
    
   # Next Line
    
    li $v0, 4
    la $a0, nextline
    syscall
    
    addi $t3, $t3, 1

input:
    	slt $t5, $t4, $t3 
    	beq $t5, $0, next 
    	
	move $a0, $t4
	li $v0, 1
	syscall
	
	li $v0, 4
	la $a0, colon
	syscall
	
	li $v0, 5
	syscall 
	move $t2, $v0
	
	sw $t2, array($t1)
	addi $t1, $t1, 4
	addi $t4, $t4, 1
	
	j input

next:
    la  $t0, array      # Copy the address of the array to register t0
    add $t0, $t0, $s5
    move $t2, $zero
    move $t3, $zero
    
Loop:           
    add $t1, $0, $0     # $t1 holds a flag to determine when the list is sorted
    la  $a0, array      # Make $a0 to the base address of the Array
    
sorting:                 
    lw  $t2, 0($a0)         # set register t2 as the current element array[i]
    lw  $t3, 4($a0)         # sets register t3 as the next element array[i+1]
    slt $t5, $t2, $t3       # use set less than equal, if $t5 = 1 then $t2 < $t3
    li  $t9, 1
    beq $t5, $0, continue   # if $t5 = 1, then procced to switch their places
    add $t1, $0, $t9         # if we need to swap, we need to check the list again
    sw  $t3, 0($a0)         # store the greater number between the two 
    sw  $t2, 4($a0)         # store the smaller number between the two
    
continue:
    addi $a0, $a0, 4            # Increment the array to the next element
    bne  $a0, $t0, sorting    # If $a0 != the end of Array, jump back to sorting
    bne  $t1, $0, Loop
    
buffer:
	#Print string
	li $v0, 4
        la $a0, resultLine
        syscall
	
	move $t7, $s5
	li $t3, 4
	sub $t7, $t7, $t3
while:
		beq $t7 -4 exit
		
		 #load the first element
		lw $t6, array($t7)

		#increment
		sub $t7, $t7, $t3
		
		#print current number
		li $v0, 1
		move $a0, $t6 
		syscall
		
		#print a new line
		li $v0, 4
		la $a0, newLine
		syscall
		
		j while
	exit:
		#Tell system this is end of program
		li $v0, 10
		syscall 

