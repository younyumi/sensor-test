import pandas as pd
import matplotlib.pyplot as plt

# CSV 파일 불러오기
file_path = 'sensor_data.csv'
sensor_data = pd.read_csv(file_path)

# 필요한 컬럼들이 숫자형으로 변환되도록 설정
sensor_data['MPU6050 1 Z_acc'] = pd.to_numeric(sensor_data['MPU6050 1 Z_acc'], errors='coerce')
sensor_data['MPU6050 2 Z_acc'] = pd.to_numeric(sensor_data['MPU6050 2 Z_acc'], errors='coerce')

# Z축 가속도 변화 계산
sensor_data['MPU6050 1 Z_acc_change'] = sensor_data['MPU6050 1 Z_acc'].diff().abs()
sensor_data['MPU6050 2 Z_acc_change'] = sensor_data['MPU6050 2 Z_acc'].diff().abs()

# 초음파 센서의 도로 변화 감지 계산
sensor_data['Ultrasonic 1 change'] = sensor_data['Ultrasonic 1 (cm)'].diff().abs()
sensor_data['Ultrasonic 2 change'] = sensor_data['Ultrasonic 2 (cm)'].diff().abs()
sensor_data['Ultrasonic 3 change'] = sensor_data['Ultrasonic 3 (cm)'].diff().abs()
sensor_data['Ultrasonic 4 change'] = sensor_data['Ultrasonic 4 (cm)'].diff().abs()

# 포트홀 감지 임계값 설정
z_acc_threshold = 10.0  # MPU6050 Z축 가속도 변화 임계값
ultrasonic_threshold = 10  # 초음파 센서 거리 변화 임계값 (단위: cm)
shock_trigger_value = 1  # 충격 감지 센서 활성화 값

# 포트홀 감지 조건 정의
pothole_data = sensor_data[
    (sensor_data['Shock FR'] >= shock_trigger_value) |
    (sensor_data['Shock FL'] >= shock_trigger_value) |
    (sensor_data['Shock RR'] >= shock_trigger_value) |
    (sensor_data['Shock RL'] >= shock_trigger_value) |
    (sensor_data['MPU6050 1 Z_acc_change'] > z_acc_threshold) |
    (sensor_data['MPU6050 2 Z_acc_change'] > z_acc_threshold) |
    (sensor_data['Ultrasonic 1 change'] > ultrasonic_threshold) |
    (sensor_data['Ultrasonic 2 change'] > ultrasonic_threshold) |
    (sensor_data['Ultrasonic 3 change'] > ultrasonic_threshold) |
    (sensor_data['Ultrasonic 4 change'] > ultrasonic_threshold)
]

# GPS 값이 0이 아닌 행만 필터링
pothole_data = pothole_data[(pothole_data['Latitude'] != 0) & (pothole_data['Longitude'] != 0)]

# 포트홀 감지 위치 시각화
plt.figure(figsize=(8, 6))

# 포트홀 감지 위치 표시
plt.scatter(pothole_data['Longitude'], pothole_data['Latitude'], c='red', label='Pothole Detected', s=100)

# 그래프 제목과 축 레이블 설정
plt.title('Pothole Detection Locations Based on Sensor Data')
plt.xlabel('Longitude')
plt.ylabel('Latitude')

plt.xlim([127.048860, 127.048880])
plt.ylim([38.451650, 38.451660])

# 범례 추가
plt.legend()

# 그래프 보여주기
plt.grid(True)
plt.show()