import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM0', 115200)  
ser.flush()

with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'Distance', 'Accel_X', 'Accel_Y', 'Accel_Z', 'Roll', 'Pitch'])  # 헤더

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)  
            parts = line.split(', ')

            if len(parts) == 6:  
                distance = parts[0].split(': ')[1].replace("cm", "").strip()
                accel_x = parts[1].split(': ')[1].replace("m/s^2", "").strip()
                accel_y = parts[2].split(': ')[1].replace("m/s^2", "").strip()
                accel_z = parts[3].split(': ')[1].replace("m/s^2", "").strip()
                roll = parts[4].split(': ')[1].replace("deg", "").strip()
                pitch = parts[5].split(': ')[1].replace("deg", "").strip()
                
                timestamp = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())

                writer.writerow([timestamp, distance, accel_x, accel_y, accel_z, roll, pitch])
