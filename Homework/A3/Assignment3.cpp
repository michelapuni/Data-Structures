//#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool append(string* &str_arr, string s, int &numEntries, int &arraySize){//not sure what the pointer next to & is trying to say
   
    if(numEntries == arraySize){
     
        int newSize = arraySize * 2;

      
        string *newArray =  new string[newSize];
   
        for (int i = 0; i < numEntries; i++){
            newArray[i] = str_arr[i];
        }

        delete[] str_arr;

        str_arr = newArray;
        arraySize = newSize;

 
            str_arr[numEntries] = s;
            numEntries++;
            return true;//doubled true
    }
    str_arr[numEntries] = s;
    numEntries++;
    return false;
}

Country* CountryNetwork::searchNetwork(string countryName) 
{
    // TODO: Complete the definition
       Country *finder = head;
   while (finder != 0){
    if(finder->name == countryName){
        return finder;
    }
    else{
        finder = finder->next;
    }
   }
  
}

void CountryNetwork::insertCountry(Country* previous, string countryName)
{

   Country *newCountry = new Country;//allocating memory for new Country item
   newCountry->name = countryName;

   if(previous == NULL){
       newCountry->next = head;
       head = newCountry;
       cout<<"adding: "<< countryName << " (HEAD)" << endl;
   }
   else{
    newCountry->next = previous->next;
     previous->next = newCountry;
     
       cout<<"adding: " << countryName << " (prev: " << previous->name <<")"<<endl;
   }
    
    
}

void CountryNetwork::loadDefaultSetup() {
    // TODO: Complete the definition
     insertCountry(NULL,"United States");
     Country *ptr = head;
    insertCountry(ptr,"Canada");
    insertCountry(ptr->next,"Brazil");
    insertCountry(ptr->next->next,"India");
    insertCountry(ptr->next->next->next,"China");
    insertCountry(ptr->next->next->next->next,"Australia");
    
}

void CountryNetwork::transmitMsg(string receiver, string message)
{
    // TODO: Complete the definition
   int found = 0;
    int empty = 0;
    Country *finder = head;

   while (finder != NULL && found == 0){//while the finder pointer does not point to a null node
    empty = 1;
    finder->message = message;
    finder->numberMessages += 1;
    if(finder->name == receiver){
        found = 1;
    }
    
    cout<<finder->name<<" [# messages received: "<<finder->numberMessages<<"] received: "<<message<<endl;//using finder->message to print out message didn't work
    finder = finder->next;
   }
    if (empty == 0){
        cout<<"Empty list"<<endl;
        return;
    }
    if (found == 0){
        cout<<"Country not found"<<endl;
    }
}

void displayMenu();  

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    bool display = true;
    int index = 0;
    while(display != false){
    displayMenu();
    cin>>index;
    if(index == 1){
        CountryNet.loadDefaultSetup();
        CountryNet.printPath();
    }
    else if(index == 2)
    {
        CountryNet.printPath();
    }
    else if(index == 3)
    {
        string country;
        string message;
        cout<<"Enter name of the country to receive the message:"<<endl;
        cin>>country;
        
        cout<<"Enter the message to send:"<<endl;
         cin.ignore();
        getline(cin,message);
        cout<<endl;
        CountryNet.transmitMsg(country,message);
        
    }
    else if(index == 4)
    {
         string newerCountry;
        string oldCountry;

        cout<<"Enter a new country name:"<<endl;
        cin>>newerCountry;
        cout<<"Enter the previous country name (or First):"<<endl;
        cin>>oldCountry;
        if (oldCountry == "First"){
            CountryNet.insertCountry(NULL, newerCountry);
        }
        else{
           if(CountryNet.searchNetwork(oldCountry) != NULL){
            //CountryNet.insertCountry(NULL, newerCountry);
            Country *previous = CountryNet.searchNetwork(oldCountry);
            CountryNet.insertCountry(previous, newerCountry);
           }
           else{
               cout<<"INVALID(previous country name)...Please enter a VALID previous country name!"<<endl;
               
               cin>>oldCountry;
               if(CountryNet.searchNetwork(oldCountry) != NULL){
            Country *previous = CountryNet.searchNetwork(oldCountry);
            CountryNet.insertCountry(previous, newerCountry);
           }
              
           }
            
        }
        
        //CountryNet.insertCountry(oldCountry, newerCountry);
        CountryNet.printPath();
    }
    else if(index == 5)
    {
        cout<<"Quitting..."<<endl;
        display = false;
    }
    }

    cout<<"Goodbye!"<<endl;
    
    return 0;
}

