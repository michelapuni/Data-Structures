#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void destructor(TreeNode* node){
    LLMovieNode *temp;
    if(node){
        destructor(node->leftChild);
        destructor(node->rightChild);
        while(node->head != NULL){
            temp = node->head;
            node->head = node->head->next;
            delete temp;
            temp = NULL;//mdl
        }
      delete node;
    }
    return;//mdl
}

MovieTree::~MovieTree()
{
    
    destructor(root);
    root = NULL;//MDL
}

void printMovieHelper(TreeNode* currNode){
    if(currNode){
    LLMovieNode* finder = currNode->head;
        printMovieHelper(currNode->leftChild);
        cout << "Movies starting with letter: " << currNode->titleChar << endl;
        while(finder){
            cout << " >> " << finder->title << " " << finder->rating << endl;
            finder = finder->next;
        }
        printMovieHelper(currNode->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    if(root == NULL){
        return;
    }
    else{
        printMovieHelper(root);
        //cout<<endl;
   }
}

TreeNode* addHelper(TreeNode* currNode, TreeNode* newNode){
    if(currNode == NULL){
      
      newNode->leftChild = NULL;
      newNode->rightChild = NULL;
      return newNode;
    }
    else if(currNode->titleChar < newNode->titleChar){
      currNode->rightChild = addHelper(currNode->rightChild, newNode);
      newNode->parent = currNode;
    }
    else if(currNode->titleChar > newNode->titleChar){
      currNode->leftChild = addHelper(currNode->leftChild, newNode);
      newNode->parent = currNode;
      
    }
    return currNode;
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    LLMovieNode* newNode = new LLMovieNode(ranking, title, year, rating);
    char key = title[0];
    
    TreeNode* keyNode = searchChar(key);
    
    if(keyNode == NULL && root != NULL){//checking if key was not found and that tree isn't empty
        
        //add node with starting character of given title    
        //in this scenario, the linkedlist would be empty so dont check for that
        TreeNode* newerNode = new TreeNode;
        newerNode->titleChar = key;
        //TreeNode* currNode = root;
        LLMovieNode* link = newerNode->head;
        root = addHelper(root, newerNode);
        
            if(link==NULL || link->title >= newNode->title){//if ll empty or head is more than new node
                
                newNode->next = link;
                newerNode->head = newNode;//makes the movie node the head of the linked list if it's empty
                
            }
            else{
                //traverse through and put the title in alphebetical order
                while(link->next != NULL && link->next->title < newNode->title){
                    link = link->next;
                }
                newNode->next = link->next;
                link->next = newNode;
            }
        
    
    

    }
    if(keyNode == NULL && root == NULL){//if tree is empty
            
            TreeNode* newerNode = new TreeNode;
            root = newerNode;//make keyNode the root of the tree then do linked list stuff
            newerNode->titleChar = key;
            
            //check if linked list empty
            LLMovieNode* link = newerNode->head;
            if(link==NULL || link->title >= newNode->title){//if ll empty or head is more than new node
                
                newNode->next = link;
                newerNode->head = newNode;//makes the movie node the head of the linked list if it's empty
                
            }
            else{
                //traverse through and put the title in alphebetical order
                while(link->next != NULL && link->next->title < newNode->title){
                    link = link->next;
                }
                newNode->next = link->next;
                link->next = newNode;
            }

        }
    if(keyNode != NULL && root != NULL){
        //TreeNode* newerNode = new TreeNode;
        //newerNode = keyNode;
            LLMovieNode* link = keyNode->head;//newer
            if(link==NULL || link->title >= newNode->title){//if ll empty or head is more than new node
                
                newNode->next = link;
                keyNode->head = newNode;//makes the movie node the head of the linked list if it's empty
                //^newer
            }
            else{
                //traverse through and put the title in alphebetical order
                while(link->next != NULL && link->next->title < newNode->title){
                    link = link->next;
                }
                newNode->next = link->next;
                link->next = newNode;
            } 
        }
        
    
}

TreeNode* findMin(TreeNode* curr){
    while(curr->leftChild != NULL){
        curr = curr->leftChild;
    }
    return curr;
}

void MovieTree::deleteMovie(std::string title)
{
    //first take first character of title and find node that corresponds
    char key = title[0];
    TreeNode* keyNode = searchChar(key);
    if(keyNode == NULL){
        
        cout<<"Movie: "<<title<<" not found, cannot delete."<<endl;
        return;
    }
    else{
        LLMovieNode* link = keyNode->head;
        while(link != NULL && link->title != title){
            link = link->next;
        }
        if(link == NULL){//or just link
            cout<<"Movie: "<<title<<" not found, cannot delete."<<endl;
        }
        else{
            LLMovieNode* toBeDeleted;
            if(link->title == keyNode->head->title){
                if(link->next == NULL){//if it's only node in ll
                    //delete ll and then do delete tree stuff
                    delete keyNode->head;
                    if(keyNode->leftChild == NULL && keyNode->rightChild == NULL){
                        delete keyNode;
                    }
                    if(keyNode->leftChild != NULL || keyNode->rightChild != NULL){
                        if(keyNode->leftChild != NULL && keyNode->rightChild != NULL){
                            TreeNode* min = findMin(keyNode->rightChild);
                            if(keyNode == root){
                                if(min == keyNode->rightChild){
                                //cout<<"check 1"<<endl;
                                    root = min;
                                    min->leftChild = keyNode->leftChild;
                                    min->leftChild->parent = min;
                                    min->parent = NULL;
                                    delete keyNode;
                                }
                                else{
                                //cout<<"check 2"<<endl;
                                    if(min->rightChild != NULL){
                                        min->parent->leftChild = min->rightChild;
                                        min->rightChild->parent = min->parent;
                                    }                            
                                    root = min;
                                    min->leftChild = keyNode->leftChild;
                                    min->rightChild = keyNode->rightChild;
                                    min->leftChild->parent = min;
                                    min->rightChild->parent = min;
                                    min->parent = NULL;
                                    delete keyNode;
                                }
                            }
                            else if(min == keyNode->rightChild){
                                if(keyNode->parent->leftChild == keyNode){
                                    keyNode->parent->leftChild = min;
                                }
                                if(keyNode->parent->rightChild == keyNode){
                                    keyNode->parent->rightChild = min;
                                    
                                } 
                                min->leftChild = keyNode->leftChild;
                                min->leftChild->parent = min;
                                delete keyNode;
                            }
                            else{
                            
                                if(min->rightChild != NULL){
                                    min->parent->leftChild = min->rightChild;
                                    min->rightChild->parent = min->parent;
                                }                            
                                min->parent = keyNode->parent;
                                if(keyNode->parent->leftChild == keyNode){
                                    keyNode->parent->leftChild = min;
                                }
                                if(keyNode->parent->rightChild == keyNode){
                                    keyNode->parent->rightChild = min;
                                    
                                } 
                                min->leftChild = keyNode->leftChild;
                                min->rightChild = keyNode->rightChild;
                                min->leftChild->parent = min;
                                min->rightChild->parent = min;
                                delete keyNode;
                            }
                        }
                        else{
                            if(keyNode->leftChild == NULL){
                                if(keyNode == keyNode->parent->rightChild){
                                    keyNode->parent->rightChild = keyNode->rightChild;
                                    keyNode->rightChild->parent = keyNode->parent;
                                }
                                if(keyNode == keyNode->parent->leftChild){
                                    keyNode->parent->leftChild = keyNode->rightChild;
                                    keyNode->rightChild->parent = keyNode->parent;
                                }                                
                                delete keyNode;
                            }
                            if(keyNode->rightChild == NULL){
                                if(keyNode == keyNode->parent->rightChild){
                                    keyNode->parent->rightChild = keyNode->leftChild;
                                    keyNode->leftChild->parent = keyNode->parent;
                                }
                                if(keyNode == keyNode->parent->leftChild){
                                    keyNode->parent->leftChild = keyNode->leftChild;
                                    keyNode->leftChild->parent = keyNode->parent;
                                }                             
                                delete keyNode;
                            }
                        }
                    }
                }
                else{//if it's not the only node in ll
                    toBeDeleted = keyNode->head;
                    keyNode->head = keyNode->head->next;
                    delete toBeDeleted;
                }
            }
            else{
                LLMovieNode* prev = keyNode->head;
                LLMovieNode* temp = keyNode->head->next;
                bool found = false;
                while(temp != NULL && found == false){
                    if(temp->title == title){
                        prev->next = temp->next;
                        delete temp;
                        found = true;
                    }
                    else{
                        prev = temp;
                        temp = temp->next;
                    }
                }

            }
        }
   }
   }
void MovieTree::leftRotation(TreeNode* curr)
{
    if(curr->rightChild != NULL){
        if(curr == root){
            TreeNode* y = curr->rightChild;
            root = y;
            
            curr->rightChild = y->leftChild;
            if(y->leftChild != NULL){
                curr->rightChild = y->leftChild;
                y->leftChild->parent = curr;
            }
            y->leftChild = curr;
            curr->parent = y;  
            y->parent = NULL;
        }
        else{
            int check = 0;
            TreeNode* parent = curr->parent;//a
            TreeNode* y = curr->rightChild;//c
            y->parent = curr->parent;//a->c
            curr->rightChild = y->leftChild;
            if(curr == curr->parent->leftChild){
                check = 1;
            }
            if(curr == curr->parent->rightChild){
                check = 2;
            } 
            if(y->leftChild != NULL){
                
                curr->rightChild = y->leftChild;
                y->leftChild->parent = curr;
            }
            y->leftChild = curr;
            curr->parent = y;
            if(check ==1){
                parent->leftChild = y;
                
            }
            if(check == 2){
               parent->rightChild = y;
            }


        }
    }
    else{
        return;
    }
}

//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}