//
// Created by admin1 on 08-03-2024.
//

#ifndef DA_PROJECT_23_24_CITY_H
#define DA_PROJECT_23_24_CITY_H

#include "Vertex.h"

/**
 * @brief Class representing a city vertex in the graph.
 */
class City : public Vertex{
private:
    std::string cityName; ///< Name of the city.
    unsigned int cityId; ///< ID of the city.
    unsigned int pop; ///< Population of the city.
    double demand; ///< Demand of the city.
public:

    /**
     * @brief Constructor for the City class.
     *
     * @param vertexId The ID of the vertex.
     * @param name The name of the city.
     * @param id The ID of the city.
     * @param demand_ The demand of the city.
     * @param population The population of the city.
     * @complexity O(1), direct assignments of basic data types and string.
     */
    City(const std::string& vertexId, const std::string &name, unsigned int id, double demand_, unsigned int population);
    City(City* city);

    // Getters and setters

    /**
     * @brief Sets the name of the city.
     *
     * @param name The name of the city.
     * @complexity O(1) assuming string assignment is O(1).
     */
    void setName(const std::string& name);

    /**
     * @brief Sets the ID of the city.
     *
     * @param id The ID of the city.
     * @complexity O(1), direct assignment.
     */
    void setID(unsigned int id);

    /**
     * @brief Sets the population of the city.
     *
     * @param pop_ The population of the city.
     * @complexity O(1), direct assignment.
     */
    void setPop(unsigned int pop_);

    /**
     * @brief Sets the demand of the city.
     *
     * @param demand_ The demand of the city.
     * @complexity O(1), direct assignment.
     */
    void setDemand(double demand_);

    /**
     * @brief Gets the name of the city.
     *
     * @return The name of the city.
     * @complexity O(1), direct return of a member variable.
     */
    const std::string& getName() const;

    /**
     * @brief Gets the ID of the city.
     *
     * @return The ID of the city.
     * @complexity O(1), direct return of a member variable.
     */
    unsigned int getID() const;

    /**
     * @brief Gets the population of the city.
     *
     * @return The population of the city.
     * @complexity O(1), direct return of a member variable.
     */
    unsigned int getPop() const;

    /**
     * @brief Gets the demand of the city.
     *
     * @return The demand of the city.
     * @complexity O(1), direct return of a member variable.
     */
    double getDemand() const;

    /**
     * @brief Gets the type of the vertex.
     *
     * @return The type of the vertex (CityVertex).
     * @complexity O(1), direct return of an enum value.
     */
    VertexType getType() const override;

};

#endif //DA_PROJECT_23_24_CITY_H
