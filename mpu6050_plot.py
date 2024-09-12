# mpu6050_data.csv 파일에서 데이터를 불러와서 그래프를 그리는 코드입니다.
import pandas as pd
import matplotlib.pyplot as plt

# mpu6050_data.csv 파일 읽기
df = pd.read_csv('mpu6050_data.csv')

# 시간 데이터를 숫자로 변경 (초 단위)
df['Timestamp'] = pd.to_datetime(df['Timestamp'], format='%H:%M:%S').dt.second

# 그래프 그리기
plt.figure(figsize=(10, 6))

# Sensor 1 Z_acc vs. Timestamp
plt.plot(df['Timestamp'], df['Sensor 1 Z_acc'], label="Sensor 1 Z_acc")
# Sensor 2 Z_acc vs. Timestamp
plt.plot(df['Timestamp'], df['Sensor 2 Z_acc'], label="Sensor 2 Z_acc")

plt.xlabel('Time (seconds)')
plt.ylabel('Z-axis Acceleration')
plt.title('Z-axis Acceleration over Time for Two MPU6050 Sensors')
plt.legend()
plt.grid(True)

# 그래프 보여주기
plt.show()
