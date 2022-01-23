#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::endl;
using std::ios;
using std::ofstream;
using std::string;

ofstream OutFile;

// Define the variables
static UINT64 memoryInstructionCounter = 0;
static UINT64 totalBranchCounter = 0;
static UINT64 branchInstructionCount = 0;
static UINT64 arithmeticIntructionCount = 0;

// Define Register Variables
static UINT64 accumulatorRegCounter = 0;
static UINT64 baseIndexRegCounter = 0;
static UINT64 counterRegCounter = 0;
static UINT64 rdxRegCounter = 0;
static UINT64 rsiRegCounter = 0;
static UINT64 rdiRegCounter = 0;
static UINT64 rspRegCounter = 0;
static UINT64 rbpRegCounter = 0;
static UINT64 regularRegCounter = 0;

// Count for every instruction that occurs
VOID findBranchCount() { branchInstructionCount++; }
VOID findMemoryCount() { memoryInstructionCounter++; }
VOID findtotalInstructionCount() { totalBranchCounter++; }

// Function to count the number of specific register types
VOID incrementAccumulator() { accumulatorRegCounter++; }
VOID incrementBaseIndex() { baseIndexRegCounter++; }
VOID incrementCounter() { counterRegCounter++; }
VOID incrementRdx() { rdxRegCounter++; }
VOID incrementRsi() { rsiRegCounter++; }
VOID incrementRdi() { rdiRegCounter++; }
VOID incrementRsp() { rspRegCounter++; }
VOID incrementRbp() { rbpRegCounter++; }
VOID incrementRegular() { regularRegCounter++; }

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{

    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findtotalInstructionCount, IARG_END);
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    // add 1 for each memory operand.

    if (INS_IsBranch(ins))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findBranchCount, IARG_END);
    }
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {

        if (INS_MemoryOperandIsWritten(ins, memOp) || INS_MemoryOperandIsRead(ins, memOp))
        {
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)findMemoryCount, IARG_END);
        }

    }

    if (INS_RegWContain(ins, REG_RAX))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementAccumulator, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RBX))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementBaseIndex, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RCX))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementCounter, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RDX))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRdx, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RSI))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRsi, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RDI))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRdi, IARG_END);
    }


    if (INS_RegWContain(ins, REG_RSP))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRsp, IARG_END);
    }

    if (INS_RegWContain(ins, REG_RBP))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRbp, IARG_END);
    }

    if (INS_RegWContain(ins, REG_R8) || INS_RegWContain(ins, REG_R9) || INS_RegWContain(ins, REG_R10) || INS_RegWContain(ins, REG_R11) || INS_RegWContain(ins, REG_R12) || INS_RegWContain(ins, REG_R13) || INS_RegWContain(ins, REG_R14) || INS_RegWContain(ins, REG_R15))
    {
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)incrementRegular, IARG_END);
    }

}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                            "o", "results.out", "specify output file name");

// This function is executed when the application is found
VOID Fini(INT32 code, VOID *v)
{

    arithmeticIntructionCount = totalBranchCounter - (branchInstructionCount + memoryInstructionCounter);

    double ratioBranchInstructions = (double)branchInstructionCount / (double)totalBranchCounter;
    double ratioMemoryInstructions = (double)memoryInstructionCounter / (double)totalBranchCounter;
    double ratioArithmeticInstructions = (double)arithmeticIntructionCount / (double)totalBranchCounter;

    

    // Execute and print the tasks
    OutFile.setf(ios::showbase);
    OutFile << "Task1\nThe total Count of macroinstructions and microinstructions is:  "
            << totalBranchCounter << endl;

    OutFile << "\nTask2\nResult of the istructions are: " << endl;
    OutFile << "The number of Branch Instruction in the code is: " << branchInstructionCount << endl;
    OutFile << "The number of Memory Instructions in the code is: " << memoryInstructionCounter << endl;
    OutFile << "The number of Arithmetic and Logic Instructions in the code is: " << totalBranchCounter - (branchInstructionCount + memoryInstructionCounter) << endl;

    OutFile << "Ratio of branch instructions: " << ratioBranchInstructions << endl;
    OutFile << "Ratio of memory instructions: " << ratioMemoryInstructions << endl;
    OutFile << "Ratio of arithmetic instructions: " << ratioArithmeticInstructions << endl;


    double totalRegCount = accumulatorRegCounter + baseIndexRegCounter + counterRegCounter + rdxRegCounter + rsiRegCounter + rdiRegCounter + rspRegCounter + rbpRegCounter + regularRegCounter;

    OutFile << "\nTask3\nRAX Count is : " << accumulatorRegCounter << " with a frequency of: " << (accumulatorRegCounter * 100) / totalRegCount << endl;
    OutFile << "Base Index Count is : " << baseIndexRegCounter << " with a frequency of: " << (baseIndexRegCounter * 100) / totalRegCount << endl;;
    OutFile << "RCX Count is: " << counterRegCounter << " with a frequency of: " << (counterRegCounter * 100) / totalRegCount << endl;
    OutFile << "RDX Count is : " << rdxRegCounter << " with a frequency of: " << (rdxRegCounter * 100) / totalRegCount << endl;
    OutFile << "RSI Count is : " << rsiRegCounter  << " with a frequency of: " << (rsiRegCounter * 100) / totalRegCount << endl;
    OutFile << "RDI Count is : " << rdiRegCounter << " with a frequency of: " << (rdiRegCounter * 100) / totalRegCount << endl;
    OutFile << "RSP Count is : " << rspRegCounter << " with a frequency of: " << (rspRegCounter * 100) / totalRegCount << endl;
    OutFile << "RBP Count is : " << rbpRegCounter  << " with a frequency of: " << (rbpRegCounter * 100) / totalRegCount << endl;
    OutFile << "general Purpose register Count is : " << regularRegCounter << " with a frequency of: " << (regularRegCounter * 100) / totalRegCount << endl;
    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl
         << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv))
        return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}