import pandas as pd
import matplotlib as plt
import numpy as np

data = pd.read_csv('sensor_data.csv')

data['Time'] = pd.to_datetime(data['Timestamp'])

def kalman_filter(data, Q, R):
    n= len(data)
    x_est =np.zeros(n)
    P = np.zeros(n)
    
    x_est[0] = data[0]
    P[0] = 1.0
    
    for k in range(1, n):
        # prediction
        x_pred = x_est[k-1]
        P_pred = P[k-1] + Q
        
        # update
        K = P_pred / (P_pred + R)
        x_est[k] = x_pred + K * (data[k] - x_pred)
        P[k] = (1 - K) * P_pred
        
    return x_est

Q = 0.01  # 프로세스 노이즈
R = 1.0   # 측정 노이즈
data['Filtered_Accel_Z'] = kalman_filter(data['Accel_Z'].values, Q, R)
    
    