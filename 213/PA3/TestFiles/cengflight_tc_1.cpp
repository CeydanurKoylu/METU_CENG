#include "CENGFlight.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Halt Flight" << std::endl;
    std::cout << std::endl;
    
    try
    {
        CENGFlight flightSystem("turkey_flight.map");
        std::cout << "Loading Map" << std::endl;
        
        flightSystem.PrintMap();
    
        std::cout << "--------------------" << std::endl;
        std::cout << "Halting Flight Ankara(ESB), Istanbul(IST), THY" << std::endl;
        flightSystem.HaltFlight("Ankara(ESB)", "Istanbul(IST)", "THY");
        std::cout << "--------------------" << std::endl;
        std::cout << "Halting Flight Van(VAN), Dalaman(DLM), THY" << std::endl;
        flightSystem.HaltFlight("Van(VAN)", "Dalaman(DLM)", "THY");
        
        flightSystem.PrintMap();
    }
    catch(SameNamedEdgeException& e)
    {
        std::cout << e.ToString() << std::endl;
        return 0;
    }
    catch(DuplicateVertexException& e)
    {
        std::cout << e.ToString() << std::endl;
        return 0;
    }
    catch(VertexNotFoundException& e)
    {
        std::cout << e.ToString() << std::endl;
        return 0;
    }
    
	return 0;
}