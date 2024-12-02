import re

I = [list(map(int, re.findall(r'\d+', l)[:2])) for l in open("Data/Global/results.txt").readlines() if l[0] == "F"]
print(I[:3])
for guard in range(3, 7):
    print("Guard: ", guard)
    for steps in range(2 * guard + 1, 4 * guard):
        print(steps, ": ", sum(s for g, s in I if g == guard and s == steps))