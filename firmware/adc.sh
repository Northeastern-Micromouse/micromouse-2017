#! /bin/bash

BASE_ADC_FILEPATH="/sys/bus/iio/devices/iio:device2/in_voltage"
BASE_CALIBRATION_FILEPATH="calibration/sensor"
BASE_OUTPUT_PATH="/home/debian/sensors/sensor"
NUM_SENSORS=6

while [ 1 ]
do
    # Loop through each of the sensors
    for x in $(seq 0 $NUM_SENSORS);
    do
        average=0
        # Sample each sensor 200 times
        for t in $(seq 0 200);
        do
            value=$(cat '/sys/bus/iio/devices/iio:device2/in_voltage'"${x}"'_raw')
            value=$(( $value+2 ))
			distance=$(sed -n "${value}p" "/home/debian/calibration/sensor${x}.csv")
            average=$(echo 'scale=10; '"$average"'+'"$distance" | tr -d $'\r' | bc)
        done

        # Calculate the final average
        average=$(( $average / 200 ))

        # Write it to the output file
        echo ${average} > $BASE_OUTPUT_PATH$x
    done
done


