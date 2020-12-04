
void CountryNetwork::deleteCountry(string countryName) {
    //TODO: Complete this function
    Country *finder = head;
    Country *temp;
    Country *left;
    
    if(finder->name == countryName){//if the head is the country we're looking for
       
        
        temp = head; //set temp = to current head
        head = head->next;//make head equal to node after current head
        delete temp; //delete current head
        
        
    }
    else{//if not head (tail or middle)
        
       left = head;//left is head
       temp = finder->next;//temp is node after head
       bool found = false;
       while (temp != NULL && found == false){//searches through list while the node after current is not null (so not tail) or name has not been found yet
           
           if (temp->name == countryName){//if node after current is what we're looking for
               
               left->next = temp->next;//the current node should point to what temp points to
               if (temp->next == NULL){//if temp is the tail; points to null
                    
                    left->next = NULL; //make current node the tail
               }
               delete temp;
               found = true;
           }
           else{
           
               left = temp;
               temp = temp->next;//updates values by shifting over
           }
       }
       if (found == false){
           cout<<"Country does not exist."<<endl;
       }
    }

}

void CountryNetwork::deleteEntireNetwork()
{
    //TODO: Complete this function
    Country *finder = head;
    Country *temp;
    Country *left;
    if(finder == NULL){
        return;
    } 
    else{
        while (!(finder == NULL)){//while there is something in the list and the list isn't at the end
            //cout<<"entering while loop"<<endl;
            temp = finder; //set temp = to current head
            finder = finder->next;//make head equal to node after current head
            cout<<"deleting: "<<temp->name<<endl;
            //cout<<finder->name<<endl;
            delete temp;
            //cout<<"exiting loop"<<endl;
        }
    }
    head = NULL;
    cout<<"Deleted network"<<endl;
}

Country* CountryNetwork::createLoop(string countryName)
{
    //TODO: Complete this function
    Country *finder = head;
    Country *ptr = head;
    while (ptr != NULL && ptr->name != countryName)
    {
        ptr = ptr->next;//not sure how to call search Network
        
        //ptr = node we want to loop back to
    }
    //cout<<ptr->name<<endl;
    while(!(finder == NULL) && finder->next != NULL)
    {
        finder = finder->next;//tail
    } 
    //cout<<finder->name<<endl;
    if(finder == NULL){
        return finder;
    }
    finder->next = ptr;
    return finder;
}

bool CountryNetwork::detectLoop() {
    //TODO: Complete this function
    Country *theHead = head;
    Country *fast = head->next;
    Country *slow = head;
    if (theHead == NULL){
        return false;
    }
    while(fast != NULL && slow!=NULL && fast->next!=NULL){
        if (fast == slow){
            return true;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return false;
}

void CountryNetwork:: readjustNetwork(int start_index, int end_index)
{
    //TODO: Complete this function
    Country *finder = head;
    Country *index = head;
    Country *before = head;
    Country *after = head;
    Country *first = head;
    int count = 0;
    int countIndex = 0;
    int afterIndex = 0;
    if(finder == NULL){
        cout<<"Linked List is Empty"<<endl;
    }
    else
    {
        while(!(finder == NULL) && finder->next != NULL)
        {
            finder = finder->next;//tail
            count++;
        } 
        if(end_index<0 || count<end_index){
            cout<<"Invalid end index"<<endl;
            
        }
        else if(start_index > count || start_index < 0){
            cout<<"Invalid start index"<<endl;
        }
        else if(start_index > end_index){
            cout<<"Invalid indices"<<endl;
        }
        else{
            if(start_index == 0){
                while(!(index == NULL) && index->next != NULL )
                {
                    if(countIndex == end_index){//last node in nodes we're moving
                        after = index;
                        head = after->next;
                        after->next = NULL;
                    }
                    if(countIndex == start_index){
                        
                        finder->next = index;//pointing tail to our first node
                    }

                    index = index->next;//tail

                    countIndex++;

                }
            }
            else{
                while(!(index == NULL) && index->next != NULL )
                {
                    if(countIndex == start_index-1){
                        before = index;//finding node before start index
                    }
                   
                    if(countIndex == start_index){
                        first = index;
                    }
                     if(afterIndex == end_index){
                        after = index;
                        before->next = after->next;
                        finder->next = first;
                        after->next = NULL;
                    }

                    index = index->next;//tail
                    afterIndex++;
                    
                    countIndex++;

                }
            }
        } 
    }
}