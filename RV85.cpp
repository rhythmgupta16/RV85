#include <iostream>
#include <assert.h>
#include <typeinfo>
#include <string>
#include<sstream>
#include<cctype>
using namespace std;


int convert (const string& str)
{
stringstream ss(str);
int n;
ss >> n;
return n;
}
/**********************************************
Function prototypes
*********************************************/
// Shows the main prompt
int read(int operand, int memory[]);
int write(int operand, int memory[]);
int load(int operand, int memory[] );
int store(int operand, int memory[] );
int add(int operand, int memory[] );
int subtract(int operand, int memory[] );
int divide(int operand, int memory[] );
int multiply(int operand, int memory[] );
string convert_hexcode(string a);


int prompt();

// This is the main Memory that contains all the data
int memory[256];

// This is the A register in the CPU
int accumulator;
// This is the Negative flag in the CPU
bool neg_flag=0;



int main() {
	cout << ">>>    	Welcome to RV85 \n"<< ">>> 	Please enter you program below.\n"<< ">>> 	You can either enter an instruction\n"<< ">>> 	one a time or enter a data byte.\n";


	prompt();
	return 0;
}
int prompt() {
	string instruction,operand_ins,currentInstruction = "";
	int operand ;
	int currentLine = 0;
	int operationNumeric;



	while (currentInstruction!="9900") {
		cout << "[" << currentLine << "]: ";

		cin >> instruction;
		currentInstruction=convert_hexcode(instruction);
		if(currentInstruction=="99"  || currentInstruction=="34"  ||  currentInstruction=="35"  ||  currentInstruction=="36")
        {
            currentInstruction+="00";
            memory[currentLine++] = convert(currentInstruction);
            continue;
        }
		cin>>operand_ins;
		currentInstruction+=operand_ins;
		if (currentInstruction.length() != 4) {
			cout << "Instructions can only be 4 letters long!\nHALTING!\n";
			return 1;
		}

		memory[currentLine++] = convert(currentInstruction);
        }
		int programCounter=0;
		while(programCounter<currentLine)
        {
            int currentInstruction=memory[programCounter++];
		operationNumeric 	= currentInstruction/100;
		operand 	= currentInstruction%100;
        cout <<"Operation : "<< operationNumeric <<endl<<"Operand : "<<operand<< endl;
	switch ( operationNumeric ) {
		case 10:
		read(operand, memory);
			break;

		case 11:
		write(operand, memory);
			break;

		case 20:
		load(operand, memory);
		break;

		case 21:
		store(operand, memory);
		break;

		case 30:
		add(operand, memory);
		break;

		case 31:
		subtract(operand, memory);
		break;

		case 32:
		divide(operand, memory);
		break;

		case 33:
		multiply(operand, memory);
		break;

		case 34:
        accumulator=255-accumulator;
        break;

        case 35:
        accumulator++;
        break;

        case 36:
        accumulator--;
        break;

        case 40:
        programCounter=operand;
        break;

        case 41:
        if(neg_flag==1)
                programCounter=operand;
        break;

		case 99:
		cout << "\nQuitting!"<<endl;
		break;

		default:
		cout << "\nUnknown command, error! Quiting!"<<endl;
		return 1;
		break;
	}
	cout<<"Accumulator    : "<<accumulator<<endl<<endl;
	}
	return 0;
}



/********************************************************
* FUNCTION DECLARATIONS!
*******************************************************/
int read(int operand, int memory[]){
	int address = operand;
	int userInput = 0;
	cout<<endl<<"["<<address<<"x"<<"] : ";
	cin >> userInput;
	cout<<endl;
	memory[address] = userInput;
	return 0;
}

int write(int operand, int memory[]){
	int address = operand;
	cout<<endl<<"["<<address<<"x"<<"] : "<<memory[address]<<endl<<endl;
	return 0;
}

int load(int operand, int memory[]){
	int address = operand;
	accumulator = memory[address];
	if(accumulator<0)
    {
        accumulator=255+accumulator;
        neg_flag=1;
    }
    else
    {
        neg_flag=0;
    }
	return 0;
}

int store(int operand, int memory[]){
	// Store a word from the memory into the accumulator
	int address = operand;
	memory[address] = accumulator;
	return 0;
}

int add(int operand, int memory[]){
	// Add the value in the given address into the accumulator
	// and leave the result there
	int address = operand;
	accumulator+=memory[address] ;
	if(accumulator<0)
    {
        accumulator=255+accumulator;
        neg_flag=1;
    }
    else
    {
        neg_flag=0;
    }
	return 0;
}

int subtract(int operand, int memory[]){
	// Subtract the value in the given address into the accumulator
	// and leave the result there
	int address = operand;
	int value = accumulator - memory[address];
	accumulator = value;
	if(accumulator<0)
    {
        accumulator=255+accumulator;
        neg_flag=1;
    }
    else
    {
        neg_flag=0;
    }
	return 0;
}

int divide(int operand, int memory[]){

	int address = operand;
	int value = accumulator / memory[address];
	accumulator = value;
	return 0;
}

int multiply(int operand, int memory[]){
	int address = operand;
	int value = accumulator * memory[address];
	accumulator = value;
	return 0;
}

string convert_hexcode(string a)
{
    for(int i=0;i<a.size();i++)
       a[i] = toupper(a[i]);
    if(a=="LDA")
        return "20";
    else if(a=="STA")
        return "21";
    else if(a=="RED")
        return "10";
    else if(a=="WRI")
        return "11";
    else if(a=="ADD")
        return "30";
    else if(a=="SUB")
        return "31";
    else if(a=="MUL")
        return "33";
    else if(a=="DIV")
        return "32";
    else if(a=="CMA")
        return "34";
    else if(a=="INR")
        return "35";
    else if(a=="DCR")
        return "36";
    else if(a=="JMP")
        return "40";
    else if(a=="JPN")
        return "41";
    else if(a=="HLT")
        return "99";
    else
        return "99";
}
