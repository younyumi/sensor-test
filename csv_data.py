import serial
import csv
import time

# Set up the serial connection (adjust the port as needed)
ser = serial.Serial('/dev/ttyACM0', 115200)  # Change 'COM3' to your port
time.sleep(1)  # Wait for the serial connection to establish

# Open the CSV file for writing
with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)

    # Write the header
    header = ['Timestamp', 'Ultrasonic 1 (cm)', 'Ultrasonic 2 (cm)', 'Ultrasonic 3 (cm)', 'Ultrasonic 4 (cm)',
              'Shock FR', 'Shock FL', 'Shock RR', 'Shock RL',
              'MPU6050 1 Z_acc', 'MPU6050 1 Roll', 'MPU6050 1 Pitch',
              'MPU6050 2 Z_acc', 'MPU6050 2 Roll', 'MPU6050 2 Pitch',
              'Latitude', 'Longitude']
    writer.writerow(header)

    while True:
        try:
            # Read a line from the serial port
            line = ser.readline().decode('utf-8', errors='ignore').strip()

            if "Ultrasonic 1" in line:
                # Initialize a list to hold sensor data
                data = []

                # Add a timestamp
                data.append(time.strftime("%H:%M:%S"))

                # Collect ultrasonic sensor data
                for i in range(1, 5):
                    line = ser.readline().decode('utf-8').strip()
                    distance = line.split(": ")[1]
                    data.append(distance)

                # Collect shock sensor data
                for i in range(4):
                    line = ser.readline().decode('utf-8').strip()
                    shock_status = line.split(": ")[1]
                    data.append(shock_status)

                # Collect MPU6050 sensor data
                for i in range(1, 3):
                    # Z_acc
                    line = ser.readline().decode('utf-8').strip()
                    z_acc = line.split(": ")[1]
                    data.append(z_acc)

                    # Roll
                    line = ser.readline().decode('utf-8').strip()
                    roll = line.split(": ")[1]
                    data.append(roll)

                    # Pitch
                    line = ser.readline().decode('utf-8').strip()
                    pitch = line.split(": ")[1]
                    data.append(pitch)

                # Read the GPS data if available
                line = ser.readline().decode('utf-8').strip()
                # if "Latitude" in line:
                #     latitude = line.split(": ")[1]
                #     longitude = ser.readline().decode('utf-8').strip().split(": ")[1]
                #     data.append(latitude)
                #     data.append(longitude)
                if "Latitude" in line:
                    latitude = line.split(": ")[1].split(',')[0]
                    longitude = line.split(": ")[1].split(', ')[1].split(': ')[1]
                    data.append(latitude)
                    data.append(longitude)
                # else:
                #     data.append('N/A')  # No GPS data
                #     data.append('N/A')

                # Write the row to the CSV file
                writer.writerow(data)
                print(data)  # Optionally print to console for debugging

            # Optional: Insert a small delay to avoid overwhelming the serial port
            time.sleep(0.1)

        except KeyboardInterrupt:
            print("Program interrupted")
            break


# import serial
# import csv
# import time

# # Initialize serial connection
# ser = serial.Serial('/dev/ttyACM0', 115200)

# # Open or create a CSV file to write the data
# with open('sensor_data.csv', mode='w', newline='') as file:
#     writer = csv.writer(file)
    
#     # Write CSV headers
#     header = ['Timestamp', 'Ultrasonic 1 (cm)', 'Ultrasonic 2 (cm)', 'Ultrasonic 3 (cm)', 'Ultrasonic 4 (cm)',
#               'Shock Sensor 1', 'Shock Sensor 2', 'Shock Sensor 3', 'Shock Sensor 4',
#               'MPU6050 1 Z_acc', 'MPU6050 1 Roll', 'MPU6050 1 Pitch',
#               'MPU6050 2 Z_acc', 'MPU6050 2 Roll', 'MPU6050 2 Pitch',
#               'Latitude', 'Longitude']
#     writer.writerow(header)
    
#     # 이전 센서 값을 저장할 리스트
#     prev_sensor_values = [None, None, None, None]  # 센서 4개의 이전 값 저장
    
#     while True:
#         sensor_values = []
#         shock_values = []
#         mpu6050_1_values = [None, None, None]  # Z_acc, Roll, Pitch
#         mpu6050_2_values = [None, None, None]  # Z_acc, Roll, Pitch
#         gps_values = [None, None]  # Latitude, Longitude
        
#         for i in range(14):  # 초음파 4개 + 충격감지 4개 + MPU6050 6개 + GPS 2개
#             line = ser.readline().decode('utf-8', errors='ignore').strip()

#             # 데이터를 처리할 수 있는 형식인지 확인
#             if ": " in line:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     value = parts[1].strip().replace("cm", "").strip()
#                     try:
#                         value = float(value)  # 문자열을 숫자로 변환
#                     except ValueError:
#                         value = 0  # 숫자로 변환할 수 없으면 기본값 0으로 설정
                    
#                     # 값이 100 이상일 경우 이전 값으로 대체
#                     if value > 100 and prev_sensor_values[i % 4] is not None:
#                         value = prev_sensor_values[i % 4]
#                     else:
#                         prev_sensor_values[i % 4] = value  # 정상 값일 경우 저장
#                     sensor_values.append(value)

#             elif "Shock Sensor" in line:
#                 parts = line.split(":")
#                 if len(parts) == 2:
#                     shock_values.append(int(parts[1].strip()))  # Shock Sensor는 정수로 처리
                
#             elif "MPU6050 Sensor 1 Z_acc" in line:
#                 mpu6050_1_values[0] = float(line.split(":")[1].strip())
#             elif "MPU6050 Sensor 1 Roll" in line:
#                 mpu6050_1_values[1] = float(line.split(":")[1].strip())
#             elif "MPU6050 Sensor 1 Pitch" in line:
#                 mpu6050_1_values[2] = float(line.split(":")[1].strip())
                
#             elif "MPU6050 Sensor 2 Z_acc" in line:
#                 mpu6050_2_values[0] = float(line.split(":")[1].strip())
#             elif "MPU6050 Sensor 2 Roll" in line:
#                 mpu6050_2_values[1] = float(line.split(":")[1].strip())
#             elif "MPU6050 Sensor 2 Pitch" in line:
#                 mpu6050_2_values[2] = float(line.split(":")[1].strip())
            
#             elif "Latitude" in line:
#                 parts = line.split(",")
#                 if len(parts) == 2:
#                     gps_values[0] = float(parts[0].split(":")[1].strip())
#                     gps_values[1] = float(parts[1].split(":")[1].strip())
        
#         # 모든 데이터를 수집한 후에 한 번에 CSV로 저장
#         if len(sensor_values) == 4 and len(shock_values) == 4 and None not in mpu6050_1_values and None not in mpu6050_2_values and None not in gps_values:
#             timestamp = time.strftime('%H:%M:%S', time.localtime())
#             data_row = [timestamp] + sensor_values + shock_values + mpu6050_1_values + mpu6050_2_values + gps_values
#             writer.writerow(data_row)
#             print(data_row)  # 디버깅을 위한 출력
        
#         # Add a small delay to control the data acquisition rate
#         time.sleep(0.1)

        