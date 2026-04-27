import random
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]      
plt.rcParams["axes.unicode_minus"] = False  

def main():
    random.seed(20260427)

    n = 80
    points = [(random.randint(0, 1000), random.randint(0, 1000)) for _ in range(n)]

    xs = [p[0] for p in points]
    ys = [p[1] for p in points]

    mid_x = sorted(xs)[n // 2]
    d = 120

    plt.figure(figsize=(7, 6))

    left_points = [p for p in points if p[0] <= mid_x]
    right_points = [p for p in points if p[0] > mid_x]

    plt.scatter(
        [p[0] for p in left_points],
        [p[1] for p in left_points],
        s=20,
        label="左半部分"
    )

    plt.scatter(
        [p[0] for p in right_points],
        [p[1] for p in right_points],
        s=20,
        label="右半部分"
    )

    plt.axvline(mid_x, linestyle="--", label="分界线")

    plt.axvspan(mid_x - d, mid_x + d, alpha=0.2, label="条带区域")

    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("分治算法中的分界线与条带区域示意图")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    plt.savefig("strip_region.png", dpi=300)
    plt.show()

if __name__ == "__main__":
    main()