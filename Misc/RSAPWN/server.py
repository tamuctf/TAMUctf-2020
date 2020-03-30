import time
import random

primes = [9998279, 9998281, 9998309, 9998321, 9998323, 9998333, 9998377, 9998381, 9998393, 9998413, 9998423, 9998441, 9998447, 9998459, 9998479, 9998539, 9998543, 9998557, 9998561, 9998581, 9998587, 9998603, 9998623, 9998633, 9998641, 9998689, 9998699, 9998701, 9998719, 9998741, 9998743, 9998749, 9998753, 9998777, 9998797, 9998801, 9998809, 9998851, 9998861, 9998867, 9998887, 9998893, 9998903, 9998929, 9998969, 9998971, 9998977, 9999047, 9999049, 9999053, 9999071, 9999083, 9999161, 9999163, 9999167, 9999193, 9999217, 9999221, 9999233, 9999271, 9999277, 9999289, 9999299, 9999317, 9999337, 9999347, 9999397, 9999401, 9999419, 9999433, 9999463, 9999469, 9999481, 9999511, 9999533, 9999593, 9999601, 9999637, 9999653, 9999659, 9999667, 9999677, 9999713, 9999739, 9999749, 9999761, 9999823, 9999863, 9999877, 9999883, 9999889, 9999901, 9999907, 9999929, 9999931, 9999937, 9999943, 9999971, 9999973, 9999991]

def go():
    print('We must train future hackers to break RSA quickly. Here is how this will work.\nI will multiply together two big primes (<= 10000000), give you the result,\nand you must reply to me in less than two seconds telling me what primes I\nmultiplied.', flush=True)
    print()
    print('Press enter when you are ready.', flush=True)
    input()

    i = random.randint(0, len(primes)-1)
    j = random.randint(0, len(primes)-1)
    print(primes[i]*primes[j], flush=True)
    t = time.time()
    a, b = map(int, input().split())
    t1 = time.time()
    if t1-t > 2:
        print('Too slow :(', flush=True)
        return

    if a*b != primes[i]*primes[j]:
        print('Wrong answer :(', flush=True)
        return

    with open('flag.txt', 'r') as flagfile:
        print('Good job :)', flush=True)
        print(flagfile.read(), flush=True)


if __name__ == '__main__':
    go()
