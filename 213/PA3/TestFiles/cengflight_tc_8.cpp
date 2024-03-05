#include "CENGFlight.h"
#include <iostream>

int main()
{
    std::cout << "Testing Find Furthest Transfer Via Airline" << std::endl;
    std::cout << std::endl;

    try
    {
        CENGFlight flightSystem("basic_flight.map");
        std::cout << "Loading Map" << std::endl;

        flightSystem.PrintMap();

        int result;
        std::cout << "--------------------" << std::endl;
        std::cout << "Furthest Transfer From A via EDGE0" << std::endl;
        result = flightSystem.FurthestTransferViaAirline("A", "EDGE0");
        std::cout << "Result is: " << result << std::endl;

        std::cout << "--------------------" << std::endl;
        std::cout << "Furthest Transfer From B via EDGE1" << std::endl;
        result = flightSystem.FurthestTransferViaAirline("B", "EDGE1");
        std::cout << "Result is: " << result << std::endl;
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