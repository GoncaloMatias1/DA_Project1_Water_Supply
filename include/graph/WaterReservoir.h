#ifndef DA_PROJECT_23_24_WATERRESERVOIR_H
#define DA_PROJECT_23_24_WATERRESERVOIR_H

#include "Vertex.h"

/**
 * @class WaterReservoir
 * @brief Represents a water reservoir vertex in the network.
 * @details Inherits from the Vertex class and adds specific properties related to water reservoirs.
 */
class WaterReservoir : public Vertex {
private:
    std::string name; /**< The name of the water reservoir. */
    std::string municipality; /**< The municipality where the water reservoir is located. */
    unsigned int reservoirID; /**< The unique identifier of the water reservoir. */
    double maxDelivery; /**< The maximum delivery capacity of the water reservoir. */

public:
    /**
     * @brief Constructs a WaterReservoir object with the specified attributes.
     *
     * The constructor for the WaterReservoir class.
     * It initializes a new instance of a water reservoir vertex with the provided attributes such as ID, name, municipality, reservoir ID, and maximum delivery capacity.
     * These attributes are stored within the object for later use.
     *
     * @param id The ID of the water reservoir.
     * @param name The name of the water reservoir.
     * @param municipality The municipality where the water reservoir is located.
     * @param resID The unique identifier of the water reservoir.
     * @param maxDel The maximum delivery capacity of the water reservoir.
     */
    WaterReservoir(const std::string& id, const std::string& name, const std::string& municipality, unsigned int resID, double maxDel);

    /**
     * @brief Gets the type of the vertex (WaterReservoir).
     *
     * Returns the type of the vertex, specifically indicating that it's a reservoir vertex.
     *
     * @return The type of the vertex.
     */
    VertexType getType() const override;

    /**
     * @brief Gets the maximum delivery capacity of the water reservoir.
     *
     * Returns the maximum delivery capacity of the water reservoir.
     *
     * @return The maximum delivery capacity.
     */
    double getMaxDelivery() const;
};


#endif //DA_PROJECT_23_24_WATERRESERVOIR_H
