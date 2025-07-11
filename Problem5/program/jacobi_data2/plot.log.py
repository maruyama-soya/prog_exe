import numpy as np
import matplotlib.pyplot as plt

# --- 設定 ---
LOG_FILENAME = 'jacobi_norm_log.txt'
OUTPUT_FILENAME = 'norm_vs_iteration.png'

# --- データの読み込みとプロット ---
try:
    data = np.loadtxt(LOG_FILENAME)
    iterations = data[:, 0]
    norms = data[:, 1]
    
    plt.figure(figsize=(10, 6))
    plt.plot(iterations, norms, '-') # 線でプロット
    
    plt.title('Solution Norm vs. Iteration')
    plt.xlabel('Iteration')
    plt.ylabel('Solution Norm (Sn)')
    plt.grid(True, linestyle='--')
    
    # 必要に応じてx軸の範囲を調整 (例: 最初の10万回だけ見る)
    # plt.xlim(0, 100000)
    
    plt.savefig(OUTPUT_FILENAME)
    print(f"グラフを '{OUTPUT_FILENAME}' として保存しました。")

except FileNotFoundError:
    print(f"エラー: ログファイル '{LOG_FILENAME}' が見つかりません。")
    print("先にC++のプログラムを実行してください。")