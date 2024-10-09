package sensor_project2;

//package inet.examples.wireless.mactest;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;


import inet.visualizer.contract.IIntegratedVisualizer;
import ned.IdealChannel;


network SmartFactory
{
    @display("bgb=426.62,421.48");
    types:
        simple Sensor
        {
            parameters:
                string sensorType; // "temperature", "vibration", "pressure", "torque"
                double sensorId;
                double sendInterval; // Interval between sending sensor data
                double value; // Current value of the sensor
                double weight; // Weight for the sensor in failure calculation
                double thresholdLower; // Lower threshold for the sensor
                double thresholdUpper; // Upper threshold for the sensor
                double degradationRate; // rate at which the sensor value degrades over time

                double defaultValue;

                @class(Sensor);

            gates:
                output out;
                input in;

        }

        simple Equipment
        {
            parameters:
                string status;
                double tempThresholdUpper = default(150);
                double tempThresholdLower = default(70);
                double vibThresholdUpper = default(50);
                double vibThresholdLower = default(0);
                double pressThresholdUpper = default(100);
                double pressThresholdLower = default(0);
                double torqueThresholdUpper = default(1100);
                double torqueThresholdLower = default(400);
                @class(Equipment);
            gates:
                input in[];
                output out[12];
        }
    submodules:
        tempSensor1: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 1.0;
                sendInterval = 1;
                value = 110; // Initial value for the temperature sensor
                weight = 1.8;

                thresholdLower = 70;
                thresholdUpper = 150;
//                degradationRate = 2;
                degradationRate = 1;

                defaultValue = 110;
                @display("p=276,196");
        }
        tempSensor2: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 2;
                sendInterval = 1;
                value = 120; // Initial value for the temperature sensor
                weight = 1.3;
                thresholdLower = 70;
                thresholdUpper = 150;
//                degradationRate = 1;
                degradationRate = 0.5;
                defaultValue = 120;
                @display("p=104,81");
        }
        tempSensor3: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 3;
                sendInterval = 1;
                value = 130; // Initial value for the temperature sensor
                weight = 0.9;
                thresholdLower = 70;
                thresholdUpper = 150;
//                degradationRate = 0.5;
                degradationRate = 0.1;
                defaultValue = 130;
                @display("p=219,219");
        }
        vibSensor1: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 1;
                sendInterval = 1;
                value = 25; // Initial value for the vibration sensor
                weight = 1.8;
                thresholdLower = 0;
                thresholdUpper = 50;
//                degradationRate = 2;
				degradationRate = 1;
                defaultValue = 25;
                @display("p=282,145");
        }
        vibSensor2: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 2;
                sendInterval = 1;
                value = 20; // Initial value for the vibration sensor
                weight = 1.3;
                thresholdLower = 0;
                thresholdUpper = 50;
//                degradationRate = 1;
                degradationRate = 0.5;
                defaultValue = 20;
                @display("p=157,258");
        }
        vibSensor3: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 3;
                sendInterval = 1;
                value = 15; // Initial value for the vibration sensor
                weight = 0.9;
                thresholdLower = 0;
                thresholdUpper = 50;
//                degradationRate = 0.5;
                degradationRate = 0.1;
                defaultValue = 15;
                @display("p=80,184");
        }
        pressSensor1: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 1;
                sendInterval = 1;
                value = 50; // Initial value for the pressure sensor
                weight = 1.8;
                thresholdLower = 0;
                thresholdUpper = 100;
//                degradationRate = 2;
                degradationRate = 1;
                defaultValue = 50;
                @display("p=110,219");
        }
        pressSensor2: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 2;
                sendInterval = 1;
                value = 60; // Initial value for the pressure sensor
                weight = 1.3;
                thresholdLower = 0;
                thresholdUpper = 100;
//                degradationRate = 1;
                degradationRate = 0.5;
                defaultValue = 60;
                @display("p=110,133");
        }
        pressSensor3: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 3;
                sendInterval = 1;
                value = 70; // Initial value for the pressure sensor
                weight = 0.9;
                thresholdLower = 0;
                thresholdUpper = 100;
//                degradationRate = 0.5;
                degradationRate = 0.1;
                defaultValue = 70;
                @display("p=205,283");
        }
        torqueSensor1: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 1;
                sendInterval = 1;
                value = 750; // Initial value for the torque sensor
                weight = 1.8;
                thresholdLower = 400;
                thresholdUpper = 1100;
//                degradationRate = 2;
                degradationRate = 1;
                defaultValue = 750;
                @display("p=262,114");
        }
        torqueSensor2: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 2;
                sendInterval = 1;
                value = 600; // Initial value for the torque sensor
                weight = 1.3;
                thresholdLower = 400;
                thresholdUpper = 1100;
//                degradationRate = 1;
                degradationRate = 0.5;
                defaultValue = 600;
                @display("p=166,69");
        }
        torqueSensor3: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 3;
                sendInterval = 1;
                value = 500; // Initial value for the torque sensor
                weight = 0.9;
                thresholdLower = 400;
                thresholdUpper = 1100;
//                degradationRate = 0.5;
                degradationRate = 0.1;
                defaultValue = 500;
                @display("p=219,87");
        }
        //
        equipment1: Equipment {//AdhocHost  
            parameters:
                status = "normal";

                @display("p=180.928,155.228");
        }
    connections:


        tempSensor1.out --> IdealChannel --> equipment1.in++;
        tempSensor2.out --> IdealChannel --> equipment1.in++;
        tempSensor3.out --> IdealChannel --> equipment1.in++;

        vibSensor1.out --> IdealChannel --> equipment1.in++;
        vibSensor2.out --> IdealChannel --> equipment1.in++;
        vibSensor3.out --> IdealChannel --> equipment1.in++;

        pressSensor1.out --> IdealChannel --> equipment1.in++;
        pressSensor2.out --> IdealChannel --> equipment1.in++;
        pressSensor3.out --> IdealChannel --> equipment1.in++;


        torqueSensor1.out --> IdealChannel --> equipment1.in++;
        torqueSensor2.out --> IdealChannel --> equipment1.in++;
        torqueSensor3.out --> IdealChannel --> equipment1.in++;



        equipment1.out[0] --> IdealChannel --> tempSensor1.in;
        equipment1.out[1] --> IdealChannel --> tempSensor2.in;
        equipment1.out[2] --> IdealChannel --> tempSensor3.in;

        equipment1.out[3] --> IdealChannel --> vibSensor1.in;
        equipment1.out[4] --> IdealChannel --> vibSensor2.in;
        equipment1.out[5] --> IdealChannel --> vibSensor3.in;

        equipment1.out[6] --> IdealChannel --> pressSensor1.in;
        equipment1.out[7] --> IdealChannel --> pressSensor2.in;
        equipment1.out[8] --> IdealChannel --> pressSensor3.in;

        equipment1.out[9] --> IdealChannel --> torqueSensor1.in;
        equipment1.out[10] --> IdealChannel --> torqueSensor2.in;
        equipment1.out[11] --> IdealChannel --> torqueSensor3.in;
}
