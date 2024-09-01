import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM0', 115200)  # 포트 설정(꼭 확인해야 함)

with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'Distance', 'Accel_X', 'Accel_Y', 'Accel_Z', 'Roll', 'Pitch'])  # 헤더

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(f"{line}") 
            parts = line.split(',')

            if len(parts) == 6:  
                try:
                    distance = parts[0].split(':')[1].strip()
                    accel_x = parts[1].split(':')[1].strip()
                    accel_y = parts[2].split(':')[1].strip()
                    accel_z = parts[3].split(':')[1].strip()
                    roll = parts[4].split(':')[1].strip()
                    pitch = parts[5].split(':')[1].strip()
                    
                    print(f"{distance}, {accel_x}, {accel_y}, {accel_z}, {roll}, {pitch}")
                    
                    timestamp = time.strftime('%H:%M:%S', time.localtime())

                    writer.writerow([timestamp, distance, accel_x, accel_y, accel_z, roll, pitch])
                    file.flush()  
                except Exception as e:
                    print(f"Error parsing line: {e}")
