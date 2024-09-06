import pandas as pd
import matplotlib.pyplot as plt

# CSV 파일 불러오기
file_path = 'sensor_data.csv'
sensor_data = pd.read_csv(file_path)

# Timestamp 컬럼을 datetime 형식으로 변환
sensor_data['Timestamp'] = pd.to_datetime(sensor_data['Timestamp'])

# 모든 센서 데이터를 시각화
plt.figure(figsize=(15, 10))

# 초음파 센서 데이터 시각화
plt.subplot(3, 1, 1)
plt.plot(sensor_data['Timestamp'], sensor_data['Ultrasonic 1 (cm)'], label='Ultrasonic 1')
plt.plot(sensor_data['Timestamp'], sensor_data['Ultrasonic 2 (cm)'], label='Ultrasonic 2')
plt.plot(sensor_data['Timestamp'], sensor_data['Ultrasonic 3 (cm)'], label='Ultrasonic 3')
plt.plot(sensor_data['Timestamp'], sensor_data['Ultrasonic 4 (cm)'], label='Ultrasonic 4')
plt.title('Ultrasonic Sensor Data Over Time')
plt.ylabel('Distance (cm)')
plt.legend(loc='upper right')

# 충격 감지 센서 데이터 시각화
plt.subplot(3, 1, 2)
plt.plot(sensor_data['Timestamp'], sensor_data['Shock FR'], label='Shock FR')
plt.plot(sensor_data['Timestamp'], sensor_data['Shock FL'], label='Shock FL')
plt.plot(sensor_data['Timestamp'], sensor_data['Shock RR'], label='Shock RR')
plt.plot(sensor_data['Timestamp'], sensor_data['Shock RL'], label='Shock RL')
plt.title('Shock Sensor Data Over Time')
plt.ylabel('Shock Value')
plt.legend(loc='upper right')

# MPU6050 Z축 가속도 시각화
plt.subplot(3, 1, 3)
plt.plot(sensor_data['Timestamp'], sensor_data['MPU6050 1 Z_acc'], label='MPU6050 1 Z_acc')
plt.plot(sensor_data['Timestamp'], sensor_data['MPU6050 2 Z_acc'], label='MPU6050 2 Z_acc')
plt.title('MPU6050 Z-axis Acceleration Over Time')
plt.ylabel('Z-axis Acceleration')
plt.xlabel('Timestamp')
plt.legend(loc='upper right')

# 그래프 표시
plt.tight_layout()
plt.show()
