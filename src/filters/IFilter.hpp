// IFilter.hpp
#pragma once

#include "sensors/SensorData.hpp"
#include "core/Vector3D.hpp"
#include "core/Quaternion.hpp"

/**
 * @brief Interface for all navigation filters
 * 
 * IFilter defines a common interface for various filtering algorithms
 * used in the navigation system, such as Kalman filter or Madgwick filter.
 */
class IFilter {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~IFilter() = default;
    
    /**
     * @brief Updates the filter state based on new sensor data
     * 
     * @param data Sensor data to process
     */
    virtual void update(const SensorData& data) = 0;
    
    /**
     * @brief Predicts the next state
     * 
     * Predicts the next state based on the current state and system model,
     * without incorporating new measurements.
     */
    virtual void predict() = 0;
    
    /**
     * @brief Returns the current orientation
     * 
     * @return Orientation as a quaternion
     */
    virtual Quaternion getOrientation() const = 0;
    
    /**
     * @brief Returns the current position
     * 
     * @return Position as a Vector3D
     */
    virtual Vector3D getPosition() const = 0;
    
    /**
     * @brief Returns the current velocity
     * 
     * @return Velocity as a Vector3D
     */
    virtual Vector3D getVelocity() const = 0;
    
    /**
     * @brief Resets the filter to its initial state
     */
    virtual void reset() = 0;
    
    /**
     * @brief Initializes the filter based on initial data
     * 
     * @param initialData Initial data to initialize the filter
     */
    virtual void initialize(const SensorData& initialData) = 0;
    
    /**
     * @brief Returns the filter name
     * 
     * @return Filter name as a string
     */
    virtual std::string getName() const = 0;
    
    /**
     * @brief Returns position uncertainty
     * 
     * @return Position uncertainty as a Vector3D (sigma_x, sigma_y, sigma_z)
     */
    virtual Vector3D getPositionUncertainty() const = 0;
    
    /**
     * @brief Returns orientation uncertainty
     * 
     * @return Orientation uncertainty as a Vector3D (sigma_roll, sigma_pitch, sigma_yaw)
     */
    virtual Vector3D getOrientationUncertainty() const = 0;
};