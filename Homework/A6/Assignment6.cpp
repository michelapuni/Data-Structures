#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Paste all your methods for MovieTree class 
// and helper functions below

MovieTree::MovieTree() {
  //write your code
  
}

MovieTree::~MovieTree() {
  //write your code
}
void printTreeHelper(MovieNode* currNode){
     if(currNode)
     {
        printTreeHelper( currNode->left);
        cout<<"Movie: "<<currNode->title<<" "<<currNode->rating<<endl;
        printTreeHelper( currNode->right);
     }
     
 }

void MovieTree::printMovieInventory()
{
    MovieNode* node = root;
    if(node == NULL){
        cout<<"Tree is Empty. Cannot print"<<endl;
    }
    else{
        printTreeHelper(root);
        //cout<<endl;
   }
}

MovieNode* addHelper(MovieNode* currNode, MovieNode* newNode){
    if(currNode == NULL){
      newNode->left = NULL;
      newNode->right = NULL;
      return newNode;
    }
    else if(currNode->title < newNode->title){
      currNode->right = addHelper(currNode->right, newNode);
    }
    else if(currNode->title > newNode->title){
      currNode->left = addHelper(currNode->left, newNode);
    }
    return currNode;
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  MovieNode* newNode = new MovieNode(ranking, title, year, rating);
  MovieNode* currNode = root;

  root = addHelper(currNode, newNode);

}

MovieNode* searchKeyHelper(MovieNode* currNode, string title){
    if(currNode){
      if(currNode->title == title){
        return currNode;
      }
      if(currNode->title > title){
        return searchKeyHelper(currNode->left, title);
      }
      if(currNode->title < title){
        return searchKeyHelper(currNode->right, title);
      }
    }
    return NULL;
}

void MovieTree::findMovie(string title) {
  //write your code
  MovieNode* node = searchKeyHelper(root,title);
  if(node != NULL){
    cout<<"Movie Info:"<<endl;
    cout << "==================" << endl;
    cout << "Ranking:" << node->ranking << endl;
    cout << "Title  :" << node->title << endl;
    cout << "Year   :" << node->year << endl;
    cout << "rating :" << node->rating << endl;
  }
  else{
    cout<<"Movie not found."<<endl;
  }
}

void queryHelper(MovieNode* currNode, float rating, int year){
     if(currNode)
     {
       if(currNode->rating >= rating && currNode->year >= year){
         cout<<currNode->title<<"("<<currNode->year<<") "<<currNode->rating<<endl;
       }
        
        queryHelper( currNode->left,rating,year);
        queryHelper( currNode->right,rating,year);
     }
     
 }

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  MovieNode* currNode = root;
  if(currNode==NULL){
    cout<<"Tree is Empty. Cannot query Movies"<<endl;
  }
  else{
    cout<<"Movies that came out after "<<year<<" with rating at least "<<rating<<": "<<endl;
    queryHelper(currNode, rating, year);
  }
}

float averageHelper(MovieNode* currNode, int& count){
  count++;
  float sum = currNode->rating;
  if(currNode->left){
    sum += averageHelper(currNode->left, count);
  }
 if(currNode->right){
    sum += averageHelper(currNode->right, count);
  }
  return sum;
}

void MovieTree::averageRating() {
  //write your code
   MovieNode* currNode = root;
  if(currNode==NULL){
    cout<<"Average rating:0.0"<<endl;
  }
  else{
    float sum = 0.0;
    int count = 0;
    sum = averageHelper(root,count);

    float average = sum/count;
    cout<<"Average rating:"<<average<<endl;
    
  }
}

void levelHelp(MovieNode* curr, int level){
  if(curr == NULL){
    return;
  }
  if(level == 0){
    cout<<"Movie: "<< curr->title<<" "<<curr->rating<<endl;
    return;
  }
  else{
    levelHelp(curr->left, level - 1);
    levelHelp(curr->right, level - 1);
  }
}

void MovieTree::printLevelNodes(int level) {
  //write your code
  levelHelp(root, level);
}
