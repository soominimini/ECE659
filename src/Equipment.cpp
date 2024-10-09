#include <omnetpp.h>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>


using namespace omnetpp;

class Equipment : public cSimpleModule
{
private:
    std::string status;
    std::ofstream outFile;
    std::map<int, double> tempValues;
    std::map<int, double> tempWeights;
    std::map<int, double> tempThresholdLower;
    std::map<int, double> tempThresholdUpper;

    std::map<int, double> vibValues;
    std::map<int, double> vibWeights;
    std::map<int, double> vibThresholdLower;
    std::map<int, double> vibThresholdUpper;

    std::map<int, double> pressValues;
    std::map<int, double> pressWeights;
    std::map<int, double> pressThresholdLower;
    std::map<int, double> pressThresholdUpper;

    std::map<int, double> torqueValues;
    std::map<int, double> torqueWeights;
    std::map<int, double> torqueThresholdLower;
    std::map<int, double> torqueThresholdUpper;

    std::set<int> tempSensorsReceived;
    std::set<int> vibSensorsReceived;
    std::set<int> pressSensorsReceived;
    std::set<int> torqueSensorsReceived;

    std::set<int> allTempSensors;
    std::set<int> allVibSensors;
    std::set<int> allPressSensors;
    std::set<int> allTorqueSensors;

    cMessage *sendMsgEvent;
    cMessage *resetMsg;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    void checkAndDecideStatus();
    void resetSensors();
};

Define_Module(Equipment);

void Equipment::initialize()
{
    status = "normal";

    // Set of all expected sensor IDs
    allTempSensors = {1, 2, 3};
    allVibSensors = {1, 2, 3};
    allPressSensors = {1, 2, 3};
    allTorqueSensors = {1, 2, 3};

    sendMsgEvent = new cMessage("sendEvent");
    resetMsg = new cMessage("resetSensor");

    // Open file to log equipment status and sensor data
    outFile.open("all_sensor_data.csv", std::ios::out | std::ios::app);
    if (outFile.is_open()) {
        outFile << "time,temp1,temp2,temp3,vib1,vib2,vib3,press1,press2,press3,torque1,torque2,torque3,status" << std::endl;
    }
}

void Equipment::handleMessage(cMessage *msg)
{
    std::string sensorType = msg->par("sensorType").stringValue();
    double sensorId = msg->par("sensorId").doubleValue();
    double value = msg->par("sensorValue").doubleValue();
    double weight = msg->par("weight").doubleValue();
    double thresholdLower = msg->par("thresholdLower").doubleValue();
    double thresholdUpper = msg->par("thresholdUpper").doubleValue();


        if (sensorType == "temperature") {
                       tempValues[sensorId] = value;
                       tempWeights[sensorId] = weight;
                       tempThresholdLower[sensorId] = thresholdLower;
                       tempThresholdUpper[sensorId] = thresholdUpper;
                       tempSensorsReceived.insert(sensorId);
                   } else if (sensorType == "vibration") {
                       vibValues[sensorId] = value;
                       vibWeights[sensorId] = weight;
                       vibThresholdLower[sensorId] = thresholdLower;
                       vibThresholdUpper[sensorId] = thresholdUpper;
                       vibSensorsReceived.insert(sensorId);
                   } else if (sensorType == "pressure") {
                       pressValues[sensorId] = value;
                       pressWeights[sensorId] = weight;
                       pressThresholdLower[sensorId] = thresholdLower;
                       pressThresholdUpper[sensorId] = thresholdUpper;
                       pressSensorsReceived.insert(sensorId);
                   } else if (sensorType == "torque") {
                       torqueValues[sensorId] = value;
                       torqueWeights[sensorId] = weight;
                       torqueThresholdLower[sensorId] = thresholdLower;
                       torqueThresholdUpper[sensorId] = thresholdUpper;
                       torqueSensorsReceived.insert(sensorId);
                   }


    // Check if we have received data from all sensors
    checkAndDecideStatus();

    delete msg;
}

