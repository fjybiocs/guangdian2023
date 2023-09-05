import cv2
import numpy as np

# 定义回调函数
def on_trackbar(val):
    # 获取滑动条的当前值
    l_min = cv2.getTrackbarPos('L_min', 'Threshold')
    a_min = cv2.getTrackbarPos('A_min', 'Threshold')
    b_min = cv2.getTrackbarPos('B_min', 'Threshold')
    l_max = cv2.getTrackbarPos('L_max', 'Threshold')
    a_max = cv2.getTrackbarPos('A_max', 'Threshold')
    b_max = cv2.getTrackbarPos('B_max', 'Threshold')

    # 根据阈值范围生成二值图像
    mask = np.zeros_like(l_channel)
    mask[(l_channel >= l_min) & (l_channel <= l_max) &
         (a_channel >= a_min) & (a_channel <= a_max) &
         (b_channel >= b_min) & (b_channel <= b_max)] = 255

    # 在窗口中显示原始图像和阈值化结果
    cv2.imshow('Original', img)
    cv2.imshow('Threshold', mask)

# 读取图片
img = cv2.imread('image.png')

# 转换至Lab颜色空间
lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)

# 分离通道
l_channel, a_channel, b_channel = cv2.split(lab)

# 创建窗口
cv2.namedWindow('Threshold')

# 创建滑动条
cv2.createTrackbar('L_min', 'Threshold', 0, 255, on_trackbar)
cv2.createTrackbar('A_min', 'Threshold', 0, 255, on_trackbar)
cv2.createTrackbar('B_min', 'Threshold', 0, 255, on_trackbar)
cv2.createTrackbar('L_max', 'Threshold', 255, 255, on_trackbar)
cv2.createTrackbar('A_max', 'Threshold', 255, 255, on_trackbar)
cv2.createTrackbar('B_max', 'Threshold', 255, 255, on_trackbar)

# 初始化滑动条位置
cv2.setTrackbarPos('L_min', 'Threshold', 0)
cv2.setTrackbarPos('A_min', 'Threshold', 0)
cv2.setTrackbarPos('B_min', 'Threshold', 0)
cv2.setTrackbarPos('L_max', 'Threshold', 255)
cv2.setTrackbarPos('A_max', 'Threshold', 255)
cv2.setTrackbarPos('B_max', 'Threshold', 255)

# 显示原始图像和阈值化结果
cv2.imshow('Original', img)
cv2.imshow('Threshold', np.zeros_like(l_channel))

# 等待按下ESC键退出程序
while True:
    if cv2.waitKey(0) & 0xFF == 27:
        break
