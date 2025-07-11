import numpy as np
import matplotlib.pyplot as plt

# --- ★★★ 追加：ここから (グラフのスタイル設定) ★★★ ---
try:
    plt.rcParams.update({
        'font.family': 'Times New Roman', # フォントをTimes New Romanに設定
        'font.style': 'italic',         # フォントスタイルをイタリックに設定
        'font.size': 14                 # 文字の基本サイズも少し大きくしておく
    })
except Exception as e:
    print(f"フォント設定でエラーが発生しました: {e}")
    print("デフォルトフォントで続行します。")
# --- ★★★ 追加：ここまで ★★★ ---


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
    
    # 個別にフォントを変えたい場合は、以下のように引数を追加できる
    # plt.title('Solution Norm vs. Iteration', style='normal', weight='bold')
    plt.title('Solution Norm vs. Iteration')
    plt.xlabel('Iteration')
    plt.ylabel('Solution Norm (Sn)')
    plt.grid(True, linestyle='--')
    
    # plt.xlim(0, 100000)
    
    # ★★★ 変更点：解像度をdpi=300に指定 ★★★
    plt.savefig(OUTPUT_FILENAME, dpi=300, bbox_inches='tight')
    
    print(f"高解像度のグラフを '{OUTPUT_FILENAME}' として保存しました。")

except FileNotFoundError:
    print(f"エラー: ログファイル '{LOG_FILENAME}' が見つかりません。")
    print("先にC++のプログラムを実行してください。")