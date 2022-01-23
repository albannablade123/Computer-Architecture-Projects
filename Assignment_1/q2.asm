.data
	promptMessage: .asciiz "Enter a number for N: "
	resultMsg: .ascii "\nCalculating for F(N)...\nresult of F(N) is: "
	userInput: .word 0
	Result:	.word 0
	
.text 
	.globl main
	main:
	     # Get input from user
	     li $v0, 4
	     la $a0, promptMessage
	     syscall
	     
	     # Store the user value in $v0
	     li $v0, 5
	     syscall
	     
	     # store the value to userInput
	     sw $v0, userInput
	     
	     # call Recursive function
	     lw $a0, userInput
	     jal RecursiveFunction
	     sw $v0, Result
	     
	     # Print and display result
	     li $v0, 4
	     la $a0, resultMsg
	     syscall
	     
	     li $v0, 1
	     lw $a0, Result
	     syscall
	     
	     # Terminate Program
	     li $v0, 10
	     syscall
	     
# Initialize RecursiveFunction

.globl RecursiveFunction
RecursiveFunction:
		# Store the value of the address into the stack
		subu $sp, $sp, 8
		sw $ra, ($sp)
		sw $s0, 4($sp) 
		
		# Base case if 0 return 5
		li $v0, 5
		beq $a0, 0, factorialFinished # if the int is 0 go to factorialFinished
		
		# Function(N - 1)
		add $s0, $zero, $a0
		li $t6, 1
		sub $a0, $a0, $t6
		jal RecursiveFunction
		
		# it'll calculate the previous value($v0) multiplied by 2 and add to current increment which will be stored in ($v0) 
		sll $t1, $v0, 1   #multiply F(n-1)2
		add $v0, $s0, $t1 #add by x
		
		
		factorialFinished:
			lw $ra, ($sp) # restore the value of the ra from stack
			lw $s0, 4($sp) # load the local value to the register
			addu $sp, $sp, 8 # in order to restore the stack we add the value 8
			jr $ra # jump to the previous address
				  
