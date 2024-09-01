# import pandas as pd
# import matplotlib.pyplot as plt

# data = pd.read_csv('sensor_data.csv')

# data['Timestamp'] = pd.to_datetime(data['Timestamp'])

# #data['Time_Min_Sec']= data['Timestamp'].dt.strftime('%M:%S')

# plt.figure(figsize=(10, 6))

# # Z축 가속도와 초음파 센서 거리 시각화
# plt.subplot(2, 1, 1)
# plt.plot(data['Timestamp'], data['Accel_Z']) 
# plt.title('Z-axis Acceleration')
# plt.ylabel('Acceleration (m/s^2)')

# plt.subplot(2, 1, 2)
# plt.plot(data['Timestamp'], data['Distance'])
# plt.title('Ultrasonic Distance')
# plt.ylabel('Distance (cm)')
# plt.xlabel('Time')

# plt.tight_layout()
# plt.show()



import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv('sensor_data.csv')

data['Timestamp'] = pd.to_datetime(data['Timestamp'])

# 칼만 필터 함수
def kalman_filter(data, Q, R):
    n = len(data)
    x_est = np.zeros(n)
    P = np.zeros(n)
    
    x_est[0] = data[0]
    P[0] = 1.0
    
    for k in range(1, n):
        # 예측
        x_pred = x_est[k-1]
        P_pred = P[k-1] + Q
        
        # 업데이트
        K = P_pred / (P_pred + R)
        x_est[k] = x_pred + K * (data[k] - x_pred)
        P[k] = (1 - K) * P_pred
        
    return x_est

# 칼만 필터 적용
Q = 0.01  # 프로세스 노이즈
R = 1.0   # 측정 노이즈
data['Filtered_Accel_Z'] = kalman_filter(data['Accel_Z'].values, Q, R)

plt.figure(figsize=(10, 6))

# Z축 가속도 원본 데이터 시각화
plt.subplot(2, 1, 1)
plt.plot(data['Timestamp'], data['Accel_Z'], label='Raw Data')
plt.title('Z-axis Acceleration (Raw)')
plt.ylabel('Acceleration (m/s^2)')
plt.legend()

# Z축 가속도 필터링된 데이터 시각화
plt.subplot(2, 1, 2)
plt.plot(data['Timestamp'], data['Filtered_Accel_Z'], label='Kalman Filtered', color='orange')
plt.title('Z-axis Acceleration (Kalman Filtered)')
plt.ylabel('Acceleration (m/s^2)')
plt.xlabel('Time')
plt.legend()

plt.tight_layout()
plt.show()
