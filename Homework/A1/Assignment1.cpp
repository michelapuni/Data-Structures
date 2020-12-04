#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std; 



int insertIntoSortedArray( float myArray[], int numEntries, float newValue){
    
    myArray[numEntries]=newValue;
    numEntries++;
    for(int i = 0; i < numEntries; i++){
        for(int j = i+1; j < numEntries; j++){
            if(myArray[i] < myArray[j])
            {
            float temp = myArray[i];
            myArray[i] = myArray[j];
            myArray[j] = temp;
            
         } 
         
        }
   
        
    }
      for (int i = 0; i < numEntries; i++){
          if(i==0){
              cout<<myArray[i];
          }
          else{
            cout<<","<<myArray[i];
            }
        }
    return numEntries;
}

int main(int argc, char *argv[]){
float tempArr[100];
int count = 0;
  ifstream sampleFile(argv[1]);
  string line = "";
  string temp = "";
  if(sampleFile.is_open()){
      while(getline(sampleFile, line)){
          stringstream ss(line);
          getline(ss, temp, ',');
          tempArr[count] = stof(temp);
        
          insertIntoSortedArray(tempArr, count, tempArr[count]);
          cout<<endl;
          count++;


      }
    }
  else
  {
      cout<<"Failed to open the file."<<endl;
  }
    sampleFile.close();
}

//second part of assignment

struct Park{
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkName, string State, int Area, int length){
    Park temp;
    temp.parkname = parkName;
    temp.state = State;
    temp.area = Area;
    parks[length] = temp;
    
}

void printList(const Park parks[], int length){
    for (int i = 0; i < length; i++){
        cout << parks[i].parkname <<" ["<< parks[i].state<< "] area: "<<parks[i].area<< endl;
    }
}

int main(int argc, char *argv[]){
    Park tempArr[100];
    int count = 0;
    ifstream sampleFile(argv[1]);
  string line = "";
  string tempName = "";
  string tempState = "";
  string tempArea = "";
  int tempArea2 = 0;
  if(sampleFile.is_open()){
      while(getline(sampleFile, line)){
          stringstream ss(line);
          getline(ss, tempName, ',');
          tempArr[count].parkname = tempName;
        getline(ss, tempState, ',');
          tempArr[count].state = tempState;
          getline(ss, tempArea, ',');
          tempArea2 = stoi(tempArea);
          tempArr[count].area = tempArea2;
          addPark(tempArr,tempName, tempState, tempArea2, count);
          count++;
            

      }
      printList(tempArr, count);
      ofstream outputFile;
      outputFile.open("outputfile.csv");
      int lowerBound = stoi(argv[3]);
      int higherBound = stoi(argv[4]);
      for (int i = 0; i < count; i++){
          if ( tempArr[i].area > lowerBound && tempArr[i].area < higherBound){
              outputFile<<tempArr[i].parkname<<","<<tempArr[i].state<<","<<tempArr[i].area<<endl;
          }
      }
            
  }
  else
  {
      cout<<"Failed to open the file."<<endl;
  }
    sampleFile.close();
}