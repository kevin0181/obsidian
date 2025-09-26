array = [
       83,     100,      94,      40,       5,     458,     364,      26,      64,     635, 
       90,     489,      1,      504,      88,      97,     226,     218,     186,     268, 
       46,      82,      21,      58,      22,      54,      71,     215,      99,     227, 
       73,      24,      17,      44,     244,      78,      25,      66,      47,       3, 
       87,      33,     312,     242,      42,      61,     348,     946,      98,      92, 
]

def down_heap(arr, root, size):
  a = arr
  i = root
  while True:
    lc = (i << 1) + 1 
    if lc >= size:
      break 
    rc = lc + 1
    child = rc if rc < size and a[rc] > a[lc] else lc
    if a[i] >= a[child]:
      break
    a[i], a[child] = a[child], a[i]
    i = child

def sort_heap(arr):
  n = len(arr)
  print('=' * 60)
  print(f'HE <: {arr}')

  if n < 2:
    print(f'HE >: {arr}')
    return arr

  last_parent = (n // 2) - 1
  for i in range(last_parent, -1, -1):
    down_heap(arr, i, n)

  end = n - 1
  while end > 0:
    arr[0], arr[end] = arr[end], arr[0]
    down_heap(arr, 0, end)
    end -= 1

  print(f'HE >: {arr}')
  return arr
    
def main():
  sort_heap(array[:])

if __name__ == '__main__':
  main()

