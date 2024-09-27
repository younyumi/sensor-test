# import folium

# # 성균관대학교 자연과학캠퍼스(수원)의 GPS 좌표 (위도, 경도)
# latitude = 37.2934
# longitude = 126.9768

# map_skku = folium.Map(location=[latitude, longitude], zoom_start=18, tiles = 'Stamen Toner',attr='Map tiles by Stamen Design, under CC BY 3.0. Data by OpenStreetMap, under ODbL.')

# # 일반 마커 추가
# folium.Marker([latitude, longitude], popup="Suwon skku").add_to(map_skku)

# # 원형 마커 추가 (CircleMarker)
# folium.CircleMarker(
#     location=[37.2948, 126.97765],  # 원형 마커의 위치
#     radius=4,  # 원형 마커의 반경 (줌 레벨에 따라 변하지 않음)
#     color='red',  # 외곽선 색상
#     fill=False,  # 원 내부 채우기
#     popup="SKKU CircleMarker"  # 팝업 메시지
# ).add_to(map_skku)

# # 지도 HTML 파일로 저장
# map_skku.save("skku_map_with_circle.html")

# print("성균관대학교 위치에 원형 마커가 추가된 지도가 'skku_map_with_circle.html'로 저장되었습니다.")


import pandas as pd
import folium

# CSV 파일 불러오기
file_path = '7.15:15,15:21.csv'  # 센서 데이터 CSV 파일 경로
sensor_data = pd.read_csv(file_path)

# GPS 좌표 필터링 - 0이 아닌 값만 사용
sensor_data = sensor_data[(sensor_data['Latitude'] != 0) & (sensor_data['Longitude'] != 0)]

# 포트홀 감지 알고리즘
potholes = []

# for index, row in sensor_data.iterrows():
#     # 1. 4바퀴 모두에서 충격이 감지된 경우
#     if row['Shock FR'] >= 1 and row['Shock FL'] >= 1 and row['Shock RR'] >= 1 and row['Shock RL'] >= 1:
#         # Front Z_acc와 Rear Z_acc가 모두 10 이하인 경우 포트홀로 판단
#         if row['Front Z_acc'] <= 10 and row['Rear Z_acc'] <= 10:
#             potholes.append({
#                 'latitude': row['Latitude'],
#                 'longitude': row['Longitude'],
#                 'size': 'large'
#             })

#     # 2. 일부 바퀴에서만 충격이 감지된 경우
#     elif row['Shock FR'] >= 1 or row['Shock FL'] >= 1 or row['Shock RR'] >= 1 or row['Shock RL'] >= 1:
#         # 초음파 센서의 거리 변화를 확인
#         ultrasonic_changes = [
#             row['Ultrasonic 1 (cm)'],
#             row['Ultrasonic 2 (cm)'],
#             row['Ultrasonic 3 (cm)'],
#             row['Ultrasonic 4 (cm)']
#         ]
#         # 4개의 거리값이 모두 일정하게 변하지 않고 일부만 변화하는 경우
#         if not (ultrasonic_changes[0] == ultrasonic_changes[1] == ultrasonic_changes[2] == ultrasonic_changes[3]):
#             potholes.append({
#                 'latitude': row['Latitude'],
#                 'longitude': row['Longitude'],
#                 'size': 'small'
#             })

for index, row in sensor_data.iterrows():
    # 1. 4바퀴에서 전부 충격이 감지된 경우
    if row['Shock FR'] >= 1 and row['Shock FL'] >= 1 and row['Shock RR'] >= 1 and row['Shock RL'] >= 1:
        # Front Z_acc와 Rear Z_acc가 모두 10 이하인 경우 large 포트홀로 판단
        if row['Front Z_acc'] <= 10 and row['Rear Z_acc'] <= 10:
            pothole_data = {
                'latitude': row['Latitude'],
                'longitude': row['Longitude'],
                'size': 'large'
            }
            potholes.append(pothole_data)
            print(f"Large Pothole Detected - Latitude: {pothole_data['latitude']}, Longitude: {pothole_data['longitude']}")
    
    # 2. 1개 ~ 3개의 바퀴에서만 충격이 감지된 경우
    elif 1 <= sum([row['Shock FR'] >= 1, row['Shock FL'] >= 1, row['Shock RR'] >= 1, row['Shock RL'] >= 1]) <= 3:
        # 초음파 센서의 거리 변화를 확인
        ultrasonic_changes = [
            row['Ultrasonic 1 (cm)'],
            row['Ultrasonic 2 (cm)'],
            row['Ultrasonic 3 (cm)'],
            row['Ultrasonic 4 (cm)']
        ]
        
        # 거리 변화가 1cm 이하이면 동일한 값으로 간주
        def is_similar(val1, val2, threshold=2):
            return abs(val1 - val2) <= threshold
        
        # 4개의 값이 모두 비슷한지 확인 (1cm 이하 차이 무시)
        if not (is_similar(ultrasonic_changes[0], ultrasonic_changes[1]) and 
                is_similar(ultrasonic_changes[1], ultrasonic_changes[2]) and 
                is_similar(ultrasonic_changes[2], ultrasonic_changes[3])):
            pothole_data= {
                'latitude': row['Latitude'],
                'longitude': row['Longitude'],
                'size': 'small'
            }
            potholes.append(pothole_data)
            print(f"Small Pothole Detected - Latitude: {pothole_data['latitude']}, Longitude: {pothole_data['longitude']}")


latitude = 37.2934  # 기본 위치
longitude = 126.9768  # 기본 위치
map_potholes = folium.Map(location=[latitude, longitude], zoom_start=18)

# 포트홀 데이터로 마커 추가
for pothole in potholes:
    if pothole['size'] == 'large':
        # 큰 포트홀은 반경이 4인 마커
        folium.CircleMarker(
            location=[pothole['latitude'], pothole['longitude']],
            radius=4,
            color='red',
            fill=False,
            fill_opacity=0.7,
            popup='Large Pothole Detected'
        ).add_to(map_potholes)
    else:
        # 작은 포트홀은 반경이 3인 마커
        folium.CircleMarker(
            location=[pothole['latitude'], pothole['longitude']],
            radius=3,
            color='blue',
            fill=False,
            fill_opacity=0.7,
            popup='Small Pothole Detected'
        ).add_to(map_potholes)

# 지도 HTML 파일로 저장
map_potholes.save("pothole_map.html")

print(f"Total Potholes Detected: {len(potholes)}")
