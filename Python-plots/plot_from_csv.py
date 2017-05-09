import os
import glob
from multiprocessing import Pool, TimeoutError


def figure(file):
    os.system('E:\Anaconda3\python.exe wykresy.py %s' % file)


if __name__ == '__main__':
    # start 4 worker processes
    with Pool(processes=10) as pool:

        for file in glob.glob("..\*.CSV"):
            pool.apply_async(figure, (file,))

        pool.close()
        pool.join()
