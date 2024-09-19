import serial
import csv
import time


ser = serial.Serial('/dev/ttyACM0', 115200) 

with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)

    header = ['Timestamp', 'Ultrasonic 1 (cm)', 'Ultrasonic 2 (cm)', 'Ultrasonic 3 (cm)', 'Ultrasonic 4 (cm)',
              'Shock FR', 'Shock FL', 'Shock RR', 'Shock RL',
              'Front Z_acc', 'Front Roll', 'Front Pitch',
              'Rear Z_acc', 'Rear Roll', 'Rear Pitch',
              'Latitude', 'Longitude']
    writer.writerow(header)

    while True:
        try:
            line = ser.readline().decode('utf-8', errors='ignore').strip()

            if "Ultrasonic 1" in line:
                # Initialize a list to hold sensor data
                data = []

                # Add a timestamp
                data.append(time.strftime("%H:%M:%S"))


                # 초음파 센서 1 데이터 수집
                ultrasonic1 = line.split(": ")[1]
                data.append(ultrasonic1)

                # 초음파 센서 2~4 데이터 수집
                for i in range(2, 5):
                    line = ser.readline().decode('utf-8').strip()
                    if ": " in line:
                        distance = line.split(": ")[1]
                    data.append(distance)

                # Collect shock sensor data
                for i in range(4):
                    line = ser.readline().decode('utf-8').strip()
                    if ": " in line:
                        shock_status = line.split(": ")[1]
                    data.append(shock_status)

                # Collect MPU6050 sensor data
                for i in range(1, 3):
                    # Z_acc
                    line = ser.readline().decode('utf-8').strip()
                    if ": " in line:
                        z_acc = line.split(": ")[1]
                    data.append(z_acc)

                    # Roll
                    line = ser.readline().decode('utf-8').strip()
                    if ": " in line:
                        roll = line.split(": ")[1]
                    data.append(roll)

                    # Pitch
                    line = ser.readline().decode('utf-8').strip()
                    if ": " in line:
                        pitch = line.split(": ")[1]
                    data.append(pitch)

                # Read the GPS data if available
                line = ser.readline().decode('utf-8').strip()
                if "Latitude" in line and "Longitude" in line:
                    parts = line.split(", ")
                    latitude = parts[0].split(": ")[1]  # Latitude 값 추출
                    longitude = parts[1].split(": ")[1]  # Longitude 값 추출 
                    data.append(latitude)
                    data.append(longitude)

                

                writer.writerow(data)
                print(data)  # Optionally print to console for debugging

            # Optional: Insert a small delay to avoid overwhelming the serial port
            time.sleep(0.2)

        except KeyboardInterrupt:
            print("Program interrupted")
            break


















