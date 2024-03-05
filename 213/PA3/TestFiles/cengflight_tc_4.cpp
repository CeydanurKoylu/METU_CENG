#include "CENGFlight.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Find Specific Flight" << std::endl;
    std::cout << std::endl;
    
     
    try
    {
        CENGFlight flightSystem("turkey_flight.map");
        std::cout << "Loading Map" << std::endl;
        
        flightSystem.PrintMap();
    
        std::cout << "--------------------" << std::endl;
        std::cout << "Finding Flight Between Istanbul(IST), Trabzon(TZX), 0.0 but without BoraJet" << std::endl;
        flightSystem.FindSpecificFlight("Istanbul(IST)", "Trabzon(TZX)", 0.0f, {"BoraJet"});
        
        std::cout << "Finding Flight Between Istanbul(IST), Trabzon(TZX), 0.0 but **with** BoraJet" << std::endl;
        flightSystem.FindFlight("Istanbul(IST)", "Trabzon(TZX)", 0.0f);
        
        std::cout << "--------------------" << std::endl;
        std::cout << "Finding Flight Between Istanbul(IST), Trabzon(TZX), 0.0 but without BoraJet ***Again***" << std::endl;
        flightSystem.FindSpecificFlight("Istanbul(IST)", "Trabzon(TZX)", 0.0f, {"BoraJet"});
        
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