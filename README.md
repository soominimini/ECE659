<h1>Project Overview</h1>
The project focuses on implementing a predictive maintenance system for smart factory equipment using advanced machine learning techniques. Predictive maintenance seeks to forecast equipment failures before they occur, minimizing unplanned downtime, cutting maintenance costs, extending equipment lifespan, and enhancing safety.
<br><br>
The project employs Long Short-Term Memory (LSTM) neural networks to predict the Time-to-Failure (TTF) of equipment based on sensor data. Sensor types include temperature, pressure, vibration, and torque, simulating both normal and failure scenarios within a factory environment using OMNeT++. This simulation generates realistic time-series data, which is processed and analyzed using Python, incorporating feature engineering to extract health indicators from the equipment.
<br><br>
The system includes a real-time monitoring system, continuously collecting and processing sensor data to provide immediate insights and enable proactive interventions.

<h1>Detailed System Flow</h1>

<h3> Data Generation (OMNeT++ Simulation)</h3>
<ul>
<li>Sensor Module: The system simulates multiple sensors (temperature, vibration, pressure, torque) embedded in the equipment. Each sensor has unique identifiers and operates based on thresholds and degradation rates. The sensors produce realistic sensor data, which either increases (temperature and pressure) or decreases (vibration and torque) over time as the equipment operates.</li>
<br><br>
<li>Scheduling: The sensors transmit data to a central processing unit (CPU) using an exponential backoff algorithm, which manages when the sensors send the data by introducing randomized intervals between transmissions.</li>
</ul>

<video width="320" height="240" controls>
  <source src="https://github.com/soominimini/ECE659/blob/main/sensor_test.mp4" type="video/mp4">
</video>
<h3>Data Transmission and Processing</h3>
<ul>
<li>Data Transmission: Sensor data (including sensor ID, values, and reliability weights) are periodically transmitted to the equipment's CPU. Data is aggregated in categorized maps (temperature, vibration, etc.).
Equipment Status Determination: The equipment CPU processes the received sensor data, determining the machine's health. If any sensor data crosses predefined thresholds, the system identifies the equipment as malfunctioning.</li>
</ul>
<h3>LSTM Prediction Model</h3>
<ul>
<li>Data Collection: The simulated data from sensors is logged and prepared for training the LSTM model. A large dataset is collected (278,152 samples), including time-series data for each sensor type.
Feature Engineering: Lag features are generated to capture temporal dependencies, which are crucial for the LSTM model to predict equipment failure. Missing data points are removed.
Training: The LSTM model is trained with multiple layers to capture the complex patterns in sensor data. The training includes techniques like dropout to avoid overfitting and early stopping to halt training when validation performance plateaus.
Prediction: The trained model predicts TTF (Time-to-Failure) for each piece of equipment based on real-time data, enabling proactive maintenance.</li></ul>

<ul>
<li><h3>Real-Time Monitoring</h3>
Local and Online Monitoring: The system continuously collects data in real-time from the OMNeT++ simulation, which is stored in a shared CSV file. A Python script periodically uploads this data to a Google Spreadsheet for real-time updates.
Anomaly Detection: A Google Colab script fetches this data and performs real-time anomaly detection, identifying any irregular sensor readings that could indicate an impending failure.</li></ul>
