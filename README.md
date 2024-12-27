# AVR_basic
- 마이크로프로세서 기초 실습 (*ATmega1281*)

## 개발 환경

- Atmel Studio 7.0
- ATmega1281 Microcontroller
- Terminal Program 
- Programming Language: C

## 참조

[마이크로프로세서 실험 보고서](https://studyhoons.tistory.com/category/%EC%A0%84%EC%9E%90%EA%B3%B5%ED%95%99/%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9C%ED%94%84%EB%A1%9C%EC%84%B8%EC%84%9C)

## 목차

### ControlLED1 
* 스위치(SW2)를 누를 때 LED on/off
* 스위치를 누를 때마다 toggle

### ControlLED2
* 스위치를 누를 때마다 LED 변화
* 스위치를 누를 때와 눌렀다 뗐을 때 비교
* 스위치를 눌렀다 떼도 변화 X
 - 스위치를 좀 더 긴 시간 동안 누르고 있으면 해결
 - 소프트웨어적 Debouncing 

### 7SegmentLED
* 스위치를 누를 때를 기준으로 mode 설정
* 스위치 여러 개의 기능 설정
* 전력효율을 높이기 위해 fnd_write_number_ultra 함수 생성

### External Interrupt
* Test 6: LOW 레벨 트리거로 인한 연속 인터럽트 발생으로 FND가 888처럼 보이는 현상 구현
* Test 7: INT7 ISR을 값 표시만 하도록 수정하여 SW3의 증가 동작이 실제로 반영되는 것을 확인
* Test 8: INT3/INT7 ISR 교체 및 LOW 레벨 트리거 변경으로 인터럽트 우선순위 동작 테스트
* Test 9: SW2 누를 때 FND 증가, 뗄 때 LED 8번 패턴으로 즉시 변경하는 기능 구현

### Pin Change Interrupt
* 기계식 스위치의 바운싱 현상을 이해하고 PCINT 인터럽트를 통한 스위치 입력 처리 구현
* SW3, SW4 스위치를 PCINT5, PCINT6으로 설정하여 FND 값 증감 제어 구현 (PB5, PB6 핀 사용)
* SW4의 바운싱 현상으로 인한 값 감소 문제 확인 및 스위치 떼는 순간의 동작 차이 분석

### Timer Basic: Normal vs CTC
* 7. 듀얼 타이머 동작: 파형 생성을 위한 Timer3과 Timer5 동시 처리 구현
* 8. 하드웨어 Compare Match 기능을 활용한 효율적인 파형 출력
* 9. 자동 핀 제어를 위한 Timer5 오버플로우 인터럽트 구현
* 10. 정밀 주파수 생성을 위한 Timer5의 Normal 모드에서 CTC 모드로 변환
* 11. Timer3 Compare Match를 활용한 90도 위상차 듀얼 파형 생성

### Timer Basic2: FND Counter & Music Player
* 타이머 기반 FND 카운터와 음악 재생
 - FND 0.1초 자동 카운트와 음악 재생 기능 구현
 - SW2를 통한 음악 재생/정지 및 재생 위치 기억 기능
 - SW3를 이용한 음악 처음부터 재시작 기능

### Timer Basic3: PWM
* Timer2: LED 제어를 위한 8비트 고속 PWM
* Timer3: 정밀 제어를 위한 16비트 위상 교정 PWM (모터 제어)
* Timer5: 주기적 인터럽트를 위한 CTC 모드

### Asynchronous Communication
* 비동기 직렬 통신에서 엔터키(CR: 13, LF: 10) 처리를 통한 줄바꿈과 명령어 입력 기능 
* UART 송수신을 위한 인터럽트 기반 통신 구조와 버퍼 제어 방식 
* printf(), scanf()와 fdevopen() 함수를 이용한 UART 입출력 스트림 설정 및 데이터 포맷팅 기능 

### ADC (Analog to Digital Conversion)
* ADC의 다양한 변환 모드 설정 및 구현
 - Single Conversion mode
 - Free Running mode
* UART 통신을 통한 ADC 제어 구현


### 20191055
- LED pattern control
- FND display
- Speaker control
- UART communication
- Timer-based operations
- Switch interrupt handling
