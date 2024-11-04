### 간단한 설명

1. 사용자가 마우스를 누르면 PointerPressed가 호출되고, 현재 포인트가 currentLine에 추가됩니다.
2. 마우스를 이동하면 PointerMoved가 호출되어 계속 포인트가 추가됩니다.
3. 마우스 버튼을 놓으면 PointerReleased가 호출되어 현재 선을 저장합니다.
4. 사용자가 색상을 변경하면 myCol_ColorChanged가 호출되어 색상이 업데이트됩니다.
5. 그려진 선은 CanvasControl_Draw를 통해 화면에 표시됩니다.
