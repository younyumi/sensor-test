import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv('sensor_data.csv')

# 데이터 시각화
plt.figure(figsize=(10, 6))

# Z축 가속도와 초음파 센서 거리 시각화
plt.subplot(2, 1, 1)
plt.plot(data['Time'], data['Accel_Z(m/s^2)'])
plt.title('Z-axis Acceleration')
plt.ylabel('Acceleration (m/s^2)')

plt.subplot(2, 1, 2)
plt.plot(data['Time'], data['Distance(cm)'])
plt.title('Ultrasonic Distance')
plt.ylabel('Distance (cm)')
plt.xlabel('Time')

plt.tight_layout()
plt.show()
