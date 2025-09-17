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
  for i in range(n):
    for j in range(0, n - i - 1):
      if arr[j] > arr[j + 1]:
        arr[j], arr[j + 1] = arr[j + 1], arr[j]
  print(f'BU >: {arr}')

def sort_select(arr):
  print('=' * 60)
  print(f'SE <: {arr}')
  n = len(arr)
  for i in range(n):
    min_idx = i
    for j in range(i + 1, n):
      if arr[j] < arr[min_idx]:
        min_idx = j
    arr[i], arr[min_idx] = arr[min_idx], arr[i]
  print(f'SE >: {arr}')

def sort_insert(arr):
  print('=' * 60)
  print(f'IN <: {arr}')
  n = len(arr)
  for i in range(1, n):
    key = arr[i]
    j = i - 1
    while j >= 0 and arr[j] > key:
      arr[j + 1] = arr[j]
      j -= 1
    arr[j + 1] = key
  print(f'IN >: {arr}')

def sort_shell(arr):
  print('=' * 60)
  print(f'SH <: {arr}')
  GAPS = [19, 7, 3, 1]
  n = len(arr)
  for gap in GAPS:
    for i in range(gap, n):
      temp = arr[i]
      j = i
      while j >= gap and arr[j - gap] > temp:
        arr[j] = arr[j - gap]
        j -= gap
      arr[j] = temp
  print(f'SH >: {arr}')

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

