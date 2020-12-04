#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed
using namespace std;

RPNCalculator::RPNCalculator(){
    stackHead = NULL; //how do i set stackhead pointer to null
}

RPNCalculator::~RPNCalculator(){
    if(!(isEmpty())){
        Operand *x = stackHead;//temp variable that holds top
    while(!(isEmpty())){
        pop();
    }
    x = NULL;
    }


}

bool RPNCalculator::isEmpty(){
    if(stackHead == NULL){
        return true;
    }
    else{
        return false;
    }
}

void RPNCalculator::push(float number){
    //can the stack never get full? since no full function
    Operand *topStack = new Operand;//why do i need new?
    topStack->number = number;
    topStack->next = stackHead;
    stackHead = topStack;
    
}

void RPNCalculator::pop(){
    // if(isEmpty()){
    //     cout<<"Stack empty, cannot pop an item"<<endl;//might not need this
    //     return;
    // }
    //stackHead = stackHead->next;//assuming next points to previous node
    // return x; //not sure what this is doing but doesn't work anyways
    if(!(isEmpty())){
        Operand *x = stackHead;
        stackHead = stackHead -> next;//makes previous node new top
        delete x;
    }
    else{
        cout<<"Stack empty, cannot pop an item."<<endl;
    }
}

Operand* RPNCalculator::peek(){
    if(isEmpty()){
        cout<<"Stack empty, cannot peek."<<endl;
        return NULL;
    }
    else{
        return stackHead;
    }
}

bool RPNCalculator::compute(string symbol){
    Operand* topStack = stackHead;
    
    float sum = 0.0;
    float product = 0.0;
    float storeFirs = 0.0;
    float storeSec = 0.0;

    //store floats from top two stacks in variables
    if(isEmpty()){
        cout<<"err: not enough operands"<<endl;
        return false;
    }else{
        storeFirs = topStack->number;
        pop();
    }
    if(isEmpty()){
        cout<<"err: not enough operands"<<endl;
        push(storeFirs);//why don't i need rpncal.push()
        return false;
    }else{
        Operand* secondStack = topStack->next;
        storeSec = secondStack->number;
        pop();//pop second
    }
    
    
        if(symbol == "+" ){
            //store float sum in variable and pop it
            sum = storeFirs + storeSec;
            push(sum);
        }
        else if(symbol == "*" ){
            //store float product in variable and pop it
            product = storeFirs * storeSec;
            push(product);
        }
        else{
            cout<<"err: invalid operation"<<endl;
            if(isEmpty()){
        push(storeFirs);
        push(storeSec);
    }
            return false;
        }
    
}

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{
  // TODO - Declare a stack to hold the operands
  string input;
  RPNCalculator calc;
  RPNCalculator temp;
  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, input);
    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. Use the isNumber function to check if the input is an operand
       3. push all operands to the stack
       4. If input is not an operand, call the compute function to evaluate
          the partial expression
    */
    if(input == "="){
      break;//breaks out of loop if user inputs equal sign
    }
    else{//if not equal sign
      if(isNumber(input)){//if input is a number 
        float converted = stof(input);//convert input to float
        calc.push(converted);//push converted float number to stack
      }
      else{
        calc.compute(input);//if input is not number is an operand, compute
      }
    }
  }

  /* TODO - If the stack is empty then print "No operands: Nothing to evaluate" */
    if(calc.isEmpty()){
      cout<<"No operands: Nothing to evaluate"<<endl;
      return 0;
    }
    //temp = calc;
    //temp.pop();
    
    float tempFloat = calc.peek()->number;

    calc.pop();

     if(!(calc.isEmpty())){
        cout<<"Invalid expression"<<endl;
       return 0;
      
     }
     else{
        calc.push(tempFloat);
       cout<<calc.peek()->number<<endl;
     }

  /* TODO - Validate the expression
      1. If valid then print the result
      2. Else, print "Invalid expression"*/

  return 0;
}

ProducerConsumer::ProducerConsumer(){
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty(){
if (counter == 0){
    return true;
}
else{
    return false;
}
}

bool ProducerConsumer::isFull(){
if (counter == 20){
    return true;
}
else{
    return false;
}
}

void ProducerConsumer::enqueue(string item){
 if(!(isFull())){
     if(queueEnd == SIZE -1){
        queue[queueEnd] = item;
        queueEnd = 0;
     }
    else{
        
        queue[queueEnd] = item;
        queueEnd++;
    }    
    counter++;
 }
 else{
     cout<<"Queue full, cannot add new item"<<endl;
 }
}

void ProducerConsumer::dequeue(){
    if(!(isEmpty())){
        if(queueFront == SIZE -1){
            queueFront = 0;
        }
        else{
            queueFront++;
        }
        counter--;
    }
    else{
        cout<<"Queue empty, cannot dequeue an item"<<endl;
    }
}

int ProducerConsumer::queueSize(){
    //traverse list and use counter then return counter
    return counter;
}

string ProducerConsumer::peek(){
    if(isEmpty()){
        cout<<"Queue empty, cannot peek"<<endl;
        return "";//returning empty string
    }
    else{
        return queue[queueFront];//returning first item in queue
    }
}

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	ProducerConsumer Producer;
	int index = 0;
	while (true){
		menu();
		
		string input;
		getline(cin, input);
		index = stoi(input);

		if(index == 1){
			cout<<"Enter the number of items to be produced:"<<endl;
			getline(cin, input);
			int items = stoi(input);
			for(int i = 0; i < items; i++){
				cout<<"Item" << i+1 << ":" <<endl;
				getline(cin, input);
				Producer.enqueue(input);
				
			}
			
		}
		else if(index == 2)
		{
			cout<<"Enter the number of items to be consumed:"<<endl;
			getline(cin,input);
			int items = stoi(input);
			int size = Producer.queueSize();
			if(items > size){
				for(int i = 0; i < size; i++){
					cout<<"Consumed: "<<Producer.peek()<<endl;
					Producer.dequeue();
				}
				cout<<"No more items to consume from queue"<<endl;
			}
			else{
				for(int i = 0; i < items; i++){
					cout<<"Consumed: "<<Producer.peek()<<endl;
					Producer.dequeue();
				}
			}
			
		}
		else if(index == 3)
		{
			
			cout<<"Number of items in the queue:"<<Producer.queueSize()<<endl;
			return 0;
		}
	}
}