Binary Instrumentation with PIN
Definition: In this homework, you are going to do some experiments with X68 ISA, which is the instruction set in your computers. For this task, you will use PIN Binary Instrumentation Tool:
o	 https://software.intel.com/en-us/articles/pin-a-dynamic-binary-instrumentation-tool 
PIN allows you to collect runtime information about any application compiled and running on an X86 computer. In this homework, you will instrument simple factorial application both for iterative and recursive versions. You can get the code from here: https://www.javatpoint.com/factorial-program-in-c.
Task1: Count the total number of macroinstructions and microinstructions in the application. 
Task2: In the ISAs, there are three classes of machine instructions: 
       - Memory Instructions (ie. Loads and Stores)
       - Branch Instructions (ie. Jumps, Branches etc.)
        - Arithmetic and Logic Instructions (ie. Add, Sub, Mul, Div, Shift, And, Or etc.)
     Count the number of instructions in each class and find their ratio. 
Task3: Here is the list of registers and their purposes in X86. 
RAX: Accumulator
RBX: Base index (for use with arrays)
RCX: Counter (for use with loops and strings)
RDX: Extend the precision of the accumulator
RSI: Source index for string operations.
RDI: Destination index for string operations.
RSP: Stack pointer for top address of the stack.
RBP: Stack base pointer for holding the address of the current stack frame.
R8-R15: general purposed registers
Calculate the frequency of usage of each register as a destination register. Also, calculate the number of data dependencies occurring between two consecutive instructions.  
Submission: 
Write your instrumentation code for each task into the same instrumentation file as a .c or .cpp file.
Also prepare a report including the following information:
1. Explain your instrumentation code 
2. Put the results of Task1-2-3 for the iterative and recursive factorial applications. Make a comparison about the numbers for the application to explain if both numbers are identical or not and why?
3. Put the screen shot of your executions.
Submit your code and your report on Canvas .
