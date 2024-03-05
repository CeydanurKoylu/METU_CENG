#include "CENGFlight.h"
#include <iostream>

//=======================//
// Implemented Functions //
//=======================//
void CENGFlight::PrintCanNotHalt(const std::string& airportFrom,
                                 const std::string& airportTo,
                                 const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines is not found and cannot be halted"
              << std::endl;
}

void CENGFlight::PrintCanNotResumeFlight(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         const std::string& airlineName)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" via "
              << airlineName
              << " airlines cannot be resumed"
              << std::endl;
}

void CENGFlight::PrintFlightFoundInCache(const std::string& airportFrom,
                                         const std::string& airportTo,
                                         bool isCostWeighted)
{
    std::cout << "A flight path between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  " is found in cache." << std::endl;
}

void CENGFlight::PrintFlightCalculated(const std::string& airportFrom,
                                       const std::string& airportTo,
                                       bool isCostWeighted)
{
    std::cout << "A flight path is calculated between \""
              << airportFrom << "\" and \""
              << airportTo << "\" using "
              << ((isCostWeighted) ? "cost" : "price")
              <<  "." << std::endl;
}

void CENGFlight::PrintPathDontExist(const std::string& airportFrom,
                                    const std::string& airportTo)
{
    std::cout << "A flight path does not exists between \""
              << airportFrom << "\" and \""
              << airportTo <<"\"." << std::endl;
}

void CENGFlight::PrintSisterAirlinesDontCover(const std::string& airportFrom)
{
    std::cout << "Could not able to generate sister airline list from \""
              << airportFrom <<"\"." << std::endl;
}

void CENGFlight::PrintMap()
{
    navigationMap.PrintEntireGraph();
}

void CENGFlight::PrintCache()
{
    lruTable.PrintTable();
}

CENGFlight::CENGFlight(const std::string& flightMapPath)
    : navigationMap(flightMapPath)
{}

//=======================//
//          TODO         //
//=======================//
void CENGFlight::HaltFlight(const std::string& airportFrom,
                            const std::string& airportTo,
                            const std::string& airlineName)
{
    /* TODO */
    bool isOk = true;
    try{
      navigationMap.isThereAnEdge(airlineName, airportFrom ,airportTo);
    }
    catch(const VertexNotFoundException& x){
        PrintCanNotHalt(airportFrom, airportTo, airlineName);
        isOk = false;
    }
    catch(const EdgeNotFoundException& y){
        PrintCanNotHalt(airportFrom, airportTo, airlineName);
        isOk = false;
    }
    
    if(isOk){
        const GraphVertex& ver = navigationMap.isThereAnEdge(airlineName, airportFrom ,airportTo);
        
    HaltedFlight hf;
    hf.airportFrom = airportFrom;
    hf.airportTo = airportTo;
    hf.airline = airlineName;
    for(int i = 0; i < (int)ver.edges.size(); i++){
        if(ver.edges[i].name == airlineName && ver.edges[i].endVertexIndex == navigationMap.findVertex(airportTo)){
            hf.w0 = ver.edges[i].weight[0];
            hf.w1 = ver.edges[i].weight[1];
        }
    }
    haltedFlights.push_back(hf);
    
    navigationMap.RemoveEdge(airlineName, airportFrom ,airportTo);
    }
    
}

    // (Direct Function call)
void CENGFlight::ContinueFlight(const std::string& airportFrom,
                                const std::string& airportTo,
                                const std::string& airlineName)
{
    /* TODO */
    bool isOk = true;
    bool found = false;
    int i = 0;
    for(i = 0; i < (int)haltedFlights.size(); i++){
        if(haltedFlights[i].airline == airlineName && haltedFlights[i].airportFrom == airportFrom && haltedFlights[i].airportTo == airportTo ){
            found = true;
            break;
        }
    }
    if(!found){
        PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
        return;
    }
    
    try{
        navigationMap.AddEdge(haltedFlights[i].airline,haltedFlights[i].airportFrom,haltedFlights[i].airportTo,haltedFlights[i].w0,haltedFlights[i].w1);
        
    }
    catch(const VertexNotFoundException& x){
        isOk = false;
        PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
    }
    catch(const SameNamedEdgeException& y){
        isOk = false;
        PrintCanNotResumeFlight(airportFrom, airportTo, airlineName);
    }
    if(isOk){
    haltedFlights.erase(haltedFlights.begin()+i);}
}

void CENGFlight::FindFlight(const std::string& startAirportName,
                            const std::string& endAirportName,
                            float alpha)
{
    /* TODO */
    std::vector<int> intArray;
    int ind1 = navigationMap.findVertex(startAirportName);
    int ind2 = navigationMap.findVertex(endAirportName);
    if(ind1 == -1 || ind2 == -1){
      PrintPathDontExist(startAirportName, endAirportName);
      return;
    }
    if(alpha == 0.0 || alpha == 1.0){
           
        if(lruTable.Find(intArray, ind1, ind2, !alpha, true)){
               
            PrintFlightFoundInCache(startAirportName, endAirportName, !alpha);
            navigationMap.PrintPath(intArray, alpha, true);
            return;
        }
        
    }
    intArray.clear();
    try{
        navigationMap.HeuristicShortestPath(intArray, startAirportName,endAirportName, alpha);}
    catch(const VertexNotFoundException& e){
        PrintPathDontExist(startAirportName, endAirportName);
        return;
        }
    if(alpha == 0.0 || alpha == 1.0) PrintFlightCalculated(startAirportName, endAirportName, !alpha);
    
    bool inTheLoop = true;
    if(alpha == 0.0 || alpha == 1.0){   
        while(inTheLoop){
            inTheLoop = false;
        
            try{
              
            lruTable.Insert(intArray,!alpha);
            }
            catch(const TableCapFullException& e){
                inTheLoop = true;
                lruTable.RemoveLRU(1);
            }
        }
    }
    navigationMap.PrintPath(intArray, alpha, true);
}

