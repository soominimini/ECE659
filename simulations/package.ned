package sensor_project2.simulations;

 
network SmartFactory
{
    types:
        simple Sensor {
            parameters:
                string sensorType; // "temperature", "vibration", "pressure", "torque"
                int sensorId;
                double sendInterval; // Interval between sending sensor data
                double value; // Current value of the sensor
                double weight; // Weight for the sensor in failure calculation
                double thresholdLower; // Lower threshold for the sensor
                double thresholdUpper; // Upper threshold for the sensor
                @class(Sensor);
            gates:
                output out;
        }
 
        simple Equipment {
            parameters:
                string status;
                double tempBuffer = default(5);
                double vibBuffer = default(5);
                double pressBuffer = default(5);
                double torqueBuffer = default(50);
                @class(Equipment);
            gates:
                input in[];
        }
    submodules:
        tempSensor1: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 1;
                sendInterval = 1;
                value = default(75); // Initial value for the temperature sensor
                weight = 1.0;
                thresholdLower = 70;
                thresholdUpper = 150;
        }
        tempSensor2: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 2;
                sendInterval = 1;
                value = default(75); // Initial value for the temperature sensor
                weight = 0.8;
                thresholdLower = 70;
                thresholdUpper = 150;
        }
        tempSensor3: Sensor {
            parameters:
                sensorType = "temperature";
                sensorId = 3;
                sendInterval = 1;
                value = default(75); // Initial value for the temperature sensor
                weight = 0.6;
                thresholdLower = 70;
                thresholdUpper = 150;
        }
        vibSensor1: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 1;
                sendInterval = 1;
                value = default(5); // Initial value for the vibration sensor
                weight = 1.0;
                thresholdLower = 0;
                thresholdUpper = 50;
        }
        vibSensor2: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 2;
                sendInterval = 1;
                value = default(5); // Initial value for the vibration sensor
                weight = 0.8;
                thresholdLower = 0;
                thresholdUpper = 50;
        }
        vibSensor3: Sensor {
            parameters:
                sensorType = "vibration";
                sensorId = 3;
                sendInterval = 1;
                value = default(5); // Initial value for the vibration sensor
                weight = 0.6;
                thresholdLower = 0;
                thresholdUpper = 50;
        }
        pressSensor1: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 1;
                sendInterval = 1;
                value = default(50); // Initial value for the pressure sensor
                weight = 1.0;
                thresholdLower = 0;
                thresholdUpper = 100;
        }
        pressSensor2: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 2;
                sendInterval = 1;
                value = default(50); // Initial value for the pressure sensor
                weight = 0.8;
                thresholdLower = 0;
                thresholdUpper = 100;
        }
        pressSensor3: Sensor {
            parameters:
                sensorType = "pressure";
                sensorId = 3;
                sendInterval = 1;
                value = default(50); // Initial value for the pressure sensor
                weight = 0.6;
                thresholdLower = 0;
                thresholdUpper = 100;
        }
        torqueSensor1: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 1;
                sendInterval = 1;
                value = default(500); // Initial value for the torque sensor
                weight = 1.0;
                thresholdLower = 400;
                thresholdUpper = 1100;
        }
        torqueSensor2: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 2;
                sendInterval = 1;
                value = default(500); // Initial value for the torque sensor
                weight = 0.8;
                thresholdLower = 400;
                thresholdUpper = 1100;
        }
        torqueSensor3: Sensor {
            parameters:
                sensorType = "torque";
                sensorId = 3;
                sendInterval = 1;
                value = default(500); // Initial value for the torque sensor
                weight = 0.6;
                thresholdLower = 400;
                thresholdUpper = 1100;
        }
        equipment1: Equipment {
            parameters:
                status = "normal";
        }
    connections:
        tempSensor1.out --> equipment1.in++;
        tempSensor2.out --> equipment1.in++;
        tempSensor3.out --> equipment1.in++;
        vibSensor1.out --> equipment1.in++;
        vibSensor2.out --> equipment1.in++;
        vibSensor3.out --> equipment1.in++;
        pressSensor1.out --> equipment1.in++;
        pressSensor2.out --> equipment1.in++;
        pressSensor3.out --> equipment1.in++;
        torqueSensor1.out --> equipment1.in++;
        torqueSensor2.out --> equipment1.in++;
        torqueSensor3.out --> equipment1.in++;
}
