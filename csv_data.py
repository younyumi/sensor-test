


import serial
import csv
import time

# Initialize serial connection
ser = serial.Serial('/dev/ttyACM0', 115200)

# Open or create a CSV file to write the data
with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    header = ['Timestamp', 'Sensor1 (cm)', 'Sensor2 (cm)', 'Sensor3 (cm)', 'Sensor4 (cm)',
              'Shock Sensor 1', 'Shock Sensor 2', 'Shock Sensor 3', 'Shock Sensor 4']
    writer.writerow(header)
    
    # 이전 센서 값을 저장할 리스트
    prev_sensor_values = [None, None, None, None]  # 센서 4개의 이전 값 저장
    
    while True:
        sensor_values = []
        shock_values = []
        
        for i in range(8):  # 4 for ultrasonic sensors, 4 for shock sensors
            line = ser.readline().decode('utf-8').strip()
            if "Sensor" in line:
                parts = line.split(':')
                if len(parts) == 2:
                    value = parts[1].strip().replace("cm", "").strip()
                    
                    if "Ultrasonic" in parts[0]:
                        # 초음파 센서 값 처리
                        try:
                            value = float(value)  # 문자열을 숫자로 변환
                        except ValueError:
                            value = 0  # 숫자로 변환할 수 없으면 기본값 0으로 설정
                        
                        # 값이 100 이상일 경우 이전 값으로 대체
                        if value > 100 and prev_sensor_values[i % 4] is not None:
                            value = prev_sensor_values[i % 4]
                        else:
                            prev_sensor_values[i % 4] = value  # 정상 값일 경우 저장
                        
                        sensor_values.append(value)
                    
                    elif "Shock" in parts[0]:
                        shock_values.append(value)
        
        # 4개의 초음파 센서와 4개의 충격 센서 값을 모두 수집한 경우
        if len(sensor_values) == 4 and len(shock_values) == 4:
            timestamp = time.strftime('%H:%M:%S', time.localtime())
            writer.writerow([timestamp] + sensor_values + shock_values)
            # file.flush()  # 즉시 파일에 기록하고 싶다면 주석 해제
            print([timestamp] + sensor_values + shock_values)
        
        # Read the next line to prevent misalignment
        ser.readline()
        
        # Add a small delay to control the data acquisition rate
        time.sleep(0.1)