void CENGFlight::FindSpecificFlight(const std::string& startAirportName,
                                    const std::string& endAirportName,
                                    float alpha,
                                    const std::vector<std::string>& unwantedAirlineNames) const
{
    /* TODO */
    bool correct = false;
    std::vector<int> orderedVertexEdgeIndexList;
    try{
        correct = navigationMap.FilteredShortestPath(orderedVertexEdgeIndexList, startAirportName, endAirportName, alpha, unwantedAirlineNames);
        if(correct){
            navigationMap.PrintPath(orderedVertexEdgeIndexList, alpha, true);
        }
    }
    catch(const VertexNotFoundException& e){
        PrintPathDontExist(startAirportName, endAirportName);
    }
}

void CENGFlight::FindSisterAirlines(std::vector<std::string>& airlineNames,
                               const std::string& startAirlineName,
                               const std::string& airportName) const
{
   /*
    int ind = navigationMap.findVertex(airportName);
    if(ind == -1){
       
     PrintSisterAirlinesDontCover(airportName);
      return;
    }
    std::vector<std::string> sistersList;
    std::string edgeName = startAirlineName;
    std::string vertexName = airportName;
    std::vector<GraphVertex> visited;
    GraphVertex vertex;
    bool visitedChanged = false;
    bool tempbool = false;
    
    visitedChanged = navigationMap.MaxDepthViaEdgeNameMod(vertexName, edgeName, visited);
    if(!visitedChanged){
        
         PrintSisterAirlinesDontCover(airportName);
      return;
    }
    int edgeInd = 0;
    int maxNo = -1;
    int temp = -1;
    int maxInd = 0;
    int incr = 0;
    
    while((int)visited.size() != navigationMap.totalVertexCount()){
        incr++;
         for(int i = 0; i < (int)visited.size() ; i++){
            
            std::cout << visited[i].name <<std::endl; 
        }
        if(!visitedChanged){
           
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        visitedChanged = false;
        edgeInd = 0;
        maxNo = -1;
        temp = -1;
        maxInd = 0;
        
        for(int i = 0; i < (int)visited.size() ; i++){
            
            temp = navigationMap.NoOfUnvisitedNeighbours(visited[i], visited);
            if(temp>maxNo){
                maxNo = temp;
                maxInd = i;
                }
        }
        
        vertex = visited[maxInd];
        edgeInd = navigationMap.FirstNonUtilizedAirline(sistersList, startAirlineName, vertex, visited);
        if(edgeInd == -1){
            
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        edgeName = vertex.edges[edgeInd].name;
        vertexName = vertex.name;
         visitedChanged = navigationMap.MaxDepthViaEdgeNameMod(vertexName,startAirlineName, visited);
       
        for(int j = 0; j < (int)sistersList.size(); j++){
            tempbool = navigationMap.MaxDepthViaEdgeNameMod(vertexName, sistersList[j], visited);
        
            if(tempbool) visitedChanged = true;
        }
    
         std::cout<< incr << std::endl; 
    }
    
    for(int i = 0; i < (int)sistersList.size(); i++){
        airlineNames.push_back(sistersList[i]);
    }
  */
    int ind = navigationMap.findVertex(airportName);
    if(ind == -1){
       
     PrintSisterAirlinesDontCover(airportName);
      return;
    }
    std::vector<std::string> sistersList;
   
    std::string vertexName = airportName;
    std::vector<GraphVertex> visited;
    GraphVertex vertex;
    
    bool visitedChanged = false;
    bool tempbool = false;
    sistersList.push_back(startAirlineName);
    
    visitedChanged = navigationMap.MaxDepthViaEdgeNameMod(vertexName, visited, sistersList);
    if(!visitedChanged){
         PrintSisterAirlinesDontCover(airportName);
      return;
    }
    
    int edgeInd = 0;
    int maxNo = -1;
    int temp = -1;
    int maxInd = 0;
    int incr = 0;
    
    while((int)visited.size() != navigationMap.totalVertexCount()){
        incr++;
         
        if(!visitedChanged){
           
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
        visitedChanged = false;
        edgeInd = 0;
        maxNo = -1;
        temp = -1;
        maxInd = 0;
        
        for(int i = 0; i < (int)visited.size() ; i++){
            
            temp = navigationMap.NoOfUnvisitedNeighbours(visited[i], visited);
            if(temp>maxNo){
                maxNo = temp;
                maxInd = i;
                }
        }
        
        vertex = visited[maxInd];
        edgeInd = navigationMap.FirstNonUtilizedAirline(sistersList, vertex, visited);
        if(edgeInd == -1){
            
            PrintSisterAirlinesDontCover(airportName);
            return;
        }
       
        vertexName = vertex.name;
        visitedChanged = navigationMap.MaxDepthViaEdgeNameMod(vertexName, visited, sistersList);
       
    }
  
    for(int i = 1; i < (int)sistersList.size(); i++){
        airlineNames.push_back(sistersList[i]);
    }
  
}

int CENGFlight::FurthestTransferViaAirline(const std::string& airportName,
                                           const std::string& airlineName) const
{
    /* TODO */

    try{
        navigationMap.MaxDepthViaEdgeName(airportName, airlineName);
    }
    catch(const VertexNotFoundException &e){
         return -1;
    }
    int count =  navigationMap.MaxDepthViaEdgeName(airportName, airlineName);
    return count;
   
}