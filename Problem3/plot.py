import matplotlib.pyplot as plt

# データ読み込み
x = []
y = []

with open("data.txt", "r") as file:
    for line in file:
        if line.strip():  # 空行をスキップ
            xi, yi = map(float, line.strip().split())
            x.append(xi)
            y.append(yi)

# グラフ描画
plt.figure(figsize=(8, 5))
plt.plot(x, y, marker='o', linestyle='-', color='blue', label='Euler method')
plt.title("Euler's Method: Solution of dy/dx = -y")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()