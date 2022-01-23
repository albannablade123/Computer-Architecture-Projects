Q1.Assembly Language Programming in MIPS
Definition: In this question, you are asked to implement an assembly application in MIPS ISA. Your application first asks a positive integer value; N, from the console. Then, it prints a NxN right triangle to the screen by using * s. For input 7, your output should be as in the example:
     * 
     * * 
     * * * 
     * * * * 
     * * * * * 
     * * * * * * 
     * * * * * * *
Q2.Assembly Language, Programming a Recursive Method in MIPS
Definition: In this question, you are asked to implement a recursive code assembly in MIPS ISA. 
Your application should ask an N value from the console. Then it calculates the F(N) according to the given definition of f(x).
F(x) = f(x)={█(5,&x=0@2f(x)+ x,&x>0)┤
Q3.Assembly Language, Programming with Arrays in MIPS
Definition: In this question, you are asked to implement an assembly code in MIPS, which operates on arrays.
Your application first asks an integer value for the number of elements in an array. Then, that many times it gets an integer value from the console for the elements of the array. Then it sorts the array and prints the sorted array to the screen.  
Example: 
Size of the array?: 5
1: 13
2: 25
3: 2
4: 17
5: 21
Your sorted array is: 2 13 17 21 25


Rules: 
	Your code will be tested in QtSpim simulator. In case your code does not work in Qtspim simulator, it will not be evaluated at all. 
	You must do all work individually. All submitted studies will be passed through similarity check. 
	Finding an online code or using converter tools will not help you learn about computer assembly. Also, there might be other students in the class using that specific resource. 
Hints: 
	For understanding MIPS assembly better, please refer to the Appendix-A of course book (Computer Organization and Design, 5th edition). You can easily find the pdf version of the book online. Just google it. 
	In youtube, you can find many tutorial videos about how to program in qtspim. Here is an example:   https://www.youtube.com/watch?v=r8WcV7AiLXs&ab_channel=JohnMcCranie
	In your code, you need to include “.data”, “.text”, “.globl main”  and “main:” keywords 
	To be able to read from the console and write to console, you need to use system calls. SPIM provides a small set of OS–like services through the system call (syscall) instruction. To request a service, a program loads the system call code into register $v0 and arguments into registers $a0–$a3 (or $f12 for floating-point values). System calls that return values put their results in register $v0 (or $f0 for floating-point results). For example, the following program gets a value from the user and prints it back to screen. 
