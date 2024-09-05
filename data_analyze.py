# import pandas as pd
# import matplotlib as plt
# import numpy as np

# data = pd.read_csv('sensor_data.csv')

# data['Time'] = pd.to_datetime(data['Timestamp'])

# def kalman_filter(data, Q, R):
#     n= len(data)
#     x_est =np.zeros(n)
#     P = np.zeros(n)
    
#     x_est[0] = data[0]
#     P[0] = 1.0
    
#     for k in range(1, n):
#         # prediction
#         x_pred = x_est[k-1]
#         P_pred = P[k-1] + Q
        
#         # update
#         K = P_pred / (P_pred + R)
#         x_est[k] = x_pred + K * (data[k] - x_pred)
#         P[k] = (1 - K) * P_pred
        
#     return x_est

# Q = 0.01  # 프로세스 노이즈
# R = 1.0   # 측정 노이즈
# data['Filtered_Accel_Z'] = kalman_filter(data['Accel_Z'].values, Q, R)
    
import pandas as pd
import matplotlib.pyplot as plt

# CSV 파일 경로 (자신의 파일 경로로 변경 가능)
file_path = 'sensor_data.csv'

# CSV 파일 로드
sensor_data = pd.read_csv(file_path)

# 컬럼명 변경 (Shock Sensors as FR, FL, RR, RL)
sensor_data.rename(columns={
    'Shock Sensor 1': 'Shock_FR',
    'Shock Sensor 2': 'Shock_FL',
    'Shock Sensor 3': 'Shock_RR',
    'Shock Sensor 4': 'Shock_RL',
    'Sensor1 (cm)': 'Sensor1',
    'Sensor2 (cm)': 'Sensor2',
    'Sensor3 (cm)': 'Sensor3',
    'Sensor4 (cm)': 'Sensor4'
}, inplace=True)

# 'Timestamp' 컬럼을 시간 객체로 변환
sensor_data['Timestamp'] = pd.to_datetime(sensor_data['Timestamp'], format='%H:%M:%S')

# 센서 거리 시각화
fig, ax1 = plt.subplots(figsize=(12, 6))

# 첫 번째 Y축에 센서 거리 값 시각화
ax1.set_xlabel('Time')
ax1.set_ylabel('Distance (cm)')
ax1.plot(sensor_data['Timestamp'], sensor_data['Sensor1'], label='Sensor1 (FR)', color='blue')
ax1.plot(sensor_data['Timestamp'], sensor_data['Sensor2'], label='Sensor2 (FL)', color='green')
ax1.plot(sensor_data['Timestamp'], sensor_data['Sensor3'], label='Sensor3 (RR)', color='red')
ax1.plot(sensor_data['Timestamp'], sensor_data['Sensor4'], label='Sensor4 (RL)', color='orange')
ax1.legend(loc='upper left')

# 두 번째 Y축에 충격 감지 시각화
ax2 = ax1.twinx()
ax2.set_ylabel('Shock Detection')
ax2.plot(sensor_data['Timestamp'], sensor_data['Shock_FR'], label='Shock FR', color='blue', linestyle='--')
ax2.plot(sensor_data['Timestamp'], sensor_data['Shock_FL'], label='Shock FL', color='green', linestyle='--')
ax2.plot(sensor_data['Timestamp'], sensor_data['Shock_RR'], label='Shock RR', color='red', linestyle='--')
ax2.plot(sensor_data['Timestamp'], sensor_data['Shock_RL'], label='Shock RL', color='orange', linestyle='--')
ax2.legend(loc='upper right')

# 그래프 제목 설정 및 표시
plt.title('Distance and Shock Detection over Time')
plt.tight_layout()
plt.show()
