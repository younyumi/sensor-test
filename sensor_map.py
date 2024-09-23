import folium

# 성균관대학교 자연과학캠퍼스(수원)의 GPS 좌표 (위도, 경도)
latitude = 37.2934
longitude = 126.9768

map_skku = folium.Map(location=[latitude, longitude], zoom_start=18, tiles = 'Stamen Toner',attr='Map tiles by Stamen Design, under CC BY 3.0. Data by OpenStreetMap, under ODbL.')

# 일반 마커 추가
folium.Marker([latitude, longitude], popup="Suwon skku").add_to(map_skku)

# 원형 마커 추가 (CircleMarker)
folium.CircleMarker(
    location=[37.2948, 126.97765],  # 원형 마커의 위치
    radius=4,  # 원형 마커의 반경 (줌 레벨에 따라 변하지 않음)
    color='red',  # 외곽선 색상
    fill=False,  # 원 내부 채우기
    popup="SKKU CircleMarker"  # 팝업 메시지
).add_to(map_skku)

# 지도 HTML 파일로 저장
map_skku.save("skku_map_with_circle.html")

print("성균관대학교 위치에 원형 마커가 추가된 지도가 'skku_map_with_circle.html'로 저장되었습니다.")
