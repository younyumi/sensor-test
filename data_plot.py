import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# CSV 파일 불러오기
file_path = '4.중간배수구.csv'
sensor_data = pd.read_csv(file_path)

# Timestamp 컬럼을 datetime 형식으로 변환
sensor_data['Timestamp'] = pd.to_datetime(sensor_data['Timestamp'])

# 100 이상의 초음파 센서 데이터 보정 (이전 및 이후 값의 평균으로 보정)
ultrasonic_columns = ['Ultrasonic 1 (cm)', 'Ultrasonic 2 (cm)', 'Ultrasonic 3 (cm)', 'Ultrasonic 4 (cm)']
for col in ultrasonic_columns:
    sensor_data[col] = sensor_data[col].mask(sensor_data[col] > 100)
    sensor_data[col].interpolate(method='linear', inplace=True)

# LPF
def low_pass_filter(data, alpha=0.5):
    filtered_data = np.zeros(len(data))
    filtered_data[0] = data[0]
    for i in range(1, len(data)):
        filtered_data[i] = alpha * data[i] + (1 - alpha) * filtered_data[i - 1]
    return filtered_data

# KalmanFilter
class KalmanFilter:
    def __init__(self, process_variance, measurement_variance, estimate_variance, initial_value):
        self.process_variance = process_variance
        self.measurement_variance = measurement_variance
        self.estimate_variance = estimate_variance
        self.value = initial_value
        self.estimate_error = 1.0

    def update(self, measurement):
        kalman_gain = self.estimate_error / (self.estimate_error + self.measurement_variance)
        self.value += kalman_gain * (measurement - self.value)
        self.estimate_error = (1 - kalman_gain) * self.estimate_error + abs(self.value - measurement) * self.process_variance
        return self.value

# MPU6050 Z축 가속도 필터링 (두 필터를 연속 적용)
mpu_columns = ['Front Z_acc', 'Rear Z_acc']
for col in mpu_columns:
    # 1. 저역 통과 필터 적용
    lowpass_filtered = low_pass_filter(sensor_data[col], alpha=0.5)
    
    # 2. 저역 통과 필터 결과에 칼만 필터 적용
    kf = KalmanFilter(process_variance=1e-5, measurement_variance=0.1**2, estimate_variance=1e-4, initial_value=lowpass_filtered[0])
    kalman_filtered = [kf.update(val) for val in lowpass_filtered]
    
    # 결과를 새로운 열에 저장
    sensor_data[f'{col}_lowpass_kalman'] = kalman_filtered

# 그래프 시각화
plt.figure(figsize=(15, 20))

# 초음파 센서 데이터 시각화
plt.subplot(5, 1, 1)
for col in ultrasonic_columns:
    plt.plot(sensor_data['Timestamp'], sensor_data[col], label=col, linewidth=1.0)
plt.title('Ultrasonic Sensor Data Over Time', fontsize=8)
plt.ylabel('Distance (cm)')
plt.legend(loc='upper left', fontsize=8)
plt.xticks(fontsize=6)

# 충격 감지 센서 데이터 시각화
shock_columns = ['Shock FR', 'Shock FL', 'Shock RR', 'Shock RL']
plt.subplot(5, 1, 2)
for col in shock_columns:
    plt.plot(sensor_data['Timestamp'], sensor_data[col], label=col, linewidth=1.0)
plt.title('Shock Sensor Data Over Time', fontsize=8)
plt.ylabel('Shock Value')
plt.legend(loc='upper left', fontsize=8)
plt.xticks(fontsize=7)

# MPU6050 Z축 가속도 시각화 (저역 통과 + 칼만 필터 적용)
plt.subplot(5, 1, 3)
for col in mpu_columns:
    plt.plot(sensor_data['Timestamp'], sensor_data[f'{col}_lowpass_kalman'], label=f'{col} (LPF + Kalman)', linewidth=1)
plt.title('MPU6050 Z-axis Acceleration (Low-Pass + Kalman Filter) Over Time', fontsize=8)
plt.ylabel('Z-axis Acceleration')
plt.legend(loc='upper left', fontsize=8)
plt.xticks(fontsize=7)

# MPU6050 Roll 시각화
plt.subplot(5, 1, 4)
plt.plot(sensor_data['Timestamp'], sensor_data['Front Roll'], label='Front Roll', linewidth=1)
plt.plot(sensor_data['Timestamp'], sensor_data['Rear Roll'], label='Rear Roll', linewidth=1)
plt.title('MPU6050 Roll Over Time', fontsize=8)
plt.ylabel('Roll (degrees)')
plt.legend(loc='upper left', fontsize=8)
plt.xticks(fontsize=7)

# MPU6050 Pitch 시각화
plt.subplot(5, 1, 5)
plt.plot(sensor_data['Timestamp'], sensor_data['Front Pitch'], label='Front Pitch', linewidth=1)
plt.plot(sensor_data['Timestamp'], sensor_data['Rear Pitch'], label='Rear Pitch', linewidth=1)
plt.title('MPU6050 Pitch Over Time', fontsize=8)
plt.ylabel('Pitch (degrees)')
plt.xlabel('Timestamp')
plt.legend(loc='upper left', fontsize=8)
plt.xticks(fontsize=7)

# 그래프 표시
plt.tight_layout()
plt.show()
