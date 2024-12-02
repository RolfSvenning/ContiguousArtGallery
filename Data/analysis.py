import re

I = [list(map(int, re.findall(r'\d+', l)[:2])) for l in open("Data/Global/results.txt").readlines() if l[0] == "F"]
print("Number of runs: ", len(I))
for guard in range(3, 7):
    print("Guards: ", guard)
    for steps in range(2 * guard + 1, 4 * guard):
        print(steps, ": ", sum(1 for g, s in I if g == guard and s == steps))