/************************************************
      Definitions from CountryNetwork.cpp
************************************************/
CountryNetwork::CountryNetwork() {
    // TODO: Copy your definition for constructor here
        string name;
    string message;
    int numberMessages;
    Country *next; //pointer to next country
}


void CountryNetwork::insertCountry(Country* previous, string countryName)
{
    // TODO: Copy your definition for insertCountry here
       Country *newCountry = new Country;//allocating memory for new Country item
   newCountry->name = countryName;

   if(previous == NULL){
       newCountry->next = head;
       head = newCountry;
       cout<<"adding: "<< countryName << " (HEAD)" << endl;
   }
   else{
    newCountry->next = previous->next;
     previous->next = newCountry;
     
       cout<<"adding: " << countryName << " (prev: " << previous->name <<")"<<endl;
   }
}


void CountryNetwork::loadDefaultSetup() 
{
    // TODO: Copy your definition for loadDefaultSetup here
     insertCountry(NULL,"United States");
    Country *ptr = head;
    insertCountry(ptr,"Canada");
    insertCountry(ptr->next,"Brazil");
    insertCountry(ptr->next->next,"India");
    insertCountry(ptr->next->next->next,"China");
    insertCountry(ptr->next->next->next->next,"Australia");
}


Country* CountryNetwork::searchNetwork(string countryName)
{
    // TODO: Copy your definition for searchNetwork here
     Country *finder = head;
   while (finder != 0){//while the finder pointer does not point to a null node
    if(finder->name == countryName){//if the finder points at a node whose name is the parameter name
        return finder;//return the pointer of that node which is finder
    }
    else{
        finder = finder->next;//is finder like the next?
    }
   }
}


void CountryNetwork::transmitMsg(string receiver, string message)
{
    // TODO: Copy your definition for transmitMsg here
  int found = 0;
    int empty = 0;
    Country *finder = head;
    Country *secondFinder = head;
    int second = 0;


while (finder != NULL && found == 0){//while the finder pointer does not point to a null node
    empty = 1;
    if(finder->name == receiver){
        found = 1;
    }
    finder = finder->next;
   } 
   if(found ==1){
    while (secondFinder != NULL && second == 0 ){//while the finder pointer does not point to a null node
    empty = 1;
   
    secondFinder->numberMessages += 1;
    cout<<secondFinder->name<<" [# messages received: "<<secondFinder->numberMessages<<"] received: "<<message<<endl;//printing out message didnt work with finder->message
    secondFinder->message = message;
    if(secondFinder->name == receiver){
        second = 1;
    }
    
    secondFinder = secondFinder->next;
   }
   }
     
    if (empty == 0){
        cout<<"Empty list"<<endl;
        return;
    }
    if (found == 0){
        cout<<"Country not found"<<endl;
    }
    
}


void CountryNetwork::printPath()
{
    // TODO: Copy your definition for printPath
   int empty = 0;
    int fancy = 0;
    Country *finder = head;
   while (finder != NULL){//while the finder pointer does not point to a null node
   if(fancy == 0){
       cout<<"== CURRENT PATH =="<<endl;
       fancy = 1;
   }
   empty = 1;
   cout<<finder->name<<" -> ";
    finder = finder->next;
   }
   if (empty == 1){
       cout<<"NULL"<<endl;
       cout<<"==="<<endl;
   }
   else{
        cout<<"== CURRENT PATH =="<<endl;
       cout<<"nothing in path"<<endl;
       cout<<"==="<<endl;
   }
}


/************************************************
           Definitions for main.cpp
************************************************/
void displayMenu()
{
    // COMPLETE
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}