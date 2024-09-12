import serial
import csv
import time

# 시리얼 포트 설정
ser = serial.Serial('/dev/ttyACM0', 115200)  # 적절한 시리얼 포트로 변경해야 함

# CSV 파일 열기
with open('mpu6050_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    
    # CSV 파일의 헤더 작성
    writer.writerow(["Timestamp", "Sensor 1 Z_acc", "Sensor 1 Roll", "Sensor 1 Pitch", 
                     "Sensor 2 Z_acc", "Sensor 2 Roll", "Sensor 2 Pitch"])
    
    while True:
        try:
            # 시리얼 데이터 읽기
            line = ser.readline().decode('utf-8').strip()
            print(line)  # 출력하여 데이터를 확인

            # 데이터가 첫 번째 센서의 값인지 확인
            if "MPU6050 Sensor 1 Z_acc" in line:
                # 첫 번째 센서 데이터 읽기
                sensor1_z_acc = float(line.split(': ')[1])

                # 첫 번째 센서의 Roll 데이터 읽기
                line = ser.readline().decode('utf-8').strip()
                sensor1_roll = float(line.split(': ')[1])

                # 첫 번째 센서의 Pitch 데이터 읽기
                line = ser.readline().decode('utf-8').strip()
                sensor1_pitch = float(line.split(': ')[1])

                # 두 번째 센서의 Z_acc 데이터 읽기
                line = ser.readline().decode('utf-8').strip()
                if "MPU6050 Sensor 2 Z_acc" in line:
                    sensor2_z_acc = float(line.split(': ')[1])

                    # 두 번째 센서의 Roll 데이터 읽기
                    line = ser.readline().decode('utf-8').strip()
                    sensor2_roll = float(line.split(': ')[1])

                    # 두 번째 센서의 Pitch 데이터 읽기
                    line = ser.readline().decode('utf-8').strip()
                    sensor2_pitch = float(line.split(': ')[1])

                    # 현재 시간 기록
                    timestamp = time.strftime("%H:%M:%S")

                    # 데이터를 CSV 파일에 기록
                    writer.writerow([timestamp, sensor1_z_acc, sensor1_roll, sensor1_pitch, 
                                     sensor2_z_acc, sensor2_roll, sensor2_pitch])

                    # 출력 구분선 넘기기
                    ser.readline()  # "---------------------" 건너뜀

        except KeyboardInterrupt:
            print("데이터 수집 중단")
            break
