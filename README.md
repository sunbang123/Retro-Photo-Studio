<img width="800" alt="image" src="https://github.com/user-attachments/assets/50bead46-e12f-4f74-9fd8-bf091c0df1e7" />


# **추억의 사진관 (흑백/세피아 필터 생성기)**

> 기술스택: MFC framework

- 확장구현: RGB 필터 / RGB 채널 분리

<img width="600" alt="image" src="https://github.com/user-attachments/assets/3868107a-3217-4aa0-9f99-b7ba08afb4e3" />

- R 채널로 분리 = 빨간색 성분이 많은 곳일수록 화면에서 더 하얗게(밝게)


### MFC (C++)

MFC는 하드웨어와 가장 가까운 C++ 기반이므로, 이미지를 이루는 '픽셀 데이터' 자체를 이해하는 데 최적격입니다.

- **프로젝트 아이디어: 추억의 사진관 (흑백/세피아 필터 생성기)**
- **구현 목표:**
    - 사진(`.bmp` 또는 `.jpg`)을 불러와 화면에 띄웁니다.
    - 버튼을 누르면 이미지의 픽셀 데이터(RGB 배열)에 직접 접근하여 연산합니다. (예: R, G, B 값을 평균 내어 흑백 / 세피아 이미지로 변환)
    - 변환된 이미지를 다시 화면에 그려줍니다.
- **비전(Vision) 학습 포인트:** 영상 처리의 가장 기본인 **이미지 버퍼(Image Buffer) 구조와 메모리 포인터**를 다루는 감각을 확실히 익힐 수 있습니다.

### 결과

<details>
    <summary>사진 열기</summary>
    <img width="786" height="584" alt="image" src="https://github.com/user-attachments/assets/8382b098-27f9-4507-92a0-c2d6a548cf03" />
    <img width="797" height="590" alt="image" src="https://github.com/user-attachments/assets/46174901-e0ec-45b4-8fb9-8d686a4f4817" />
</details>

<details>
    <summary>흑백 / 세피아 필터</summary>
    <img width="793" height="588" alt="image" src="https://github.com/user-attachments/assets/05979573-d08b-49e5-8039-9c8f4c66bbc4" />
    <img width="794" height="587" alt="image" src="https://github.com/user-attachments/assets/99931d04-c7ab-446e-9b4c-8296a999bc51" />
</details>

<details>
    <summary>RGB 필터</summary>
    <img width="795" height="590" alt="image" src="https://github.com/user-attachments/assets/d3d69893-0212-4a1e-8199-bb16b2eefce8" />
    <img width="796" height="589" alt="image" src="https://github.com/user-attachments/assets/0cb8d25f-db79-4c91-a46b-328bd1c1207d" />
    <img width="792" height="588" alt="image" src="https://github.com/user-attachments/assets/054bfd05-a2f4-46c4-8ca5-fe2b2c1b0fab" />
</details>

<details>
    <summary>RGB 채널 분리</summary>
    <img width="796" height="587" alt="image" src="https://github.com/user-attachments/assets/2b6ee58e-d812-4ced-b070-b8fffb94fc64" />
    <img width="794" height="587" alt="image" src="https://github.com/user-attachments/assets/c4755b7a-7c95-4e4b-9cdc-18cf3871d00e" />
    <img width="796" height="589" alt="image" src="https://github.com/user-attachments/assets/540dbb10-6165-417c-ae15-28bc1354f54f" />
</details>
