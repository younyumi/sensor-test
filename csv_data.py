# import serial
# import csv
# import time

# ser = serial.Serial('/dev/ttyACM1', 115200)  

# with open('data.csv', mode='w', newline='') as file:
#     writer = csv.writer(file)
#     writer.writerow(['Timestamp', 'Distance'])  # 헤더 

#     while True:
#         line = ser.readline().decode('utf-8').strip()
#         if line:
#             print(line)  # 시리얼 모니터에 출력된 데이터 확인
#             parts = line.split(':')
#             if len(parts) == 2:
#                 distance = parts[1].strip().replace("cm", "").strip()
#                 timestamp = time.time()
#                 writer.writerow([timestamp, distance])
import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM1', 115200)  

with open('data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'Distance'])  # 헤더 

    while True:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)  # 시리얼 모니터에 출력된 데이터 확인
            parts = line.split(':')
            if len(parts) == 2:
                distance = parts[1].strip().replace("cm", "").strip()
                timestamp = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
                writer.writerow([timestamp, distance])
