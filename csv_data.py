import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM1', 9600)

with open('MultiUltra_sensor_data.csv', mode = 'w', newline='') as file:
    writer = csv.writer(file)
    header = ['Timestamp', 'Sensor1', 'Sensor2', 'Sensor3', 'Sensor4']
    writer.writerow(header)
    
    while True:
        sensor_values = []
        for i in range(4):
            line = ser.readline().decode('utf-8').strip()
            if "Sensor" in line:
                parts = line.split(':')
                if len(parts) == 2:
                    distance = parts[1].strip().replace("cm", "").strip()
                    sensor_values.append(distance)
                    
        if len(sensor_values) == 4:
            timestamp = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
            writer.writerow([timestamp] + sensor_values)
            print([timestamp]+sensor_values)
            
        ser.readline()
        
        time.sleep(0.5)