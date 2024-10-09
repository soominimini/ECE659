/*
 * Equipment.h
 *
 *  Created on: 2024. 7. 15.
 *      Author: lov4e
 */

#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_



#include <omnetpp.h>
#include <fstream>

using namespace omnetpp;

class Equipment : public cSimpleModule
{
private:
    std::string status;
    std::ofstream outFile;
    double tempThreshold, vibThreshold, pressThreshold, torqueThreshold;
    double tempBuffer,vibBuffer,pressBuffer,torqueBuffer;
    cMessage *event;
    cMessage *eventOut;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
//    virtual void resetSensors(cMessage *msg) override;
};

#endif /* EQUIPMENT_H_ */