void Equipment::resetSensors()
{
    // Send reset signal to all sensors
    for (int i : allTempSensors) {
        cMessage *resetMsg = new cMessage("resetSensor");
        resetMsg->addPar("sensorId") = i;
        resetMsg->addPar("sensorType") = "temperature";
        send(resetMsg, "out", i-1);
    }
    for (int i : allVibSensors) {
        int n= 2;
        cMessage *resetMsg = new cMessage("resetSensor");
        resetMsg->addPar("sensorId") = i;
        resetMsg->addPar("sensorType") = "vibration";
//        send(resetMsg, "out[]");
        send(resetMsg, "out", i+n);
    }
    for (int i : allPressSensors) {
        int n_2= 5;
        cMessage *resetMsg = new cMessage("resetSensor");
        resetMsg->addPar("sensorId") = i;
        resetMsg->addPar("sensorType") = "pressure";
//        send(resetMsg, "out[]");
        send(resetMsg, "out", i+n_2);
    }
    for (int i : allTorqueSensors) {
        int n_3= 8;
        cMessage *resetMsg = new cMessage("resetSensor");
        resetMsg->addPar("sensorId") = i;
        resetMsg->addPar("sensorType") = "torque";
//        send(resetMsg, "out[]");
        send(resetMsg, "out", i+n_3);
    }
}

void Equipment::checkAndDecideStatus()
{
    if (tempSensorsReceived == allTempSensors &&
        vibSensorsReceived == allVibSensors &&
        pressSensorsReceived == allPressSensors &&
        torqueSensorsReceived == allTorqueSensors) {
        double weightedSumTemp = 0;
        double totalWeightTemp = 0;

        double weightedSumTemp_1 = 0;
        double weightedSumTemp_2 = 0;
        double weightedSumTemp_3 = 0;
        for (const auto& kv : tempValues) {
            weightedSumTemp += kv.second * tempWeights[kv.first];
            totalWeightTemp += tempWeights[kv.first];

            if(kv.first==1){
                weightedSumTemp_1 = kv.second * tempWeights[kv.first];
            }
            else if(kv.first){
                weightedSumTemp_2 = kv.second * tempWeights[kv.first];
            }
            else{
                weightedSumTemp_3 = kv.second * tempWeights[kv.first];
            }
        }

        double weightedSumVib = 0;
        double totalWeightVib = 0;
        for (const auto& kv : vibValues) {
            weightedSumVib += kv.second * vibWeights[kv.first];
            totalWeightVib += vibWeights[kv.first];
        }

        double weightedSumPress = 0;
        double totalWeightPress = 0;
        for (const auto& kv : pressValues) {
            weightedSumPress += kv.second * pressWeights[kv.first];
            totalWeightPress += pressWeights[kv.first];
        }

        double weightedSumTorque = 0;
        double totalWeightTorque = 0;
        for (const auto& kv : torqueValues) {
            weightedSumTorque += kv.second * torqueWeights[kv.first];
            totalWeightTorque += torqueWeights[kv.first];
        }

        double averageTemp = weightedSumTemp / totalWeightTemp;
        double averageVib = weightedSumVib / totalWeightVib;
        double averagePress = weightedSumPress / totalWeightPress;
        double averageTorque = weightedSumTorque / totalWeightTorque;

        bool isFailure = (averageTemp < tempThresholdLower[1] || averageTemp > tempThresholdUpper[1] ||
                          averageVib < vibThresholdLower[1] || averageVib > vibThresholdUpper[1] ||
                          averagePress < pressThresholdLower[1] || averagePress > pressThresholdUpper[1] ||
                          averageTorque < torqueThresholdLower[1] || averageTorque > torqueThresholdUpper[1]);


        status = isFailure ? "failure" : "normal";
        if (status == "failure") {
                    resetSensors();
                }

        if (outFile.is_open()) {
            outFile << simTime();
            for (int i = 1; i <= 3; ++i) {
                outFile << "," << (tempValues.count(i) ? tempValues[i] : 0.0);
            }
            for (int i = 1; i <= 3; ++i) {
                outFile << "," << (vibValues.count(i) ? vibValues[i] : 0.0);
            }
            for (int i = 1; i <= 3; ++i) {
                outFile << "," << (pressValues.count(i) ? pressValues[i] : 0.0);
            }
            for (int i = 1; i <= 3; ++i) {
                outFile << "," << (torqueValues.count(i) ? torqueValues[i] : 0.0);
            }
            outFile << "," << status << std::endl;
        }


        // Clear the received sensor sets to prepare for the next round of data
        tempSensorsReceived.clear();
        vibSensorsReceived.clear();
        pressSensorsReceived.clear();
        torqueSensorsReceived.clear();
    }
}



void Equipment::finish()
{
    if (outFile.is_open()) {
        outFile.close();
    }
}
