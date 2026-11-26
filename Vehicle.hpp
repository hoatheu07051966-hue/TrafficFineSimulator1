#pragma once
#include <string>
#include <utility>

namespace model {

class Vehicle {
public:
    explicit Vehicle(std::string licensePlate, double baseRiskFactor)
        : licensePlate_(std::move(licensePlate))
        , baseRiskFactor_(baseRiskFactor) {}

    virtual ~Vehicle() = default;

    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;
    Vehicle(Vehicle&&) = default;
    Vehicle& operator=(Vehicle&&) = default;

    virtual double getRiskMultiplier() const = 0;
    virtual std::string getType() const = 0;

    const std::string& getLicensePlate() const { return licensePlate_; }
    double getBaseRiskFactor() const { return baseRiskFactor_; }

protected:
    std::string licensePlate_;
    double baseRiskFactor_;
};

class Motorbike : public Vehicle {
public:
    explicit Motorbike(std::string licensePlate)
        : Vehicle(std::move(licensePlate), 1.0) {}

    double getRiskMultiplier() const override { return baseRiskFactor_; }
    std::string getType() const override { return "Motorbike"; }
};

class Car : public Vehicle {
public:
    explicit Car(std::string licensePlate)
        : Vehicle(std::move(licensePlate), 1.2) {}

    double getRiskMultiplier() const override { return baseRiskFactor_; }
    std::string getType() const override { return "Car"; }
};

class Truck : public Vehicle {
public:
    explicit Truck(std::string licensePlate)
        : Vehicle(std::move(licensePlate), 1.5) {}

    double getRiskMultiplier() const override { return baseRiskFactor_; }
    std::string getType() const override { return "Truck"; }
};

} // namespace model
