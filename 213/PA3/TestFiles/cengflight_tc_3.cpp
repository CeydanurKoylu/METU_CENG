#include "CENGFlight.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Find Flight" << std::endl;
    std::cout << std::endl;
    
     
    try
    {
        CENGFlight flightSystem("turkey_flight.map");
        std::cout << "Loading Map" << std::endl;
        
        flightSystem.PrintMap();
    
        std::cout << "--------------------" << std::endl;
        std::cout << "Finding Flight Between Istanbul(IST), Izmir(ADB), 0.0" << std::endl;
        flightSystem.FindFlight("Istanbul(IST)", "Izmir(ADB)", 0.0f);
        std::cout << "--------------------" << std::endl;
        std::cout << "Finding Flight Between Istanbul(IST), Izmir(ADB), 0.0 ***Again***" << std::endl;
        flightSystem.FindFlight("Istanbul(IST)", "Izmir(ADB)", 0.0f);
        
        std::cout << "--------------------" << std::endl;
        std::cout << "Finding Flight Between Istanbul(IST), Ankara(ESB), 0.3" << std::endl;
        flightSystem.FindFlight("Istanbul(IST)", "Ankara(ESB)", 0.3f);
        
        flightSystem.PrintCache();
        
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