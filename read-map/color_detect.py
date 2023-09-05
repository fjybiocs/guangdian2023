import cv2
import numpy as np


def get_rect_by_threshold(img, b_min, b_max):
    # 转换至Lab颜色空间
    lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)

    # 分离通道
    l_channel, a_channel, b_channel = cv2.split(lab)

    # red:  b: [180, 255]
    # blue: b: [0, 110]

    # 定义阈值范围
    l_min, l_max = 0, 255
    a_min, a_max = 0, 255
    b_min, b_max = b_min, b_max

    # 创建掩码
    mask = np.zeros_like(l_channel)
    mask[(l_channel >= l_min) & (l_channel <= l_max) &
         (a_channel >= a_min) & (a_channel <= a_max) &
         (b_channel >= b_min) & (b_channel <= b_max)] = 255

    # 获取轮廓
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 获取边界
    rect = cv2.boundingRect(contours[0])

    return rect


def get_map_edge(img):
    blue = get_rect_by_threshold(img, 0, 100)
    blue = (blue[0] + blue[2], blue[1] + blue[3])

    red = get_rect_by_threshold(img, 180, 255)
    red = (red[0], red[1])

    return blue, red
