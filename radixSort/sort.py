import ctypes
# ctypes should be valid as a "basic python module"
# ...but i could rewrite it to lauch the c code as a subprocess (if you give me extra time to learn how)
lib = ctypes.CDLL("./rsort.so")
lib.find_min.argtypes = [
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int
]
lib.find_min.restype = ctypes.c_int
lib.find_max.argtypes = [
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int
]
lib.find_max.restype = ctypes.c_int
lib.radix_bin_sort.argtypes = [
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int
]
lib.radix_bin_sort.restype = None

def find_minimum(numbers, n) -> int:    # removed type annotations because ctypes wouldn't shut up about unexpected type even though it works ??
    minimum = lib.find_min(numbers,n)
    return minimum


def find_maximum(numbers, n) -> int:
    maximum = lib.find_max(numbers,n)
    return maximum

def sort_numbers(numbers, n) -> list[int]:
    lib.radix_bin_sort(numbers,n)
    return list(numbers)[:n]


if __name__ == "__main__":
    num = [1, 2, 12, 4, 32, 6, 75, 68, 9, 110]
    N = len(num)
    ArrayType = ctypes.c_int * N
    c_num = ArrayType(*num)
    print(sort_numbers(c_num, N))
