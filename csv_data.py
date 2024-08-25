import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM0', 115200)  

with open('data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp','Sensor', 'Distance'])  # 헤더 

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line and "Sensor" in line:
            print(line)  # 시리얼 모니터에 출력된 데이터 확인
            parts = line.split(':')
            if len(parts) == 2:
                sensor_name = parts[0].strip()
                distance = parts[1].strip().replace("cm", "").strip()
                timestamp = time.time()
                writer.writerow([timestamp, sensor_name, distance])
