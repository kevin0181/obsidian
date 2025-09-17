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
      last = 0 # 마지막 swap이 발생한 위치를 기록하기 위해.
      for i in range(end):
          if arr[i] > arr[i + 1]:
              arr[i], arr[i + 1] = arr[i + 1], arr[i]
              last = i
      end = last # 발생한 마지막 swap 위치로 end를 업데이트 (최적화

def sort_select(arr):
  print('=' * 60)
  print(f'SE <: {arr}')
  n = len(arr)
  for i in range(n):
    min_idx = i
    for j in range(i + 1, n):
      if arr[j] < arr[min_idx]:
        min_idx = j
    if min_idx != i:
      arr[i], arr[min_idx] = arr[min_idx], arr[i]
  print(f'SE >: {arr}')

def sort_insert(arr):
  print('=' * 60)
  print(f'IN <: {arr}')
  print(f'IN >: {arr}')

def sort_shell(arr):
  print('=' * 60)
  print(f'SH <: {arr}')
  print(f'SH >: {arr}')

def main():
  sort_bubble(array[:])
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

