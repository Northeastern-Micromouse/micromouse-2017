import sys

BASE_ADC_FILEPATH = '/sys/bus/iio/devices/iio:device2/in_voltage{}_raw'
NUM_SAMPLES = 200

data1 = ''
data2 = ''

while True:
    try:
        average1 = 0
        average2 = 0
        
        distance = raw_input('Distance: ')
        
        for sample in range(0, NUM_SAMPLES):
            with open('/sys/bus/iio/devices/iio:device2/in_voltage' + sys.argv[1] + '_raw') as f:
                average1 += float(f.readline())            
            with open('/sys/bus/iio/devices/iio:device2/in_voltage' + sys.argv[2] + '_raw') as f:
                average2 += float(f.readline())
               
        average1 /= NUM_SAMPLES
        average2 /= NUM_SAMPLES    
        
        data1 += ('{' + str(average1) + ',' + distance + '},')
        data2 += ('{' + str(average2) + ',' + distance + '},')
        
        print '{' + str(average1) + ',' + distance + '} {' + str(average2) + ',' + distance + '}'

    except: 
        print sys.argv[1]
        print data1
        print sys.argv[2]
        print data2
        exit()