# senior-project
—This research aims to develop a smart shoe that
can measure a knee abduction moment (KAM) while walking.
Previous research shows that activities with high KAM are related
to producing future knee pain in elders. Therefore, various kinds
of floor propose to reduce the risk of osteoarthritis and injury
of falls in elderly persons. KAM is a factor to determine a
supporting property of the floor. However, KAM is normally
measured from the optical tracking system and force plate in
the laboratory that can not be moved. Our research proposes
a smart shoe with a portable sensor to estimate KAM in
an open environment. The smart shoe consists of an inertial
measurement unit (IMU) sensor and six force sensors connected
to the microcontroller to collect forces and kinematic data while
walking. Then, it uses a multi-layer perceptron regressor (MLP
Regressor) for predicting KAM by applying collected data. The
proposed shoe can estimate peak KAM with an accuracy of 86.95
percent compared to the actual KAM measured in the laboratory.

Methodology
Our methodology is to predict the knee abduction moment.
Our tasks are separated into 2 main sections as Fig. 1. 
![image](https://user-images.githubusercontent.com/86301579/152708896-54d895bf-5127-4714-ae6a-feba17803b79.png)

The first data is a section of the ambulatory. The second data is a
section of the reference data coming from a laboratory.
A. Ambulatory (Data1)
We collect input data (the first data). This section is separated into 4 subsections as below.
![image](https://user-images.githubusercontent.com/86301579/152708908-1eb66d41-c072-4b0c-b489-db8d6ab590a1.png)

1) Implementation: Our smart shoe consists of ESP32
micro-controller (NodeMCU-32s model), 5 FSR402-sensors,
1 FSR406-sensor, and 1 IMU sensor. The ESP32 module and
IMU sensor are attached on the Printed Circuit Board (PCB)
The FSRs are attached under the smart shoe sole wiring to PCB. The PCB is attached
behind the hind ankle of the right-side shoe.

2) Data collection: Our smart shoe data are collected in
the form of a 100 Hz frequency rate from ESP32. They are
sent from ESP32 via Bluetooth to a computer, and it saves as
Comma-Separated Values (.CSV) files. The collected data are
consist of roll, pitch, and yaw from the IMU sensor and 12-
bit-analog-read value from FSRs. The tester is a 24-year-old
male with a height of 176 cm and 102 kg. We collected the
data by walking in the length of 60 steps from the right step.

3) Data processing: The data from ESP32 are inputs for
the machine learning model. We use only the stance phase
(a phase of the gait cycle). We try to filter the signal to be
the stance phase. The 12-bit-analog-read values also convert
to reaction force in this process.

4) Data analyzing: Our machine learning model is Multilayer Perceptron Regressor (MLPRegressor). 
The model is designed to be a regression model with supervised data from
the laboratory section. The supervised data comes from the
Vicon-3D-tracking system and Ground Reaction Force (GRF)
sensor as a target of the model. Our model consists of one node of the input
layer, one node of the output layer, and three hidden layers.
Each hidden layer consists of 1051 nodes, 801 nodes, and 751
nodes—the model setup shown in the experiment part.

B. Laboratory (Data2)
We collected the laboratory’s supervised or reference data
(the second data). The laboratory includes the Vicon-3D tracking system and Ground Reaction Force (GRF) sensor. 
The laboratory data result in the value of knee reaction moment.
After we finished both sections, we compared both data
to the accuracy of the MLPregressor model. If the result has
enough accuracy, we use that MLPregressor model to be the
smart shoe model. Otherwise, the MLPregressor is rejected,
and we have to repeat the data analyzing step again.
