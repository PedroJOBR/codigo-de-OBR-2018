void qtr_cal()
{
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');

  }
  Serial.println();
  Serial.println();
  delay(1000);
}
void oi() {
  unsigned int position = qtra.readLine(sensorValues);
  sensorE = analogRead(TCRT_E);
  sensorD = analogRead(TCRT_D);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  Serial.print(sensorValues[0]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[1]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[2]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[3]);//                                |qtr1|   |qtr2|   |qtr3|   |qtr4| || |qtr5|    |qtr6| ||  |qtr7|   |qtr8|
  Serial.print('\t');
  Serial.print(sensorValues[4]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[5]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[6]);//                                                                  ||                  ||
  Serial.print('\t');
  Serial.print(sensorValues[7]);//                                                                  ||                  ||
  Serial.print('\t');

  sensor_1 = analogRead(TCRT_f1);
  sensor_2 = analogRead(TCRT_f2);
  Serial.print("(");
  Serial.print(sensorE);
  Serial.print(" --- ");
  Serial.print(sensorD);
  Serial.print(") ---");
  Serial.print(sensor_1);
  Serial.print(" --- ");
  Serial.print(sensor_2);
  Serial.print('\t');
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.print(position); // comment this line out if you are using raw values
}

