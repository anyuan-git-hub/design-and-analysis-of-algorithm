import random
import matplotlib.pyplot as plt


plt.rcParams["font.sans-serif"] = ["SimHei"]      
plt.rcParams["axes.unicode_minus"] = False        

def generate_points(n, seed=20260427):
    random.seed(seed)
    points = []

    for _ in range(n):
        x = random.randint(0, 1000)
        y = random.randint(0, 1000)
        points.append((x, y))

    return points

def main():
    points = generate_points(200)

    xs = [p[0] for p in points]
    ys = [p[1] for p in points]

    plt.figure(figsize=(6, 6))
    plt.scatter(xs, ys, s=15)

    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("随机生成的二维点集分布")
    plt.grid(True)
    plt.tight_layout()

    plt.savefig("point_distribution.png", dpi=300)
    plt.show()

if __name__ == "__main__":
    main()