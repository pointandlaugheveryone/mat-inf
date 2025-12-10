def max_mul(sequence: list):
    seq = 0
    seqsum = 0
    start = 0
    maxseq = 0
    maxsum = 0
    maxstart = 0

    for i in range(len(sequence)):
        if sequence[i] % 3 == 0:
            if seq == 0:
                start = i
            seq += 1
            seqsum += sequence[i]
            if seq >= maxseq and seqsum > maxsum:
                maxseq = seq
                maxstart = start
                maxsum = seqsum
        else:
            seq = 0
            seqsum = 0

    return maxstart, maxseq, maxsum


nums = list(map(int, input().split()))
print(max_mul(nums))
