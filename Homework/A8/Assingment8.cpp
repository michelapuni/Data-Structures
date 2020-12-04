void Graph::addVertex(std::string name){
    bool found = false; //check if vertex with given name already exists
    for(int i = 0; i < vertices.size(); i++){//checking vertices vector
        if(vertices[i]->name == name){//if vertex with given name already exists
            found == true;
            return;
        }
    }
    //don't need if statement (if false)
    vertex *v = new vertex;//w/o new it gives seg fault
    v->name = name;
    vertices.push_back(v);
}

void Graph::addEdge(std::string v1, std::string v2){
    //first check if v1 and v2 even exist
    bool foundOne = false;
    bool foundTwo = false;
    for(int i = 0; i <vertices.size(); i++){
        if(vertices[i]->name == v1){
            foundOne = true;
        }
    }
    for(int i = 0; i <vertices.size(); i++){
        if(vertices[i]->name == v2){
            foundTwo = true;
        }
    } 
    if(foundOne && foundTwo){//both exist
        for(int i = 0; i < vertices.size(); i++){
            if(vertices[i]->name == v1){//find v1 again
                
                for(int j = 0; j<vertices.size(); j++){//once get to v1, loop through all vertices
                    if(vertices[j]->name == v2 && i != j){//find v2 and 
                        adjVertex av;
                        av.v = vertices[j];//when to use arrows vs. dots
                        vertices[i]->adj.push_back(av);
                        //although it doesn't mention it in writeup, connect other way as well
                        adjVertex av2;
                        av2.v = vertices[i];
                        vertices[j]->adj.push_back(av2);
                    }
                }
            }
        }
    }  
    else{
        return;
    }
}

void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<" --> ";
        for(int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<vertices[i]->adj[j].v->name<<" ";//again not sure difference between dot and arrow adj[j]->v
        }
        cout<<endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex* source;//make vertex for given string
    for(int i = 0; i < vertices.size(); i++){//check through vertices vector
        if (vertices[i]->name == sourceVertex){//find vertex in vertices vector that has name of given string
            source = vertices[i];
        }
    }
    source->visited = true;//set the visited to true for given string vertex

    queue<vertex*> q;//create a queue
    q.push(source);//push the source vertex onto the queue
    
    cout<<"Starting vertex (root): "<< source->name <<"-> ";
    
    vertex *s;//create vertex for traversing
    while(!q.empty()){//run this loop until the queue is empty
    
        s = q.front();//set the vertex s equal to the vertex at the front of the queue
        q.pop();//get rid of the vertex at the front of the queue but s is still there to check adj vertices
        for( int x = 0; x < s->adj.size(); x++ )//check all of the vertices adjacent to s
        {
            if(!s->adj[x].v->visited){//if the adj vertice of s has not been visited
                s->adj[x].v->distance = s->distance+1;//make that adj vertex's distance equal to s's distance +1
                s->adj[x].v->visited = true;//then set its visisted to true
                q.push(s->adj[x].v);//now add that vertex to the queue 
                cout<<s->adj[x].v->name<<"("<<s->adj[x].v->distance <<")"<< " ";
            }

        }
    }

}

void DFSHelper(vertex *y){
    for(int i = 0; i < y->adj.size(); i++){
        if (y->adj[i].v->visited == false){//if the adj vertex we're visiting hasn't already been visited
            y->adj[i].v->visited = true;//mark it as visited
            DFSHelper(y->adj[i].v);
        }
    }
}

int Graph::getConnectedComponents(){
    int count = 0; //keep track of connected
    for(int i = 0; i < vertices.size(); i++){//traversing through vertices to see which ones haven't been visited
        if(vertices[i]->visited == false ){//if vertex hasn't been visited yet then implement dfs on it
            vertices[i]->visited = true;//mark that vertex as visited for future reference
            count += 1; //increase count of connected components
            DFSHelper(vertices[i]);//perform dfs on all of its adjecent vertices so that we don't perform "4 lines above" again
        }
    }
    return count;
}