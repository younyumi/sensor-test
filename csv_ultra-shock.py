import serial
import csv
import time

# Initialize serial connection
ser = serial.Serial('/dev/ttyACM0', 115200)

# Open or create a CSV file to write the data
with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    
    # Write the header with columns for timestamp, sensor distances, and shock detection
    header = ['Timestamp', 'Sensor1 (cm)', 'Sensor2 (cm)', 'Sensor3 (cm)', 'Sensor4 (cm)',
              'Shock Sensor 1', 'Shock Sensor 2', 'Shock Sensor 3', 'Shock Sensor 4']
    writer.writerow(header)
    
    while True:
        sensor_values = []
        shock_values = []
        
        # Read and parse sensor values
        for i in range(8):  # 4 for ultrasonic sensors, 4 for shock sensors
            line = ser.readline().decode('utf-8').strip()
            if "Sensor" in line:
                parts = line.split(':')
                if len(parts) == 2:
                    value = parts[1].strip().replace("cm", "").strip()
                    
                    if "Ultrasonic" in parts[0]:
                        sensor_values.append(value)
                    elif "Shock" in parts[0]:
                        shock_values.append(value)
        
        # If we have collected all the necessary values, write them to the CSV file
        if len(sensor_values) == 4 and len(shock_values) == 4:
            timestamp = time.strftime('%H:%M:%S', time.localtime())
            writer.writerow([timestamp] + sensor_values + shock_values)
            file.flush()
            print([timestamp] + sensor_values + shock_values)
        
        # Read the next line to prevent misalignment
        ser.readline()
        
        # Add a small delay to control the data acquisition rate
        time.sleep(0.5)
