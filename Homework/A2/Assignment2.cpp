#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
    
    int count = 0;
    ifstream sampleFile(ignoreWordFileName);
    string line = "";
    string temp = "";
    if(sampleFile.is_open()){
      while(sampleFile >> temp){
          //stringstream ss(line);
          //getline(ss, temp, '.');
          ignoreWords[count] = temp;  
          count++;
      }
            
  }
  else
  {
      cout<<"Failed to open "<< ignoreWordFileName <<endl;
  }
    sampleFile.close();
}

bool isStopWord(string word, string ignoreWords[]){
    for (int i = 0; i < 50; i++){
        if (ignoreWords[i] == word){
            return true;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
    //counting the number of words that aren't the ignore words
    int countWord = 0;
    for (int i = 0; i < length; i++){
        countWord += uniqueWords[i].count;
        
        
    }
   return countWord;
}

void arraySort(wordItem uniqueWords[], int length){
    for(int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if (uniqueWords[j].count > uniqueWords[i].count){
                wordItem temp = uniqueWords[j];
                uniqueWords[j] = uniqueWords[i];
                uniqueWords[i] = temp;
            }
        }
    }
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords){
    for (int i = N; i < N + 10; i++){
        float prob = (float)uniqueWords[i].count/(float)totalNumWords;

       cout<<fixed<<setprecision(4)<<prob << " - " <<uniqueWords[i].word<<endl;
    }
    
}

struct wordItem{
    string word;
    int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
    
    int count = 0;
    ifstream sampleFile(ignoreWordFileName);
    string line = "";
    string temp = "";
    if(sampleFile.is_open()){
      while(sampleFile >> temp){
          //stringstream ss(line);
          //getline(ss, temp, '.');
          ignoreWords[count] = temp;  
          count++;
      }
            
  }
  else
  {
      cout<<"Failed to open "<< ignoreWordFileName <<endl;
  }
    sampleFile.close();
}

bool isStopWord(string word, string ignoreWords[]){
    for (int i = 0; i < 50; i++){
        if (ignoreWords[i] == word){
            return true;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
    //counting the number of words that aren't the ignore words
    int countWord = 0;
    for (int i = 0; i < length; i++){
        countWord += uniqueWords[i].count;
        
    }
   return countWord;
}

void arraySort(wordItem uniqueWords[], int length){
    for(int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if (uniqueWords[j].count > uniqueWords[i].count){
                wordItem temp = uniqueWords[j];
                uniqueWords[j] = uniqueWords[i];
                uniqueWords[i] = temp;
            }
        }
    }
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords){
    for (int i = N; i < N + 10; i++){
        float prob = (float)(uniqueWords[i].count/(float)totalNumWords);

       cout<<fixed<<setprecision(4)<<prob << " - " <<uniqueWords[i].word<<endl;
    }
    
}

int main(int argc, char *argv[]){
    //check if there are 3 arguments; if not
    if (argc != 4){
        cout<<"Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>"<<endl;
        return 0;
    }
    
    int capacity = 100;
    int count = 0;
    int countDouble = 0;
    wordItem *uniqueWords = new wordItem[capacity];
    string ignoreWords[50];
    getStopWords(argv[3], ignoreWords);
    //int doNothing = 0;
    bool stop = true;
    bool addWord = true;
    string line = "";
    ifstream sampleFile(argv[2]);//opens text
    string temp = "";
    if(sampleFile.is_open()){
        while(sampleFile>>temp){
            addWord=true;
            wordItem tempHolder;//takes in word
            tempHolder.word = temp;
            stop = isStopWord(tempHolder.word, ignoreWords);//checks if that word is ignore word
            //cout<<tempHolder.word<<endl;
            if(stop == false){//if not an ignore word; first check if we're gonna add word to array (hasn't been added already)
                for(int i = 0; i < count; i++){//am i using the right variable (count)
                    if(tempHolder.word == uniqueWords[i].word){//checks if word is already in array
                        uniqueWords[i].count += 1;//if it is only increase the count of the word, don't add it
                        addWord = false;//sets bool to false so we don't add word into array
                    }
                    // else{
                    //     doNothing = 0;
                    // }
                }
                if(addWord == true){//if word is not in the array
                    if(count<capacity){//checks if count is less than capacity 
                    uniqueWords[count].word = temp;//adds word to the array
                    uniqueWords[count].count = 1;
                    count++;//increase number of elements in the array
                    
                    }
                    else /*if(count == capacity)*/{//if number of elements in array reaches capacity
                        wordItem *tempArr;//doubling array 
                        int newCapacity = capacity *2;
                        tempArr = new wordItem[newCapacity];
                        for (int j = 0; j <capacity; j++){
                            tempArr[j] = uniqueWords[j];
                        }
                        countDouble++;//increases number of times array has been doubled
                        delete[] uniqueWords;
                        uniqueWords = tempArr;
                        capacity = newCapacity;
                        uniqueWords[count].word = temp;//then adds word to the array
                        uniqueWords[count].count += 1;//increases the count of that word in the array
                        count++;//increases count of number of elements
                        
                    }
                }
            }
            
        }
        sampleFile.close();
    }
    int index = stoi(argv[1]);//converts index to integer
    arraySort(uniqueWords, count);//sorts the array
    int total = getTotalNumberNonStopWords(uniqueWords, count);//gets total number of words

    cout<<"Array doubled: "<<countDouble<<endl;
    cout<<"#"<<endl;
    cout<<"Unique non-common words: "<<count<<endl;
    cout<<"#"<<endl;
    cout<<"Total non-common words: "<<total<<endl;
    cout<<"#"<<endl;
    cout<<"Probability of next 10 words from rank "<<index<<endl;
    cout<<"---------------------------------------"<<endl;
    printNext10(uniqueWords, index, total);
}