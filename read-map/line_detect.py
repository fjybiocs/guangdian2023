import cv2
import numpy as np


# [0][2]为x坐标
# [1][3]为y坐标
def get_line(img):
    # 转换为灰度图像
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 二值化处理
    _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)

    # 运行LSD算法
    lsd = cv2.createLineSegmentDetector(0)
    lines = lsd.detect(binary)[0]

    return lines


def draw_lines(img, lines):
    # 在原图上绘制线段
    drawn_img = np.copy(img)

    for line in lines:
        x1, y1, x2, y2 = map(int, line[0])
        cv2.line(drawn_img, (x1, y1), (x2, y2), (0, 0, 255), 2)
        print(line)

        cv2.imshow('Detected Lines', drawn_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
