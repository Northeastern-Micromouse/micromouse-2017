#! /bin/bash

BASE_ADC_FILEPATH="/sys/bus/iio/devices/iio:device2/in_voltage"
BASE_CALIBRATION_FILEPATH="calibration/sensor"
BASE_OUTPUT_PATH="/home/debian/sensors/sensor"
NUM_SENSORS=5
ADC_0="test"
ADC_1="test1"
ADC_2="test2"
ADC_3="test3"
ADC_4="test4"

# Read in the calibration tables
readarray ADC_0 < $BASE_CALIBRATION_FILEPATH"0.csv"
readarray ADC_1 < $BASE_CALIBRATION_FILEPATH"1.csv"
readarray ADC_2 < $BASE_CALIBRATION_FILEPATH"2.csv"
readarray ADC_3 < $BASE_CALIBRATION_FILEPATH"3.csv"
readarray ADC_4 < $BASE_CALIBRATION_FILEPATH"4.csv"

while [ 1 ]
do
    # Loop through each of the sensors
    for x in $(seq 0 $NUM_SENSORS);
    do
        average=0
        adc="ADC_"$x
        # Sample each sensor 200 times
        for x in $(seq 0 200);
        do
            value=$(<$BASE_ADC_FILEPATH"$x""_raw")
            value+=2
            average+=${${!adc}[$value]}
        done

        # Calculate the final average
        average=$average/200

        # Write it to the output file
        $average > $BASE_OUTPUT_PATH$x
    done
done


