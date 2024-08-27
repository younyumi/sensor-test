import serial
import csv
import time
import re

ser = serial.Serial('/dev/ttyACM0', 115200)
output_file = 'acc_data.csv'


with open(output_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Acc.X", "Acc.Y", "Acc.Z", "Roll", "Pitch"])

    try:
        while True:
            line1 = ser.readline().decode('utf-8').strip()  # 첫 번째 줄(가속도)
            line2 = ser.readline().decode('utf-8').strip()  # 두 번째 줄(roll, pitch)
            
            if line1 and line2:
                match_accel = re.match(
                    r'Acceleration X:\s*([\d\.\-]+)\s*Acceleration Y:\s*([\d\.\-]+)\s*Acceleration Z:\s*([\d\.\-]+)m/s\^2', 
                    line1
                )

                match_angle = re.match(
                    r'Roll:\s*([\d\.\-]+)\s*deg,\s*Pitch:\s*([\d\.\-]+)\s*deg', 
                    line2
                )

                if match_accel and match_angle:
                    accel_data = match_accel.groups()  # 가속도 값 추출
                    angle_data = match_angle.groups()  # 각도 값 추출

                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())

                    writer.writerow([timestamp] + list(accel_data) + list(angle_data))
                    print(f"{timestamp}, {accel_data}, {angle_data}")

                else:
                    print(f"Data format does not match, skipping lines.\nLine 1: {line1}\nLine 2: {line2}")

    except KeyboardInterrupt:
        print("Data logging stopped.")

    finally:
        ser.close()
