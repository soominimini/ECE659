#ifndef SENSOR_H_
#define SENSOR_H_

#include <omnetpp.h>
#include <fstream>

using namespace omnetpp;

class Sensor : public cSimpleModule
{
private:
    std::string sensorType;
    double id;
    cMessage *event;
    cMessage *eventIn;
    std::ofstream outFile;
    double sendInterval; // Interval between sending sensor data
    double value; // Current value of the sensor
    double weight; // Weight for the sensor in failure calculation
    double thresholdLower; // Lower threshold for the sensor
    double thresholdUpper; // Upper threshold for the sensor

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif /* SENSOR_H_ */
