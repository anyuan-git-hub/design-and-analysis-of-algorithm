import pandas as pd
import matplotlib.pyplot as plt


plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

def main():
    data = pd.read_csv("runtime_result.csv")

    plt.figure(figsize=(8, 5))

    plt.plot(
        data["n"],
        data["brute_ms"],
        marker="o",
        label="暴力算法"
    )

    plt.plot(
        data["n"],
        data["divide_ms"],
        marker="s",
        label="分治算法"
    )

    plt.yscale("log")

    plt.xlabel("点的数量 n")
    plt.ylabel("运行时间 / ms（对数刻度）")
    plt.title("对数刻度下的运行时间对比")
    plt.legend()
    plt.grid(True, which="both")
    plt.tight_layout()

    plt.savefig("runtime_comparison_log.png", dpi=300)
    plt.show()

if __name__ == "__main__":
    main()