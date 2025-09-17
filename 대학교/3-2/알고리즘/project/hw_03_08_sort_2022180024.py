array = [
       83,     100,      94,      40,       5,     458,     364,      26,      64,     635, 
       90,     489,      1,      504,      88,      97,     226,     218,     186,     268, 
       46,      82,      21,      58,      22,      54,      71,     215,      99,     227, 
       73,      24,      17,      44,     244,      78,      25,      66,      47,       3, 
       87,      33,     312,     242,      42,      61,     348,     946,      98,      92, 
]

def sort_bubble(arr):
  print('=' * 60)
  print(f'BU <: {arr}')
  n = len(arr)
  end = n - 1
  while end > 0:
      last = 0              # 마지막 swap이 발생한 위치를 기록하기 위해.
      for i in range(end):
          if arr[i] > arr[i + 1]:
              arr[i], arr[i + 1] = arr[i + 1], arr[i]
              last = i
      end = last            # 발생한 마지막 swap 위치로 end를 업데이트 (최적화

def sort_select(arr):
  print('=' * 60)                  
  print(f'SE <: {arr}')            
  n = len(arr)                     
  for i in range(n):               
    min_idx = i                    # 항상 첫번째 인덱스 값을 최소값으로 줌.
    for j in range(i + 1, n):
      if arr[j] < arr[min_idx]:    
        min_idx = j                # 만약에 최소값을 찾았다? min_idx에 최소값 인덱스를 업데이트
    if min_idx != i:               
      arr[i], arr[min_idx] = arr[min_idx], arr[i]  # 스왑 수행
  print(f'SE >: {arr}')            

def sort_insert(arr):
  print('=' * 60)                 
  print(f'IN <: {arr}')           
  n = len(arr)                    
  for i in range(1, n):           
    key = arr[i]                  # ex> 0번째 값 넣음 (두번째 값이면?)
    j = i - 1                     # ex> 0번째 값 기준 0번째 값보다 앞에 값 0 이면 -1임 (1번째 값이면 0번째넣고 비교)
    while j >= 0 and arr[j] > key:  # 만약에 현재 비교하는 key보다 값이 작다면? j>=0은 반드시 넣어줘야함 0번째보다 앞은 없으니깐..
      arr[j + 1] = arr[j]         # j값 (이전 키값)을 오른칸으로 이동시킴
      j -= 1                      # 왼쪽으로 인덱스 이동
    arr[j + 1] = key              # key 값 줌
  print(f'IN >: {arr}')           

def sort_shell(arr):
  print('=' * 60)                  # 구분선 출력
  print(f'SH <: {arr}')            # 정렬 전 배열 출력
  GAPS = [19, 7, 3, 1]             # 주어진 gap 시퀀스 (수업 요구사항)
  n = len(arr)                     # 배열 길이
  for gap in GAPS:                 # gap 을 순서대로 적용
    if gap >= n:                   # 배열 길이보다 크면 의미 없으므로 건너뜀 (불필요 비교 제거)
      continue
    # gap 간격의 삽입 정렬 수행
    for i in range(gap, n):        # gap 떨어진 위치부터 끝까지
      temp = arr[i]                # 현재 삽입할 값 저장
      j = i - gap                  # 이전 gap 위치 인덱스
      while j >= 0 and arr[j] > temp:  # gap 간격 비교하며 큰 값들은 뒤로 밀기
        arr[j + gap] = arr[j]      # 값을 gap 만큼 뒤로 이동
        j -= gap                   # 더 이전 gap 위치로 이동
      arr[j + gap] = temp          # 올바른 위치에 삽입
  print(f'SH >: {arr}')            # 정렬 후 배열 출력

def main():
  sort_bubble(array[:]) # 딥카피 방법을 몰라서 gpt에게 물어봐서 알게 되었습니다.
  sort_insert(array[:])
  sort_select(array[:])
  sort_shell(array[:])

if __name__ == '__main__':
  main()

# 전역변수 array는 건들이지 않고,
# 딥카피를한다. (복사본을 하나 만든다.)
# arr이라는 인자로 받는다.
# 정렬은 오름차순으로 되게 하라.
# shell sort 에서 gap 은 다음을 사용한다
# GAPS = [19, 7, 3, 1]
# for g in GAPS: 로 루프를 돌며, 수업에서 소개한 next_gap() 은 사용하지 않는다.

