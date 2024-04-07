#ifndef DA_PROJECT_23_24_PUMPINGSTATION_H
#define DA_PROJECT_23_24_PUMPINGSTATION_H

#include "Vertex.h"

/**
 * @class PumpingStation
 * @brief Represents a pumping station vertex in a graph.
 * @details Inherits from the Vertex class and adds specific properties related to pumping stations.
 */
class PumpingStation : public Vertex {
private:
    unsigned int stationId; /**< Identifier for the pumping station */

public:
    /**
     * @brief Constructor for PumpingStation class.
     *
     * Initializes a new pumping station object with the provided ID and pumping station ID (psID).
     * It calls the constructor of the Vertex base class, passing the provided ID to initialize the vertex.
     * Then, it sets the stationId member variable to the provided psID.
     *
     * @param id The identifier for the pumping station vertex.
     * @param psID The identifier for the pumping station.
     * @complexity O(1), as the operation involves direct assignment of basic types.
     */
    PumpingStation(const std::string& id, unsigned int psID);

    /**
     * @brief Returns the type of vertex, which is PumpingStation.
     *
     * Returns the type of the vertex, which is specifically a pumping station vertex.
     *
     * @return VertexType::PumpingStation.
     * @complexity O(1), simply returns the enum value indicating the vertex type.
     */
    VertexType getType() const override;
};

#endif //DA_PROJECT_23_24_PUMPINGSTATION_H
