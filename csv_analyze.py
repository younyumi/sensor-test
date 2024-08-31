import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('sensor_data.csv')

data['Timestamp'] = pd.to_datetime(data['Timestamp'])

data['Time_Min_Sec']= data['Timestamp'].dt.strftime('%M:%S')

plt.figure(figsize=(10, 6))

# Z축 가속도와 초음파 센서 거리 시각화
plt.subplot(2, 1, 1)
plt.plot(data['Timestamp'], data['Accel_Z']) 
plt.title('Z-axis Acceleration')
plt.ylabel('Acceleration (m/s^2)')

plt.subplot(2, 1, 2)
plt.plot(data['Timestamp'], data['Distance'])
plt.title('Ultrasonic Distance')
plt.ylabel('Distance (cm)')
plt.xlabel('Time')

plt.tight_layout()
plt.show()
