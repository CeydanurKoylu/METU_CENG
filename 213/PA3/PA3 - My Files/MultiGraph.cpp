#include "MultiGraph.h"
#include "Exceptions.h"
#include "IntPair.h"
#include <iostream>
#include <iomanip>
#include <fstream>

//=======================//
// Implemented Functions //
//=======================//
MultiGraph::MultiGraph()
{}

MultiGraph::MultiGraph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[5];
    std::ifstream mapFile(filePath.c_str());

    if(!mapFile.is_open())
    {
        std::cout << "Unable to open " << filePath << std::endl;
        return;
    }

    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly 5 tokens (Meaning it is an edge)
        else if(i == 5)
        {
            // Rename vars for readablity
            const std::string& vertexFromName = tokens[0];
            const std::string& vertexToName = tokens[1];
            const std::string& edgeName = tokens[2];
            float weight0 = static_cast<float>(std::atof(tokens[3].c_str()));
            float weight1 = static_cast<float>(std::atof(tokens[4].c_str()));
            AddEdge(edgeName, vertexFromName, vertexToName,
                    weight0, weight1);
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void MultiGraph::PrintPath(const std::vector<int>& orderedVertexEdgeIndexList,
                           float heuristicWeight,
                           bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //

    // Name is too long
    const std::vector<int>& ove = orderedVertexEdgeIndexList;
    // Invalid list
    // At least three items should be available
    if(ove.size() < 3) return;

    // Check vertex and an edge
    for(size_t i = 0; i < orderedVertexEdgeIndexList.size(); i += 2)
    {
        int vertexId = ove[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "VertexId " << vertexId
                      << " not found!" << std::endl;
            return;
        }


        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == ove.size() - 1) break;
        int nextVertexId = ove[i + 2];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "VertexId " << vertexId
                    << " not found!" << std::endl;
            return;
        }

        // Find the edge between these two vertices
        int localEdgeId = ove[i + 1];
        if(localEdgeId >= static_cast<int>(vertex.edges.size()))
        {
            // Return if there is a bad vertex id
            std::cout << "EdgeId " << localEdgeId
                      << " not found in " << vertexId << "!" << std::endl;
            return;
        }

        const GraphEdge& edge = vertex.edges[localEdgeId];

        // Combine with heuristic (linear interpolation)
        float weight = Lerp(edge.weight[0], edge.weight[1],
                            heuristicWeight);

        std::cout << "-" << std::setfill('-')
                  << std::setw(4)
                  << weight << "->";
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void MultiGraph::PrintEntireGraph() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(size_t j = 0; j < v.edges.size(); j++)
        {
            const GraphEdge& edge = v.edges[j];

            // List the all vertex names and weight
            std::cout << "    -"
                      << std::setfill('-')
                      << std::setw(4) << edge.weight[0]
                      << "-"
                      << std::setw(4) << edge.weight[1]
                      << "-> ";
            std::cout << vertexList[edge.endVertexIndex].name;
            std::cout << " (" << edge.name << ")" << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

//=======================//
//          TODO         //
//=======================//
int MultiGraph::findVertex(const std::string& vertexName)const
{
    int ind = -1;
    for(int i = 0;  i < (int)vertexList.size(); i++){
        if((vertexList[i]).name == vertexName){
            ind = i;
            break;
        }
    }
    return ind;
}

float MultiGraph::Lerp(float w0, float w1, float alpha)
{
    /* TODO */
    return w1*alpha + w0*(1-alpha);
}

void MultiGraph::InsertVertex(const std::string& vertexName)
{
    /* TODO */
    if(findVertex(vertexName) != -1){
        throw DuplicateVertexException(vertexName);
    }
    GraphVertex newVertex;
    newVertex.name = vertexName;
    vertexList.push_back(newVertex);
}

void MultiGraph::RemoveVertex(const std::string& vertexName)
{
    /* TODO */
    /*
    int ind = findVertex(vertexName);
    if(ind == -1){
        throw VertexNotFoundException();
    }
    vertexList[ind].name = "";
    (vertexList[ind].edges).clear();
    for(int i = 0; i < vertexList.size(); i++){
        if(vertexList[i].name != ""){
            for(j = 0; j < (vertexList[i]).edges.size(); j++){
                if(((vertexList[i]).edges)[j].endVertexIndex == ind){
                   ((vertexList[i]).edges).erase((vertexList[i]).edges.begin() + j);
                   j--;
                }
            }
        }
    }
    */
    int ind = findVertex(vertexName);
    if(ind == -1){
        throw VertexNotFoundException(vertexName);
    }
    vertexList.erase(vertexList.begin()+ind);
    for(int i = 0; i < (int)vertexList.size(); i++){
        
            for(int j = 0; j < (int)(vertexList[i]).edges.size(); j++){
                if(((vertexList[i]).edges)[j].endVertexIndex == ind){
                   ((vertexList[i]).edges).erase((vertexList[i]).edges.begin() + j);
                   j--;
                }
                else if(((vertexList[i]).edges)[j].endVertexIndex > ind){
                   ((vertexList[i]).edges)[j].endVertexIndex = ((vertexList[i]).edges)[j].endVertexIndex - 1;
            }
        }
        
    }
    
}

void MultiGraph::AddEdge(const std::string& edgeName,
                         const std::string& vertexFromName,
                         const std::string& vertexToName,
                         float weight0, float weight1)
{
    /* TODO */
    bool found = false;
    int ind1 = findVertex(vertexFromName);
    int ind2 = findVertex(vertexToName);
    if(ind1 == -1 || ind2 == -1){
        if(ind2 == -1) throw VertexNotFoundException(vertexToName);
        else throw VertexNotFoundException(vertexFromName);
    }
     for(int j = 0; j < (int)(vertexList[ind1]).edges.size(); j++){
                if(((vertexList[ind1]).edges)[j].name == edgeName && ((vertexList[ind1]).edges)[j].endVertexIndex == ind2){
                   found = true;
                   break;
                }
            }
    if(found){
        throw SameNamedEdgeException(edgeName, vertexFromName, vertexToName);
    }
    
    GraphEdge newEdge;
    newEdge.name = edgeName;
    newEdge.endVertexIndex = ind2;
    newEdge.weight[0] = weight0;
    newEdge.weight[1] = weight1;
    vertexList[ind1].edges.push_back(newEdge);
}

void MultiGraph::RemoveEdge(const std::string& edgeName,
                            const std::string& vertexFromName,
                            const std::string& vertexToName)
{
    /* TODO */
    bool found = false;
    int ind1 = findVertex(vertexFromName);
    int ind2 = findVertex(vertexToName);
    if(ind1 == -1 || ind2 == -1){
        if(ind2 == -1) throw VertexNotFoundException(vertexToName);
        else throw VertexNotFoundException(vertexFromName);
    }
    
    for(int j = 0; j < (int)(vertexList[ind1]).edges.size(); j++){
                if(((vertexList[ind1]).edges)[j].name == edgeName && ((vertexList[ind1]).edges)[j].endVertexIndex == ind2){
                   ((vertexList[ind1]).edges).erase((vertexList[ind1]).edges.begin() + j);
                   found = true;
                   break;
                }
            }
    if(!found){
        throw EdgeNotFoundException(vertexFromName, edgeName);
    }
    

    
}

bool MultiGraph::HeuristicShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                       const std::string& vertexNameFrom,
                                       const std::string& vertexNameTo,
                                       float heuristicWeight) const
{
    /* TODO */
    bool found = false;
    GraphVertex g1; g1.name = "";
    GraphVertex g2;
    float newDist;
    Pair<int,int> PrevVerEdge;
    PrevVerEdge.key = -1; PrevVerEdge.value = -1;
    std::vector<float> distances((int)vertexList.size(),9999999);
    std::vector<Pair<int,int>> previous((int)vertexList.size(),PrevVerEdge);
   
    
    int ind1 = findVertex(vertexNameFrom);
    int ind2 = findVertex(vertexNameTo);
    if(ind1 == -1 || ind2 == -1){
        if(ind2 == -1) throw VertexNotFoundException(vertexNameTo);
        else throw VertexNotFoundException(vertexNameFrom);
    }
    
    
    float w0 = 0.0;
    float w1 = 0.0;
    float beta;
    
    Pair<float,int> p1;
    Pair<float,int> p2;
    MinPairHeap<float,int> pq;
    
    p1.key = 0; p1.value = ind1;
    distances[ind1] = 0;
    pq.push(p1);
    while(!pq.empty()){
        p1 = pq.top();
        pq.pop();
        if(p1.value == ind2){
            found = true;
            break;
        }
        g1 =  vertexList[p1.value];
        
        for(int j = 0; j < (int)g1.edges.size(); j++){
            w0 = g1.edges[j].weight[0];
            w1 = g1.edges[j].weight[1];
            beta = Lerp(w0,w1,heuristicWeight);
            newDist = distances[p1.value] + beta;
            
            if(newDist < distances[g1.edges[j].endVertexIndex]){
                p2.key = newDist;
                p2.value = g1.edges[j].endVertexIndex;
                distances[p2.value] = newDist;
                PrevVerEdge.key = p1.value;
                PrevVerEdge.value = j;
                previous[p2.value] = PrevVerEdge;
                pq.push(p2);
            }
        }
    }
    std::vector<int> temp;
    int ind = ind2;
    if(found){
        while(previous[ind].key != -1){
            temp.push_back(previous[ind].value);
            temp.push_back(previous[ind].key);
            ind = previous[ind].key;
        }
        for(int i = (int)temp.size()-1; i > -1; i--){
            orderedVertexEdgeIndexList.push_back(temp[i]);
        }
        orderedVertexEdgeIndexList.push_back(ind2);
        return true;
    }
    
    return false;
}

bool MultiGraph::FilteredShortestPath(std::vector<int>& orderedVertexEdgeIndexList,
                                      const std::string& vertexNameFrom,
                                      const std::string& vertexNameTo,
                                      float heuristicWeight,
                                      const std::vector<std::string>& edgeNames) const
{
    /* TODO */
 /* TODO */
    bool found = false;
    GraphVertex g1; g1.name = "";
    GraphVertex g2;
    float newDist;
    Pair<int,int> PrevVerEdge;
    PrevVerEdge.key = -1; PrevVerEdge.value = -1;
    std::vector<float> distances((int)vertexList.size(),9999999);
    std::vector<Pair<int,int>> previous((int)vertexList.size(),PrevVerEdge);
   
    
    int ind1 = findVertex(vertexNameFrom);
    int ind2 = findVertex(vertexNameTo);
    if(ind1 == -1 || ind2 == -1){
        if(ind2 == -1) throw VertexNotFoundException(vertexNameTo);
        else throw VertexNotFoundException(vertexNameFrom);
    }
    
    bool inEdges = false;
    
    float w0 = 0.0;
    float w1 = 0.0;
    float beta;
    
    Pair<float,int> p1;
    Pair<float,int> p2;
    MinPairHeap<float,int> pq;
    
    p1.key = 0; p1.value = ind1;
    distances[ind1] = 0;
    pq.push(p1);
    while(!pq.empty()){
        p1 = pq.top();
        pq.pop();
        if(p1.value == ind2){
            found = true;
            break;
        }
        g1 =  vertexList[p1.value];
        
        for(int j = 0; j < (int)g1.edges.size(); j++){
            inEdges = false;
          for(int i = 0; i < (int)edgeNames.size(); i++){  
              if(g1.edges[j].name == edgeNames[i]){
                  inEdges = true;
                continue;
            }
        }
        if(inEdges) continue;
        
            w0 = g1.edges[j].weight[0];
            w1 = g1.edges[j].weight[1];
            beta = Lerp(w0,w1,heuristicWeight);
            newDist = distances[p1.value] + beta;
            
            if(newDist < distances[g1.edges[j].endVertexIndex]){
                p2.key = newDist;
                p2.value = g1.edges[j].endVertexIndex;
                distances[p2.value] = newDist;
                PrevVerEdge.key = p1.value;
                PrevVerEdge.value = j;
                previous[p2.value] = PrevVerEdge;
                pq.push(p2);
            }
        }
    }
    std::vector<int> temp;
    int ind = ind2;
    if(found){
        while(previous[ind].key != -1){
            temp.push_back(previous[ind].value);
            temp.push_back(previous[ind].key);
            ind = previous[ind].key;
        }
        orderedVertexEdgeIndexList.clear();
        for(int i = (int)temp.size()-1; i > -1; i--){
            orderedVertexEdgeIndexList.push_back(temp[i]);
        }
        orderedVertexEdgeIndexList.push_back(ind2);
        return true;
    }
    
    return false;
}

int MultiGraph::BiDirectionalEdgeCount() const
{
    /* TODO */
    int count = 0;
    int j = 0, k = 0;
    for(int i = 0; i < (int) vertexList.size(); i++){
        for(j = 0; j < (int) (vertexList[i]).edges.size() ;j++){
            for(k = 0; k < (int) (vertexList[vertexList[i].edges[j].endVertexIndex]).edges.size(); k++){
                if((vertexList[vertexList[i].edges[j].endVertexIndex]).edges[k].endVertexIndex == i && (vertexList[vertexList[i].edges[j].endVertexIndex]).edges[k].name == vertexList[i].edges[j].name){
                    count++;
                }
            }
            
        }
    }
    return count/2;
}


int MultiGraph::MaxDepthViaEdgeName(const std::string& vertexName,
                                    const std::string& edgeName) const
{
   
    int ind = findVertex(vertexName);
    bool isIn = false;
   
    if(ind == -1){
        throw VertexNotFoundException(vertexName);
    }
    std::vector<int> visited;
    Pair<int,int> IndVisit, current;
    MinPairHeap<int,int> pq;
    std::vector<int> path_length(vertexList.size(),-1);
    
    IndVisit.key = 0; IndVisit.value = ind;
    pq.push(IndVisit);
    visited.push_back(ind);
    path_length[ind] = 0;
    
    while(!pq.empty()){
        current = pq.top();
        pq.pop();
        ind = current.value;
        
        for(int i = 0; i < (int)vertexList[ind].edges.size(); i++){
            if(vertexList[ind].edges[i].name == edgeName) {
                isIn = false;
                
                for(int j = 0; j < (int)visited.size(); j++){
                    if(visited[j] == vertexList[ind].edges[i].endVertexIndex){
                        isIn = true;
                    }
                }
                
                if(!isIn){
                    IndVisit.key = IndVisit.key + 1;
                    IndVisit.value = vertexList[ind].edges[i].endVertexIndex;
                    pq.push(IndVisit);
                    
                    visited.push_back(vertexList[ind].edges[i].endVertexIndex);
                    
                    path_length[vertexList[ind].edges[i].endVertexIndex] = path_length[ind] + 1;
                    }
                }
            }
    }
    int max = 0;
    for(int i = 0; i < (int)path_length.size(); i++){
        if(path_length[i] > max){
            max = path_length[i];
        }
    }
    
    return max;
}

bool MultiGraph::MaxDepthViaEdgeNameMod(const std::string& vertexName,
                                        std::vector<GraphVertex>& visited,
                                        std::vector<std::string>& sistersList) const
{
   
    int ind1 = findVertex(vertexName);
    bool isIn = false;
    bool found = false;
    int ind = ind1;
    if(ind == -1){
        throw VertexNotFoundException(vertexName);
    }
    
    Pair<int,int> IndVisit, current;
    MinPairHeap<int,int> pq;
    std::vector<int> path_length(vertexList.size(),-1);
    
    
    if(visited.empty()){
        visited.push_back(vertexList[ind]);
    }
    std::string edgeName;
    
    
 
    IndVisit.key = 0; IndVisit.value = ind1;
    ind = ind1;
    pq.push(IndVisit);
    
        while(!pq.empty()){
            current = pq.top();
            pq.pop();
            ind = current.value;
            
            for(int i = 0; i < (int)vertexList[ind].edges.size(); i++){
                for(int z = sistersList.size()-1; z > -1; z--){
                    edgeName = sistersList[z]; 
                    if(vertexList[ind].edges[i].name == edgeName) {
                        isIn = false;
                        
                        for(int j = 0; j < (int)visited.size(); j++){
                            if(visited[j].name == vertexList[vertexList[ind].edges[i].endVertexIndex].name){
                                isIn = true;
                            }
                        }
                        
                        if(!isIn){
                            found = true;
                            IndVisit.key = IndVisit.key + 1;
                            IndVisit.value = vertexList[ind].edges[i].endVertexIndex;
                            pq.push(IndVisit);
                            
                            visited.push_back(vertexList[vertexList[ind].edges[i].endVertexIndex]);
                            
                            
                            }
                        }
                
                    }
                }
        }
    
    
    return found;
}
/*
bool MultiGraph::MaxDepthViaEdgeNameMod( const std::string& vertexName,
                                                    const std::string& edgeName,
                                                    std::vector<GraphVertex>& visited) const
{
   
    int ind = findVertex(vertexName);
    bool isIn = false;
    bool found = false;
   
    if(ind == -1){
        throw VertexNotFoundException(vertexName);
    }
    
    Pair<int,int> IndVisit, current;
    MinPairHeap<int,int> pq;
    std::vector<int> path_length(vertexList.size(),-1);
    
    IndVisit.key = 0; IndVisit.value = ind;
    pq.push(IndVisit);
    
    if(visited.empty()){
        visited.push_back(vertexList[ind]);
    }
    

    while(!pq.empty()){
        current = pq.top();
        pq.pop();
        ind = current.value;
        
        for(int i = 0; i < (int)vertexList[ind].edges.size(); i++){
            if(vertexList[ind].edges[i].name == edgeName) {
                isIn = false;
                
                for(int j = 0; j < (int)visited.size(); j++){
                    if(visited[j].name == vertexList[vertexList[ind].edges[i].endVertexIndex].name){
                        isIn = true;
                    }
                }
                
                if(!isIn){
                    found = true;
                    IndVisit.key = IndVisit.key + 1;
                    IndVisit.value = vertexList[ind].edges[i].endVertexIndex;
                    pq.push(IndVisit);
                    
                    visited.push_back(vertexList[vertexList[ind].edges[i].endVertexIndex]);
                    
                    
                    }
                }
            }
    }
    
    
    return found;
}
*/

int MultiGraph::NoOfUnvisitedNeighbours(const GraphVertex& vertex, const std::vector<GraphVertex>& visited)const {
    bool isIn = false;
    int count = 0;
    
    
    for(int i = 0; i < (int)vertex.edges.size(); i++){
            
                isIn = false;
                
                for(int j = 0; j < (int)visited.size(); j++){
                    if(visited[j].name == vertexList[vertex.edges[i].endVertexIndex].name){
                        isIn = true;
                    }
                }
                if(!isIn){
                    count++;
                }
    }
    return count;
}

int MultiGraph::FirstNonUtilizedAirline(std::vector<std::string>& sistersList,  const GraphVertex& vertex,const std::vector<GraphVertex>& visited )const {
    bool isIn = false;
    bool isVisited = false;
    
    int k = -1;
    for(int i = 0; i < (int)vertex.edges.size(); i++){
                isVisited = false;   
                isIn = false;
                
                for(int j = 0; j < (int)sistersList.size(); j++){
                    if(sistersList[j] == vertex.edges[i].name){
                        isIn = true;
                    }
                }
                for(int z = 0; z < (int)visited.size(); z++){
                    if(visited[z].name == vertexList[vertex.edges[i].endVertexIndex].name){
                        isVisited = true;
                    }
                }
                if(!isIn && !isVisited){
                    sistersList.push_back(vertex.edges[i].name);
                    k = i;
                    break;
                }
    }
    return k;
}

const GraphVertex& MultiGraph::isThereAnEdge( const std::string& edgeName,
                                const std::string& vertexFromName,
                                const std::string& vertexToName)const{
    
    bool found = false;
    int ind1 = findVertex(vertexFromName);
    int ind2 = findVertex(vertexToName);
    if(ind1 == -1 || ind2 == -1){
        if(ind2 == -1) throw VertexNotFoundException(vertexToName);
        else throw VertexNotFoundException(vertexFromName);
    }
    
    for(int j = 0; j < (int)(vertexList[ind1]).edges.size(); j++){
                if(((vertexList[ind1]).edges)[j].name == edgeName && ((vertexList[ind1]).edges)[j].endVertexIndex == ind2){
                   found = true;
                   break;
                }
            }
    if(!found){
        throw EdgeNotFoundException(vertexFromName, edgeName);
    }
    return vertexList[ind1];
                                    
}