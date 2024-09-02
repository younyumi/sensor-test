import serial
import csv
import time

ser = serial.Serial('/dev/ttyACM0', 115200)  # 포트 설정(꼭 확인해야 함)
time.sleep(2)

sensorLabels = ['FR', 'FL', 'RR', 'RL']

with open('sensor_data.csv', 'w', newline='') as csvfile:
    fieldnames = ['Time', 'Sensor1', 'Sensor2', 'Sensor3', 'Sensor4',
                  'FR_Acc_X', 'FR_Acc_Y', 'FR_Acc_Z', 'FR_Roll', 'FR_Pitch',
                  'FL_Acc_X', 'FL_Acc_Y', 'FL_Acc_Z', 'FL_Roll', 'FL_Pitch',
                  'RR_Acc_X', 'RR_Acc_Y', 'RR_Acc_Z', 'RR_Roll', 'RR_Pitch',
                  'RL_Acc_X', 'RL_Acc_Y', 'RL_Acc_Z', 'RL_Roll', 'RL_Pitch',
                  'FR_Shock', 'FL_Shock', 'RR_Shock', 'RL_Shock']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    writer.writeheader()

    while True:
        line = ser.readline().decode('utf-8').strip()  

        if line.startswith("Sensor1"):
            data = {}
            
            timestamp = time.strftime('%H:%M:%S', time.localtime())
            data['Time'] = timestamp
            # 거리 센서 데이터
            sensor_data = line.split(', ')
            for i in range(4):
                data[f'Sensor{i+1}'] = sensor_data[i].split(': ')[1]
            
            # 가속도 센서 데이터& 충격 감지 상태
            for i in range(4):
                acc_line = ser.readline().decode('utf-8').strip().split('- ')[1]
                acc_data = acc_line.split(', ')
                data[f'{sensorLabels[i]}_Acc_X'] = acc_data[0].split(':')[1]
                data[f'{sensorLabels[i]}_Acc_Y'] = acc_data[1].split(':')[1]
                data[f'{sensorLabels[i]}_Acc_Z'] = acc_data[2].split(':')[1]
                data[f'{sensorLabels[i]}_Roll'] = acc_data[3].split(':')[1]
                data[f'{sensorLabels[i]}_Pitch'] = acc_data[4].split(':')[1]
            
            # 충격 감지 상태
            for i in range(4):
                shock_line = ser.readline().decode('utf-8').strip().split('- ')[1]
                shock_status = shock_line.split(': ')[1]
                data[f'{sensorLabels[i]}_Shock'] = shock_status
            
            writer.writerow(data)

            print(data)
            
        time.sleep(0.5)  # 다음 데이터 읽기 전 대기

ser.close()