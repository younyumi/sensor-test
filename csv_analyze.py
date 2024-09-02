import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 칼만 필터 함수 정의
def kalman_filter(data, Q=1e-5, R=0.1**2):
    """
    칼만 필터로 1차원 데이터를 필터링하는 함수
    data: 필터링할 1차원 데이터 (리스트나 numpy 배열)
    Q: 프로세스 노이즈 공분산 (기본값: 1e-5)
    R: 측정 노이즈 공분산 (기본값: 0.1^2)
    """
    n = len(data)
    xhat = np.zeros(n)  # 필터링된 데이터
    P = np.zeros(n)     # 추정 오류 공분산
    xhatminus = np.zeros(n)  # 업데이트 전 추정치
    Pminus = np.zeros(n)     # 업데이트 전 오류 공분산
    K = np.zeros(n)      # 칼만 이득

    # 초기값 설정
    xhat[0] = data[0]
    P[0] = 1.0

    for k in range(1, n):
        # 시간 업데이트 (예측 단계)
        xhatminus[k] = xhat[k-1]
        Pminus[k] = P[k-1] + Q

        # 측정 업데이트 (수정 단계)
        K[k] = Pminus[k] / (Pminus[k] + R)
        xhat[k] = xhatminus[k] + K[k] * (data[k] - xhatminus[k])
        P[k] = (1 - K[k]) * Pminus[k]

    return xhat

# CSV 파일 로드
data = pd.read_csv('sensor_data.csv')

# 시간 데이터를 pandas datetime 형식으로 변환
data['Time'] = pd.to_datetime(data['Time'], format='%H:%M:%S')

# 칼만 필터를 적용하여 가속도 데이터 필터링
for label in ['FR', 'FL', 'RR', 'RL']:
    for axis in ['X', 'Y', 'Z']:
        data[f'{label}_Acc_{axis}_filtered'] = kalman_filter(data[f'{label}_Acc_{axis}'])

# 초음파 센서 거리 변화 시각화
plt.figure(figsize=(12, 6))
plt.plot(data['Time'], data['Sensor1'], label='Sensor1')
plt.plot(data['Time'], data['Sensor2'], label='Sensor2')
plt.plot(data['Time'], data['Sensor3'], label='Sensor3')
plt.plot(data['Time'], data['Sensor4'], label='Sensor4')
plt.title('Distance Measurements from Ultrasonic Sensors Over Time')
plt.xlabel('Time')
plt.ylabel('Distance (cm)')
plt.legend()
plt.grid(True)
plt.show()

# 4개의 축에 대한 가속도, 롤, 피치, 충격 여부 시각화
fig, axs = plt.subplots(4, 3, figsize=(15, 10))

sensor_labels = ['FR', 'FL', 'RR', 'RL']
axis_labels = ['X', 'Y', 'Z']
colors = ['r', 'g', 'b']

for i, label in enumerate(sensor_labels):
    # 3축 가속도 시각화 (원본 및 필터링된 데이터 비교)
    for j, axis in enumerate(axis_labels):
        axs[i, 0].plot(data['Time'], data[f'{label}_Acc_{axis}'], color=colors[j], linestyle='--', label=f'{label}_Acc_{axis} (Raw)')
        axs[i, 0].plot(data['Time'], data[f'{label}_Acc_{axis}_filtered'], color=colors[j], label=f'{label}_Acc_{axis} (Filtered)')
    axs[i, 0].set_title(f'{label} Accelerometer Data')
    axs[i, 0].set_ylabel('Acceleration (g)')
    axs[i, 0].legend()
    axs[i, 0].grid(True)
    
    # Roll, Pitch 시각화
    axs[i, 1].plot(data['Time'], data[f'{label}_Roll'], label=f'{label}_Roll', color='orange')
    axs[i, 1].plot(data['Time'], data[f'{label}_Pitch'], label=f'{label}_Pitch', color='purple')
    axs[i, 1].set_title(f'{label} Roll and Pitch')
    axs[i, 1].set_ylabel('Angle (degrees)')
    axs[i, 1].legend()
    axs[i, 1].grid(True)

    # 충격 감지 여부 시각화
    axs[i, 2].plot(data['Time'], data[f'{label}_Shock'], label=f'{label}_Shock', color='black', marker='o')
    axs[i, 2].set_title(f'{label} Shock Detection')
    axs[i, 2].set_ylabel('Shock Detected (0 or 1)')
    axs[i, 2].set_yticks([0, 1])
    axs[i, 2].grid(True)

# 공통 X축 라벨
for ax in axs[-1, :]:
    ax.set_xlabel('Time')

plt.tight_layout()
plt.show()
