vertex* search(vector<vertex*> vertice, string name){
    for(int i = 0; i <vertice.size(); i++){
        if(vertice[i]->name == name){
            return vertice[i];
        }
    }
}

void Graph::addEdge(string v1, string v2, int num){
    vertex* vertex1 = search(vertices,v1);
    vertex* vertex2 = search(vertices,v2);
    adjVertex av1;
    av1.v = vertex1;
    adjVertex av2;
    av2.v = vertex2;
    av1.weight = num;
    av2.weight = num;
    vertex1->adj.push_back(av2);
    vertex2->adj.push_back(av1);
}

vertex* search(vector<vertex*> vertice, string name){
    for(int i = 0; i <vertice.size(); i++){
        if(vertice[i]->name == name){
            return vertice[i];
        }
    }
}

void DFTraversal(vertex *source){
    source->visited = true;
    for(int x = 0; x < source->adj.size(); x++ )
    {
        // TODO
        if (source->adj[x].v->visited == false){//if the adj vertex we're visiting hasn't already been visited
            source->adj[x].v->visited = true;//mark it as visited
            cout<<source->adj[x].v->name<< " -> ";
            DFTraversal(source->adj[x].v);
        }        
    }
}

vertex* search(vector<vertex*> vertice, string name){
    for(int i = 0; i <vertice.size(); i++){
        if(vertice[i]->name == name){
            return vertice[i];
        }
    }
}

void Graph::dijkstraTraverse(string sourceVertex){
    vertex* start = search(vertices, sourceVertex);
    start->visited = true;
    start->distance = 0;
    vector<vertex*> visitedList;
    visitedList.push_back(start);
    bool allVisited = false;

    while(!allVisited){
        int minDistance = 200;
        vertex* vVis = nullptr;
        allVisited = true;
        for(int i = 0; i < visitedList.size(); i++){
            vertex* temp = visitedList[i];
            for(int j = 0; j < temp->adj.size(); j++){
                if(!temp->adj[j].v->visited){
                    int distance = temp->distance + temp->adj[j].weight;//

                    if(distance < minDistance){
                        vVis = temp->adj[j].v;
                        minDistance = distance;
                    }
                    allVisited = false;
                }
            }
        }
    if(!allVisited){
        vVis->distance = minDistance;
        
        vVis->visited = true;
        visitedList.push_back(vVis);
    }
    }

}

vertex* search(vector<vertex*> vertice, string name){
    for(int i = 0; i <vertice.size(); i++){
        if(vertice[i]->name == name){
            return vertice[i];
        }
    }
}

void Graph::shortestPath(string start, string end){
    vertex* endVertex = search(vertices, start);
    vertex* startVertex = search(vertices, end);
    startVertex->visited = true;
    startVertex->distance = 0;
    vector<vertex*> visitedList;
    visitedList.push_back(startVertex);
    //cout<<startVertex->name<<" -> ";
    while(!endVertex->visited){
        int minDistance = 200;
        vertex* parent = nullptr;
        vertex* vVis = nullptr;
        for(int i = 0; i < visitedList.size(); i++){
            vertex* temp = visitedList[i];
            for(int j = 0; j < temp->adj.size(); j++){
                if(!temp->adj[j].v->visited){
                    int distance = temp->distance + temp->adj[j].weight;//

                    if(distance < minDistance){
                        vVis = temp->adj[j].v;
                        minDistance = distance;
                        parent = temp;
                    }
                }
            }
        }
        vVis->distance = minDistance; 
        vVis->pred = parent;
        vVis->visited = true;
        visitedList.push_back(vVis);
    }
    vertex* current = endVertex;
    
    while(current->pred != nullptr){
        cout<<current->name<<" -> ";
        current = current->pred;
    }
    cout<<current->name<<" -> ";
    cout<<"DONE "<< "["<<endVertex->distance<< "]"<<endl;
}