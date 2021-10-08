import numpy as np


def las_vegas_retry(las_vegas_algo):
    def algo(*args, **kwargs):
        if "seed" in kwargs:
            raise ValueError("Kwargs must not contain seed")
        
        seed = 0
        result = None
        while result == None:
            result = las_vegas_algo(*args, **kwargs, seed=seed)
            seed += 1
        return result

    return algo


@las_vegas_retry
def rand_median(a, seed=None):
    rng = np.random.RandomState(seed)
    n = len(a)
    size_b = round(n**(3/4)) + 1
    b = [0,]*size_b

    for i in range(size_b):
        b[i] = a[rng.randint(0, n)]

    sorted_b = sorted(b)
    left_pivot_idx = round(0.5*n**(3/4) - n**0.5) - 1
    right_pivot_idx = round(0.5*n**(3/4) + n**0.5)
    left_pivot = sorted_b[left_pivot_idx]
    right_pivot = sorted_b[right_pivot_idx]

    T = [0,]*n
    s = 0
    t = 0
    for item in a:
        if item < left_pivot:
            s += 1
        elif item <= right_pivot:
            T[t] = item
            t += 1

    n_half_rounded_up = n // 2 if n % 2 == 0 else n // 2 +1
    if s < n_half_rounded_up and s + t >= n_half_rounded_up and t < 4*n**(3/4):
        sorted_T = sorted(T[:t])
        if n % 2 == 0:
            return 0.5*(sorted_T[n // 2 - s] + sorted_T[n // 2 - s - 1])
        else:
            return sorted_T[n // 2 - s]

    return None


if __name__ == "__main__":
    for i in range(20000, 20100):
        random_list = list(np.random.rand(i))
        a = np.median(random_list)
        b = rand_median(random_list)
        assert a==b
