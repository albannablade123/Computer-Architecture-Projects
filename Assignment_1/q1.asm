.data
	question: .asciiz "Please Enter A positive Integer N: "
	character: .asciiz "*"
	newLine: .asciiz  "\n"
	doneMessage: .asciiz "Done"
	

.text
.globl main

 main:
 	#prompt user input
 	li $v0, 4 
 	la $a0, question
 	syscall 
 	
 	#store user input
 	li $v0, 5 
 	syscall 
 	
 	add $s0, $zero, $v0 
 	
 	add $t1, $zero, $t1 
 	
 	
 ForLoopOne:
 	beq $t1, $s0, exit
 	addi $t1, $t1, 1
 	li $t2, 1
 	
 	jal callNewLine
 	
 ForLoopTwo:
 	bgt $t2, $t1, ForLoopOne
 	
 	li $v0, 4     
        la $a0, character
        syscall 
        
        li $t3, 1
        add $t2, $t2, $t3
        
        j ForLoopTwo
        
 callNewLine:
 	li $v0, 4     
        la $a0, newLine
        syscall 
        
        jr $ra
 exit:
 	li $v0, 4     
        la $a0, newLine
        syscall 
        
 	li $v0, 4     
        la $a0, doneMessage
        syscall 
        
 	li $v0, 10
 	syscall 
 	
 
 	
