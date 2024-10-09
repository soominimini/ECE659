#include <omnetpp.h>

using namespace omnetpp;

class Sensor : public cSimpleModule
{
private:
    double thresholdLower;
    double thresholdUpper;
    double degradationRate;
    double currentValue;
    double weight; // Weight for the sensor in failure calculation
    double sensorId;
    double defaultValue;
    cMessage *sendMsgEvent;
    cMessage *resetMsg;
    std::string sensorType;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void generateSensorValue();
};

Define_Module(Sensor);

void Sensor::initialize()
{
    thresholdLower = par("thresholdLower").doubleValue();
    thresholdUpper = par("thresholdUpper").doubleValue();
    degradationRate = par("degradationRate").doubleValue();
    weight = par("weight").doubleValue();
//     random generation of the current value
//    currentValue = uniform(thresholdLower, thresholdUpper);
    currentValue = par("value").doubleValue();
    sendMsgEvent = new cMessage("sendEvent");
    sensorId =  par("sensorId").doubleValue();
    scheduleAt(simTime() + exponential(1.0), sendMsgEvent);  // Schedule the first event
    sensorType = par("sensorType").stringValue();
    defaultValue = par("defaultValue").doubleValue();
}

void Sensor::handleMessage(cMessage *msg)
{
    if (msg == sendMsgEvent) {
        generateSensorValue();
        scheduleAt(simTime() + exponential(1.0), sendMsgEvent);  // Schedule the next event
    }
    //code for renew the value
//    if(currentValue< thresholdLower ||currentValue> thresholdUpper){
//            currentValue = defaultValue;
//        }
    else{
        currentValue =defaultValue;
    }



}

void Sensor::generateSensorValue()
{

    // Randomly choose to degrade upwards or downwards
    //temperature and pressure factors keep increasing by the random chance
    //vibration and torque factors keep decreasing by the random chance
    if(sensorType=="temperature"){
        if (uniform(0, 1) < 0.5) {
            currentValue += degradationRate;
        }
    }
    else if(sensorType=="pressure"){
        if (uniform(0, 1) < 0.5) {
            currentValue += degradationRate;
        }
    }
    else if(sensorType=="vibration"){
        if (uniform(0, 1) < 0.5) {
            currentValue -= degradationRate;
        }
    }
    else{
        if (uniform(0, 1) < 0.5) {
            currentValue -= degradationRate;
        }
    }


    cMessage *msg = new cMessage("sensorValue");
    msg->addPar("sensorId") = sensorId;
    msg->addPar("sensorValue") = currentValue;
    msg->addPar("weight") = weight;
    msg->addPar("sensorType") = par("sensorType").stringValue();
    msg->addPar("thresholdUpper") = thresholdUpper;
    msg->addPar("thresholdLower") = thresholdLower;
    send(msg, "out");




}
