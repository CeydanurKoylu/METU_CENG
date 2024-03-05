#include "CENGFlight.h"
#include <iostream>

int main()
{
    std::cout << "Testing Find Furthest Transfer Via Airline" << std::endl;
    std::cout << std::endl;

    try
    {
        CENGFlight flightSystem("turkey_flight.map");
        std::cout << "Loading Map" << std::endl;

        flightSystem.PrintMap();

        int result;
        std::cout << "--------------------" << std::endl;
        std::cout << "Furthest Transfer From Istanbul(IST) via BoraJet" << std::endl;
        result = flightSystem.FurthestTransferViaAirline("Istanbul(IST)", "BoraJet");
        std::cout << "Result is: " << result << std::endl;

        std::cout << "--------------------" << std::endl;
        std::cout << "Furthest Transfer From Istanbul(IST) via Pegasus" << std::endl;
        result = flightSystem.FurthestTransferViaAirline("Istanbul(IST)", "Pegasus");
        std::cout << "Result is: " << result << std::endl;

        std::cout << "--------------------" << std::endl;
        std::cout << "Furthest Transfer From Ankara(ESB) via Pegasus" << std::endl;
        result = flightSystem.FurthestTransferViaAirline("Ankara(ESB)", "Pegasus");
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